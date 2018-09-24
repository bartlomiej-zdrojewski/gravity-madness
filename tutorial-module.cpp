#include "tutorial-module.hpp"

/*
 *
0. Ruch w przód, w tył, lewo i prawo - wleć do kółka zanim umrzesz
1. Ruch wokół planety - nie wpadnij w planetę
2. Bonusy - złap bonusy by odnowić energię i życie
3. Lasery - zniszcz przeciwnika używając laserów
4. Pociski - zniszcz przeciwnika używając pocisków
5. Asteroidy - przeżyj deszcz asteroid
6. Grawitacja - przeżyj 30 sekund zanim grawitacja się ustabilizuje
 *
 */

TutorialModule::TutorialModule ( GraphicsModule * Graphics, GameModule * Game, GameplaySettings * Gameplay ) {

    this->Graphics = Graphics;
    this->Game = Game;
    this->Gameplay = Gameplay;

    for ( unsigned int i = 0; i < 7; i++ ) {

        Challenges.emplace_back( Challenge() );
        Challenges[i].Index = i + 1; }

    Challenges[0].AreaRadius = 100.f;
    Challenges[0].EndingCondition = Challenge::EndingConditions::InAreaAndNoVelocity;
    Challenges[0].PlayerPosition = sf::Vector2f( 400.f, 800.f );
    Challenges[0].PlayerVelocity = sf::Vector2f( 0.f, - 25.f );

    Challenges[1].EndingCondition = Challenge::EndingConditions::Time;
    Challenges[1].TimeLimit = sf::seconds( 30.f );
    Challenges[1].PlayerPosition = sf::Vector2f( - 450.f, - 300.f );
    Challenges[1].PlayerVelocity = sf::Vector2f( 50.f, 0.f );
    Challenges[1].Planet = true;

    Challenges[2].EndingCondition = Challenge::EndingConditions::NoPowerUps;
    Challenges[2].PlayerPosition = sf::Vector2f( 450.f, - 300.f );
    Challenges[2].PlayerVelocity = sf::Vector2f( - 50.f, 0.f );
    Challenges[2].Planet = true;
    Challenges[2].LowHealthPowerUpPrototype = new LowHealthPowerUp ( Graphics, &Game->Gravity, &Game->AsteroidCount );
    Challenges[2].LowHealthPowerUpPrototype->setPosition( sf::Vector2f( 0.f, 225.f ) );

    Challenges[3].AreaRadius = 700.f;
    Challenges[3].EndingCondition = Challenge::EndingConditions::NoEnemies;
    Challenges[3].PlayerPosition = sf::Vector2f( 450.f, 450.f );
    Challenges[3].PlayerVelocity = sf::Vector2f( - 50.f, 0.f );
    Challenges[3].PlayerRay = true;
    Challenges[3].Planet = true;
    Challenges[3].PlanetRadius = 200.f;
    Challenges[3].PlanetMass = 3000000.f;
    Challenges[3].Enemy = true;
    Challenges[3].EnemyPosition = sf::Vector2f( - 450.f, - 450.f );
    Challenges[3].EnemyVelocity = sf::Vector2f( 50.f, 0.f );

    Challenges[4].AreaRadius = 700.f;
    Challenges[4].EndingCondition = Challenge::EndingConditions::NoEnemies;
    Challenges[4].PlayerPosition = sf::Vector2f( - 450.f, 450.f );
    Challenges[4].PlayerVelocity = sf::Vector2f( 50.f, 0.f );
    Challenges[4].PlayerMissile = true;
    Challenges[4].Planet = true;
    Challenges[4].PlanetRadius = 200.f;
    Challenges[4].PlanetMass = 3000000.f;
    Challenges[4].Enemy = true;
    Challenges[4].EnemyPosition = sf::Vector2f( 450.f, - 450.f );
    Challenges[4].EnemyVelocity = sf::Vector2f( - 50.f, 0.f );

    Challenges[5].AreaRadius = 500.f;
    Challenges[5].EndingCondition = Challenge::EndingConditions::NoPowerUpsAndTime;
    Challenges[5].TimeLimit = sf::seconds( 15.f );
    Challenges[5].PlayerPosition = sf::Vector2f( 50.f, - 325.f );
    Challenges[5].PlayerVelocity = sf::Vector2f( - 50.f, 0.f );
    Challenges[5].Planet = true;
    Challenges[5].PlanetMass = 5000000.f;
    Challenges[5].RandomGravityPowerUpPrototype = new RandomGravityPowerUp ( Graphics, &Game->Gravity, &Game->AsteroidCount );
    Challenges[5].RandomGravityPowerUpPrototype->setPosition( sf::Vector2f( 0.f, 325.f ) );

    Challenges[6].AreaRadius = 500.f;
    Challenges[6].AsteroidCount = 100;
    Challenges[6].EndingCondition = Challenge::EndingConditions::Time;
    Challenges[6].TimeLimit = sf::seconds( 60.f );
    Challenges[6].PlayerPosition = sf::Vector2f( -50.f, 325.f );
    Challenges[6].PlayerVelocity = sf::Vector2f( 50.f, 0.f );
    Challenges[6].Planet = true;
    Challenges[6].PlanetMass = 5000000.f;

    ChallengeIndex = -1;
    loadNextChallenge(); }

void TutorialModule::update ( ) {

    sf::Time ElapsedTime = Clock.restart();

    if ( ElapsedTime.asSeconds() <= 0.1f ) {

        // TODO LOW FPS MESSAGE

         }

    if ( ChallengeState == 0 ) { // Reset challenge

        ChallengeIndex--;
        loadNextChallenge(); }

    if ( ChallengeState == 1 ) { // Pre-challenge manual

        // TODO PRE-CHALLENGE MANUAL
        ChallengeState = 2;

        }

    else if ( ChallengeState == 2 ) { // Actual challenge

        Game->update();

        if ( Challenges[ ChallengeIndex ].EndingCondition == Challenge::EndingConditions::None ) { // No challenge

            ChallengeState = 5; }

        else if ( Game->getAlivePlayerCount() == 0 ) { // Player was destructed

            ChallengeState = 3; }

        else { // Checking ending condition

            switch ( Challenges[ ChallengeIndex ].EndingCondition ) {

                case Challenge::EndingConditions::Time: {

                    ChallengeTime += ElapsedTime;

                    if ( ChallengeTime > Challenges[ ChallengeIndex ].TimeLimit ) {

                        Game->PlayerInterface[0]->beginFadeOut();

                        ChallengeState = 4; }

                    break; }

                case Challenge::EndingConditions::InAreaAndNoVelocity: {

                    float Distance = sqrtf( powf( Game->PlayerSpaceship[0]->getPosition().x, 2.f ) + powf( Game->PlayerSpaceship[0]->getPosition().y, 2.f ) );
                    float Velocity = sqrtf( powf( Game->PlayerSpaceship[0]->getVelocity().x, 2.f ) + powf( Game->PlayerSpaceship[0]->getVelocity().y, 2.f ) );

                    if ( Distance < Challenges[ ChallengeIndex ].AreaRadius && Velocity < 10.f ) {

                        Game->PlayerInterface[0]->beginFadeOut();

                        ChallengeState = 4; }

                    break; }

                case Challenge::EndingConditions::NoPowerUps: {

                    if ( Game->PowerUps.empty() ) {

                        Game->PlayerInterface[0]->beginFadeOut();

                        ChallengeState = 4; }

                    break; }

                case Challenge::EndingConditions::NoPowerUpsAndTime: {

                    if ( Game->PowerUps.empty() ) {

                        ChallengeTime += ElapsedTime;

                        if ( ChallengeTime > Challenges[ ChallengeIndex ].TimeLimit ) {

                            Game->PlayerInterface[0]->beginFadeOut();

                            ChallengeState = 4; } }

                    break; }

                case Challenge::EndingConditions::NoEnemies: {

                    if ( Game->Spaceships.size() == 1 ) {

                        Game->PlayerInterface[0]->beginFadeOut();

                        ChallengeState = 4; }

                    break; }

                default: break; } } }

    else if ( ChallengeState == 3 ) { // Failure

        Game->update();

        if ( Game->PlayerInterface[0]->isFadedOut() ) {

            ChallengeState = 0; } }

    else if ( ChallengeState == 4 ) { // Success

        Game->update();

        if ( Game->PlayerInterface[0]->isFadedOut() ) {

            ChallengeState = 5; } }

    else if ( ChallengeState == 5 ) { // Load next challenge or terminate

        if ( !loadNextChallenge() ) {

            Terminate = true; } } }

void TutorialModule::update ( sf::Event &Event ) {

    if ( ChallengeState == 1 ) { // Pre-challenge manual

        // TODO PRE-CHALLENGE MANUAL
        // ChallengeState = 2;

        }

    else if ( ChallengeState == 2 ) { // Actual challenge

        Game->update( Event ); }

    else if ( ChallengeState == 3 || ChallengeState == 4 ) { // Failure / Success

        if ( Event.type == sf::Event::KeyPressed ) {

            if ( Event.key.code == sf::Keyboard::Escape || Event.key.code == sf::Keyboard::Enter || Event.key.code == sf::Keyboard::Space ) {

                Game->PlayerInterface[0]->endFadeOut(); } }

        Game->update( Event ); } }

void TutorialModule::render ( sf::RenderWindow &Window ) {

    if ( ChallengeState == 1 ) { // Pre-challenge manual

        // TODO PRE-CHALLENGE MANUAL

        }

    else if ( ChallengeState == 2 ) { // Actual challenge

        Game->render( Window ); }

    else if ( ChallengeState == 3 ) { // Failure

        Game->render( Window ); }

    else if ( ChallengeState == 4 ) { // Success

        Game->render( Window ); } }

bool TutorialModule::onTerminate ( ) {

    if ( Terminate ) {

        ChallengeIndex = -1;
        loadNextChallenge();

        return true; }

    return false; }

Spaceship * TutorialModule::getPlayerSpaceship ( ) {

    auto * NewSpaceship = new Spaceship ( 400.00, 40.00 );

    NewSpaceship->getShape()->loadOutline( "(0.71,0.00),(1.00,135.00),(0.37,154.00),(0.44,180.00),(0.35,-154.00),(1.00,-135.00)", 40.00 ); // TODO LOAD SHAPE
    NewSpaceship->setHealthLimit( 100.00 );
    NewSpaceship->setHealth( 100.00 );
    NewSpaceship->setHealthRestoration( 0.f );
    NewSpaceship->setEnergyLimit( 1000.f );
    NewSpaceship->setEnergy( 1000.f );
    NewSpaceship->setEnergyRestoration( 25.f );
    NewSpaceship->setThrust( 100.f );
    NewSpaceship->setBrakingFactor( 0.75 );
    NewSpaceship->setRayPower( 25.f );
    NewSpaceship->setRayColor( sf::Color( 245, 0, 87 ) ); // #F50057
    NewSpaceship->setMissileLimit( 5 );
    NewSpaceship->setMissileCount( 5 );
    NewSpaceship->setTexture( Graphics->getTexture( "Spaceship" ) );
    NewSpaceship->setAccentTexture( Graphics->getTexture( "SpaceshipAccent" ), Gameplay->getPlayerColor( 0 ) );
    NewSpaceship->setThrusterTexture( Graphics->getTexture( "Thruster" ), sf::Color( 255, 64, 129 ) ); // #FF4081

    return NewSpaceship; }

Spaceship * TutorialModule::getEnemySpaceship ( ) {

    auto * NewSpaceship = new Spaceship ( 400.00, 40.00 );

    NewSpaceship->getShape()->loadOutline( "(0.71,0.00),(1.00,135.00),(0.37,154.00),(0.44,180.00),(0.35,-154.00),(1.00,-135.00)", 40.00 ); // TODO LOAD SHAPE
    NewSpaceship->setHealthLimit( 100.00 );
    NewSpaceship->setHealth( 100.00 );
    NewSpaceship->setHealthRestoration( 0.f );
    NewSpaceship->setEnergyLimit( 10000.f );
    NewSpaceship->setEnergy( 10000.f );
    NewSpaceship->setEnergyRestoration( 50.f );
    NewSpaceship->setThrust( 100.f );
    NewSpaceship->setBrakingFactor( 0.75 );
    NewSpaceship->setRayPower( 75.f );
    NewSpaceship->setRayColor( sf::Color( 245, 0, 87 ) ); // #F50057
    NewSpaceship->setMissileLimit( 5 );
    NewSpaceship->setMissileCount( 5 );
    NewSpaceship->setTexture( Graphics->getTexture( "Spaceship" ) );
    NewSpaceship->setAccentTexture( Graphics->getTexture( "SpaceshipAccent" ), Gameplay->getPlayerColor( 0 ) );
    NewSpaceship->setThrusterTexture( Graphics->getTexture( "Thruster" ), sf::Color( 255, 64, 129 ) ); // #FF4081

    return NewSpaceship; }

void TutorialModule::reset ( ) {

    Terminate = false;
    ChallengeTime = sf::seconds( 0.f );
    ChallengeState = 0;

    Game->reset();
    delete Game->PlayerScore[0];

    Game->AsteroidCount = 0;
    Game->AsteroidPauseTime = sf::seconds( 0.f );
    Game->AsteroidPauseDuration = sf::seconds( 0.5f );
    Game->PowerUpLimit = 0;
    Game->PlayerCount = 1;

    Game->PlayerSpaceship[0] = getPlayerSpaceship();
    Game->PlayerSpaceship[0]->setController( new PlayerController ( Gameplay->getControllerSettings( 0 ) ) );
    Game->PlayerScore[0] = new ScoreCounter ( );
    Game->PlayerInterface[0] = new Interface ( Graphics );
    Game->PlayerInterface[0]->setSpaceship( Game->PlayerSpaceship[0] );
    Game->PlayerInterface[0]->setScoreCounter( Game->PlayerScore[0] );
    Game->Spaceships.push_back( Game->PlayerSpaceship[0] ); }

bool TutorialModule::loadNextChallenge ( ) {

    ChallengeIndex++;

    if ( ChallengeIndex < Challenges.size() ) {

        reset();

        Game->AreaRadius = Challenges[ ChallengeIndex ].AreaRadius;
        Game->AsteroidCount = Challenges[ ChallengeIndex ].AsteroidCount;
        Game->initAreaLimit();

        Game->PlayerSpaceship[0]->setPosition( Challenges[ ChallengeIndex ].PlayerPosition );
        Game->PlayerSpaceship[0]->setVelocity( Challenges[ ChallengeIndex ].PlayerVelocity );

        if ( !Challenges[ ChallengeIndex ].PlayerRay ) {

            Game->PlayerSpaceship[0]->setRayPower( 0.f ); }

        if ( !Challenges[ ChallengeIndex ].PlayerMissile ) {

            Game->PlayerSpaceship[0]->setMissileCount( 0 ); }

        if ( Challenges[ ChallengeIndex ].Planet ) {

            auto * NewPlanet = new Planet ( Graphics, Challenges[ ChallengeIndex ].PlanetMass, Challenges[ ChallengeIndex ].PlanetRadius );

            NewPlanet->setPosition( Challenges[ ChallengeIndex ].PlanetPosition );

            Game->Planets.push_back( NewPlanet ); }

        if ( Challenges[ ChallengeIndex ].Enemy ) {

            Spaceship * NewSpaceship = getEnemySpaceship();

            NewSpaceship->setPosition( Challenges[ ChallengeIndex ].EnemyPosition );
            NewSpaceship->setVelocity( Challenges[ ChallengeIndex ].EnemyVelocity );
            NewSpaceship->setController( new PassiveAIController() );

            Game->Spaceships.push_back( NewSpaceship ); }

        if ( Challenges[ ChallengeIndex ].LowHealthPowerUpPrototype != nullptr ) {

            Game->PowerUps.push_back( (LowHealthPowerUp*) Challenges[ ChallengeIndex ].LowHealthPowerUpPrototype->clone( Graphics ) ); }

        if ( Challenges[ ChallengeIndex ].RandomGravityPowerUpPrototype != nullptr ) {

            Game->PowerUps.push_back( (RandomGravityPowerUp*) Challenges[ ChallengeIndex ].RandomGravityPowerUpPrototype->clone( Graphics ) ); }

        ChallengeState++;

        return true; }

    return false; }
