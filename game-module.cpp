#include "game-module.hpp"

GameModule::GameModule ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;
    Gravity = 1.f;

    // TEMP ->

    auto C = new PlayerController ( );

    auto * P = new Planet ( 25, 100 );
    P->setPosition( sf::Vector2f( 400, 300 ) );
    Planets.push_back( P );

    auto * P2 = new Planet ( 25, 100 );
    P2->setPosition( sf::Vector2f( 100, -100 ) );
    Planets.push_back( P2 );

    auto * S = new Spaceship ( 10 );
    S->setPosition( sf::Vector2f( 700, 300 ) );
    S->setSpaceshipController( C );
    Spaceships.push_back( S );
    PlayerSpaceship = S;

    // -> TEMP

    }

GameModule::~GameModule ( ) {

    // TODO RELEASE MEMORY

    }

void GameModule::update ( ) {

    sf::Time ElapsedTime = Clock.restart();

    if ( ElapsedTime.asSeconds() < 0.1f ) {

        updatePlanets( ElapsedTime );
        updateSpaceships( ElapsedTime );
        // ...

        }

    // TODO CHECK FOR MODE CHANGE

    }

void GameModule::update ( sf::Event &Event ) {

    for ( auto ActiveSpaceship : Spaceships ) {

        ActiveSpaceship->update( Event ); }

    // TODO PAUSE MENU

    }

void GameModule::render ( sf::RenderWindow &Window ) {

    if ( PlayerSpaceship ) {

        sf::View View = Window.getDefaultView();
        sf::Vector2f Center = PlayerSpaceship->getPosition();

        // Center.x += ( Graphics->getWindowHeight() * 0.17f ) * cosf( PlayerSpaceship->getVelocityAngle() );
        // Center.y += ( Graphics->getWindowHeight() * 0.17f ) * sinf( PlayerSpaceship->getVelocityAngle() );

        View.setSize( Graphics->getWindowWidth(), Graphics->getWindowHeight() );
        View.setCenter( Center );
        // View.setRotation( ( PlayerSpaceship->getVelocityAngle() * 180.f / 3.14f ) + 90.f );

        Window.setView( View ); }

    for ( auto ActivePlanet : Planets ) { // TODO CHECK IF ON THE SCREEN

        ActivePlanet->render( Window ); }

    for ( auto ActiveSpaceship : Spaceships ) { // TODO CHECK IF ON THE SCREEN

        ActiveSpaceship->render( Window ); }

    }

void GameModule::destructBody ( Body * Object ) {

    Object->onDestruction();

    if ( Object == PlayerSpaceship ) {

        PlayerSpaceship = nullptr; }

    delete Object; }

float GameModule::getMinDistance ( sf::Vector2f A, sf::Vector2f B ) {

    return std::min( fabsf( A.x - B.x ), fabsf( A.y - B.y ) ); }

float GameModule::getDistance ( sf::Vector2f A, sf::Vector2f B ) {

    float DistanceX = ( A.x - B.x );
    float DistanceY = ( A.y - B.y );

    return sqrtf( DistanceX * DistanceX + DistanceY * DistanceY ); }

Body * GameModule::getRayTarget ( sf::Vector2f Position, float Angle ) {

    // TODO
    return nullptr;

    }

Body * GameModule::getAngularTarget ( sf::Vector2f Position, sf::Vector2f Angle ) {

    // TODO
    return nullptr;

    }

void GameModule::updatePlanets ( sf::Time ElapsedTime ) {

    for ( auto ActivePlanet : Planets ) {

        ActivePlanet->update( ElapsedTime ); }

    for ( auto i = Planets.begin(); i != Planets.end(); i++ ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            Planets.erase( i ); } } }

void GameModule::updateSpaceships ( sf::Time ElapsedTime ) {

    for ( auto ActiveSpaceship : Spaceships ) {

        sf::Vector2f Acceleration;

        for ( auto ActivePlanet : Planets ) {

            float Distance = getDistance( ActiveSpaceship->getPosition(), ActivePlanet->getPosition() );

            Acceleration.x -= Gravity * ActivePlanet->getMass() * ( ActiveSpaceship->getPosition().x - ActivePlanet->getPosition().x ) / Distance;
            Acceleration.y -= Gravity * ActivePlanet->getMass() * ( ActiveSpaceship->getPosition().y - ActivePlanet->getPosition().y ) / Distance;

            if ( Distance <= ( ActiveSpaceship->getRadius() + ActivePlanet->getRadius() ) ) {

                if ( true ) { // TODO SUPER ACCURATE CHECK

                    ActiveSpaceship->onCollision( ActivePlanet ); } } }

        ActiveSpaceship->updateVelocity( Acceleration, ElapsedTime ); }

    for ( auto FirstSpaceship : Spaceships ) {

        for ( auto SecondSpaceship : Spaceships ) {

            if ( FirstSpaceship == SecondSpaceship ) {

                continue; }

            float MinimumDistance = FirstSpaceship->getRadius() + SecondSpaceship->getRadius();

            if ( getMinDistance( FirstSpaceship->getPosition(), SecondSpaceship->getPosition() ) <= MinimumDistance ) {

                if ( getDistance( FirstSpaceship->getPosition(), SecondSpaceship->getPosition() ) <= MinimumDistance ) {

                    if ( true ) { // TODO SUPER ACCURATE CHECK

                        FirstSpaceship->onCollision( SecondSpaceship ); } } } } }

    // TODO MORE COLLISIONS

    for ( auto ActiveSpaceship : Spaceships ) {

        ActiveSpaceship->update( ElapsedTime );

        if ( ActiveSpaceship->onRayShot() ) {

            // TODO

            }

        if ( ActiveSpaceship->onMissileShot() ) {

            // TODO

            }

        }

    for ( auto i = Spaceships.begin(); i != Spaceships.end(); i++ ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            Spaceships.erase( i ); } } }
