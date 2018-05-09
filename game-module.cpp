#include "game-module.hpp"

GameModule::GameModule ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    reset(); }

GameModule::~GameModule ( ) {

    reset(); }

void GameModule::setGameplay ( GameplaySettings * Gameplay ) {

    reset();

    this->Gameplay = Gameplay;
    EndingCondition = false;
    AreaRadius = Gameplay->getAreaSize();
    PlayerCount = Gameplay->getPlayerCount();
    AsteroidCount = Gameplay->getAsteroidCount(); // TODO SHOULD I MAKE IT DEPENDENT FROM RADIUS?
    PowerUpPauseDuration = sf::seconds( 60.f / ( powf( AreaRadius / 1000.f, 2 ) * Gameplay->getSpaceshipCount() ) );

    prepareAreaLimit();

    unsigned int Attempts = 1000;
    auto PlanetCount = (unsigned int) ( powf( AreaRadius / 1000.f, 2 ) * 2.f );

    for ( unsigned int i = 0; i < PlanetCount && Attempts > 0; i++ ) {

        float Mass = 3000.f + getRandomFloat() * 4000.f;
        float Radius = sqrtf( Mass / PI / 0.075f );

        auto NewPlanet = new Planet ( Mass, Radius );
        sf::Vector2f Position ( 1000000.f, 1000000.f );

        while ( Attempts > 0 && Position == sf::Vector2f( 1000000.f, 1000000.f ) ) {

            float Angle = getRandomFloat() * ( 2.f * PI );
            float Module = getRandomFloat() * ( AreaRadius - 500.f - Radius );

            Position.x = Module * cosf( Angle );
            Position.y = Module * sinf( Angle );

            for ( auto ActivePlanet : Planets ) {

                float MinimumDistance = 250.f + Radius + ActivePlanet->getRadius();

                if ( getMinDistance( Position, ActivePlanet->getPosition() ) <= MinimumDistance ) {

                    if ( getDistance(Position, ActivePlanet->getPosition() ) <= MinimumDistance ) {

                        Position = sf::Vector2f( 1000000.f, 1000000.f );

                        break; } } } }

        if ( Attempts > 0 ) {

            NewPlanet->setPosition( Position );

            Planets.push_back( NewPlanet ); } }

    auto * SpaceshipOrder = new unsigned int [ Gameplay->getSpaceshipCount() ];

    for ( unsigned int i = 0; i < Gameplay->getSpaceshipCount(); i++ ) {

        SpaceshipOrder[i] = i; }

    std::random_shuffle( &SpaceshipOrder[0], &SpaceshipOrder[ Gameplay->getSpaceshipCount() ] );

    for ( unsigned int i = 0; i < Gameplay->getSpaceshipCount(); i++ ) {

        auto Prototype = Gameplay->getSpaceshipPrototype( i );
        auto * NewSpaceship = new Spaceship ( Prototype.Mass, Prototype.Radius );

        NewSpaceship->setHealthLimit( Prototype.HealthLimit );
        NewSpaceship->setHealth( Prototype.HealthLimit );
        NewSpaceship->setHealthRestoration( Prototype.HealthRestoration );
        NewSpaceship->setEnergyLimit( Prototype.EnergyLimit );
        NewSpaceship->setEnergy( Prototype.EnergyLimit );
        NewSpaceship->setEnergyRestoration( Prototype.EnergyRestoration );
        NewSpaceship->setThrust( Prototype.Thrust );
        NewSpaceship->setSuppressingFactor( Prototype.SuppressingFactor );
        NewSpaceship->setRayPower( Prototype.RayPower );
        NewSpaceship->setMissileLimit( Prototype.MissileLimit );
        NewSpaceship->setMissileCount( Prototype.MissileCount );

        float PositionAngle = ( (float) SpaceshipOrder[i] / (float) Gameplay->getSpaceshipCount() ) * ( 2.f * PI );
        float PositionModule = AreaRadius - 200.f;
        float VelocityAngle = PI + PositionAngle;
        float VelocityModule = 25.f;

        NewSpaceship->setPosition( sf::Vector2f( PositionModule * cosf( PositionAngle ), PositionModule * sinf( PositionAngle  ) ) );
        NewSpaceship->setVelocity( sf::Vector2f( VelocityModule * cosf( VelocityAngle ), VelocityModule * sinf( VelocityAngle  ) ) );

        if ( i < PlayerCount ) {

            PlayerSpaceship[i] = NewSpaceship;
            PlayerSpaceship[i]->setController( new PlayerController ( ) ); }

        else {

            switch ( Gameplay->getAIPersonality() ) {

                case GameplaySettings::AIPersonalities::Random: {

                    auto Personality = (unsigned int) ( rand() % 3 );

                    if ( Personality == 0 ) {

                        NewSpaceship->setController( new AggressiveAIController ( ) ); }

                    else if ( Personality == 1 ) {

                        // TODO REASONABLE PERSONALITY

                        }

                    else {

                        // TODO PASSIVE PERSONALITY

                        }

                    break; }

                case GameplaySettings::AIPersonalities::Aggressive: {

                    NewSpaceship->setController( new AggressiveAIController ( ) );

                    break; }

                // TODO OTHR PERSONALITIES

                default: {

                    NewSpaceship->setController( new AIController ( ) );

                    break; } } }

        Spaceships.push_back( NewSpaceship ); }

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        Interface[i] = new PlayerInterface ( Graphics );
        Interface[i]->setSpaceship( PlayerSpaceship[i] ); }

    delete SpaceshipOrder; }

GameplaySettings * GameModule::getGameplay ( ) {

    return Gameplay; }

void GameModule::update ( ) {

    sf::Time ElapsedTime = Clock.restart();

    if ( ElapsedTime.asSeconds() < 0.1f ) {

        updatePlanets( ElapsedTime );
        updateAsteroids( ElapsedTime );
        updateSpaceships( ElapsedTime );
        updateRayShots( ElapsedTime );
        updateMissiles( ElapsedTime );
        updatePowerUps( ElapsedTime );
        updateParticleSystems( ElapsedTime );

        updateViews();

        for ( unsigned int i = 0; i < PlayerCount; i++ ) {

            Interface[i]->setViewport( Views[i].getViewport() );

            if ( PlayerSpaceship[i] ) {

                Views[i].setCenter( PlayerSpaceship[i]->getPosition() ); }

            else if ( !Interface[i]->isFadedOut() ) {

                Views[i].setCenter( Views[i].getCenter() + PlayerFinalVelocity[i] * ElapsedTime.asSeconds() ); }

            Interface[i]->update( ElapsedTime ); } }

    if ( Gameplay && !EndingCondition ) {

        bool AlivePlayer = false;

        for ( unsigned int i = 0; i < PlayerCount; i++ ) {

            if ( PlayerSpaceship[i] != nullptr ) {

                AlivePlayer = true;

                break; } }

        if ( !AlivePlayer ) {

            EndingCondition = true; }

        else {

            switch ( Gameplay->getEndingCondition() ) {

                // TODO

                default: {

                    break; } } }

        if ( EndingCondition ) {

            auto * ScoreCopy = new unsigned int [ PlayerCount ];

            for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                ScoreCopy[i] = PlayerScore[i];

                if ( !Interface[i]->isFadedOut() ) {

                    Interface[i]->beginFadeOut(); } }

            Gameplay->setScore( ScoreCopy ); } } }

void GameModule::update ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        if ( Event.key.code == sf::Keyboard::Escape ) {

            Pause = true;

            return; } }

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        PlayerSpaceship[i]->update( Event ); } }

void GameModule::render ( sf::RenderWindow &Window ) {

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        Window.setView( Views[i] );

        if ( PlayerSpaceship[i] || !Interface[i]->isFadedOut() ) {

            renderAreaLimit( Window );

            for ( auto ActiveParticleSystem : ParticleSystems ) {

                if ( isOnScreen( ActiveParticleSystem->getInfluenceArea() ) ) {

                    ActiveParticleSystem->render( Window ); } }

            for ( auto ActiveRayShot : RayShots ) {

                ActiveRayShot->render( Window ); }

            for ( auto ActivePowerUp : PowerUps ) {

                ActivePowerUp->render( Window ); }

            for ( auto ActivePlanet : Planets ) {

                if ( isOnScreen( ActivePlanet->getPosition(), ActivePlanet->getRadius() ) ) {

                    ActivePlanet->render( Window ); } }

            for ( auto ActiveAsteroid : Asteroids ) {

                if ( isOnScreen( ActiveAsteroid->getPosition(), ActiveAsteroid->getRadius() ) ) {

                    ActiveAsteroid->render( Window ); } }

            for ( auto ActiveSpaceship : Spaceships ) {

                if ( isOnScreen( ActiveSpaceship->getPosition(), ActiveSpaceship->getInfluenceRadius() ) ) {

                    ActiveSpaceship->render( Window ); } }

            for ( auto ActiveMissile : Missiles ) {

                if ( isOnScreen( ActiveMissile->getPosition(), ActiveMissile->getInfluenceRadius() ) ) {

                    ActiveMissile->render( Window ); } } }

        Interface[i]->render( Window ); }

    renderViewsOutline( Window ); }

void GameModule::reset ( ) {

    Gameplay = nullptr;

    Pause = false;
    EndingCondition = false;

    Gravity = 1.f;
    DetectionDistance = 750.f;
    AreaRadius = 1500.f;
    PlayerCount = 0;

    AsteroidCount = 5;
    AsteroidPauseDuration = sf::seconds( 5.f );
    AsteroidPauseTime = sf::seconds( 30.f );

    PowerUpPauseDuration = sf::seconds( 5.f );
    PowerUpPauseTime = sf::seconds( 30.f );
    GravityPowerUp = nullptr;
    AsteroidPowerUp = nullptr;

    for ( unsigned int i = 0; i < MaximumPlayerCount; i++ ) {

        delete Interface[i];

        PlayerSpaceship[i] = nullptr;
        PlayerScore[i] = 0;
        Interface[i] = nullptr; }

    for ( auto i = Planets.begin(); i != Planets.end(); i++ ) {

        delete *i;
        i = Planets.erase( i ); }

    for ( auto i = Asteroids.begin(); i != Asteroids.end(); i++ ) {

        delete *i;
        i = Asteroids.erase( i ); }

    for ( auto i = Spaceships.begin(); i != Spaceships.end(); i++ ) {

        delete *i;
        i = Spaceships.erase( i ); }

    for ( auto i = Missiles.begin(); i != Missiles.end(); i++ ) {

        delete *i;
        i = Missiles.erase( i ); }

    for ( auto i = RayShots.begin(); i != RayShots.end(); i++ ) {

        delete *i;
        i = RayShots.erase( i ); }

    for ( auto i = ParticleSystems.begin(); i != ParticleSystems.end(); i++ ) {

        delete *i;
        i = ParticleSystems.erase( i ); } }

void GameModule::terminate ( ) {

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        PlayerSpaceship[i]->destruct(); } }

bool GameModule::onPause ( ) {

    return Pause; }

bool GameModule::onEndingCondition ( ) {

    bool FadedOut = true;

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( !Interface[i]->isFadedOut() ) {

            FadedOut = false;

            break; } }

    return EndingCondition && FadedOut; }

void GameModule::destructBody ( Body * Object ) {

    ParticleSystem * Explosion = Object->onDestruction();

    if ( Explosion ) {

        ParticleSystems.push_back( Explosion ); }

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( Object == PlayerSpaceship[i] ) {

            PlayerFinalVelocity[i] = PlayerSpaceship[i]->getVelocity();
            Interface[i]->update( sf::seconds( 0.01f ) );
            Interface[i]->beginFadeOut();

            delete PlayerSpaceship[i]->getController();

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

Spaceship * GameModule::getRayTarget ( Spaceship * Requester, sf::Vector2f &Intersection, bool AffectMissiles ) {

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
    // if ( AffectMissiles ) then ...

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

        if ( fabsf( AngleDifference ) <= ( 0.5f * MaximumAngle ) ) {

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

Spaceship * GameModule::getAngularTarget ( Missile * Requester, float MaximumAngle ) {

    float TargetDistance = 1000000.f;
    Spaceship * Target = nullptr;

    for ( auto ActiveSpaceship : Spaceships ) {

        if ( getMinDistance( Requester->getPosition(), ActiveSpaceship->getPosition() ) > DetectionDistance ) {

            continue; }

        float AngleDifference = atan2f( ActiveSpaceship->getPosition().y - Requester->getPosition().y, ActiveSpaceship->getPosition().x - Requester->getPosition().x );
        AngleDifference = Requester->normalizeAngle( Requester->getVelocityAngle() - AngleDifference );

        if ( fabsf( AngleDifference ) <= ( 0.5f * MaximumAngle ) ) {

            float Distance = getDistance( Requester->getPosition(), ActiveSpaceship->getPosition() );

            if ( Distance <= DetectionDistance && Distance < TargetDistance ) {

                Target = ActiveSpaceship;
                TargetDistance = Distance; } } }

    return Target; }

PowerUp * GameModule::detectPowerUp ( Spaceship * Requester, float &Distance, float &Angle ) {

    float TargetDistance = 1000000.f;
    PowerUp * Target = nullptr;
    Angle = PI;

    for ( auto ActivePowerUp : PowerUps ) {

        if ( getMinDistance( Requester->getPosition(), ActivePowerUp->getPosition() ) > DetectionDistance ) {

            continue; }

        float AngleDifference = atan2f( ActivePowerUp->getPosition().y - Requester->getPosition().y, ActivePowerUp->getPosition().x - Requester->getPosition().x );
        AngleDifference = Requester->normalizeAngle( Requester->getVelocityAngle() - AngleDifference );

        if ( fabsf( AngleDifference ) <= ( PI / 6.f ) ) {

            Distance = getDistance( Requester->getPosition(), ActivePowerUp->getPosition() );

            if ( Distance <= DetectionDistance && Distance < TargetDistance ) {

                Target = ActivePowerUp;
                TargetDistance = Distance;
                Angle = AngleDifference; } } }

    if ( Target ) {

        Distance = TargetDistance; }

    else {

        Distance = 1000000.f; }

    return Target; }

void GameModule::updatePlanets ( sf::Time ElapsedTime ) {

    // Update planets' state

    for ( auto ActivePlanet : Planets ) {

        ActivePlanet->update( ElapsedTime ); }

    // Delete destructed planets

    for ( auto i = Planets.begin(); i != Planets.end(); i++ ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            i = Planets.erase( i ); } } }

void GameModule::updateAsteroids ( sf::Time ElapsedTime ) {

    // Generate asteroids

    AsteroidPauseTime -= ElapsedTime;

    if ( Asteroids.size() < AsteroidCount && AsteroidPauseTime.asSeconds() <= 0.f ) {

        AsteroidPauseTime = AsteroidPauseDuration;

        float Mass = 8.f + getRandomFloat() * 12.f;
        float Radius = Mass * ( 0.75f + getRandomFloat() * 0.5f );

        auto * NewAsteroid = new Asteroid ( Mass, Radius );

        float Angle = getRandomFloat() * ( 2.f * PI );
        float AngleFluctuation = ( - PI / 6.f ) + getRandomFloat() * ( PI / 3.f );
        float Distance = AreaRadius + 1000.f;

        NewAsteroid->setPosition( sf::Vector2f( Distance * cosf( Angle ), Distance * sinf( Angle ) ) );
        NewAsteroid->setVelocity( sf::Vector2f( 50.f * cosf( Angle - PI + AngleFluctuation ), 50.f * sinf( Angle - PI + AngleFluctuation ) ) );

        Asteroids.push_back( NewAsteroid ); }

    // Update gravity acceleration, detect collisions with planets

    for ( auto ActiveAsteroid : Asteroids ) {

        for ( auto ActivePlanet : Planets ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveAsteroid->getPosition(), ActivePlanet->getPosition() );

            Acceleration.x -= Gravity * ActivePlanet->getMass() * ( ActiveAsteroid->getPosition().x - ActivePlanet->getPosition().x ) / ( Distance * Distance );
            Acceleration.y -= Gravity * ActivePlanet->getMass() * ( ActiveAsteroid->getPosition().y - ActivePlanet->getPosition().y ) / ( Distance * Distance );

            ActiveAsteroid->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveAsteroid->getRadius() + ActivePlanet->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveAsteroid->onCollision( ActivePlanet );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        float DistanceFromOrigin = getDistance( sf::Vector2f ( 0.f, 0.f ), ActiveAsteroid->getPosition() );

        if ( DistanceFromOrigin < AreaRadius ) {

            ActiveAsteroid->resetExistenceTime(); } }

    // Detect collisions between asteroids

    for ( auto FirstAsteroid : Asteroids ) {

        for ( auto SecondAsteroid : Asteroids ) {

            if ( FirstAsteroid == SecondAsteroid ) {

                continue; }

            float MinimumDistance = FirstAsteroid->getRadius() + SecondAsteroid->getRadius();

            if ( getMinDistance( FirstAsteroid->getPosition(), SecondAsteroid->getPosition() ) <= MinimumDistance ) {

                if ( getDistance( FirstAsteroid->getPosition(), SecondAsteroid->getPosition() ) <= MinimumDistance ) {

                    if ( true ) { // TODO ACCURATE CHECK

                        ParticleSystem * Explosion = FirstAsteroid->onCollision( SecondAsteroid );

                        if ( Explosion ) {

                            ParticleSystems.push_back( Explosion ); } } } } } }

    // Update asteroids' state

    for ( auto ActiveAsteroid : Asteroids ) {

        ActiveAsteroid->update( ElapsedTime ); }

    // Delete destructed asteroids

    for ( auto i = Asteroids.begin(); i != Asteroids.end(); i++ ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            i = Asteroids.erase( i ); } } }

void GameModule::updateSpaceships ( sf::Time ElapsedTime ) {

    // Update gravity acceleration and influence of area limit, detect collisions with planets and asteroids

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

                if ( true ) { // TODO ACCURATE CHECK

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

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveSpaceship->onCollision( ActiveAsteroid );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        if ( !isPlayer( ActiveSpaceship ) && ActiveSpaceship->getController() != nullptr ) {

            ( (AIController*) ActiveSpaceship->getController() )->setClosestBodyDistance( ClosestBodyDistance );
            ( (AIController*) ActiveSpaceship->getController() )->setClosestBodyAcceleration( ClosestBodyAcceleration ); }

        if ( fabsf( ActiveSpaceship->getPosition().x ) > ( SQRT2_2ND * AreaRadius ) || fabsf( ActiveSpaceship->getPosition().y ) > ( SQRT2_2ND * AreaRadius ) ) {

            float Distance = getDistance( sf::Vector2f ( 0.f, 0.f ), ActiveSpaceship->getPosition() );

            if ( Distance > ( AreaRadius - 150.f ) && !isPlayer( ActiveSpaceship ) && ActiveSpaceship->getController() != nullptr ) {

                ( (AIController*) ActiveSpaceship->getController() )->enableLimitPanic(); }

            if ( Distance > AreaRadius ) {

                ActiveSpaceship->updateHealth( - 5.f * ElapsedTime.asSeconds() ); } }

        ActiveSpaceship->updateVelocity( AccelerationSum, ElapsedTime ); }

    // Detect collisions between spaceships

    for ( auto FirstSpaceship : Spaceships ) {

        for ( auto SecondSpaceship : Spaceships ) {

            if ( FirstSpaceship == SecondSpaceship ) {

                continue; }

            float MinimumDistance = FirstSpaceship->getRadius() + SecondSpaceship->getRadius();

            if ( getMinDistance( FirstSpaceship->getPosition(), SecondSpaceship->getPosition() ) <= MinimumDistance ) {

                if ( getDistance( FirstSpaceship->getPosition(), SecondSpaceship->getPosition() ) <= MinimumDistance ) {

                    if ( true ) { // TODO ACCURATE CHECK

                        ParticleSystem * Explosion = FirstSpaceship->onCollision( SecondSpaceship );

                        if ( Explosion ) {

                            ParticleSystems.push_back( Explosion ); } } } } } }

    // Update spaceships' state and spaceship controllers

    for ( auto ActiveSpaceship : Spaceships ) {

        if ( !isPlayer( ActiveSpaceship ) && ActiveSpaceship->getController() != nullptr ) {

            float TargetDistance, TargetAngle;
            Spaceship * Target = getAngularTarget( ActiveSpaceship, 2.f * PI / 3.f, TargetDistance, TargetAngle );

            if ( Target ) {

                ( (AIController*) ActiveSpaceship->getController() )->setTargetIn120Degrees( Target, TargetDistance, TargetAngle );
                Target = getAngularTarget( ActiveSpaceship, PI / 3.f, TargetDistance, TargetAngle );

                if ( Target ) {

                    ( (AIController*) ActiveSpaceship->getController() )->setTargetIn60Degrees( Target, TargetDistance, TargetAngle );
                    Target = getAngularTarget( ActiveSpaceship, PI / 6.f, TargetDistance, TargetAngle );

                    if ( Target ) {

                        ( (AIController*) ActiveSpaceship->getController() )->setTargetIn30Degrees( Target, TargetDistance, TargetAngle ); }

                    else {

                        ( (AIController*) ActiveSpaceship->getController() )->setTargetIn30Degrees( nullptr ); } }

                else {

                    ( (AIController*) ActiveSpaceship->getController() )->setTargetIn60Degrees( nullptr ); } }

            else {

                ( (AIController*) ActiveSpaceship->getController() )->setTargetIn120Degrees( nullptr ); }

            float PowerUpDistance, PowerUpAngle;
            PowerUp * MyPowerUp = detectPowerUp( ActiveSpaceship, PowerUpDistance, PowerUpAngle );

            if ( MyPowerUp ) {

                ( (AIController*) ActiveSpaceship->getController() )->setPowerUp( MyPowerUp, PowerUpDistance, PowerUpAngle ); }

            else {

                ( (AIController*) ActiveSpaceship->getController() )->setPowerUp( nullptr ); } }

        ActiveSpaceship->update( ElapsedTime );

        if ( ActiveSpaceship->onRayShot() ) {

            sf::Vector2f Intersection;
            Spaceship * Target = getRayTarget( ActiveSpaceship, Intersection );
            auto RayShot = new Ray ( ActiveSpaceship->getPosition(), ActiveSpaceship->getVelocityAngle() );

            if ( Target ) {

                Target->updateHealth( - 0.2f *  ActiveSpaceship->getRayPower() );

                if ( isPlayer( Target ) ) {

                    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                        if ( PlayerSpaceship[i] == ActiveSpaceship ) {

                            Interface[i]->onShot();

                            break; } } }

                else if ( ActiveSpaceship->getController() != nullptr ) {

                    ( (AIController*) Target->getController() )->enableShotPanic(); }

                // TODO PARTICLE EFFECT ON HIT

                }

            if ( Intersection != ActiveSpaceship->getPosition() ) {

                RayShot->enableRendering( Intersection.x ); }

            else {

                RayShot->enableRendering(); }

            RayShots.push_back( RayShot ); }

        if ( ActiveSpaceship->onMissileShot() ) {

            auto * NewMissile = new Missile ( );

            float TargetDistance, TargetAngle;
            Spaceship * Target = getAngularTarget( ActiveSpaceship, 2.f * PI / 3.f, TargetDistance, TargetAngle );

            sf::Vector2f MissilePosition = ActiveSpaceship->getPosition();
            MissilePosition.x += ( ActiveSpaceship->getRadius() + NewMissile->getRadius() + 20.f ) * cosf( ActiveSpaceship->getVelocityAngle() );
            MissilePosition.y += ( ActiveSpaceship->getRadius() + NewMissile->getRadius() + 20.f ) * sinf( ActiveSpaceship->getVelocityAngle() );

            NewMissile->setPosition( MissilePosition );
            NewMissile->setVelocity( ActiveSpaceship->getVelocity() );
            NewMissile->setTarget( Target );

            Missiles.push_back( NewMissile ); } }

    // Delete destructed spaceships

    for ( auto i = Spaceships.begin(); i != Spaceships.end(); i++ ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            i = Spaceships.erase( i ); } } }

void GameModule::updateMissiles ( sf::Time ElapsedTime ) {

    // Update gravity acceleration, detect collisions with planets, asteroids and spaceships

    for ( auto ActiveMissile : Missiles ) {

        for ( auto ActivePlanet : Planets ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveMissile->getPosition(), ActivePlanet->getPosition() );

            Acceleration.x -= Gravity * ActivePlanet->getMass() * ( ActiveMissile->getPosition().x - ActivePlanet->getPosition().x ) / ( Distance * Distance );
            Acceleration.y -= Gravity * ActivePlanet->getMass() * ( ActiveMissile->getPosition().y - ActivePlanet->getPosition().y ) / ( Distance * Distance );

            ActiveMissile->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveMissile->getRadius() + ActivePlanet->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveMissile->onCollision( ActivePlanet );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        for ( auto ActiveAsteroid : Asteroids ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveMissile->getPosition(), ActiveAsteroid->getPosition() );

            Acceleration.x -= Gravity * ActiveAsteroid->getMass() * ( ActiveMissile->getPosition().x - ActiveAsteroid->getPosition().x ) / ( Distance * Distance );
            Acceleration.y -= Gravity * ActiveAsteroid->getMass() * ( ActiveMissile->getPosition().y - ActiveAsteroid->getPosition().y ) / ( Distance * Distance );

            ActiveMissile->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveMissile->getRadius() + ActiveAsteroid->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveMissile->onCollision( ActiveAsteroid );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        for ( auto ActiveSpaceship : Spaceships ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveMissile->getPosition(), ActiveSpaceship->getPosition() );

            Acceleration.x -= Gravity * ActiveSpaceship->getMass() * ( ActiveMissile->getPosition().x - ActiveSpaceship->getPosition().x ) / ( Distance * Distance );
            Acceleration.y -= Gravity * ActiveSpaceship->getMass() * ( ActiveMissile->getPosition().y - ActiveSpaceship->getPosition().y ) / ( Distance * Distance );

            ActiveMissile->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveMissile->getRadius() + ActiveSpaceship->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveMissile->onCollision( ActiveSpaceship );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } } }

    // Detect collisions between missiles

    for ( auto FirstMissile : Missiles ) {

        for ( auto SecondMissile : Missiles ) {

            if ( FirstMissile == SecondMissile ) {

                continue; }

            float MinimumDistance = FirstMissile->getRadius() + SecondMissile->getRadius();

            if ( getMinDistance( FirstMissile->getPosition(), SecondMissile->getPosition() ) <= MinimumDistance ) {

                if ( getDistance( FirstMissile->getPosition(), SecondMissile->getPosition() ) <= MinimumDistance ) {

                    if ( true ) { // TODO ACCURATE CHECK

                        ParticleSystem * FirstExplosion = FirstMissile->onCollision( SecondMissile );
                        ParticleSystem * SecondExplosion = SecondMissile->onCollision( FirstMissile );

                        if ( FirstExplosion ) {

                            ParticleSystems.push_back( FirstExplosion ); }

                        if ( SecondExplosion ) {

                            ParticleSystems.push_back( SecondExplosion ); } } } } } }

    // Update missiles' state

    for ( auto ActiveMissile : Missiles ) {

        if ( !ActiveMissile->getTarget() ) {

            float TargetDistance, TargetAngle;
            Spaceship * Target = getAngularTarget( ActiveMissile, 2.f * PI / 3.f );

            ActiveMissile->setTarget( Target ); }

        ActiveMissile->update( ElapsedTime ); }

    // Delete destructed missiles

    for ( auto i = Missiles.begin(); i != Missiles.end(); i++ ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            i = Missiles.erase( i ); } } }

void GameModule::updatePowerUps ( sf::Time ElapsedTime ) {

    // Generate power ups

    PowerUpPauseTime -= ElapsedTime;

    if ( PowerUpPauseTime.asSeconds() <= 0.f ) {

        PowerUpPauseTime = PowerUpPauseDuration;

        sf::Vector2f Position;
        float MinimumPlanetDistance = 150.f;
        float MinimumPowerUpDistance = 50.f;
        unsigned int Attempts = 25;

        while ( Attempts > 0 && Position == sf::Vector2f ( 1000000.f, 1000000.f ) ) {

            float Angle = ( - PI ) + getRandomFloat() * 2.f * PI;

            Position.x = getRandomFloat() * ( AreaRadius - 500.f ) * cosf( Angle );
            Position.y = getRandomFloat() * ( AreaRadius - 500.f ) * sinf( Angle );

            for ( auto ActivePlanet : Planets ) {

                if ( getMinDistance( Position, ActivePlanet->getPosition() ) <= ( MinimumPlanetDistance + ActivePlanet->getRadius() ) ) {

                    if ( getDistance( Position, ActivePlanet->getPosition() ) <= ( MinimumPlanetDistance + ActivePlanet->getRadius() ) ) {

                        Position = sf::Vector2f ( 1000000.f, 1000000.f );

                        break; } } }

            for ( auto ActivePowerUp : PowerUps ) {

                if ( getMinDistance( Position, ActivePowerUp->getPosition() ) <= ( MinimumPowerUpDistance + ActivePowerUp->getRadius() ) ) {

                    if ( getDistance( Position, ActivePowerUp->getPosition() ) <= ( MinimumPowerUpDistance + ActivePowerUp->getRadius() ) ) {

                        Position = sf::Vector2f ( 1000000.f, 1000000.f );

                        break; } } }

            Attempts--; }

        if ( Attempts > 0 ) { // TODO GENERATE DIFFERENT POWER UPS

            PowerUp * NewPowerUp = nullptr;

            if ( true ) {

                auto * NewEnergyPowerUp = new EnergyPowerUp ( Graphics, PowerUpRadius, &Gravity, &AsteroidCount );

                NewPowerUp = NewEnergyPowerUp;
                }

            NewPowerUp->setPosition( Position );

            PowerUps.push_back( NewPowerUp ); } }

    // Detect collisions with spaceships

    for ( auto ActivePowerUp : PowerUps ) {

        if ( !ActivePowerUp->isCaught() ) {

            for ( auto ActiveSpaceship : Spaceships ) {

                float MinimumDistance = ActivePowerUp->getRadius() + ActiveSpaceship->getRadius();

                if ( getMinDistance( ActivePowerUp->getPosition(), ActiveSpaceship->getPosition() ) <= MinimumDistance ) {

                    if ( getDistance( ActivePowerUp->getPosition(), ActiveSpaceship->getPosition() ) <= MinimumDistance ) {

                        ActivePowerUp->onCatch( ActiveSpaceship );

                        if ( ActivePowerUp->isGravityModifier() ) {

                            if ( GravityPowerUp != nullptr ) {

                                GravityPowerUp->finish(); }

                            GravityPowerUp = ActivePowerUp; }

                        if ( ActivePowerUp->isAsteroidModifier() ) {

                            if ( AsteroidPowerUp != nullptr ) {

                                AsteroidPowerUp->finish(); }

                            AsteroidPowerUp = ActivePowerUp; }

                        break; } } } } }

    // Update power ups' state

    for ( auto ActivePowerUp : PowerUps ) {

        ActivePowerUp->update( ElapsedTime ); }

    // Delete inactive power ups

    for ( auto i = PowerUps.begin(); i != PowerUps.end(); i++ ) {

        if ( (*i)->isExpired() ) {

            if ( (*i) == GravityPowerUp ) {

                GravityPowerUp = nullptr; }

            if ( (*i) == AsteroidPowerUp ) {

                AsteroidPowerUp = nullptr; }

            delete (*i);
            i = PowerUps.erase( i ); } } }

void GameModule::updateRayShots ( sf::Time ElapsedTime ) {

    // Update ray shots' state

    for ( auto ActiveRayShot : RayShots ) {

        ActiveRayShot->update( ElapsedTime ); }

    // Delete inactive ray shots

    for ( auto i = RayShots.begin(); i != RayShots.end(); i++ ) {

        if ( !(*i)->isRenderingEnabled() ) {

            delete (*i);
            i = RayShots.erase( i ); } } }

void GameModule::updateParticleSystems ( sf::Time ElapsedTime ) {

    // Update particle systems' state

    for ( auto ActiveParticleSystem : ParticleSystems ) {

        ActiveParticleSystem->update( ElapsedTime ); }

    // Delete inactive particle systems

    for ( auto i = ParticleSystems.begin(); i != ParticleSystems.end(); i++ ) {

        if ( (*i)->getParticleCount() == 0 ) {

            delete (*i);
            i = ParticleSystems.erase( i ); } } }

void GameModule::updateViews ( ) { // TODO UPDATE VIEWS OUTLINE

    float ViewWidth = ( 800.f / Graphics->getWindowHeight() ) * Graphics->getWindowWidth();
    float ViewHeight = 800.f;

    if ( PlayerCount == 1 ) {

        Views[0].setSize( ViewWidth, ViewHeight );
        Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 1.f, 1.f ) ); }

    else if ( PlayerCount == 2 ) {

        if ( ViewWidth >= ViewHeight ) {

            Views[0].setSize( ViewWidth / 2.f, ViewHeight );
            Views[1].setSize( ViewWidth / 2.f, ViewHeight );
            Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 0.5f, 1.f ) );
            Views[1].setViewport( sf::FloatRect( 0.5f, 0.f, 0.5f, 1.f ) ); }

        else {

            Views[0].setSize( ViewWidth, ViewHeight / 2.f );
            Views[1].setSize( ViewWidth, ViewHeight / 2.f );
            Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 1.f, 0.5f ) );
            Views[1].setViewport( sf::FloatRect( 0.f, 0.5f, 1.f, 0.5f ) ); } }

    else if ( PlayerCount == 3 ) {

        Views[0].setSize( ViewWidth / 2.f, 0.6f * ViewHeight );
        Views[1].setSize( ViewWidth / 2.f, 0.6f * ViewHeight );
        Views[2].setSize( ViewWidth, 0.4f * ViewHeight );
        Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 0.5f, 0.6f ) );
        Views[1].setViewport( sf::FloatRect( 0.5f, 0.f, 0.5f, 0.6f ) );
        Views[2].setViewport( sf::FloatRect( 0.f, 0.6f, 1.f, 0.4f ) ); }

    else if ( PlayerCount == 4 ) {

        Views[0].setSize( ViewWidth / 2.f, ViewHeight / 2.f );
        Views[1].setSize( ViewWidth / 2.f, ViewHeight / 2.f );
        Views[2].setSize( ViewWidth / 2.f, ViewHeight / 2.f );
        Views[3].setSize( ViewWidth / 2.f, ViewHeight / 2.f );
        Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 0.5f, 0.5f ) );
        Views[1].setViewport( sf::FloatRect( 0.5f, 0.f, 0.5f, 0.5f ) );
        Views[2].setViewport( sf::FloatRect( 0.f, 0.5f, 0.5f, 0.5f ) );
        Views[3].setViewport( sf::FloatRect( 0.5f, 0.5f, 0.5f, 0.5f ) ); } }

void GameModule::renderViewsOutline ( sf::RenderWindow &Window ) {

    Window.draw( &ViewsOutline[0], ViewsOutline.size(), sf::Lines ); }

void GameModule::prepareAreaLimit ( ) {

    AreaLimit.resize( 1000 );

    for ( unsigned int i = 0; i < 1000; i++ ) {

        AreaLimit[i].position.x = AreaRadius * cosf( 2.f * PI * ( i / 1000.f ) );
        AreaLimit[i].position.y = AreaRadius * sinf( 2.f * PI * ( i / 1000.f ) );
        AreaLimit[i].color = sf::Color::White; } }

void GameModule::renderAreaLimit ( sf::RenderWindow &Window ) {

    Window.draw( &AreaLimit[0], AreaLimit.size(), sf::Lines ); }