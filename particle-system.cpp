#include "particle-system.hpp"

ParticleSystem::ParticleSystem ( ) {

    AxisAngle = 0.f;
    AngleRange = PI / 6.f;
    MinVelocity = 25.f;
    MaxVelocity = 100.f;
    MinColor = sf::Color ( 200, 200, 200 );
    MaxColor = sf::Color ( 255, 255, 255 );
    MinDuration = sf::seconds( 1.0f );
    MaxDuration = sf::seconds( 10.f ); }

sf::FloatRect ParticleSystem::getInfluenceArea ( ) {

    return InfluenceArea; }

void ParticleSystem::setOriginPosition ( sf::Vector2f Position ) {

    OriginPosition = Position; }

void ParticleSystem::setOriginVelocity ( sf::Vector2f Velocity ) {

    OriginVelocity = Velocity; }

void ParticleSystem::setAngleRange ( float AxisAngle, float AngleRange ) {

    this->AxisAngle = AxisAngle;
    this->AngleRange = AngleRange; }

void ParticleSystem::setVelocityRange ( float MinVelocity, float MaxVelocity ) {

    if ( MinVelocity > MaxVelocity ) {

        float Temp = MinVelocity;

        MinVelocity = MaxVelocity;
        MaxVelocity = Temp; }

    this->MinVelocity = MinVelocity;
    this->MaxVelocity = MaxVelocity; }

void ParticleSystem::setColorRange ( sf::Color MinColor, sf::Color MaxColor ) {

    if ( MinColor.r > MaxColor.r ) {

        sf::Uint8 Temp = MinColor.r;

        MinColor.r = MaxColor.r;
        MaxColor.r = Temp; }

    if ( MinColor.g > MaxColor.g ) {

        sf::Uint8 Temp = MinColor.g;

        MinColor.g = MaxColor.g;
        MaxColor.g = Temp; }

    if ( MinColor.b > MaxColor.b ) {

        sf::Uint8 Temp = MinColor.b;

        MinColor.b = MaxColor.b;
        MaxColor.b = Temp; }

    this->MinColor = MinColor;
    this->MaxColor = MaxColor; }

void ParticleSystem::setDuration ( sf::Time MinDuration, sf::Time MaxDuration ) {

    if ( MinDuration > MaxDuration ) {

        sf::Time Temp = MinDuration;

        MinDuration = MaxDuration;
        MaxDuration = Temp; }

    this->MinDuration = MinDuration;
    this->MaxDuration = MaxDuration; }

unsigned int ParticleSystem::getParticleCount ( ) {

    return (unsigned int) ( Particles.size() ); }

void ParticleSystem::generateParticles ( unsigned int Count ) {

    for ( unsigned int i = 0; i < Count; i++ ) {

        Particle NewParticle;

        NewParticle.Position = OriginPosition;
        NewParticle.Velocity = OriginVelocity;
        NewParticle.Time = sf::seconds( MinDuration.asSeconds() + getRandomFloat() * ( MaxDuration.asSeconds() - MinDuration.asSeconds() ) );

        float Angle = AxisAngle - AngleRange / 2.f + getRandomFloat() * AngleRange;
        float Velocity = MinVelocity + getRandomFloat() * ( MaxVelocity - MinVelocity );
        auto Red = (sf::Uint8) ( MinColor.r + getRandomFloat() * ( MaxColor.r - MinColor.r ) );
        auto Green = (sf::Uint8) ( MinColor.g + getRandomFloat() * ( MaxColor.g - MinColor.g ) );
        auto Blue = (sf::Uint8) ( MinColor.b + getRandomFloat() * ( MaxColor.b - MinColor.b ) );

        NewParticle.Velocity.x += Velocity * cosf( Angle );
        NewParticle.Velocity.y += Velocity * sinf( Angle );
        NewParticle.Color = sf::Color ( Red, Green, Blue, 255 );

        Particles.push_back( NewParticle ); } }

void ParticleSystem::update ( sf::Time ElapsedTime ) {

    InfluenceArea = sf::FloatRect ( OriginPosition.x, OriginPosition.y, 0.f, 0.f );

    for ( auto i = Particles.begin(); i != Particles.end(); i++ ) {

        Particle &ActiveParticle = *i;
        ActiveParticle.Time -= ElapsedTime;

        if ( ActiveParticle.Time.asSeconds() <= 0.f ) {

            i = Particles.erase( i );

            continue; }

        ActiveParticle.Position += ActiveParticle.Velocity * ElapsedTime.asSeconds();
        ActiveParticle.Color.a = (sf::Uint8) ( 255.f * ActiveParticle.Time.asSeconds() / MaxDuration.asSeconds() );

        if ( ActiveParticle.Position.x < InfluenceArea.left ) {

            InfluenceArea.left = ActiveParticle.Position.x; }

        else if ( ActiveParticle.Position.x > ( InfluenceArea.left + InfluenceArea.width ) ) {

            InfluenceArea.width = ActiveParticle.Position.x - InfluenceArea.left; }

        if ( ActiveParticle.Position.y < InfluenceArea.top ) {

            InfluenceArea.top = ActiveParticle.Position.y; }

        else if ( ActiveParticle.Position.y > ( InfluenceArea.top + InfluenceArea.height ) ) {

            InfluenceArea.height = ActiveParticle.Position.y - InfluenceArea.top; } } }

void ParticleSystem::render ( sf::RenderWindow &Window ) {

    unsigned int Index = 0;
    Vertices.resize( Particles.size() );

    for ( auto ActiveParticle : Particles ) {

        Vertices[Index].position = ActiveParticle.Position;
        Vertices[Index].color = ActiveParticle.Color;

        Index++; }

    Window.draw( &Vertices[0], Vertices.size(), sf::Points ); }

float ParticleSystem::getRandomFloat ( ) {

    return ( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ); }