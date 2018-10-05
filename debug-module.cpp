#include "debug-module.hpp"

void DebugModule::update ( ) {

    if ( Terminate ) {

        return; }

    sf::Time ElapsedTime = Clock.restart();

    if ( ElapsedTime.asSeconds() < 0.1f ) {

        TestDuration[TestIndex] -= ElapsedTime;

        Game->update(); }

    if ( TestDuration[TestIndex].asSeconds() <= 0.f ) {

        TestIndex++;

        if ( TestIndex < TestCount ) {

            prepareTest(); }

        else {

            Terminate = true; } } }

void DebugModule::update ( sf::Event &Event ) {

    // NOTHING

    }

void DebugModule::render ( sf::RenderWindow &Window ) {

    if ( Terminate ) {

        return; }

    Game->render( Window );

    sf::Text BottomText;
    BottomText.setString( TestTitle[ TestIndex ] );
    BottomText.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    BottomText.setCharacterSize( 20 );
    BottomText.setPosition( Graphics->getWindowWidth() - 15.f - BottomText.getLocalBounds().width, Graphics->getWindowHeight() - 34.f );

    Window.draw( BottomText ); }

bool DebugModule::onTerminate ( ) {

    return Terminate; }

void DebugModule::prepareTest ( ) {

    Game->reset();
    Game->AreaRadius = 500.f;
    Game->AsteroidCount = 0;
    Game->PowerUpLimit = 0;
    Game->initAreaLimit();

    if ( TestIndex < 3 ) {

        auto MyPlanet = getPlanet();
        auto MySpaceship = getSpaceship();
        auto MyAsteroid = getAsteroid();

        MySpaceship->setPosition( sf::Vector2f( 300.f, - 300.f ) );
        MySpaceship->setVelocity( sf::Vector2f( - 40.f, 0.f ) );
        MyAsteroid->setPosition( sf::Vector2f( - 300.f, 300.f ) );
        MyAsteroid->setVelocity( sf::Vector2f( 40.f, 0.f ) );

        Game->Planets.emplace_back( MyPlanet );
        Game->Spaceships.emplace_back( MySpaceship );
        Game->Asteroids.emplace_back( MyAsteroid ); }

    if ( TestIndex == 1 ) {

        Game->Gravity = 0.25f; }

    if ( TestIndex == 2 ) {

        Game->Gravity = 4.f; }

    if ( TestIndex == 3 ) {

        auto FirstAsteroid = getAsteroid();
        auto SecondAsteroid = getAsteroid();

        FirstAsteroid->setPosition( sf::Vector2f( - 300.f, 50.f ) );
        FirstAsteroid->setVelocity( sf::Vector2f( 75.f, - 10.f ) );
        SecondAsteroid->setPosition( sf::Vector2f( 300.f, - 50.f ) );
        SecondAsteroid->setVelocity( sf::Vector2f( - 75.f, 10.f ) );
        SecondAsteroid->setMass( 20.f );
        SecondAsteroid->setRadius( 20.f );

        Game->Asteroids.emplace_back( FirstAsteroid );
        Game->Asteroids.emplace_back( SecondAsteroid ); }

    if ( TestIndex == 4 ) {

        auto MySpaceship = getSpaceship();
        auto MyAsteroid = getAsteroid();

        MySpaceship->setPosition( sf::Vector2f( 300.f, - 50.f ) );
        MySpaceship->setVelocity( sf::Vector2f( - 75.f, 10.f ) );
        MyAsteroid->setPosition( sf::Vector2f( - 300.f, 50.f ) );
        MyAsteroid->setVelocity( sf::Vector2f( 75.f, - 10.f ) );

        Game->Spaceships.emplace_back( MySpaceship );
        Game->Asteroids.emplace_back( MyAsteroid ); }

    if ( TestIndex == 5 ) {

        auto FirstSpaceship = getSpaceship();
        auto SecondSpaceship = getSpaceship();

        FirstSpaceship->setPosition( sf::Vector2f( 300.f, - 50.f ) );
        FirstSpaceship->setVelocity( sf::Vector2f( - 75.f, 10.f ) );
        SecondSpaceship->setPosition( sf::Vector2f( - 300.f, 50.f ) );
        SecondSpaceship->setVelocity( sf::Vector2f( 75.f, - 10.f ) );
        SecondSpaceship->setMass( 10.f );
        SecondSpaceship->setRadius( 30.f );

        Game->Spaceships.emplace_back( FirstSpaceship );
        Game->Spaceships.emplace_back( SecondSpaceship ); }

    if ( TestIndex == 6 ) {

        auto MySpaceship = getSpaceship();
        auto MyMissile = getMissile();

        MySpaceship->setPosition( sf::Vector2f( 300.f, - 100.f ) );
        MySpaceship->setVelocity( sf::Vector2f( - 25.f, - 25.f ) );
        MyMissile->setPosition( sf::Vector2f( - 300.f, 100.f ) );
        MyMissile->setVelocity( sf::Vector2f( 25.f, 0.f ) );
        MyMissile->setTarget( MySpaceship );

        Game->Spaceships.emplace_back( MySpaceship );
        Game->Missiles.emplace_back( MyMissile );

        }

    }

Planet * DebugModule::getPlanet ( ) {

    auto * NewPlanet = new Planet ( Graphics, 2500.f, 100.f );

    return NewPlanet; }

Asteroid * DebugModule::getAsteroid ( ) {

    auto * NewAsteroid = new Asteroid ( Graphics, 15.f, 15.f );

    return NewAsteroid; }

Spaceship * DebugModule::getSpaceship ( ) {

    GameplaySettings::SpaceshipPrototype Prototype;

    Prototype.Name = "Hercules the Unbroken";
    Prototype.Texture = "Spaceship";
    Prototype.AccentTexture = "SpaceshipAccent";
    Prototype.Mass = 4.f;
    Prototype.Radius = 20.f;
    Prototype.HealthLimit = 200;
    Prototype.HealthRestoration = 2.f;
    Prototype.EnergyLimit = 2500;
    Prototype.EnergyRestoration = 20;
    Prototype.Thrust = 75;
    Prototype.BrakingFactor = 0.6;
    Prototype.FuelColor = sf::Color( 213, 0, 0 );
    Prototype.RayPower = 20;
    Prototype.RayColor = sf::Color( 255, 23, 68 );
    Prototype.MissileCount = 3;
    Prototype.MissileLimit = 3;
    Prototype.ScoreMultiplier = 2.0f;

    auto * NewSpaceship = new Spaceship ( Prototype.Mass, Prototype.Radius );

    NewSpaceship->setHealthLimit( Prototype.HealthLimit );
    NewSpaceship->setHealth( Prototype.HealthLimit );
    NewSpaceship->setHealthRestoration( Prototype.HealthRestoration );
    NewSpaceship->setEnergyLimit( Prototype.EnergyLimit );
    NewSpaceship->setEnergy( Prototype.EnergyLimit );
    NewSpaceship->setEnergyRestoration( Prototype.EnergyRestoration );
    NewSpaceship->setThrust( Prototype.Thrust );
    NewSpaceship->setBrakingFactor( Prototype.BrakingFactor );
    NewSpaceship->setRayPower( Prototype.RayPower );
    NewSpaceship->setRayColor( Prototype.RayColor );
    NewSpaceship->setMissileLimit( Prototype.MissileLimit );
    NewSpaceship->setMissileCount( Prototype.MissileCount );
    NewSpaceship->setTexture( Graphics->getTexture( Prototype.Texture ) );
    NewSpaceship->setAccentTexture( Graphics->getTexture( Prototype.AccentTexture ), sf::Color::Red );
    NewSpaceship->setThrusterTexture( Graphics->getTexture( "Thruster" ), Prototype.FuelColor );

    return NewSpaceship; }

Missile * DebugModule::getMissile ( ) {

    auto * NewMissile = new Missile ( );

    return NewMissile; }
