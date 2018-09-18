#include <iostream> // TODO TEMP
#include "debug-module.hpp"
#include "game-module.hpp"

GameModule::GameModule ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    for ( unsigned int i = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

        PlayerSpaceship[i] = nullptr;
        PlayerScore[i] = nullptr;
        Interface[i] = nullptr; }

    reset(); }

GameModule::~GameModule ( ) {

    reset(); }

void GameModule::setGameplay ( GameplaySettings * Gameplay ) {

    reset();

    this->Gameplay = Gameplay;
    AreaRadius = Gameplay->getAreaSize();
    PlayerCount = Gameplay->getPlayerCount();
    GameplayTime = ( Gameplay->getEndingCondition() == GameplaySettings::EndingConditions::Time ) ? Gameplay->getTimeLimit() : sf::seconds( 0.f );
    PowerUpLimit = (unsigned int) ( 5.f * powf( AreaRadius / 1000.f, 2 ) );

    initAreaLimit();

    switch ( Gameplay->getAsteroidFrequency() ) {

        case GameplaySettings::AsteroidFrequencies::Rarely: {

            AsteroidCount = (unsigned int) ( 2.f * powf( AreaRadius / 1000.f, 2 ) );

            break; }

        case GameplaySettings::AsteroidFrequencies::Occasionally: {

            AsteroidCount = (unsigned int) ( 3.f * powf( AreaRadius / 1000.f, 2 ) );

            break; }

        case GameplaySettings::AsteroidFrequencies::Often: {

            AsteroidCount = (unsigned int) ( 4.f * powf( AreaRadius / 1000.f, 2 ) );

            break; }

        default: {

            AsteroidCount = (unsigned int) ( 3.f * powf( AreaRadius / 1000.f, 2 ) );

            break; } }

    if ( AsteroidCount >= 25 ) {

        AsteroidPauseDuration = sf::seconds( 0.5f ); }

    switch ( Gameplay->getAIPersonality() ) {

        case GameplaySettings::AIPersonalities::Aggressive: {

            ScoreMultiplier *= 2.f;

            break; }

        case GameplaySettings::AIPersonalities::Passive: {

            ScoreMultiplier *= 0.5f;

            break; }

        default: {

            break; } }

    auto PlanetCount = (unsigned int) ( 0.10f * ( powf( AreaRadius, 2.f ) / powf( 200.f, 2.f ) ) ); // Average planet radius is ~200

    for ( unsigned int i = 0; i < PlanetCount; i++ ) {

        float Mass = 1000000.f * ( 4.f + getRandomFloat() * 2.f );
        float Radius = cbrtf( ( Mass / 0.25f ) / ( PI * 0.75f ) ) * ( 0.75f + getRandomFloat() * 0.5f );

        auto NewPlanet = new Planet ( Graphics, Mass, Radius );
        sf::Vector2f Position ( 1000000.f, 1000000.f );

        unsigned int Attempts = 25;

        while ( Attempts > 0 && Position == sf::Vector2f( 1000000.f, 1000000.f ) ) {

            float Angle = getRandomFloat() * ( 2.f * PI );
            float Module = getRandomFloat() * ( AreaRadius - 500.f - Radius );

            Position.x = Module * cosf( Angle );
            Position.y = Module * sinf( Angle );

            for ( auto ActivePlanet : Planets ) {

                float MinimumDistance = 500.f + Radius + ActivePlanet->getRadius();

                if ( getMinDistance( Position, ActivePlanet->getPosition() ) <= MinimumDistance ) {

                    if ( getDistance(Position, ActivePlanet->getPosition() ) <= MinimumDistance ) {

                        Position = sf::Vector2f( 1000000.f, 1000000.f );

                        break; } } }

            Attempts--; }

        if ( Attempts > 0 ) {

            NewPlanet->setPosition( Position );

            Planets.push_back( NewPlanet ); } }

    auto * SpaceshipOrder = new unsigned int [ Gameplay->getSpaceshipCount() ];

    for ( unsigned int i = 0; i < Gameplay->getSpaceshipCount(); i++ ) {

        SpaceshipOrder[i] = i; }

    std::shuffle( &SpaceshipOrder[0], &SpaceshipOrder[ Gameplay->getSpaceshipCount() ], std::mt19937( (unsigned int) time( nullptr ) ) );

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        PlayerScore[i] = &( Gameplay->getScores()[i] );
        PlayerScore[i]->reset(); }

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
        NewSpaceship->setBrakingFactor( Prototype.BrakingFactor );
        NewSpaceship->setRayPower( Prototype.RayPower );
        NewSpaceship->setRayColor( Prototype.RayColor );
        NewSpaceship->setMissileLimit( Prototype.MissileLimit );
        NewSpaceship->setMissileCount( Prototype.MissileCount );
        NewSpaceship->setTexture( Graphics->getTexture( Prototype.Texture ) );
        NewSpaceship->setAccentTexture( Graphics->getTexture( Prototype.AccentTexture ), sf::Color::Red ); // TODO MORE COLORS
        NewSpaceship->setThrusterTexture( Graphics->getTexture( "Thruster" ), Prototype.FuelColor );

        float PositionAngle = ( (float) SpaceshipOrder[i] / (float) Gameplay->getSpaceshipCount() ) * ( 2.f * PI );
        float PositionModule = AreaRadius - 200.f;
        float VelocityAngle = PI + PositionAngle;
        float VelocityModule = 25.f;

        NewSpaceship->setPosition( sf::Vector2f( PositionModule * cosf( PositionAngle ), PositionModule * sinf( PositionAngle  ) ) );
        NewSpaceship->setVelocity( sf::Vector2f( VelocityModule * cosf( VelocityAngle ), VelocityModule * sinf( VelocityAngle  ) ) );

        if ( i < PlayerCount ) {

            PlayerSpaceship[i] = NewSpaceship;
            PlayerSpaceship[i]->setController( new PlayerController ( Gameplay->getPlayerControllerSettings( i ) ) );
            PlayerScore[i]->addMultiplier( ScoreMultiplier );
            PlayerScore[i]->addMultiplier( Prototype.ScoreMultiplier );
            Interface[i] = new PlayerInterface ( Graphics );
            Interface[i]->setSpaceship( PlayerSpaceship[i] );
            Interface[i]->setScoreCounter( PlayerScore[i] ); }

        else {

            switch ( Gameplay->getAIPersonality() ) {

                case GameplaySettings::AIPersonalities::Random: {

                    auto Personality = (unsigned int) ( rand() % 3 );

                    if ( Personality == 0 ) {

                        NewSpaceship->setController( new AggressiveAIController ( ) ); }

                    else if ( Personality == 1 ) {

                        NewSpaceship->setController( new ReasonableAIController ( ) ); }

                    else {

                        NewSpaceship->setController( new PassiveAIController ( ) ); }

                    break; }

                case GameplaySettings::AIPersonalities::Aggressive: {

                    NewSpaceship->setController( new AggressiveAIController ( ) );

                    break; }

                case GameplaySettings::AIPersonalities::Reasonable: {

                    NewSpaceship->setController( new ReasonableAIController ( ) );

                    break; }

                case GameplaySettings::AIPersonalities::Passive: {

                    NewSpaceship->setController( new PassiveAIController ( ) );

                    break; }

                default: {

                    NewSpaceship->setController( new AIController ( ) );

                    break; } } }

        Spaceships.push_back( NewSpaceship ); }

    delete SpaceshipOrder; }

GameplaySettings * GameModule::getGameplay ( ) {

    return Gameplay; }

void GameModule::update ( ) {

    sf::Time ElapsedTime = Clock.restart();

    if ( ElapsedTime.asSeconds() < 0.1f ) {

        if ( Gameplay ) {

            if ( Gameplay->getEndingCondition() == GameplaySettings::EndingConditions::Time ) {

                auto Minutes = (unsigned int) ( GameplayTime.asSeconds() / 60.f );

                GameplayTime -= ElapsedTime;

                auto MinutesAfter = (unsigned int) ( GameplayTime.asSeconds() / 60.f );

                if ( Minutes != MinutesAfter ) {

                    std::string MinutesNotification;

                    if ( Minutes >= 5 ) {

                        if ( Minutes % 5 == 0 ) {

                            MinutesNotification = std::to_string( Minutes ) + " minutes are left"; } }

                    else if ( Minutes > 1 ) {

                        MinutesNotification = std::to_string( Minutes ) + " minutes are left"; }

                    else if ( Minutes == 1 ) {

                        MinutesNotification = std::to_string( Minutes ) + " minute is left"; }

                    if ( !MinutesNotification.empty() ) {

                        displayNotification( MinutesNotification ); } } }

            else {

                GameplayTime += ElapsedTime; } }

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

            PlayerScore[i]->update( ElapsedTime );
            Interface[i]->update( ElapsedTime ); } }

    else {

        // TODO LOW FPS COUNTER AND MESSAGE

        }

    if ( Gameplay ) {

        if ( !EndingCondition ) {

            if ( getAlivePlayerCount() == 0 ) {

                EndingCondition = true; }

            else {

                switch ( Gameplay->getEndingCondition() ) {

                    case GameplaySettings::EndingConditions::Time: {

                        if ( GameplayTime.asSeconds() <= 0.f ) {

                            EndingCondition = true;
                            Gameplay->setWinner( 0 );

                            for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                                if ( PlayerSpaceship[i] ) {

                                    unsigned char Bit = 0x01;

                                    for ( unsigned int j = 0; j < i; j++ ) {

                                        Bit *= 2; }

                                    Gameplay->setWinner( Gameplay->getWinner() | Bit );
                                    PlayerScore[i]->update( ScoreCounter::Event::Time, Gameplay->getTimeLimit().asSeconds() ); } } }

                        break; }

                    case GameplaySettings::EndingConditions::NoEnemies: {

                        if ( getAlivePlayerCount() == Spaceships.size() ) {

                            EndingCondition = true;
                            Gameplay->setWinner( 0 );

                            for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                                if ( PlayerSpaceship[i] ) {

                                    unsigned char Bit = 0x01;

                                    for ( unsigned int j = 0; j < i; j++ ) {

                                        Bit *= 2; }

                                    Gameplay->setWinner( Gameplay->getWinner() | Bit ); } } }

                        break; }

                    case GameplaySettings::EndingConditions::LastPlayer: {

                        if ( getAlivePlayerCount() == 1 ) {

                            unsigned char Bit = 0x01;

                            for ( unsigned int j = 0; j < getLastAlivePlayer(); j++ ) {

                                Bit *= 2; }

                            EndingCondition = true;
                            Gameplay->setWinner( Bit ); }

                        break; }

                    case GameplaySettings::EndingConditions::LastSpaceship: {

                        if ( getAlivePlayerCount() == 1 && Spaceships.size() == 1 ) {

                            unsigned char Bit = 0x01;

                            for ( unsigned int j = 0; j < getLastAlivePlayer(); j++ ) {

                                Bit *= 2; }

                            EndingCondition = true;
                            Gameplay->setWinner( Bit ); }

                        break; }

                    default: {

                        break; } } }

            if ( EndingCondition ) {

                for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                    if ( !Interface[i]->isFadedOut() ) {

                        Interface[i]->beginFadeOut(); } } } }

        else {

            SkipProtectionTime -= ElapsedTime; } } }

void GameModule::update ( sf::Event &Event ) {

    if ( !EndingCondition ) {

        if ( Event.type == sf::Event::LostFocus ) {

            Pause = true;

            return; }

        if ( Event.type == sf::Event::KeyPressed ) {

            if ( Event.key.code == sf::Keyboard::Escape ) {

                Pause = true;

                return; } } }

    else if ( SkipProtectionTime.asSeconds() <= 0.f ) {

        if ( Event.type == sf::Event::KeyPressed ) {

            if ( Event.key.code == sf::Keyboard::Escape || Event.key.code == sf::Keyboard::Enter || Event.key.code == sf::Keyboard::Space ) {

                for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                    if ( !Interface[i]->isFadedOut() ) {

                        Interface[i]->endFadeOut(); } } } } }

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( PlayerSpaceship[i] ) {

            PlayerSpaceship[i]->update( Event ); } } }

void GameModule::render ( sf::RenderWindow &Window ) {

    if ( PlayerCount > 0 ) { // Players' view (for game mode)

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

                    if ( isOnScreen( ActivePowerUp->getPosition(), ActivePowerUp->getInfluenceRadius() ) ) {

                        ActivePowerUp->render( Window ); } }

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

            Window.setView( Window.getDefaultView() );

            Interface[i]->render( Window ); }

        renderViewsOutline( Window ); }

    else { // No player view (for debug mode)

        float ViewWidth = ( 900.f / Graphics->getWindowHeight() ) * Graphics->getWindowWidth();
        float ViewHeight = 900.f;

        sf::View NoPlayerView;
        NoPlayerView.setSize( ViewWidth, ViewHeight );
        NoPlayerView.setViewport( sf::FloatRect( 0.f, 0.f, 1.f, 1.f ) );
        NoPlayerView.setCenter( 0.f, 0.f );
        Window.setView( NoPlayerView );

        renderAreaLimit( Window );

        for ( auto ActiveParticleSystem : ParticleSystems ) {

            if ( isOnScreen( ActiveParticleSystem->getInfluenceArea() ) ) {

                ActiveParticleSystem->render( Window ); } }

        for ( auto ActiveRayShot : RayShots ) {

            ActiveRayShot->render( Window ); }

        for ( auto ActivePowerUp : PowerUps ) {

            if ( isOnScreen( ActivePowerUp->getPosition(), ActivePowerUp->getInfluenceRadius() ) ) {

                ActivePowerUp->render( Window ); } }

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

                ActiveMissile->render( Window ); } }

        Window.setView( Window.getDefaultView() ); } }

void GameModule::reset ( ) {

    Gameplay = nullptr;

    Pause = false;
    EndingCondition = false;

    Gravity = 1.f;
    DetectionDistance = 600.f;
    AreaRadius = 1500.f;
    ScoreMultiplier = 1.f;
    SkipProtectionTime = sf::seconds( 0.5f );
    PlayerCount = 0;

    AsteroidCount = 18;
    AsteroidPauseDuration = sf::seconds( 1.f );
    AsteroidPauseTime = sf::seconds( 2.f );

    PowerUpLimit = 10;
    PowerUpPauseDuration = sf::seconds( 2.f );
    PowerUpPauseTime = sf::seconds( 2.f );
    GravityPowerUp = nullptr;
    AsteroidPowerUp = nullptr;

    for ( unsigned int i = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

        if ( PlayerSpaceship[i] ) {

            delete PlayerSpaceship[i]->getController();
            PlayerSpaceship[i]->setController( nullptr ); }

        if ( Interface[i] ) {

            Interface[i]->setSpaceship( nullptr );
            delete Interface[i]; }

        PlayerSpaceship[i] = nullptr;
        Interface[i] = nullptr; }

    for ( auto i = Planets.begin(); i != Planets.end(); ) {

        delete *i;
        i = Planets.erase( i ); }

    for ( auto i = Asteroids.begin(); i != Asteroids.end(); ) {

        delete *i;
        i = Asteroids.erase( i ); }

    for ( auto i = Spaceships.begin(); i != Spaceships.end(); ) {

        delete *i;
        i = Spaceships.erase( i ); }

    for ( auto i = Missiles.begin(); i != Missiles.end(); ) {

        delete *i;
        i = Missiles.erase( i ); }

    for ( auto i = PowerUps.begin(); i != PowerUps.end(); ) {

        delete *i;
        i = PowerUps.erase( i ); }

    for ( auto i = RayShots.begin(); i != RayShots.end(); ) {

        delete *i;
        i = RayShots.erase( i ); }

    for ( auto i = ParticleSystems.begin(); i != ParticleSystems.end(); ) {

        delete *i;
        i = ParticleSystems.erase( i ); } }

void GameModule::terminate ( ) {

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( PlayerSpaceship[i] ) {

            PlayerSpaceship[i]->setHealth( 0.f );
            PlayerSpaceship[i]->updateHealth( 0.f ); } } }

bool GameModule::onPause ( ) {

    if ( Pause ) {

        Pause = false;

        return true; }

    return false; }

bool GameModule::onTerminate ( ) {

    bool FadedOut = true;

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( !Interface[i]->isFadedOut() ) {

            FadedOut = false;

            break; } }

    return EndingCondition && FadedOut; }

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

bool GameModule::isOnScreen ( sf::Vector2f Center, float Radius ) { // TODO

    return true;

    }

bool GameModule::isOnScreen ( sf::FloatRect Area ) { // TODO

    return true;

    }

unsigned int GameModule::getAlivePlayerCount ( ) {

    unsigned int AlivePlayers = 0;

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( PlayerSpaceship[i] ) {

            AlivePlayers++; } }

    return AlivePlayers; }

int GameModule::getLastAlivePlayer ( ) {

    int LastAlivePlayer = -1;

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( PlayerSpaceship[i] ) {

            LastAlivePlayer = i; } }

    return LastAlivePlayer; }

void GameModule::destructBody ( Body * Object ) {

    ParticleSystem * Explosion = Object->onDestruction();

    if ( Explosion ) {

        ParticleSystems.push_back( Explosion ); }

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        if ( Object == PlayerSpaceship[i] ) {

            Interface[i]->update( sf::seconds( 0.01f ) );
            Interface[i]->beginFadeOut();

            delete PlayerSpaceship[i]->getController();
            PlayerSpaceship[i]->setController( nullptr );

            PlayerFinalVelocity[i] = PlayerSpaceship[i]->getVelocity();
            PlayerSpaceship[i] = nullptr;
            Interface[i]->setSpaceship( nullptr );

            break; } }

    delete Object; }

void GameModule::displayNotification ( std::string Message ) {

    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

        Interface[i]->displayNotification( Message ); } }

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

    for ( auto ActiveMissile : Missiles ) {

        if ( RayShot.getIntersection( ActiveMissile->getPosition(), ActiveMissile->getRadius(), Intersection, Distance ) ) {

            if ( Distance < TargetDistance ) {

                Target = nullptr;
                TargetDistance = Distance;
                TargetIntersection = Intersection;

                if ( AffectMissiles ) {

                    ActiveMissile->onShot();

                    // TODO PARTICLE EFFECT ON HIT

                    } } } }

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

    Intersection = TargetIntersection;

    return Target; }

Spaceship * GameModule::getAngularTarget ( Spaceship * Requester, float DetectionAngle, float &Distance, float &Angle ) {

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

        if ( fabsf( AngleDifference ) <= ( 0.5f * DetectionAngle ) ) {

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

Spaceship * GameModule::getAngularTarget ( Missile * Requester, float DetectionAngle ) {

    float TargetDistance = 1000000.f;
    Spaceship * Target = nullptr;

    for ( auto ActiveSpaceship : Spaceships ) {

        if ( getMinDistance( Requester->getPosition(), ActiveSpaceship->getPosition() ) > DetectionDistance ) {

            continue; }

        float AngleDifference = atan2f( ActiveSpaceship->getPosition().y - Requester->getPosition().y, ActiveSpaceship->getPosition().x - Requester->getPosition().x );
        AngleDifference = Requester->normalizeAngle( Requester->getVelocityAngle() - AngleDifference );

        if ( fabsf( AngleDifference ) <= ( 0.5f * DetectionAngle ) ) {

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

        if ( fabsf( AngleDifference ) <= ( PI / 3.f ) ) {

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

    for ( auto i = Planets.begin(); i != Planets.end(); ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            i = Planets.erase( i ); }

        else {

            ++i; } } }

void GameModule::updateAsteroids ( sf::Time ElapsedTime ) {

    // Generate asteroids

    AsteroidPauseTime -= ElapsedTime;

    if ( Asteroids.size() < AsteroidCount && AsteroidPauseTime.asSeconds() <= 0.f ) {

        AsteroidPauseTime = AsteroidPauseDuration;

        float Mass = 1000.f + getRandomFloat() * 14000.f;
        float Radius = cbrtf( ( Mass / 1.f ) / ( PI * 0.75f ) ) * ( 0.75f + getRandomFloat() * 0.5f );

        auto * NewAsteroid = new Asteroid ( Graphics, Mass, Radius );

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

            Acceleration.x = Gravity * ActivePlanet->getMass() * ( ActivePlanet->getPosition().x - ActiveAsteroid->getPosition().x ) / ( Distance * Distance * Distance );
            Acceleration.y = Gravity * ActivePlanet->getMass() * ( ActivePlanet->getPosition().y - ActiveAsteroid->getPosition().y ) / ( Distance * Distance * Distance );

            ActiveAsteroid->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveAsteroid->getRadius() + ActivePlanet->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveAsteroid->onCollision( ActivePlanet );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        for ( auto ActiveSpaceship : Spaceships ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveAsteroid->getPosition(), ActiveSpaceship->getPosition() );

            Acceleration.x = Gravity * ActiveSpaceship->getMass() * ( ActiveSpaceship->getPosition().x - ActiveAsteroid->getPosition().x ) / ( Distance * Distance * Distance );
            Acceleration.y = Gravity * ActiveSpaceship->getMass() * ( ActiveSpaceship->getPosition().y - ActiveAsteroid->getPosition().y ) / ( Distance * Distance * Distance );

            ActiveAsteroid->updateVelocity( Acceleration, ElapsedTime ); }

        float DistanceFromOrigin = getDistance( sf::Vector2f ( 0.f, 0.f ), ActiveAsteroid->getPosition() );

        if ( DistanceFromOrigin < AreaRadius ) {

            ActiveAsteroid->resetExistenceTime(); } }

    // Update gravity acceleration, detect collisions between asteroids

    for ( auto FirstAsteroid : Asteroids ) {

        for ( auto SecondAsteroid : Asteroids ) {

            if ( FirstAsteroid == SecondAsteroid ) {

                continue; }

            sf::Vector2f Acceleration;
            float Distance = getDistance( FirstAsteroid->getPosition(), SecondAsteroid->getPosition() );
            
            Acceleration.x = Gravity * SecondAsteroid->getMass() * ( SecondAsteroid->getPosition().x - FirstAsteroid->getPosition().x ) / ( Distance * Distance * Distance );
            Acceleration.y = Gravity * SecondAsteroid->getMass() * ( SecondAsteroid->getPosition().y - FirstAsteroid->getPosition().y ) / ( Distance * Distance * Distance );

            FirstAsteroid->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( FirstAsteroid->getRadius() + SecondAsteroid->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = FirstAsteroid->onCollision( SecondAsteroid );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } }} } }

    // Update asteroids' state

    for ( auto ActiveAsteroid : Asteroids ) {

        ActiveAsteroid->update( ElapsedTime ); }

    // Delete destructed asteroids

    for ( auto i = Asteroids.begin(); i != Asteroids.end(); ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            i = Asteroids.erase( i ); }

        else {

            ++i; } } }

void GameModule::updateSpaceships ( sf::Time ElapsedTime ) {

    // Update gravity acceleration and influence of area limit, detect collisions with planets and asteroids

    for ( auto ActiveSpaceship : Spaceships ) {

        sf::Vector2f AccelerationSum;

        float ClosestBodyDistance = 1000000.f;
        sf::Vector2f ClosestBodyAcceleration;

        for ( auto ActivePlanet : Planets ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveSpaceship->getPosition(), ActivePlanet->getPosition() );

            Acceleration.x = Gravity * ActivePlanet->getMass() * ( ActivePlanet->getPosition().x - ActiveSpaceship->getPosition().x ) / ( Distance * Distance * Distance );
            Acceleration.y = Gravity * ActivePlanet->getMass() * ( ActivePlanet->getPosition().y - ActiveSpaceship->getPosition().y ) / ( Distance * Distance * Distance );

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

            Acceleration.x = Gravity * ActiveAsteroid->getMass() * ( ActiveAsteroid->getPosition().x - ActiveSpaceship->getPosition().x ) / ( Distance * Distance * Distance );
            Acceleration.y = Gravity * ActiveAsteroid->getMass() * ( ActiveAsteroid->getPosition().y - ActiveSpaceship->getPosition().y ) / ( Distance * Distance * Distance );

            if ( ( Distance - ActiveAsteroid->getRadius() ) < ClosestBodyDistance && ( Distance - ActiveAsteroid->getRadius() ) < 100.f ) {

                ClosestBodyDistance = Distance - ActiveAsteroid->getRadius();
                ClosestBodyAcceleration = Acceleration; }

            AccelerationSum += Acceleration;

            if ( Distance <= ( ActiveSpaceship->getRadius() + ActiveAsteroid->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveSpaceship->onCollision( ActiveAsteroid );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); }

                    if ( isPlayer( ActiveSpaceship ) ) {

                        for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                            if ( PlayerSpaceship[i] == ActiveSpaceship ) {

                                Interface[i]->onDamage();

                                break; } } } } } }

        if ( !isPlayer( ActiveSpaceship ) && ActiveSpaceship->getController() != nullptr ) {

            ( (AIController*) ActiveSpaceship->getController() )->setClosestBodyDistance( ClosestBodyDistance );
            ( (AIController*) ActiveSpaceship->getController() )->setClosestBodyAcceleration( ClosestBodyAcceleration ); }

        if ( fabsf( ActiveSpaceship->getPosition().x ) > ( SQRT2_2ND * AreaRadius ) || fabsf( ActiveSpaceship->getPosition().y ) > ( SQRT2_2ND * AreaRadius ) ) {

            float Distance = getDistance( sf::Vector2f ( 0.f, 0.f ), ActiveSpaceship->getPosition() );

            if ( Distance > ( AreaRadius - 150.f ) && !isPlayer( ActiveSpaceship ) && ActiveSpaceship->getController() != nullptr ) {

                ( (AIController*) ActiveSpaceship->getController() )->enableLimitPanic(); }

            if ( Distance > ( AreaRadius + 450.f ) && isPlayer( ActiveSpaceship ) ) {

                for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                    if ( PlayerSpaceship[i] == ActiveSpaceship ) {

                        Interface[i]->enableArrow();

                        break; } } }

            else {

                for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                    if ( PlayerSpaceship[i] == ActiveSpaceship ) {

                        Interface[i]->disableArrow();

                        break; } } }

            if ( Distance > AreaRadius ) {

                ActiveSpaceship->updateHealth( - 10.f * ElapsedTime.asSeconds() ); } }

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

                            ParticleSystems.push_back( Explosion ); }

                        if ( isPlayer( FirstSpaceship ) ) {

                            for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                                if ( PlayerSpaceship[i] == FirstSpaceship ) {

                                    Interface[i]->onDamage();

                                    break; } } }

                        if ( isPlayer( SecondSpaceship ) ) {

                            for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                                if ( PlayerSpaceship[i] == SecondSpaceship ) {

                                    Interface[i]->onDamage();

                                    break; } } } } } } } }

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
            RayShot->setColor( ActiveSpaceship->getRayColor() );

            if ( Target ) {

                Target->updateHealth( - 0.5f *  ActiveSpaceship->getRayPower() );

                if ( isPlayer( ActiveSpaceship ) ) {

                    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                        if ( PlayerSpaceship[i] == ActiveSpaceship ) {

                            PlayerScore[i]->update( ScoreCounter::Event::ShotHit );

                            if ( Target->isDestructed() ) {

                                PlayerScore[i]->update( ScoreCounter::Event::ShotDestruction ); }

                            break; } } }

                if ( isPlayer( Target ) ) {

                    for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                        if ( PlayerSpaceship[i] == Target ) {

                            Interface[i]->onDamage();

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

            if ( isPlayer( ActiveSpaceship ) ) {

                for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                    if ( PlayerSpaceship[i] == ActiveSpaceship ) {

                        NewMissile->setSpaceship( ActiveSpaceship );
                        NewMissile->setScoreCounter( PlayerScore[i] );

                        break; } } }

            float TargetDistance, TargetAngle;
            Spaceship * Target = getAngularTarget( ActiveSpaceship, 2.f * PI / 3.f, TargetDistance, TargetAngle );

            sf::Vector2f MissilePosition = ActiveSpaceship->getPosition();
            MissilePosition.x += ( ActiveSpaceship->getRadius() + NewMissile->getRadius() + 5.f ) * cosf( ActiveSpaceship->getVelocityAngle() );
            MissilePosition.y += ( ActiveSpaceship->getRadius() + NewMissile->getRadius() + 5.f ) * sinf( ActiveSpaceship->getVelocityAngle() );

            NewMissile->setPosition( MissilePosition );
            NewMissile->setVelocity( ActiveSpaceship->getVelocity() );
            NewMissile->setTexture( Graphics->getTexture( "Missile" ) );
            NewMissile->setThrusterTexture( Graphics->getTexture( "Thruster" ) );
            NewMissile->setTarget( Target );

            Missiles.push_back( NewMissile ); } }

    // Delete destructed spaceships

    for ( auto i = Spaceships.begin(); i != Spaceships.end(); ) {

        if ( (*i)->isDestructed() ) {

            if ( Gameplay ) { // Messages for players' interfaces

                if ( !isPlayer( *i ) ) {

                    std::string EnemiesNotification;
                    auto EnemiesCount = (unsigned int) ( Spaceships.size() - getAlivePlayerCount() - 1 );

                    if ( EnemiesCount >= 5 ) {

                        if ( EnemiesCount % 5 == 0 ) {

                            EnemiesNotification = std::to_string( EnemiesCount ) + " enemies are left"; } }

                    else if ( EnemiesCount > 1 ) {

                        EnemiesNotification = std::to_string( EnemiesCount ) + " enemies are left"; }

                    else if ( EnemiesCount == 1 ) {

                        EnemiesNotification = "1 enemy is left"; }

                    else {

                        EnemiesNotification = "No enemies are left"; }

                    if ( !EnemiesNotification.empty() ) {

                        for ( unsigned int j = 0; j < PlayerCount; j++ ) {

                            displayNotification( EnemiesNotification ); } } }

                else if ( Gameplay->getEndingCondition() == GameplaySettings::LastPlayer || Gameplay->getEndingCondition() == GameplaySettings::LastSpaceship ) {

                    std::string AlivePlayersNotification;
                    unsigned int AlivePlayersCount = getAlivePlayerCount() - 1;

                    if ( AlivePlayersCount >= 5 ) {

                        if ( AlivePlayersCount % 5 == 0 ) {

                            AlivePlayersNotification = std::to_string( AlivePlayersCount ) + " players are left"; } }

                    else if ( AlivePlayersCount > 1 ) {

                        AlivePlayersNotification = std::to_string( AlivePlayersCount ) + " players are left"; }

                    else if ( AlivePlayersCount == 1 ) {

                        AlivePlayersNotification = "1 players is left"; }

                    else {

                        AlivePlayersNotification = "No players are left"; }

                    if ( !AlivePlayersNotification.empty() ) {

                        for ( unsigned int j = 0; j < PlayerCount; j++ ) {

                            displayNotification( AlivePlayersNotification ); } } } }

            destructBody( *i );
            i = Spaceships.erase( i ); }

        else {

            ++i; } } }

void GameModule::updateMissiles ( sf::Time ElapsedTime ) {

    // Update gravity acceleration, detect collisions with planets, asteroids and spaceships

    for ( auto ActiveMissile : Missiles ) {

        for ( auto ActivePlanet : Planets ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveMissile->getPosition(), ActivePlanet->getPosition() );

            Acceleration.x = Gravity * ActivePlanet->getMass() * ( ActivePlanet->getPosition().x - ActiveMissile->getPosition().x ) / ( Distance * Distance * Distance );
            Acceleration.y = Gravity * ActivePlanet->getMass() * ( ActivePlanet->getPosition().y - ActiveMissile->getPosition().y ) / ( Distance * Distance * Distance );

            ActiveMissile->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveMissile->getRadius() + ActivePlanet->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveMissile->onCollision( ActivePlanet );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        for ( auto ActiveAsteroid : Asteroids ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveMissile->getPosition(), ActiveAsteroid->getPosition() );

            Acceleration.x = Gravity * ActiveAsteroid->getMass() * ( ActiveAsteroid->getPosition().x - ActiveMissile->getPosition().x ) / ( Distance * Distance * Distance );
            Acceleration.y = Gravity * ActiveAsteroid->getMass() * ( ActiveAsteroid->getPosition().y - ActiveMissile->getPosition().y ) / ( Distance * Distance * Distance );

            ActiveMissile->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveMissile->getRadius() + ActiveAsteroid->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveMissile->onCollision( ActiveAsteroid );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); } } } }

        for ( auto ActiveSpaceship : Spaceships ) {

            sf::Vector2f Acceleration;
            float Distance = getDistance( ActiveMissile->getPosition(), ActiveSpaceship->getPosition() );

            Acceleration.x = Gravity * ActiveSpaceship->getMass() * ( ActiveSpaceship->getPosition().x - ActiveMissile->getPosition().x ) / ( Distance * Distance * Distance );
            Acceleration.y = Gravity * ActiveSpaceship->getMass() * ( ActiveSpaceship->getPosition().y - ActiveMissile->getPosition().y ) / ( Distance * Distance * Distance );

            ActiveMissile->updateVelocity( Acceleration, ElapsedTime );

            if ( Distance <= ( ActiveMissile->getRadius() + ActiveSpaceship->getRadius() ) ) {

                if ( true ) { // TODO ACCURATE CHECK

                    ParticleSystem * Explosion = ActiveMissile->onCollision( ActiveSpaceship );

                    if ( Explosion ) {

                        ParticleSystems.push_back( Explosion ); }

                    if ( isPlayer( ActiveSpaceship ) ) {

                        for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                            if ( PlayerSpaceship[i] == ActiveSpaceship ) {

                                Interface[i]->onDamage();

                                break; } } }

                    } } } }

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

            ActiveMissile->setTarget( getAngularTarget( ActiveMissile, 2.f * PI / 3.f ) ); }

        ActiveMissile->update( ElapsedTime ); }

    // Delete destructed missiles

    for ( auto i = Missiles.begin(); i != Missiles.end(); ) {

        if ( (*i)->isDestructed() ) {

            destructBody( *i );
            i = Missiles.erase( i ); }

        else {

            ++i; } } }

void GameModule::updatePowerUps ( sf::Time ElapsedTime ) {

    // Generate power ups

    PowerUpPauseTime -= ElapsedTime;

    if ( PowerUps.size() < PowerUpLimit && PowerUpPauseTime.asSeconds() <= 0.f ) {

        PowerUpPauseTime = PowerUpPauseDuration;

        sf::Vector2f Position ( 1000000.f, 1000000.f );
        float MinimumPlanetDistance = 200.f;
        float MinimumPowerUpDistance = 100.f;
        unsigned int Attempts = 25;

        while ( Attempts > 0 && Position == sf::Vector2f ( 1000000.f, 1000000.f ) ) {

            float Angle = ( - PI ) + getRandomFloat() * 2.f * PI;

            Position.x = getRandomFloat() * ( AreaRadius - 200.f ) * cosf( Angle );
            Position.y = getRandomFloat() * ( AreaRadius - 200.f ) * sinf( Angle );

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

        if ( Attempts > 0 ) {

            PowerUp * NewPowerUp = nullptr;
            float Draw = getRandomFloat();

            if ( Draw < 0.3f ) { // Health Power Ups (30%)

                if ( Draw < 0.15f ) { // Low Health Power Up (15%)

                    NewPowerUp = new LowHealthPowerUp ( Graphics, &Gravity, &AsteroidCount ); }

                else { // High Health Power Up (15%)

                    NewPowerUp = new HighHealthPowerUp ( Graphics, &Gravity, &AsteroidCount ); } }

            else if ( Draw < 0.6f ) { // Energy Power Ups (30%)

                if ( Draw < 0.45f ) { // Low Energy Power Up (15%)

                    NewPowerUp = new LowEnergyPowerUp ( Graphics, &Gravity, &AsteroidCount ); }

                else { // High Energy Power Up (15%)

                    NewPowerUp = new HighEnergyPowerUp ( Graphics, &Gravity, &AsteroidCount ); } }

            else if ( Draw < 0.9f ) { // Missile Power Up (30%)

                NewPowerUp = new MissilePowerUp ( Graphics, &Gravity, &AsteroidCount ); }

            else if ( Draw < 0.95f ) { // Asteroid Power Ups (5%)

                if ( Draw < 0.925f ) { // No Asteroid Power Up (2.5%)

                    NewPowerUp = new NoAsteroidsPowerUp ( Graphics, &Gravity, &AsteroidCount ); }

                else { // More Asteroids Power Up (2.5%)

                    NewPowerUp = new MoreAsteroidsPowerUp ( Graphics, &Gravity, &AsteroidCount ); } }

            else { // Gravity Power Ups (5%)

                if ( Draw < 0.965f ) { // Low Gravity Power Up (1.5%)

                    NewPowerUp = new LowGravityPowerUp ( Graphics, &Gravity, &AsteroidCount ); }

                else if ( Draw < 0.98f ) { // High Gravity Power Up (1.5%)

                    NewPowerUp = new HighGravityPowerUp ( Graphics, &Gravity, &AsteroidCount ); }

                else { // Random Gravity Power Up (2%)

                    NewPowerUp = new RandomGravityPowerUp ( Graphics, &Gravity, &AsteroidCount ); } }

            NewPowerUp->setPosition( Position );

            PowerUps.push_back( NewPowerUp ); } }

    // Detect collisions with spaceships

    for ( auto ActivePowerUp : PowerUps ) {

        if ( !ActivePowerUp->isCaught() ) {

            for ( auto ActiveSpaceship : Spaceships ) {

                float MinimumDistance = ActivePowerUp->getInfluenceRadius() + ActiveSpaceship->getRadius();

                if ( getMinDistance( ActivePowerUp->getPosition(), ActiveSpaceship->getPosition() ) <= MinimumDistance ) {

                    if ( getDistance( ActivePowerUp->getPosition(), ActiveSpaceship->getPosition() ) <= MinimumDistance ) {

                        ActivePowerUp->onCatch( ActiveSpaceship );

                        if ( ActivePowerUp->isGravityModifier() ) {

                            if ( GravityPowerUp != nullptr ) {

                                GravityPowerUp->finish(); }

                            else {

                                displayNotification( "Gravity will act weird for a while" ); }

                            GravityPowerUp = ActivePowerUp; }

                        if ( ActivePowerUp->isAsteroidModifier() ) {

                            if ( AsteroidPowerUp != nullptr ) {

                                AsteroidPowerUp->finish(); }

                            else {

                                displayNotification( "Asteroids will be disturbed for a while" ); }

                            AsteroidPowerUp = ActivePowerUp; }

                        break; } } } } }

    // Update power ups' state

    for ( auto ActivePowerUp : PowerUps ) {

        ActivePowerUp->update( ElapsedTime ); }

    // Delete inactive power ups

    for ( auto i = PowerUps.begin(); i != PowerUps.end(); ) {

        if ( (*i)->isExpired() ) {

            if ( (*i) == GravityPowerUp ) {

                GravityPowerUp = nullptr;

                displayNotification( "Gravity is back to normal" ); }

            if ( (*i) == AsteroidPowerUp ) {

                AsteroidPowerUp = nullptr;

                displayNotification( "Asteroids are back to normal" ); }

            delete (*i);
            i = PowerUps.erase( i ); }

        else {

            ++i; } } }

void GameModule::updateRayShots ( sf::Time ElapsedTime ) {

    // Update ray shots' state

    for ( auto ActiveRayShot : RayShots ) {

        ActiveRayShot->update( ElapsedTime ); }

    // Delete inactive ray shots

    for ( auto i = RayShots.begin(); i != RayShots.end(); ) {

        if ( !(*i)->isRenderingEnabled() ) {

            delete (*i);
            i = RayShots.erase( i ); }

        else {

            ++i; } } }

void GameModule::updateParticleSystems ( sf::Time ElapsedTime ) {

    // Update particle systems' state

    for ( auto ActiveParticleSystem : ParticleSystems ) {

        ActiveParticleSystem->update( ElapsedTime ); }

    // Delete inactive particle systems

    for ( auto i = ParticleSystems.begin(); i != ParticleSystems.end(); ) {

        if ( (*i)->getParticleCount() == 0 ) {

            delete (*i);
            i = ParticleSystems.erase( i ); }

        else {

            ++i; } } }

void GameModule::updateViews ( ) {

    ViewsOutline.clear();

    float ViewWidth = ( 900.f / Graphics->getWindowHeight() ) * Graphics->getWindowWidth();
    float ViewHeight = 900.f;

    float ViewOutlineThickness = 1.5f;
    sf::Color ViewOutlineColor = sf::Color( 13, 71, 161 ); // #0D47A1

    if ( PlayerCount > 1 ) {

        if ( Interface[0]->getFadeInAlpha() != 0.f ) {

            ViewOutlineColor.a = (sf::Uint8) ( 255 * ( 1.f - Interface[0]->getFadeInAlpha() ) ); }

        else if ( EndingCondition ) {

            float Alpha = 1.f;

            for ( unsigned int i = 0; i < PlayerCount; i++ ) {

                Alpha = fminf( Alpha, Interface[i]->getFadeOutAlpha() ); }

            ViewOutlineColor.a = (sf::Uint8) ( 255 * ( 1.f - Alpha ) ); } }

    if ( PlayerCount == 1 ) {

        Views[0].setSize( ViewWidth, ViewHeight );
        Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 1.f, 1.f ) ); }

    else if ( PlayerCount == 2 ) {

        if ( ViewWidth >= ViewHeight ) {

            Views[0].setSize( ViewWidth / 2.f, ViewHeight );
            Views[1].setSize( ViewWidth / 2.f, ViewHeight );
            Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 0.5f, 1.f ) );
            Views[1].setViewport( sf::FloatRect( 0.5f, 0.f, 0.5f, 1.f ) );

            ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f, 0.f ), ViewOutlineColor ) );
            ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f, Graphics->getWindowHeight() ), ViewOutlineColor ) );
            ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f + ViewOutlineThickness, Graphics->getWindowHeight() ), ViewOutlineColor ) );
            ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f + ViewOutlineThickness, 0.f ), ViewOutlineColor ) ); }

        else {

            Views[0].setSize( ViewWidth, ViewHeight / 2.f );
            Views[1].setSize( ViewWidth, ViewHeight / 2.f );
            Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 1.f, 0.5f ) );
            Views[1].setViewport( sf::FloatRect( 0.f, 0.5f, 1.f, 0.5f ) );

            ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( 0.f, Graphics->getWindowHeight() / 2.f ), ViewOutlineColor ) );
            ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth(), Graphics->getWindowHeight() / 2.f ), ViewOutlineColor ) );
            ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth(), Graphics->getWindowHeight() / 2.f + ViewOutlineThickness ), ViewOutlineColor ) );
            ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( 0.f, Graphics->getWindowHeight() / 2.f + ViewOutlineThickness ), ViewOutlineColor ) ); } }

    else if ( PlayerCount == 3 ) {

        Views[0].setSize( ViewWidth / 2.f, 0.6f * ViewHeight );
        Views[1].setSize( ViewWidth / 2.f, 0.6f * ViewHeight );
        Views[2].setSize( ViewWidth, 0.4f * ViewHeight );
        Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 0.5f, 0.6f ) );
        Views[1].setViewport( sf::FloatRect( 0.5f, 0.f, 0.5f, 0.6f ) );
        Views[2].setViewport( sf::FloatRect( 0.f, 0.6f, 1.f, 0.4f ) );

        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( 0.f, 0.6f * Graphics->getWindowHeight() ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth(), 0.6f * Graphics->getWindowHeight() ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth(), 0.6f * Graphics->getWindowHeight() + ViewOutlineThickness ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( 0.f, 0.6f * Graphics->getWindowHeight() + ViewOutlineThickness ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f, 0.f ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f, 0.6f * Graphics->getWindowHeight() ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f + ViewOutlineThickness, 0.6f * Graphics->getWindowHeight() ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f + ViewOutlineThickness, 0.f ), ViewOutlineColor ) ); }

    else if ( PlayerCount == 4 ) {

        Views[0].setSize( ViewWidth / 2.f, ViewHeight / 2.f );
        Views[1].setSize( ViewWidth / 2.f, ViewHeight / 2.f );
        Views[2].setSize( ViewWidth / 2.f, ViewHeight / 2.f );
        Views[3].setSize( ViewWidth / 2.f, ViewHeight / 2.f );
        Views[0].setViewport( sf::FloatRect( 0.f, 0.f, 0.5f, 0.5f ) );
        Views[1].setViewport( sf::FloatRect( 0.5f, 0.f, 0.5f, 0.5f ) );
        Views[2].setViewport( sf::FloatRect( 0.f, 0.5f, 0.5f, 0.5f ) );
        Views[3].setViewport( sf::FloatRect( 0.5f, 0.5f, 0.5f, 0.5f ) );

        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( 0.f, Graphics->getWindowHeight() / 2.f ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth(), Graphics->getWindowHeight() / 2.f ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth(), Graphics->getWindowHeight() / 2.f + ViewOutlineThickness ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( 0.f, Graphics->getWindowHeight() / 2.f + ViewOutlineThickness ), ViewOutlineColor ) );

        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f, 0.f ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f, Graphics->getWindowHeight() ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f + ViewOutlineThickness, Graphics->getWindowHeight() ), ViewOutlineColor ) );
        ViewsOutline.emplace_back( sf::Vertex( sf::Vector2f( Graphics->getWindowWidth() / 2.f + ViewOutlineThickness, 0.f ), ViewOutlineColor ) ); } }

void GameModule::renderViewsOutline ( sf::RenderWindow &Window ) {

    Window.draw( &ViewsOutline[0], ViewsOutline.size(), sf::Quads ); }

void GameModule::initAreaLimit ( ) {

    AreaLimit.resize( 1000 );

    for ( unsigned int i = 0; i < 1000; i++ ) {

        AreaLimit[i].position.x = AreaRadius * cosf( 2.f * PI * ( i / 1000.f ) );
        AreaLimit[i].position.y = AreaRadius * sinf( 2.f * PI * ( i / 1000.f ) );
        AreaLimit[i].color = sf::Color::White; } }

void GameModule::renderAreaLimit ( sf::RenderWindow &Window ) {

    Window.draw( &AreaLimit[0], AreaLimit.size(), sf::Lines ); }
