#include <iostream>
#include "game-module.hpp"

GameModule::GameModule ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    PlayerCount = 1;
    Gravity = 1.f;

    for ( unsigned int i = 0; i < MaximumPlayerCount; i++ ) {

        PlayerSpaceship[i] = nullptr;
        Interface[i] = new PlayerInterface ( Graphics ); }

    // TEMP ->

    auto C = new AIController ( );

    auto * P = new Planet ( 5000, 100 ); // density 0.0012 -> M = ( 1.33f * M_PI * R * R * R )
    P->setPosition( sf::Vector2f( 400, 300 ) );
    Planets.push_back( P );

    auto * P2 = new Planet ( 5000, 100 );
    P2->setPosition( sf::Vector2f( 100, -100 ) );
    Planets.push_back( P2 );

    auto * S = new Spaceship ( 10 );
    S->setPosition( sf::Vector2f( 700, 300 ) );
    S->setSpaceshipController( C );
    Spaceships.push_back( S );
    PlayerSpaceship[0] = S;

    PlayerSpaceship[0]->setEnergy( 1000.f );
    Interface[0]->setSpaceship( PlayerSpaceship[0] );

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

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        Interface[i]->update(); }

    // TODO CHECK FOR MODE CHANGE

    }

void GameModule::update ( sf::Event &Event ) {

    for ( auto ActiveSpaceship : Spaceships ) {

        ActiveSpaceship->update( Event ); }

    // TODO PAUSE MENU

    }

void GameModule::render ( sf::RenderWindow &Window ) {

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        float ViewWidth = Graphics->getWindowWidth();
        float ViewHeight = Graphics->getWindowHeight();

        // TODO SET VIEWPORT

        Interface[0]->setViewport( sf::FloatRect( 0.f, 0.f, ViewWidth, ViewHeight ) );
        Interface[0]->setOrientation( PlayerInterface::Orientations::Left );

        if ( PlayerSpaceship[i] ) {

            sf::View View = Window.getDefaultView();
            sf::Vector2f Center = PlayerSpaceship[i]->getPosition();

            // Center.x += ( ViewWidth * 0.17f ) * cosf( PlayerSpaceship->getVelocityAngle() );
            // Center.y += ( ViewHeight * 0.17f ) * sinf( PlayerSpaceship->getVelocityAngle() );

            View.setCenter( Center );
            View.setSize( ViewWidth, ViewHeight );
            // View.setRotation( ( PlayerSpaceship->getVelocityAngle() * 180.f / 3.14f ) + 90.f );
            View.zoom( 600.f / Graphics->getWindowHeight() );

            Window.setView( View ); }

        for ( auto ActivePlanet : Planets ) { // TODO CHECK IF ON THE SCREEN

            ActivePlanet->render( Window ); }

        for ( auto ActiveSpaceship : Spaceships ) { // TODO CHECK IF ON THE SCREEN

            ActiveSpaceship->render( Window ); }


        Interface[i]->render( Window );

        } }

void GameModule::destructBody ( Body * Object ) {

    Object->onDestruction();

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( Object == PlayerSpaceship[i] ) {

            PlayerSpaceship[i] = nullptr;
            Interface[i]->setSpaceship( nullptr ); } }

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

        sf::Vector2f AccelerationSum;

        float ClosestBodyDistance = 1000000.f;
        sf::Vector2f ClosestBodyAcceleration;

        for ( auto ActivePlanet : Planets ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveSpaceship->getPosition(), ActivePlanet->getPosition() );

            Acceleration.x -= Gravity * ActivePlanet->getMass() * ( ActiveSpaceship->getPosition().x - ActivePlanet->getPosition().x ) / ( Distance * Distance );
            Acceleration.y -= Gravity * ActivePlanet->getMass() * ( ActiveSpaceship->getPosition().y - ActivePlanet->getPosition().y ) / ( Distance * Distance );

            if ( ( Distance - ActivePlanet->getRadius() ) < ClosestBodyDistance ) {

                ClosestBodyDistance = Distance - ActivePlanet->getRadius();
                ClosestBodyAcceleration = Acceleration; }

            AccelerationSum += Acceleration;

            if ( Distance <= ( ActiveSpaceship->getRadius() + ActivePlanet->getRadius() ) ) {

                if ( true ) { // TODO SUPER ACCURATE CHECK

                    ActiveSpaceship->onCollision( ActivePlanet ); } } }

        // TODO ASTEROIDS

        bool AI = true;
        /*
        for ( unsigned int i = 0; i < PlayerCount; i++ ) {

            if ( PlayerSpaceship[i] == ActiveSpaceship ) {

                AI = false; } }
        */
        if ( AI ) {

            ( (AIController*) ActiveSpaceship->getSpaceshipController() )->setClosestBodyDistance( ClosestBodyDistance );
            ( (AIController*) ActiveSpaceship->getSpaceshipController() )->setClosestBodyAcceleration( ClosestBodyAcceleration ); }

        ActiveSpaceship->updateVelocity( AccelerationSum, ElapsedTime ); }

    for ( auto FirstSpaceship : Spaceships ) {

        for ( auto SecondSpaceship : Spaceships ) {

            if ( FirstSpaceship == SecondSpaceship ) {

                continue; }

            float MinimumDistance = FirstSpaceship->getRadius() + SecondSpaceship->getRadius();

            if ( getMinDistance( FirstSpaceship->getPosition(), SecondSpaceship->getPosition() ) <= MinimumDistance ) {

                if ( getDistance( FirstSpaceship->getPosition(), SecondSpaceship->getPosition() ) <= MinimumDistance ) {

                    if ( true ) { // TODO SUPER ACCURATE CHECK

                        FirstSpaceship->onCollision( SecondSpaceship ); } } } } }

    // TODO POWER UPS

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
            i = Spaceships.erase( i ); } } }
