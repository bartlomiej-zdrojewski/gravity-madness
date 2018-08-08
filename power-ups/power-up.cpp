#include "power-up.hpp"

PowerUp::PowerUp ( sf::Time Duration, float * Gravity, unsigned int * AsteroidCount ) {

    MySpaceship = nullptr;
    this->Gravity = Gravity;
    this->AsteroidCount = AsteroidCount;

    Caught = false;
    Expired = false;
    GravityModifier = false;
    AsteroidModifier = false;

    FadeDuration = sf::seconds( 1.f );
    OscillationFrequency = sf::Vector2f( 0.25f + getRandomFloat() * 0.25f, 0.25f + getRandomFloat() * 0.25f );
    ExistenceTime = Duration; }

bool PowerUp::isCaught ( ) {

    return Caught; }

bool PowerUp::isExpired ( ) {

    return Expired; }

bool PowerUp::isGravityModifier ( ) {

    return GravityModifier; }

bool PowerUp::isAsteroidModifier ( ) {

    return AsteroidModifier; }

sf::Vector2f PowerUp::getPosition ( ) {

    return Position; }

void PowerUp::setPosition ( sf::Vector2f Position ) {

    this->Position = Position; }

float PowerUp::getRadius ( ) {

    return Radius; }

void PowerUp::update ( sf::Time ElapsedTime ) {

    OscillationTime += ElapsedTime;

    if ( FadeTime < FadeDuration ) {

        FadeTime += ElapsedTime; }

    else {

        FadeTime = FadeDuration; }

    if ( !Expired ) {

        if ( !Caught ) {

            ExistenceTime -= ElapsedTime;

            if ( ExistenceTime.asSeconds() <= 0.f ) {

                Expired = true; } }

        else {

            updateEffect( ElapsedTime ); } } }

void PowerUp::render ( sf::RenderWindow &Window ) {

    if ( !Caught ) {

        sf::Sprite Sprite ( Texture );

        Sprite.setOrigin( Texture.getSize().x / 2.f, Texture.getSize().y / 2.f );
        Sprite.setScale( ( 2.f * getRadius() ) / Texture.getSize().x, ( 2.f * getRadius() ) / Texture.getSize().y );
        Sprite.setPosition( getPosition() + getRadius() * sf::Vector2f( cosf( PI * OscillationTime.asSeconds() * OscillationFrequency.x ), sinf( PI * OscillationTime.asSeconds() * OscillationFrequency.y ) ) );

        if ( FadeTime <= FadeDuration ) {

            Sprite.setColor( sf::Color( 255, 255, 255, (sf::Uint8) ( 255 * FadeTime.asSeconds() / FadeDuration.asSeconds() ) ) ); }

        else if ( ExistenceTime <= FadeDuration ) {

            Sprite.setColor( sf::Color( 255, 255, 255, (sf::Uint8) ( 255 * ExistenceTime.asSeconds() / FadeDuration.asSeconds() ) ) ); }

        Window.draw( Sprite ); } }

void PowerUp::finish ( ) {

    Expired = true;

    onEffectEnd(); }

void PowerUp::onCatch ( Spaceship * MySpaceship ) {

    Caught = true;
    this->MySpaceship = MySpaceship;

    onEffectBegin(); }

float PowerUp::getRandomFloat ( ) {

    return ( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ); }
