#include "asteroid.hpp"

void Asteroid::resetExistenceTime ( ) {

    ExistenceTime = ExistenceDuration; }

void Asteroid::update ( sf::Time ElapsedTime ) {

    ExistenceTime -= ElapsedTime;

    if ( ExistenceTime.asSeconds() <= 0.f ) {

        DestructionTime -= ElapsedTime;

        if ( DestructionTime.asSeconds() <= 0.f ) {

            destruct(); } }

    else if ( DestructionTime < DestructionDuration ) {

        DestructionTime += 2.f * ElapsedTime; }

    if ( DestructionTime > DestructionDuration ) {

        DestructionTime = DestructionDuration; }

    Angle += AngularSpeed * ElapsedTime.asSeconds();

    updatePosition( ElapsedTime ); }

void Asteroid::render ( sf::RenderWindow &Window ) {

    sf::Sprite Sprite ( Texture );

    Sprite.setOrigin( (float) Texture.getSize().x / 2, (float) Texture.getSize().y / 2 );
    Sprite.setScale( ( 2.f * getRadius() ) / Texture.getSize().x, ( 2.f * getRadius() ) / Texture.getSize().y );
    Sprite.setPosition( getPosition() );
    Sprite.setRotation( RAD_TO_DEG * Angle );
    Sprite.setColor( sf::Color( 255, 255, 255, (sf::Uint8) ( 255.f * DestructionTime.asSeconds() / DestructionDuration.asSeconds() ) ) );

    Window.draw( Sprite ); }

ParticleSystem * Asteroid::onCollision ( Planet * Other ) {

    auto * Explosion = new ParticleSystem ( );
    float Normal = PI + atan2f( Other->getPosition().y - getPosition().y, Other->getPosition().x - getPosition().x );
    float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );

    Explosion->setOriginPosition( Other->getPosition() + sf::Vector2f( Other->getRadius() * cosf( Normal ), Other->getRadius() * sinf( Normal ) ) );
    Explosion->setOriginVelocity( sf::Vector2f( 0, 0 ) );
    Explosion->setAngleRange( Normal, 0.95f * PI );
    Explosion->setVelocityRange( 10.f, 10.f + 0.8f * Velocity );
    Explosion->setColorRange( sf::Color ( 25, 25, 50 ), sf::Color ( 125, 125, 150 ) );
    Explosion->setDuration( sf::seconds( 0.5f ), sf::seconds( 4.f ) );
    Explosion->generateParticles( (unsigned int) ( getMass() * ( Velocity / 100.f ) ) );

    destruct();

    return Explosion; }

ParticleSystem * Asteroid::onCollision ( Asteroid * Other ) {

    float Distance;
    BodyCollision Collision ( BodyCollision::Types::Elastic, this, Other, 0.50f ); // 50% of kinetic is released

    setVelocity( Collision.getFirstVelocity() );
    Other->setVelocity( Collision.getSecondVelocity() );

    if ( sf::Vector2i( (int) getVelocity().x, (int) getVelocity().y ) == sf::Vector2i( 0, 0 ) && sf::Vector2i( (int) Other->getVelocity().x, (int) Other->getVelocity().y ) == sf::Vector2i( 0, 0 ) ) {

        setVelocity( sf::Vector2f( 1.f, 1.f ) );
        Other->setVelocity( sf::Vector2f( - 1.f, - 1.f ) ); }

    do {

        updatePosition( sf::seconds( 0.01f ) );
        Other->updatePosition( sf::seconds( 0.01f ) );

        float DistanceX = getPosition().x - Other->getPosition().x;
        float DistanceY = getPosition().y - Other->getPosition().y;
        Distance = sqrtf( DistanceX * DistanceX + DistanceY * DistanceY ); }

    while ( Distance <= ( getRadius() + Other->getRadius() ) );

    return nullptr; }

float Asteroid::getRandomFloat ( ) {

    return ( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ); }