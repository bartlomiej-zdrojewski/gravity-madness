#include <iostream>
#include "game-module.hpp"

GameModule::GameModule ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    PlayerCount = 1;
    Gravity = 1.f;
    DetectionDistance = 750.f;
    AreaRadius = 1500.f;
    AsteroidCount = 5;

    AsteroidPauseDuration = sf::seconds( 5.f );
    AsteroidPauseTime = sf::seconds( 0.f );

    for ( unsigned int i = 0; i < MaximumPlayerCount; i++ ) {

        PlayerSpaceship[i] = nullptr;
        Interface[i] = new PlayerInterface ( Graphics ); }

    // TEMP ->

    auto C = new PlayerController ( );
    auto C2 = new AggressiveAIController ( );

    auto * P = new Planet ( 5000, 100 ); // density 0.0012 -> M = 0.0012 * ( 1.33f * M_PI * R * R * R )
    P->setPosition( sf::Vector2f( 400, 300 ) );
    Planets.push_back( P );

    auto * P2 = new Planet ( 5000, 100 );
    P2->setPosition( sf::Vector2f( 100, -100 ) );
    Planets.push_back( P2 );

    auto * S = new Spaceship ( 10 );
    S->setPosition( sf::Vector2f( 700, 300 ) );
    S->setController( C );
    S->setThrust( 250.f );
    S->setEnergy( 10000.f );
    S->setEnergyLimit( 10000.f );
    Spaceships.push_back( S );

    PlayerSpaceship[0] = S;
    Interface[0]->setSpaceship( PlayerSpaceship[0] );

    S = new Spaceship ( 10 );
    S->setPosition( sf::Vector2f( -700, -300 ) );
    S->setController( C2 );
    S->setEnergy( 10000.f );
    S->setEnergyLimit( 10000.f );
    Spaceships.push_back( S );

    auto C3 = new AggressiveAIController ( );
    S = new Spaceship ( 10 );
    S->setPosition( sf::Vector2f( -700, -200 ) );
    S->setController( C3 );
    //Spaceships.push_back( S );

    // -> TEMP

    auto * PS = new ParticleSystem ( );
    PS->setOriginPosition( sf::Vector2f( 750, 300 ) );
    PS->generateParticles( 10000 );
    //ParticleSystems.push_back( PS );

    auto * A = new Asteroid ( 100, 15 );
    A->setPosition( sf::Vector2f( 900, 200 ) );
    A->setVelocity( sf::Vector2f( -0, 0 ) );
    Asteroids.push_back( A );

    prepareAreaLimit();

    }

GameModule::~GameModule ( ) {

    // TODO RELEASE MEMORY

    }

void GameModule::update ( ) {

    sf::Time ElapsedTime = Clock.restart();

    if ( ElapsedTime.asSeconds() < 0.1f ) {

        updatePlanets( ElapsedTime );
        updateAsteroids( ElapsedTime );
        updateSpaceships( ElapsedTime );
        updateRayShots( ElapsedTime );
        updateMissiles( ElapsedTime );
        updatePowerUps( ElapsedTime );
        updateParticleSystems( ElapsedTime ); }

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        Interface[i]->update( ElapsedTime ); }

    // TODO CHECK FOR MODE CHANGE

    }

void GameModule::update ( sf::Event &Event ) {

    for ( auto ActiveSpaceship : Spaceships ) {

        ActiveSpaceship->update( Event ); }

    // TODO PAUSE MENU

    }

void GameModule::render ( sf::RenderWindow &Window ) { // TODO VIEW FOR EACH PLAYER

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        float ViewWidth = Graphics->getWindowWidth();
        float ViewHeight = Graphics->getWindowHeight();

        // TODO SET VIEWPORT
        Interface[0]->setViewport( sf::FloatRect( 0.f, 0.f, ViewWidth, ViewHeight ) );

        if ( PlayerSpaceship[i] ) {

            sf::View View = Window.getDefaultView();
            sf::Vector2f Center = PlayerSpaceship[i]->getPosition();

            // Center.x += ( ViewWidth * 0.17f ) * cosf( PlayerSpaceship->getVelocityAngle() );
            // Center.y += ( ViewHeight * 0.17f ) * sinf( PlayerSpaceship->getVelocityAngle() );

            View.setCenter( Center );
            View.setSize( ViewWidth, ViewHeight );
            // View.setRotation( ( PlayerSpaceship->getVelocityAngle() * 180.f / 3.14f ) + 90.f );
            View.zoom( 800.f / Graphics->getWindowHeight() );

            Window.setView( View ); }

        // TODO MOVE 'SET VIEW' HERE

        renderAreaLimit( Window );

        for ( auto ActiveParticleSystem : ParticleSystems ) {

            if ( isOnScreen( ActiveParticleSystem->getInfluenceArea() ) ) {

                ActiveParticleSystem->render( Window ); } }

        for ( auto ActiveRayShot : RayShots ) {

            ActiveRayShot->render( Window ); }

        for ( auto ActivePlanet : Planets ) {

            if ( isOnScreen( ActivePlanet->getPosition(), ActivePlanet->getRadius() ) ) {

                ActivePlanet->render( Window ); } }

        for ( auto ActiveAsteroid : Asteroids ) {

            if ( isOnScreen( ActiveAsteroid->getPosition(), ActiveAsteroid->getRadius() ) ) {

                ActiveAsteroid->render( Window ); } }

        for ( auto ActiveSpaceship : Spaceships ) {

            if ( isOnScreen( ActiveSpaceship->getPosition(), ActiveSpaceship->getInfluenceRadius() ) ) {

                ActiveSpaceship->render( Window ); } }

        // TODO MISSILES
        // TODO POWER UPS

        Interface[i]->render( Window ); } }

void GameModule::destructBody ( Body * Object ) {

    ParticleSystem * Explosion = Object->onDestruction();

    if ( Explosion ) {

        ParticleSystems.push_back( Explosion ); }

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( Object == PlayerSpaceship[i] ) {

            Interface[i]->update( sf::seconds( 0.01f ) );

            PlayerSpaceship[i] = nullptr;
            Interface[i]->setSpaceship( nullptr );

            break; } }

    delete Object; }

float GameModule::getMinDistance ( sf::Vector2f A, sf::Vector2f B ) {

    return std::min( fabsf( A.x - B.x ), fabsf( A.y - B.y ) ); }

float GameModule::getDistance ( sf::Vector2f A, sf::Vector2f B ) {

    const float DistanceX = ( A.x - B.x );
    const float DistanceY = ( A.y - B.y );

    return sqrtf( DistanceX * DistanceX + DistanceY * DistanceY ); }

float GameModule::getRandomFloat ( ) {

    return ( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ); }

bool GameModule::isPlayer ( Spaceship * MySpaceship ) {

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( MySpaceship == PlayerSpaceship[i] ) {

            return true; } }

    return false; }

bool GameModule::isOnScreen ( sf::Vector2f Center, float Radius ) {

    // TODO
    return true;

    }

bool GameModule::isOnScreen ( sf::FloatRect Area ) {

    // TODO
    return true;

    }

Spaceship * GameModule::getRayTarget ( Spaceship * Requester, sf::Vector2f &Intersection ) {

    Spaceship * Target = nullptr;
    float TargetDistance = 1000000.f;
    sf::Vector2f TargetIntersection = Requester->getPosition();

    float Distance;
    Ray RayShot ( Requester->getPosition(), Requester->getVelocityAngle() );

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

    for ( auto ActiveAsteroid : Asteroids ) {

        if ( RayShot.getIntersection( ActiveAsteroid->getPosition(), ActiveAsteroid->getRadius(), Intersection, Distance ) ) {

            if ( Distance < TargetDistance ) {

                Target = nullptr;
                TargetDistance = Distance;
                TargetIntersection = Intersection; } } }

    // TODO MISSILES

    Intersection = TargetIntersection;

    return Target; }

Spaceship * GameModule::getAngularTarget ( Spaceship * Requester, float MaximumAngle, float &Distance, float &Angle ) {

    float TargetDistance = 1000000.f;
    Spaceship * Target = nullptr;
    Angle = PI;

    for ( auto ActiveSpaceship : Spaceships ) {

        if ( ActiveSpaceship == Requester ) {

            continue; }

        if ( !isPlayer( ActiveSpaceship ) ) {

            continue; }

        if ( getMinDistance( Requester->getPosition(), ActiveSpaceship->getPosition() ) > DetectionDistance ) {

            continue; }

        float AngleDifference = atan2f( ActiveSpaceship->getPosition().y - Requester->getPosition().y, ActiveSpaceship->getPosition().x - Requester->getPosition().x );
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

void GameModule::updateAsteroids ( sf::Time ElapsedTime ) {

    AsteroidPauseTime -= ElapsedTime;

    if ( Asteroids.size() < AsteroidCount && AsteroidPauseTime.asSeconds() <= 0.f ) {

        AsteroidPauseTime = AsteroidPauseDuration;

        float Mass = 8.f + getRandomFloat() * 12.f;
        float Radius = Mass * ( 0.75f + getRandomFloat() * 0.5f );

        auto * NewAsteroid = new Asteroid ( Mass, Radius );

        float Angle = ( - PI ) + getRandomFloat() * ( 2.f * PI ) + ( - PI / 6.f ) + getRandomFloat() * ( PI / 3.f );
        float Distance = AreaRadius + 1000.f;

        NewAsteroid->setPosition( sf::Vector2f( Distance * cosf( Angle ), Distance * sinf( Angle ) ) );
        NewAsteroid->setVelocity( sf::Vector2f( 50.f * cosf( Angle - PI ), 50.f * sinf( Angle - PI ) ) );

        Asteroids.push_back( NewAsteroid ); }

    for ( auto ActiveAsteroid : Asteroids ) {

        for ( auto ActivePlanet : Planets ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveAsteroid->getPosition(), ActivePlanet->getPosition() );

            Acceleration.x -= Gravity * ActivePlanet->getMass() * ( ActiveAsteroid->getPosition().x - ActivePlanet->getPosition().x ) / ( Distance * Distance );
            Acceleration.y -= Gravity * ActivePlanet->getMass() * ( ActiveAsteroid->getPosition().y - ActivePlanet->getPosition().y ) / ( Distance * Distance );

            ActiveAsteroid->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveAsteroid->getRadius() + ActivePlanet->getRadius() ) ) {

                if ( true ) { // TODO SUPER ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveAsteroid->onCollision( ActivePlanet );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        for ( auto ActiveSpaceship : Spaceships ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveAsteroid->getPosition(), ActiveSpaceship->getPosition() );

            Acceleration.x -= Gravity * ActiveSpaceship->getMass() * ( ActiveAsteroid->getPosition().x - ActiveSpaceship->getPosition().x ) / ( Distance * Distance );
            Acceleration.y -= Gravity * ActiveSpaceship->getMass() * ( ActiveAsteroid->getPosition().y - ActiveSpaceship->getPosition().y ) / ( Distance * Distance );

            ActiveAsteroid->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveAsteroid->getRadius() + ActiveSpaceship->getRadius() ) ) {

                if ( true ) { // TODO SUPER ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveAsteroid->onCollision( ActiveSpaceship );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        float DistanceFromOrigin = getDistance( sf::Vector2f ( 0.f, 0.f ), ActiveAsteroid->getPosition() );

        if ( DistanceFromOrigin < AreaRadius ) {

            ActiveAsteroid->resetExistenceTime(); } }

    for ( auto FirstAsteroid : Asteroids ) {

        for ( auto SecondAsteroid : Asteroids ) {

            if ( FirstAsteroid == SecondAsteroid ) {

                continue; }

            float MinimumDistance = FirstAsteroid->getRadius() + SecondAsteroid->getRadius();

            if ( getMinDistance( FirstAsteroid->getPosition(), SecondAsteroid->getPosition() ) <= MinimumDistance ) {

                if ( getDistance( FirstAsteroid->getPosition(), SecondAsteroid->getPosition() ) <= MinimumDistance ) {

                    if ( true ) { // TODO SUPER ACCURATE CHECK

                        ParticleSystem * Explosion = FirstAsteroid->onCollision( SecondAsteroid );

                        if ( Explosion ) {

                            ParticleSystems.push_back( Explosion ); } } } } } }

    for ( auto ActiveAsteroid : Asteroids ) {

        ActiveAsteroid->update( ElapsedTime ); }

    for ( auto i = Asteroids.begin(); i != Asteroids.end(); i++ ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            i = Asteroids.erase( i ); } } }

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

                    ParticleSystem * Explosion = ActiveSpaceship->onCollision( ActivePlanet );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        for ( auto ActiveAsteroid : Asteroids ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveSpaceship->getPosition(), ActiveAsteroid->getPosition() );

            Acceleration.x -= Gravity * ActiveAsteroid->getMass() * ( ActiveSpaceship->getPosition().x - ActiveAsteroid->getPosition().x ) / ( Distance * Distance );
            Acceleration.y -= Gravity * ActiveAsteroid->getMass() * ( ActiveSpaceship->getPosition().y - ActiveAsteroid->getPosition().y ) / ( Distance * Distance );

            if ( ( Distance - ActiveAsteroid->getRadius() ) < ClosestBodyDistance ) {

                ClosestBodyDistance = Distance - ActiveAsteroid->getRadius();
                ClosestBodyAcceleration = Acceleration; }

            AccelerationSum += Acceleration;

            if ( Distance <= ( ActiveSpaceship->getRadius() + ActiveAsteroid->getRadius() ) ) {

                if ( true ) { // TODO SUPER ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveSpaceship->onCollision( ActiveAsteroid );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        if ( !isPlayer( ActiveSpaceship ) && ActiveSpaceship->getController() != nullptr ) {

            ( (AIController*) ActiveSpaceship->getController() )->setClosestBodyDistance( ClosestBodyDistance );
            ( (AIController*) ActiveSpaceship->getController() )->setClosestBodyAcceleration( ClosestBodyAcceleration ); }

        if ( fabsf( ActiveSpaceship->getPosition().x ) > ( SQRT2_2ND * AreaRadius ) || fabsf( ActiveSpaceship->getPosition().y ) > ( SQRT2_2ND * AreaRadius ) ) {

            float Distance = getDistance( sf::Vector2f ( 0.f, 0.f ), ActiveSpaceship->getPosition() );

            if ( Distance > ( AreaRadius - 0.3f * DetectionDistance ) && !isPlayer( ActiveSpaceship ) && ActiveSpaceship->getController() != nullptr ) {

                ( (AIController*) ActiveSpaceship->getController() )->enableLimitPanic(); }

            if ( Distance > AreaRadius ) {

                ActiveSpaceship->updateHealth( - 5.f * ElapsedTime.asSeconds() ); } }

        ActiveSpaceship->updateVelocity( AccelerationSum, ElapsedTime ); }

    for ( auto FirstSpaceship : Spaceships ) {

        for ( auto SecondSpaceship : Spaceships ) {

            if ( FirstSpaceship == SecondSpaceship ) {

                continue; }

            float MinimumDistance = FirstSpaceship->getRadius() + SecondSpaceship->getRadius();

            if ( getMinDistance( FirstSpaceship->getPosition(), SecondSpaceship->getPosition() ) <= MinimumDistance ) {

                if ( getDistance( FirstSpaceship->getPosition(), SecondSpaceship->getPosition() ) <= MinimumDistance ) {

                    if ( true ) { // TODO SUPER ACCURATE CHECK

                        ParticleSystem * Explosion = FirstSpaceship->onCollision( SecondSpaceship );

                        if ( Explosion ) {

                            ParticleSystems.push_back( Explosion ); } } } } } }

    for ( auto ActiveSpaceship : Spaceships ) {

        if ( !isPlayer( ActiveSpaceship ) && ActiveSpaceship->getController() != nullptr ) {

            float Distance, Angle;
            Spaceship * Target = getAngularTarget( ActiveSpaceship, 2.f * PI / 3.f, Distance, Angle );

            if ( Target ) {

                ( (AIController*) ActiveSpaceship->getController() )->setTargetIn120Degrees( Target, Distance, Angle );
                Target = getAngularTarget( ActiveSpaceship, PI / 3.f, Distance, Angle );

                if ( Target ) {

                    ( (AIController*) ActiveSpaceship->getController() )->setTargetIn60Degrees( Target, Distance, Angle );
                    Target = getAngularTarget( ActiveSpaceship, PI / 6.f, Distance, Angle );

                    if ( Target ) {

                        ( (AIController*) ActiveSpaceship->getController() )->setTargetIn30Degrees( Target, Distance, Angle ); }

                    else {

                        ( (AIController*) ActiveSpaceship->getController() )->setTargetIn30Degrees( nullptr ); } }

                else {

                    ( (AIController*) ActiveSpaceship->getController() )->setTargetIn60Degrees( nullptr ); } }

            else {

                ( (AIController*) ActiveSpaceship->getController() )->setTargetIn120Degrees( nullptr ); }

            // TODO SHOW AI POWER UPS

            }

        ActiveSpaceship->update( ElapsedTime );

        if ( ActiveSpaceship->onRayShot() ) {

            sf::Vector2f Intersection;
            Spaceship * Target = getRayTarget( ActiveSpaceship, Intersection );
            auto RayShot = new Ray ( ActiveSpaceship->getPosition(), ActiveSpaceship->getVelocityAngle() );

            if ( Target ) {

                Target->updateHealth( - 0.2f *  ActiveSpaceship->getRayPower() );

                if ( isPlayer( Target ) ) {

                    // TODO SCREEN EFFECT IN INTERFACE

                    }

                else if ( ActiveSpaceship->getController() != nullptr ) {

                    ( (AIController*) Target->getController() )->enableShotPanic(); }

                // TODO PARTICLE EFFECT ON HIT

                }

            // TODO IF MISSILE

            if ( Intersection != ActiveSpaceship->getPosition() ) {

                RayShot->enableRendering( Intersection.x ); }

            else {

                RayShot->enableRendering(); }

            RayShots.push_back( RayShot ); }

        if ( ActiveSpaceship->onMissileShot() ) { std::cout << "MISSILE SHOT\n";

            // TODO

            }

        }

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

void GameModule::updateMissiles ( sf::Time ElapsedTime ) {

    // TODO

    }

void GameModule::updatePowerUps ( sf::Time ElapsedTime ) {

    // TODO

    }

void GameModule::updateParticleSystems ( sf::Time ElapsedTime ) {

    for ( auto ActiveParticleSystem : ParticleSystems ) {

        ActiveParticleSystem->update( ElapsedTime ); }

    for ( auto i = ParticleSystems.begin(); i != ParticleSystems.end(); i++ ) {

        if ( (*i)->getParticleCount() == 0 ) {

            delete (*i);
            i = ParticleSystems.erase( i ); } } }

void GameModule::prepareAreaLimit ( ) {

    AreaLimit.resize( 1000 );

    for ( unsigned int i = 0; i < 1000; i++ ) {

        AreaLimit[i].position.x = AreaRadius * cosf( 2.f * PI * ( i / 1000.f ) );
        AreaLimit[i].position.y = AreaRadius * sinf( 2.f * PI * ( i / 1000.f ) );
        AreaLimit[i].color = sf::Color::White; } }

void GameModule::renderAreaLimit ( sf::RenderWindow &Window ) {

    Window.draw( &AreaLimit[0], AreaLimit.size(), sf::Lines ); }