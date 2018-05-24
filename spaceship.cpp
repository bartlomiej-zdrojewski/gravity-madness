#include <iostream>
#include "spaceship.hpp"

Spaceship::~Spaceship ( ) {

    if ( Controller ) {

        Controller->setSpaceship( nullptr ); } }

SpaceshipController * Spaceship::getController ( ) {

    return Controller; }

void Spaceship::setController ( SpaceshipController * Controller ) {

    this->Controller = Controller;

    if ( Controller ) {

        Controller->setSpaceship( this ); } }

float Spaceship::getInfluenceRadius ( ) {

    // TODO
    return getRadius();

    }

float Spaceship::getHealth ( ) {

    return Health; }

void Spaceship::setHealth ( float Health ) {

    this->Health = Health; }

float Spaceship::getHealthRestoration ( ) {

    return HealthRestoration; }

void Spaceship::setHealthRestoration ( float HealthRestoration ) {

    this->HealthRestoration = HealthRestoration; }

float Spaceship::getHealthLimit ( ) {

    return HealthLimit; }

void Spaceship::setHealthLimit ( float HealthLimit ) {

    this->HealthLimit = HealthLimit; }

void Spaceship::updateHealth ( float DeltaHealth ) {

    if ( isDestructed() ) {

        return; }

    Health += DeltaHealth;

    if ( Health <= 0.f ) {

        Health = 0.f;
        Energy = 0.f;

        destruct(); }

    else if ( Health > HealthLimit ) {

        Health = HealthLimit; } }

float Spaceship::getEnergy ( ) {

    return Energy; }

void Spaceship::setEnergy ( float Energy ) {

    this->Energy = Energy; }

float Spaceship::getEnergyRestoration ( ) {

    return EnergyRestoration; }

void Spaceship::setEnergyRestoration ( float EnergyRestoration ) {

    this->EnergyRestoration = EnergyRestoration; }

float Spaceship::getEnergyLimit ( ) {

    return EnergyLimit; }

void Spaceship::setEnergyLimit ( float EnergyLimit ) {

    this->EnergyLimit = EnergyLimit; }

void Spaceship::updateEnergy ( float DeltaEnergy ) {

    if ( isDestructed() ) {

        return; }

    Energy += DeltaEnergy;

    if ( Energy < 0.f ) {

        Energy = 0.f; }

    else if ( Energy > EnergyLimit ) {

        Energy = EnergyLimit; } }

void Spaceship::updateEnergy ( sf::Vector2f Acceleration, sf::Time ElapsedTime ) {

    const float DeltaEnergy = 1.25f * ElapsedTime.asSeconds() * sqrtf( Acceleration.x * Acceleration.x + Acceleration.y * Acceleration.y );

    updateEnergy( - DeltaEnergy ); }

float Spaceship::getThrust ( ) {

    return Thrust; }

void Spaceship::setThrust ( float Thrust ) {

    this->Thrust = Thrust; }

float Spaceship::getSuppressingFactor ( ) {

    return SuppressingFactor; }

void Spaceship::setSuppressingFactor ( float SuppressingFactor ) {

    this->SuppressingFactor = SuppressingFactor; }

float Spaceship::getRayPower ( ) {

    return RayPower; }

void Spaceship::setRayPower ( float RayPower ) {

    this->RayPower = RayPower; }

sf::Color Spaceship::getRayColor ( ) {

    return RayColor; }

void Spaceship::setRayColor ( sf::Color RayColor ) {

    this->RayColor = RayColor; }

unsigned int Spaceship::getMissileCount ( ) {

    return MissileCount; }

void Spaceship::setMissileCount ( unsigned int MissileCount ) {

    this->MissileCount = MissileCount; }

void Spaceship::setMissileLimit ( unsigned int MissileLimit ) {

    this->MissileLimit = MissileLimit; }

void Spaceship::update ( sf::Event &Event ) {

    if ( isDestructed() ) {

        return; }

    if ( Controller ) {

        Controller->update( Event ); } }

void Spaceship::update ( sf::Time ElapsedTime ) {

    if ( isDestructed() ) {

        return; }

    updateHealth( HealthRestoration * ElapsedTime.asSeconds() );
    updateEnergy( EnergyRestoration * ElapsedTime.asSeconds() );

    if ( Controller ) {

        Controller->update( ElapsedTime );

        if ( Controller->onThrustForward() && Energy >= ( Thrust * ElapsedTime.asSeconds() ) ) {

            float Angle = getVelocityAngle();

            if ( Controller->onThrustLeft() ) {

                Angle -= PI / 3.f; }

            else if ( Controller->onThrustRight() ) {

                Angle += PI / 3.f; }

            sf::Vector2f Acceleration;
            Acceleration.x = Thrust * cosf( Angle );
            Acceleration.y = Thrust * sinf( Angle );

            updateEnergy( Acceleration, ElapsedTime );
            updateVelocity( Acceleration, ElapsedTime ); }

        else if ( Controller->onThrustBackward() && Energy >= ( Thrust * ElapsedTime.asSeconds() ) ) {

            const float MinimumVelocity = 1.f;

            if ( fabsf( getVelocity().x ) > MinimumVelocity || fabsf( getVelocity().y ) > MinimumVelocity ) {

                float Angle = getVelocityAngle() + PI;
                float Module = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );

                sf::Vector2f Acceleration;
                Acceleration.x = SuppressingFactor * Module * cosf( Angle );
                Acceleration.y = SuppressingFactor * Module * sinf( Angle );

                updateEnergy( Acceleration, ElapsedTime );
                updateVelocity( Acceleration, ElapsedTime ); } }

        if ( Controller->onRayShot() && !RayShot && Energy >= RayPower ) {

            RayShot = true;

            updateEnergy( - RayPower ); }

        if ( Controller->onMissileShot() ) {

            if ( !MissileShot && MissileCount > 0 ) {

                MissileShot = true;

                MissileCount--; } } }

    updatePosition( ElapsedTime ); }

void Spaceship::render ( sf::RenderWindow &Window ) { // TODO

    sf::CircleShape Circle;

    Circle.setRadius( getRadius() );
    Circle.setOrigin( getRadius(), getRadius() );
    Circle.setFillColor( sf::Color::Blue );

    Circle.setPosition( getPosition() );
    Window.draw( Circle );

    Circle.setFillColor( sf::Color::Green );
    Circle.setPosition( getPosition() + sf::Vector2f( 5.f * cosf( getVelocityAngle() ), 5.f * sinf( getVelocityAngle() ) ) );
    Window.draw( Circle );

    }

bool Spaceship::onRayShot ( ) {

    if ( RayShot ) {

        RayShot = false;

        return true; }

    return false; }

bool Spaceship::onMissileShot ( ) {

    if ( MissileShot ) {

        MissileShot = false;

        return true; }

    return false; }

ParticleSystem * Spaceship::onCollision ( Planet * Other ) {

    auto * Explosion = new ParticleSystem ( );
    float Normal = PI + atan2f( Other->getPosition().y - getPosition().y, Other->getPosition().x - getPosition().x );
    float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );
    ExplosionOnDestruction = false;

    Explosion->setOriginPosition( Other->getPosition() + sf::Vector2f( Other->getRadius() * cosf( Normal ), Other->getRadius() * sinf( Normal ) ) );
    Explosion->setOriginVelocity( sf::Vector2f( 0, 0 ) );
    Explosion->setAngleRange( Normal, 0.8f * PI );
    Explosion->setVelocityRange( 15.f, 15.f + 0.8f * Velocity );
    Explosion->setColorRange( sf::Color ( 150, 0, 0 ), sf::Color ( 255, 150, 50 ) );
    Explosion->setDuration( sf::seconds( 0.5f ), sf::seconds( 3.f ) );
    Explosion->generateParticles( (unsigned int) ( ( Velocity > 200.f ? 10000 : 5000 ) * ( getMass() / 4.f ) ) );

    setHealth( 0.f );
    setEnergy( 0.f );
    setVelocity( sf::Vector2f( 0.f, 0.f ) );// Necessary for PlayerFinalVelocity
    destruct();

    return Explosion; }

ParticleSystem * Spaceship::onCollision ( Asteroid * Other ) {

    float Distance;
    BodyCollision Collision ( BodyCollision::Types::Elastic, this, Other, 0.7f );

    setVelocity( Collision.getFirstVelocity() );
    Other->setVelocity( Collision.getSecondVelocity() );

    updateHealth( - 0.5f * Collision.getReleasedEnergy() );

    if ( getVelocity() == sf::Vector2f( 0.f, 0.f ) && Other->getVelocity() == sf::Vector2f ( 0.f, 0.f ) ) {

        setVelocity( sf::Vector2f( 1.f, 0.f ) );
        Other->setVelocity( sf::Vector2f( - 1.f, 0.f ) ); }

    do {

        updatePosition( sf::seconds( 0.01f ) );
        Other->updatePosition( sf::seconds( 0.01f ) );

        float DistanceX = getPosition().x - Other->getPosition().x;
        float DistanceY = getPosition().y - Other->getPosition().y;
        Distance = sqrtf( DistanceX * DistanceX + DistanceY * DistanceY ); }

    while ( Distance <= ( getRadius() + Other->getRadius() ) );

    if ( isDestructed() ) {

        auto * Explosion = new ParticleSystem ( );
        float Normal = PI + atan2f( Other->getPosition().y - getPosition().y, Other->getPosition().x - getPosition().x );
        float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );
        ExplosionOnDestruction = false;

        Explosion->setOriginPosition( Other->getPosition() + sf::Vector2f( Other->getRadius() * cosf( Normal ), Other->getRadius() * sinf( Normal ) ) );
        Explosion->setOriginVelocity( getVelocity() );
        Explosion->setAngleRange( getVelocityAngle(), 2.f * PI / 3.f );
        Explosion->setVelocityRange( 5.f, 15.f + 0.5f * Velocity );
        Explosion->setColorRange( sf::Color ( 150, 0, 0 ), sf::Color ( 255, 150, 50 ) );
        Explosion->setDuration( sf::seconds( 0.5f ), sf::seconds( 4.f ) );
        Explosion->generateParticles( (unsigned int) ( ( Velocity > 200.f ? 10000 : 5000 ) * ( getMass() / 4.f ) ) );

        return Explosion; }

    return nullptr; }

ParticleSystem *  Spaceship::onCollision ( Spaceship * Other ) {

    float Distance;
    BodyCollision Collision ( BodyCollision::Types::Elastic, this, Other, 0.7f );

    setVelocity( Collision.getFirstVelocity() );
    Other->setVelocity( Collision.getSecondVelocity() );

    updateHealth( - 0.5f * Collision.getReleasedEnergy() );
    Other->updateHealth( - 0.5f * Collision.getReleasedEnergy() );

    if ( getVelocity() == sf::Vector2f( 0.f, 0.f ) && Other->getVelocity() == sf::Vector2f ( 0.f, 0.f ) ) {

        setVelocity( sf::Vector2f( 1.f, 0.f ) );
        Other->setVelocity( sf::Vector2f( - 1.f, 0.f ) ); }

    do {

        updatePosition( sf::seconds( 0.01f ) );
        Other->updatePosition( sf::seconds( 0.01f ) );

        float DistanceX = getPosition().x - Other->getPosition().x;
        float DistanceY = getPosition().y - Other->getPosition().y;
        Distance = sqrtf( DistanceX * DistanceX + DistanceY * DistanceY ); }

    while ( Distance <= ( getRadius() + Other->getRadius() ) );

    return nullptr; }

ParticleSystem * Spaceship::onDestruction ( ) {

    if ( !ExplosionOnDestruction ) {

        return nullptr; }

    auto * Explosion = new ParticleSystem ( );
    float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );

    Explosion->setOriginPosition( getPosition() );
    Explosion->setOriginVelocity( getVelocity() );
    Explosion->setAngleRange( getVelocityAngle(), Velocity > 100.f ? ( 2.f * PI / 3.f ) : 0.9f * PI );
    Explosion->setVelocityRange( - 25.f, Velocity > 100.f ? 75.f : 50.f );
    Explosion->setColorRange( sf::Color ( 150, 0, 0 ), sf::Color ( 255, 150, 50 ) );
    Explosion->setDuration( sf::seconds( 1.f ), sf::seconds( 5.f ) );
    Explosion->generateParticles( (unsigned int) ( 5000 * ( getMass() / 4.f ) ) );

    return Explosion; }