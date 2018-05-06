#include "missile.hpp"

float Missile::getInfluenceRadius ( ) {

    // TODO
    return getRadius();

    }

float Missile::getExplosionPower ( ) {

    return ExplosionPower; }

void Missile::setExplosionPower ( float ExplosionPower ) {

    this->ExplosionPower = ExplosionPower; }

float Missile::getThrust ( ) {

    return Thrust; }

void Missile::setThrust ( float Thrust ) {

    this->Thrust = Thrust; }

float Missile::getThrustReduction ( ) {

    return ThrustReduction; }

void Missile::setThrustReduction ( float ThrustReduction ) {

    this->ThrustReduction = ThrustReduction; }

sf::Time Missile::getExplosionDelay ( ) {

    return ExplosionDelay; }

void Missile::setExplosionDelay ( sf::Time ExplosionDelay ) {

    ExplosionTime = ExplosionDelay;
    this->ExplosionDelay = ExplosionDelay; }

Spaceship * Missile::getTarget ( ) {

    return Target; }

void Missile::setTarget ( Spaceship * Target ) {

    this->Target = Target; }
    
void Missile::update ( sf::Time ElapsedTime ) {

    ExplosionTime -= ElapsedTime;

    if ( ExplosionTime.asSeconds() <= 0.f ) {

        destruct(); }

    else {

        float Angle = getVelocityAngle();

        if ( Target ) {

            float AngleDifference = atan2f( Target->getPosition().y - getPosition().y, Target->getPosition().x - getPosition().x );
            AngleDifference = normalizeAngle( Angle - AngleDifference );

            if ( AngleDifference > 0.f ) {

                Angle -= PI / 3.f; }

            else if ( AngleDifference < 0.f ) {

                Angle += PI / 3.f; } }

        Thrust -= ThrustReduction * ElapsedTime.asSeconds();

        if ( Thrust > 0.f ) {

            sf::Vector2f Acceleration;
            Acceleration.x = Thrust * cosf( Angle );
            Acceleration.y = Thrust * sinf( Angle );

            updateVelocity( Acceleration, ElapsedTime ); }

        updatePosition( ElapsedTime ); } }

void Missile::render ( sf::RenderWindow &Window ) { // TODO

    sf::CircleShape Circle;

    Circle.setRadius( getRadius() );
    Circle.setOrigin( getRadius(), getRadius() );
    Circle.setPosition( getPosition() );
    Circle.setFillColor( sf::Color( 0, 0, 255 ) );

    Window.draw( Circle );

    }

ParticleSystem * Missile::onCollision ( Planet * Other ) {

    auto * Explosion = new ParticleSystem ( );
    float Normal = PI + atan2f( Other->getPosition().y - getPosition().y, Other->getPosition().x - getPosition().x );
    float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );
    ExplosionOnDestruction = false;

    Explosion->setOriginPosition( Other->getPosition() + sf::Vector2f( Other->getRadius() * cosf( Normal ), Other->getRadius() * sinf( Normal ) ) );
    Explosion->setOriginVelocity( sf::Vector2f( 0, 0 ) );
    Explosion->setAngleRange( Normal, PI / 2.f );
    Explosion->setVelocityRange( 15.f, 15.f + 0.8f * Velocity );
    Explosion->setColorRange( sf::Color ( 200, 0, 50 ), sf::Color ( 255, 50, 150 ) );
    Explosion->setDuration( sf::seconds( 1.f ), sf::seconds( 3.f ) );
    Explosion->generateParticles( (unsigned int) ( ExplosionPower * 25 ) + Velocity > 200.f ? 1000 : 500 );

    destruct();

    return Explosion; }

ParticleSystem * Missile::onCollision ( Asteroid * Other ) {

    BodyCollision Collision ( BodyCollision::Types::Inelastic, this, Other );
    auto * Explosion = new ParticleSystem ( );
    float Normal = PI + atan2f( Other->getPosition().y - getPosition().y, Other->getPosition().x - getPosition().x );
    float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );
    ExplosionOnDestruction = false;

    Explosion->setOriginPosition( Other->getPosition() + sf::Vector2f( Other->getRadius() * cosf( Normal ), Other->getRadius() * sinf( Normal ) ) );
    Explosion->setOriginVelocity( Collision.getSecondVelocity() );
    Explosion->setAngleRange( Normal, PI / 2.f );
    Explosion->setVelocityRange( 15.f, 15.f + 0.8f * Velocity );
    Explosion->setColorRange( sf::Color ( 200, 0, 50 ), sf::Color ( 255, 50, 150 ) );
    Explosion->setDuration( sf::seconds( 1.f ), sf::seconds( 3.f ) );
    Explosion->generateParticles( (unsigned int) ( ExplosionPower * 25 ) + Velocity > 200.f ? 1000 : 500 );

    Other->setVelocity( Collision.getSecondVelocity() );
    destruct();

    return Explosion; }

ParticleSystem * Missile::onCollision ( Spaceship * Other ) {

    BodyCollision Collision ( BodyCollision::Types::Inelastic, this, Other );
    auto * Explosion = new ParticleSystem ( );
    float Normal = PI + atan2f( Other->getPosition().y - getPosition().y, Other->getPosition().x - getPosition().x );
    float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );
    ExplosionOnDestruction = false;

    Explosion->setOriginPosition( Other->getPosition() + sf::Vector2f( Other->getRadius() * cosf( Normal ), Other->getRadius() * sinf( Normal ) ) );
    Explosion->setOriginVelocity( Collision.getSecondVelocity() );
    Explosion->setAngleRange( Normal, PI / 3.f );
    Explosion->setVelocityRange( 10.f, 20.f + 0.8f * Velocity );
    Explosion->setColorRange( sf::Color ( 200, 0, 50 ), sf::Color ( 255, 50, 150 ) );
    Explosion->setDuration( sf::seconds( 1.f ), sf::seconds( 3.f ) );
    Explosion->generateParticles( (unsigned int) ( ExplosionPower * 25 ) );

    Other->updateHealth( - ExplosionPower );
    Other->updateHealth( - 0.25f * Collision.getReleasedEnergy() );
    Other->setVelocity( Collision.getSecondVelocity() );
    destruct();

    return Explosion; }

ParticleSystem * Missile::onCollision ( Missile * Other ) {

    auto * Explosion = new ParticleSystem ( );
    float Normal = PI + atan2f( Other->getPosition().y - getPosition().y, Other->getPosition().x - getPosition().x );
    float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );
    ExplosionOnDestruction = false;

    Explosion->setOriginPosition( Other->getPosition() + sf::Vector2f( Other->getRadius() * cosf( Normal ), Other->getRadius() * sinf( Normal ) ) );
    Explosion->setOriginVelocity( sf::Vector2f( 0, 0 ) );
    Explosion->setAngleRange( Normal, 0.8f * PI );
    Explosion->setVelocityRange( - 10.f - 0.2f * Velocity, 20.f + 0.8f * Velocity );
    Explosion->setColorRange( sf::Color ( 200, 0, 50 ), sf::Color ( 255, 50, 150 ) );
    Explosion->setDuration( sf::seconds( 0.2f ), sf::seconds( 2.f ) );
    Explosion->generateParticles( (unsigned int) ( ExplosionPower * 25 ) );

    destruct();

    return Explosion; }

ParticleSystem * Missile::onDestruction ( ) {

    if ( !ExplosionOnDestruction ) {

        return nullptr; }

    auto * Explosion = new ParticleSystem ( );

    Explosion->setOriginPosition( getPosition() );
    Explosion->setOriginVelocity( getVelocity() );
    Explosion->setAngleRange( 0.f, PI );
    Explosion->setVelocityRange( - 100.f, 100.f );
    Explosion->setColorRange( sf::Color ( 200, 0, 50 ), sf::Color ( 255, 50, 150 ) );
    Explosion->setDuration( sf::seconds( 1.f ), sf::seconds( 3.f ) );
    Explosion->generateParticles( (unsigned int) ( ExplosionPower * 25 ) );

    return Explosion; }
