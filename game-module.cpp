#include <iostream>
#include "game-module.hpp"

GameModule::GameModule ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    PlayerCount = 1;
    Gravity = 0.5f;
    DetectionDistance = 750.f;

    for ( unsigned int i = 0; i < MaximumPlayerCount; i++ ) {

        PlayerSpaceship[i] = nullptr;
        Interface[i] = new PlayerInterface ( Graphics ); }

    // TEMP ->

    auto C = new PlayerController ( );
    auto C2 = new AggressiveAIController ( );

    auto * P = new Planet ( 1000, 100 ); // density 0.0012 -> M = 0.0012 * ( 1.33f * M_PI * R * R * R )
    P->setPosition( sf::Vector2f( 400, 300 ) );
    Planets.push_back( P );

    auto * P2 = new Planet ( 5000, 100 );
    P2->setPosition( sf::Vector2f( 100, -100 ) );
    Planets.push_back( P2 );

    auto * S = new Spaceship ( 10 );
    S->setPosition( sf::Vector2f( 700, 300 ) );
    S->setSpaceshipController( C );
    S->setThrust( 250.f );
    S->setEnergy( 10000.f );
    S->setEnergyLimit( 10000.f );
    Spaceships.push_back( S );

    PlayerSpaceship[0] = S;
    Interface[0]->setSpaceship( PlayerSpaceship[0] );

    S = new Spaceship ( 10 );
    S->setPosition( sf::Vector2f( -700, -300 ) );
    S->setSpaceshipController( C2 );
    Spaceships.push_back( S );

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
        updateRayShots( ElapsedTime );
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
            View.zoom( 800.f / Graphics->getWindowHeight() );
            //View.zoom( 2.f );

            Window.setView( View ); }

        for ( auto ActiveRayShot : RayShots ) {

            ActiveRayShot->render( Window ); }

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

    const float DistanceX = ( A.x - B.x );
    const float DistanceY = ( A.y - B.y );

    return sqrtf( DistanceX * DistanceX + DistanceY * DistanceY ); }

Spaceship * GameModule::getRayTarget ( Spaceship * Requester, sf::Vector2f &Intersection ) {

    Spaceship * Target = nullptr;
    float TargetDistance = 1000000.f;
    sf::Vector2f TargetIntersection = Requester->getPosition();

    Ray RayShot ( Requester->getPosition(), Requester->getVelocityAngle() );
    float Distance;

    for ( auto ActiveSpaceship : Spaceships ) {

        if ( ActiveSpaceship == Requester ) {

            continue; }

        if ( RayShot.getIntersection( ActiveSpaceship->getPosition(), ActiveSpaceship->getRadius(), Intersection, Distance ) ) {

            if ( Distance < TargetDistance ) {

                Target = ActiveSpaceship;
                TargetDistance = Distance;
                TargetIntersection = Intersection; } } }

    for ( auto ActivePlanet : Planets ) {

        if ( RayShot.getIntersection( ActivePlanet->getPosition(), ActivePlanet->getRadius(), Intersection, Distance ) ) {

            if ( Distance < TargetDistance ) {

                Target = nullptr;
                TargetDistance = Distance;
                TargetIntersection = Intersection; } } }

    // TODO ASTEROIDS

    Intersection = TargetIntersection;

    return Target; }

Spaceship * GameModule::getAngularTarget ( Spaceship * Requester, float MaximumAngle, float &Distance, float &Angle ) {

    float TargetDistance = 1000000.f;
    Spaceship * Target = nullptr;
    Angle = PI;

    for ( auto ActiveSpaceship : Spaceships ) {

        if ( ActiveSpaceship == Requester ) {

            continue; }

        if ( true ) { // TODO FRIENDLY FIRE

            bool ActiveSpaceshipIsPlayer = false;

            for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                if ( ActiveSpaceship == PlayerSpaceship[i] ) {

                    ActiveSpaceshipIsPlayer = true;

                    break; } }

            if ( !ActiveSpaceshipIsPlayer ) {

                continue; } }

        if ( getMinDistance( Requester->getPosition(), ActiveSpaceship->getPosition() ) > DetectionDistance ) {

            continue; }

        float AngleDifference = atan2f( ActiveSpaceship->getPosition().x - Requester->getPosition().x, ActiveSpaceship->getPosition().y - Requester->getPosition().y );

        AngleDifference = PI / 2.f - AngleDifference;
        AngleDifference = Requester->normalizeAngle( Requester->getVelocityAngle() - AngleDifference );

        if ( fabsf( AngleDifference ) < ( 0.5f * MaximumAngle ) ) {

            Distance = getDistance( Requester->getPosition(), ActiveSpaceship->getPosition() );

            if ( Distance <= DetectionDistance && Distance < TargetDistance ) {

                Target = ActiveSpaceship;
                TargetDistance = Distance;
                Angle = AngleDifference; } } }

    if ( Target ) {

        Distance = TargetDistance; }

    else {

        Distance = 1000000.f; }

    return Target; }

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

        bool ActiveSpaceshipIsAI = true;

        for ( unsigned int i = 0; i < PlayerCount; i++ ) {

            if ( PlayerSpaceship[i] == ActiveSpaceship ) {

                ActiveSpaceshipIsAI = false;

                break; } }

        if ( ActiveSpaceshipIsAI ) {

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

        bool ActiveSpaceshipIsPlayer = false;

        for ( unsigned int i = 0; i < PlayerCount; i++ ) {

            if ( ActiveSpaceship == PlayerSpaceship[i] ) {

                ActiveSpaceshipIsPlayer = true;

                break; } }

        if ( !ActiveSpaceshipIsPlayer ) { // TODO  || true

            float Distance, Angle;
            Spaceship * Target = getAngularTarget( ActiveSpaceship, 2.f * PI / 3.f, Distance, Angle );

            if ( Target ) {

                ( (AIController*) ActiveSpaceship->getSpaceshipController() )->setTargetIn120Degrees( Target, Distance, Angle );
                Target = getAngularTarget( ActiveSpaceship, PI / 3.f, Distance, Angle );

                if ( Target ) {

                    ( (AIController*) ActiveSpaceship->getSpaceshipController() )->setTargetIn60Degrees( Target, Distance, Angle );
                    Target = getAngularTarget( ActiveSpaceship, PI / 6.f, Distance, Angle );

                    if ( Target ) {

                        ( (AIController*) ActiveSpaceship->getSpaceshipController() )->setTargetIn30Degrees( Target, Distance, Angle ); }

                    else {

                        ( (AIController*) ActiveSpaceship->getSpaceshipController() )->setTargetIn30Degrees( nullptr ); } }

                else {

                    ( (AIController*) ActiveSpaceship->getSpaceshipController() )->setTargetIn60Degrees( nullptr ); } }

            else {

                ( (AIController*) ActiveSpaceship->getSpaceshipController() )->setTargetIn120Degrees( nullptr ); } }

        ActiveSpaceship->update( ElapsedTime );

        if ( ActiveSpaceship->onRayShot() ) {

            sf::Vector2f Intersection;
            Spaceship * Target = getRayTarget( ActiveSpaceship, Intersection );
            auto RayShot = new Ray ( ActiveSpaceship->getPosition(), ActiveSpaceship->getVelocityAngle() );

            if ( Target ) {

                RayShot->enableRendering( Intersection.x );
                Target->updateHealth( - 0.2f *  ActiveSpaceship->getRayPower() );

                std::cout << Target->getHealth() << std::endl;

                }

            else if ( Intersection != ActiveSpaceship->getPosition() ) {

                RayShot->enableRendering( Intersection.x ); }

            else {

                RayShot->enableRendering(); }

            RayShots.push_back( RayShot ); }

        if ( ActiveSpaceship->onMissileShot() ) { std::cout << "MISSILE SHOT\n";

            // TODO

            }

        }

    // TODO MISSILES

    for ( auto i = Spaceships.begin(); i != Spaceships.end(); i++ ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            i = Spaceships.erase( i ); } } }

void GameModule::updateRayShots ( sf::Time ElapsedTime ) {

    for ( auto ActiveRayShot : RayShots ) {

        ActiveRayShot->update( ElapsedTime ); }

    for ( auto i = RayShots.begin(); i != RayShots.end(); i++ ) {

        if ( !(*i)->isRenderingEnabled() ) {

            delete (*i);
            i = RayShots.erase( i ); } } }