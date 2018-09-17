#include "missile.hpp"

void Missile::setSpaceship ( Spaceship * MySpaceship ) {

    this->MySpaceship = MySpaceship; }

void Missile::setScoreCounter ( ScoreCounter * MyScore ) {

    this->MyScore = MyScore; }

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

void Missile::setTexture ( sf::Texture &Texture ) {

    this->Texture = Texture; }

void Missile::setThrusterTexture ( sf::Texture &ThrusterTexture ) {

    this->ThrusterTexture = ThrusterTexture; }

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

            if ( fabsf( AngleDifference ) > ( PI / 24.f ) ) {

                if ( AngleDifference > 0.f ) {

                    Angle -= PI / 3.f;
                    ThrusterAngleOffset = ThrusterMaximumAngleOffset; }

                else if ( AngleDifference < 0.f ) {

                    Angle += PI / 3.f;
                    ThrusterAngleOffset = - ThrusterMaximumAngleOffset; } }

            else {

                ThrusterAngleOffset = 0.f; } }

        Thrust -= ThrustReduction * ElapsedTime.asSeconds();

        if ( Thrust > 0.f ) {

            sf::Vector2f Acceleration;
            Acceleration.x = Thrust * cosf( Angle );
            Acceleration.y = Thrust * sinf( Angle );

            updateVelocity( Acceleration, ElapsedTime );

            sf::Vector2f ThrusterPosition = getPosition();
            ThrusterPosition += ( SQRT2_2ND * 0.5f * getRadius() ) * sf::Vector2f( cosf( PI + getVelocityAngle() ), sinf( PI + getVelocityAngle() ) );
            ThrusterPosition += ( SQRT2_2ND * 0.3125f * getRadius() ) * sf::Vector2f( cosf( PI + getVelocityAngle() + ThrusterAngleOffset ), sinf( PI + getVelocityAngle() + ThrusterAngleOffset ) );

            ThrusterExhaust.setOriginPosition( ThrusterPosition );
            ThrusterExhaust.setOriginVelocity( getVelocity() );
            ThrusterExhaust.setAngleRange( PI + getVelocityAngle() + ThrusterAngleOffset, 0.05f * PI );
            ThrusterExhaust.setVelocityRange( 250.f, 500.f );
            ThrusterExhaust.setColorRange( sf::Color ( 200, 0, 50 ), sf::Color ( 255, 50, 150 ) );
            ThrusterExhaust.setDuration( sf::seconds( 1.f ), sf::seconds( 3.f ) );
            ThrusterExhaust.generateParticles( (unsigned int) ( ( Thrust / 100.f ) * 200 * ElapsedTime.asSeconds() ) ); }

        updatePosition( ElapsedTime );
        ThrusterExhaust.update( ElapsedTime ); } }

void Missile::render ( sf::RenderWindow &Window ) { // TODO

    sf::CircleShape Circle;
    Circle.setRadius( getRadius() );
    Circle.setOrigin( getRadius(), getRadius() );
    Circle.setPosition( getPosition() );
    Circle.setFillColor( sf::Color( 0, 0, 255 ) );
    //Window.draw( Circle );

    // -------------------------------

    sf::Sprite Sprite ( Texture );
    sf::Sprite ThrusterSprite ( ThrusterTexture );

    Sprite.setOrigin( (float) Texture.getSize().x / 2, (float) Texture.getSize().y / 2 );
    Sprite.setScale( ( SQRT2_2ND * 2.f * getRadius() ) / Texture.getSize().x, ( SQRT2_2ND * 2.f * getRadius() ) / Texture.getSize().y );
    Sprite.setPosition( getPosition() );
    Sprite.setRotation( RAD_TO_DEG * getVelocityAngle() + 90.f );

    float ThrusterModule = SQRT2_2ND * 0.5f * getRadius();
    float ThrusterAngle = PI + getVelocityAngle();

    ThrusterSprite.setOrigin( (float) ThrusterTexture.getSize().x / 2, (float) ThrusterTexture.getSize().y / 2 );
    ThrusterSprite.setScale( ( 0.375f * SQRT2_2ND * 2.f * getRadius() ) / ThrusterTexture.getSize().x, ( 0.375f * SQRT2_2ND * 2.f * getRadius() ) / ThrusterTexture.getSize().y );
    ThrusterSprite.setOrigin( ThrusterTexture.getSize().x / 2.f, ThrusterTexture.getSize().y / 3.f );
    ThrusterSprite.setPosition( getPosition() + ThrusterModule * sf::Vector2f( cosf( ThrusterAngle ), sinf( ThrusterAngle ) ) );
    ThrusterSprite.setRotation( RAD_TO_DEG * ( PI + ThrusterAngle + ThrusterAngleOffset ) + 90.f );

    ThrusterExhaust.render( Window );
    Window.draw( ThrusterSprite );
    Window.draw( Sprite ); }

void Missile::render ( sf::RenderTexture &Buffer ) {

    sf::Sprite Sprite ( Texture );
    sf::Sprite ThrusterSprite ( ThrusterTexture );

    Sprite.setOrigin( (float) Texture.getSize().x / 2, (float) Texture.getSize().y / 2 );
    Sprite.setScale( ( SQRT2_2ND * 2.f * getRadius() ) / Texture.getSize().x, ( SQRT2_2ND * 2.f * getRadius() ) / Texture.getSize().y );
    Sprite.setPosition( getPosition() );
    Sprite.setRotation( RAD_TO_DEG * getVelocityAngle() + 90.f );

    float ThrusterModule = SQRT2_2ND * 0.5f * getRadius();
    float ThrusterAngle = PI + getVelocityAngle();

    ThrusterSprite.setOrigin( (float) ThrusterTexture.getSize().x / 2, (float) ThrusterTexture.getSize().y / 2 );
    ThrusterSprite.setScale( ( 0.375f * SQRT2_2ND * 2.f * getRadius() ) / ThrusterTexture.getSize().x, ( 0.375f * SQRT2_2ND * 2.f * getRadius() ) / ThrusterTexture.getSize().y );
    ThrusterSprite.setOrigin( ThrusterTexture.getSize().x / 2.f, ThrusterTexture.getSize().y / 3.f );
    ThrusterSprite.setPosition( getPosition() + ThrusterModule * sf::Vector2f( cosf( ThrusterAngle ), sinf( ThrusterAngle ) ) );
    ThrusterSprite.setRotation( RAD_TO_DEG * ( PI + ThrusterAngle + ThrusterAngleOffset ) + 90.f );

    ThrusterExhaust.render( Buffer );
    Buffer.draw( ThrusterSprite );
    Buffer.draw( Sprite ); }

void Missile::onShot ( ) {

    ExplosionTime -= sf::seconds( 0.5f ); }

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

    BodyCollision Collision ( BodyCollision::Types::Inelastic, this, Other, 0.70f ); // 30% of kinetic energy is released
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

    BodyCollision Collision ( BodyCollision::Types::Inelastic, this, Other, 0.60f ); // 40% of kinetic energy is released
    auto * Explosion = new ParticleSystem ( );
    float Normal = PI + atan2f( Other->getPosition().y - getPosition().y, Other->getPosition().x - getPosition().x );
    float Velocity = sqrtf( getVelocity().x * getVelocity().x + getVelocity().y * getVelocity().y );
    ExplosionOnDestruction = false;

    Explosion->setOriginPosition( Other->getPosition() + sf::Vector2f( SQRT2_2ND * 0.75f * Other->getRadius() * cosf( Normal ), SQRT2_2ND * 0.75f * Other->getRadius() * sinf( Normal ) ) );
    Explosion->setOriginVelocity( Collision.getSecondVelocity() );
    Explosion->setAngleRange( Normal, PI / 3.f );
    Explosion->setVelocityRange( 10.f, 20.f + 0.8f * Velocity );
    Explosion->setColorRange( sf::Color ( 200, 0, 50 ), sf::Color ( 255, 50, 150 ) );
    Explosion->setDuration( sf::seconds( 1.f ), sf::seconds( 3.f ) );
    Explosion->generateParticles( (unsigned int) ( ExplosionPower * 25 ) );

    Other->updateHealth( - ExplosionPower );
    Other->updateHealth( - 10.f * Collision.getReleasedEnergy() );
    Other->setVelocity( Collision.getSecondVelocity() );

    if ( MyScore ) {

        if ( Other->isDestructed() ) {

            MyScore->update( ScoreCounter::Event::MissileDestruction ); }

        else {

            MyScore->update( ScoreCounter::Event::MissileHit ); } }

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
