#include "tutorial-module.hpp"

TutorialModule::TutorialModule ( GraphicsModule * Graphics, GameModule * Game, GameplaySettings * Gameplay ) {

    this->Graphics = Graphics;
    this->Game = Game;
    this->Gameplay = Gameplay;

    for ( unsigned int i = 0; i < 9; i++ ) {

        Challenges.emplace_back( Challenge() ); }

    Challenges[0].Index = 0;
    Challenges[0].Title = "Welcome to the tutorial!";
    Challenges[0].Description = "You've made a wise decision to come here. After just seven short "
                                "challenges you will be ready to beat any obstacle you may encounter "
                                "in the game. I'll teach you how to move in gravitational field, shoot "
                                "rays and missiles, maneuver in asteroid rain and generally not die. "
                                "You know, the fun stuff. Shall we?";
    Challenges[0].EndingCondition = Challenge::EndingConditions::None;

    Challenges[1].Index = 1;
    Challenges[1].Title = "Get into the game area";
    Challenges[1].Description = "NON STATIC DESCRIPTION";
    Challenges[1].AreaRadius = 100.f;
    Challenges[1].EndingCondition = Challenge::EndingConditions::InAreaAndNoVelocity;
    Challenges[1].PlayerPosition = sf::Vector2f( 400.f, 800.f );
    Challenges[1].PlayerVelocity = sf::Vector2f( 0.f, - 25.f );

    Challenges[2].Index = 2;
    Challenges[2].Title = "Orbit the planet for 30 seconds";
    Challenges[2].Description = "Wow, you're fast! Now something more technical. You have to learn how "
                                "to orbit the planets. You can do it like an absolute madman and use all "
                                "your fuel or you can do it like the real pilots do. You see, when you "
                                "move fast enough horizontally in relation to planet's surface, you will "
                                "never hit it. So just try to keep the constant altitude. Got it?";
    Challenges[2].EndingCondition = Challenge::EndingConditions::Time;
    Challenges[2].TimeLimit = sf::seconds( 30.f );
    Challenges[2].PlayerPosition = sf::Vector2f( - 450.f, - 300.f );
    Challenges[2].PlayerVelocity = sf::Vector2f( 50.f, 0.f );
    Challenges[2].Planet = true;

    Challenges[3].Index = 3;
    Challenges[3].Title = "Catch a power up";
    Challenges[3].Description = "Okay, this one is simple. There are several types of power ups. Some "
                                "will restore your health or your energy, some will give you additional "
                                "missiles and some will modify asteroids' or gravity's behaviour. The last "
                                "ones are the most fun, we will get back to them later. But now, you just "
                                "have to catch a health power up to restore, you guessed it, your health. "
                                "Or wait for it to disappear, if you are a rebel. So?";
    Challenges[3].EndingCondition = Challenge::EndingConditions::PowerUpCaught;
    Challenges[3].PlayerPosition = sf::Vector2f( 450.f, - 300.f );
    Challenges[3].PlayerVelocity = sf::Vector2f( - 50.f, 0.f );
    Challenges[3].Planet = true;
    Challenges[3].LowHealthPowerUpPrototype = new LowHealthPowerUp ( Graphics, &Game->Gravity, &Game->AsteroidCount );
    Challenges[3].LowHealthPowerUpPrototype->setPosition( sf::Vector2f( 0.f, 225.f ) );

    Challenges[4].Index = 4;
    Challenges[4].Title = "Destroy an enemy using ray";
    Challenges[4].Description = "NON STATIC DESCRIPTION";
    Challenges[4].AreaRadius = 700.f;
    Challenges[4].EndingCondition = Challenge::EndingConditions::NoEnemies;
    Challenges[4].PlayerPosition = sf::Vector2f( 450.f, 450.f );
    Challenges[4].PlayerVelocity = sf::Vector2f( - 50.f, 0.f );
    Challenges[4].PlayerRay = true;
    Challenges[4].Planet = true;
    Challenges[4].PlanetRadius = 200.f;
    Challenges[4].PlanetMass = 3000000.f;
    Challenges[4].Enemy = true;
    Challenges[4].EnemyPosition = sf::Vector2f( - 450.f, - 450.f );
    Challenges[4].EnemyVelocity = sf::Vector2f( 50.f, 0.f );

    Challenges[5].Index = 5;
    Challenges[5].Title = "Destroy an enemy using missile";
    Challenges[5].Description = "NON STATIC DESCRIPTION";
    Challenges[5].AreaRadius = 700.f;
    Challenges[5].EndingCondition = Challenge::EndingConditions::NoEnemies;
    Challenges[5].PlayerPosition = sf::Vector2f( - 450.f, 450.f );
    Challenges[5].PlayerVelocity = sf::Vector2f( 50.f, 0.f );
    Challenges[5].PlayerMissile = true;
    Challenges[5].Planet = true;
    Challenges[5].PlanetRadius = 200.f;
    Challenges[5].PlanetMass = 3000000.f;
    Challenges[5].Enemy = true;
    Challenges[5].EnemyPosition = sf::Vector2f( 450.f, - 450.f );
    Challenges[5].EnemyVelocity = sf::Vector2f( - 50.f, 0.f );

    Challenges[6].Index = 6;
    Challenges[6].Title = "Survive random gravity for 30 seconds";
    Challenges[6].Description = "Enough of killing. It's time to face the forces of nature! Gravity, "
                                "to be specific. Your task is to catch a random gravity power up and "
                                "survive for the next 30 seconds. There are also low and high gravity "
                                "power ups, but with the random one you will experience both of them "
                                "at once. Wanna try?";
    Challenges[6].AreaRadius = 500.f;
    Challenges[6].EndingCondition = Challenge::EndingConditions::PowerUpCaughtAndTime;
    Challenges[6].TimeLimit = sf::seconds( 35.f );
    Challenges[6].PlayerPosition = sf::Vector2f( 50.f, - 325.f );
    Challenges[6].PlayerVelocity = sf::Vector2f( - 50.f, 0.f );
    Challenges[6].Planet = true;
    Challenges[6].PlanetMass = 5000000.f;
    Challenges[6].RandomGravityPowerUpPrototype = new RandomGravityPowerUp ( Graphics, &Game->Gravity, &Game->AsteroidCount );
    Challenges[6].RandomGravityPowerUpPrototype->setPosition( sf::Vector2f( 0.f, 325.f ) );

    Challenges[7].Index = 7;
    Challenges[7].Title = "Survive asteroid rain for 60 seconds";
    Challenges[7].Description = "And finally, last but not least, the asteroid rain! It's simple, "
                                "the asteroids will fall on the planet and you just have to stay "
                                "alive for 60 seconds. The effect may be a little exaggerated, but "
                                "it's good for practice. Just don't get hit and if you do, try not "
                                "to crash into the planet. Are you prepared for your last challenge?";
    Challenges[7].AreaRadius = 500.f;
    Challenges[7].AsteroidCount = 100;
    Challenges[7].EndingCondition = Challenge::EndingConditions::Time;
    Challenges[7].TimeLimit = sf::seconds( 60.f );
    Challenges[7].PlayerPosition = sf::Vector2f( -50.f, 325.f );
    Challenges[7].PlayerVelocity = sf::Vector2f( 50.f, 0.f );
    Challenges[7].Planet = true;
    Challenges[7].PlanetMass = 5000000.f;

    Challenges[8].Index = 0;
    Challenges[8].Title = "You did it! Congrats!";
    Challenges[8].Description = "Now, without a doubt, you're ready to play some real matches! And "
                                "remember, you can always customize your game, which includes selecting "
                                "the number of players and types of spaceships. Playing with friends "
                                "is always fun! You will probably need some joysticks, but I'm sure "
                                "you, the champion of the tutorial, will manage it easily. So, my brave "
                                "player, are you ready to play on the big arena?";
    Challenges[8].EndingCondition = Challenge::EndingConditions::None;

    ChallengeIndex = -1;
    MenuOptionCount = 2;
    MenuOptionText[0] = "I'm ready!";
    MenuOptionText[1] = "I give up, let me leave.";

    loadNextChallenge();
    update(); }

void TutorialModule::update ( ) {

    sf::Time ElapsedTime = Clock.restart();

    if ( ElapsedTime.asSeconds() <= 0.1f ) {

        // TODO LOW FPS MESSAGE

        }

    if ( ChallengeState == 0 ) { // Reset challenge

        ChallengeIndex--;
        loadNextChallenge(); }

    if ( ChallengeState == 1 ) { // Pre-challenge manual

        TitleFontSize = 100;
        SubTitleFontSize = 100;
        ContentFontSize = 100;
        MenuOptionFontSize = 100;

        TitlePosition = 0.05f * Graphics->getWindowHeight();
        SubTitlePosition = 0.15f * Graphics->getWindowHeight();
        ContentPosition = 0.25f * Graphics->getWindowHeight();
        MenuOptionPosition[0] = 0.8f * Graphics->getWindowHeight();
        MenuOptionPosition[1] = 0.87f * Graphics->getWindowHeight();

        float ContentHeight = 0.5f * Graphics->getWindowHeight();

        if ( Challenges[ ChallengeIndex ].Index != 0 ) {

            TitleText = "Challenge #" + std::to_string( Challenges[ ChallengeIndex ].Index );
            SubTitleText = Challenges[ ChallengeIndex ].Title; }

        else {

            TitleText = Challenges[ ChallengeIndex ].Title;

            SubTitlePosition -= Graphics->getWindowHeight();
            ContentPosition -= 0.07f * Graphics->getWindowHeight();
            ContentHeight += 0.07f * Graphics->getWindowHeight(); }

        ContentText = Challenges[ ChallengeIndex ].Description;

        size_t DividerShift;

        if ( Graphics->getWindowHeight() < 600.f ) {

            DividerShift = 55; }

        else if ( Graphics->getWindowHeight() >= 600.f && Graphics->getWindowHeight() <= 800.f ) {

            DividerShift = 55; }

        else if ( Graphics->getWindowHeight() > 800.f && Graphics->getWindowHeight() <= 1000.f ) {

            DividerShift = 60; }

        else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

            DividerShift = 60; }

        else {

            DividerShift = 65; }

        size_t DividerPosition = DividerShift;

        do {

            size_t NextSpace = ContentText.find( ' ', DividerPosition );
            size_t NextComma = ContentText.find( ',', DividerPosition - 6 );
            size_t NextPoint = ContentText.find( '.', DividerPosition - 6 );

            if ( NextPoint != std::string::npos && abs( (int) NextPoint - (int) DividerPosition ) < 6 ) {

                DividerPosition = NextPoint + 1; }

            else if ( NextComma != std::string::npos && abs( (int) NextComma - (int) DividerPosition ) < 6 ) {

                DividerPosition = NextComma + 1; }

            else {

                DividerPosition = NextSpace; }

            if ( DividerPosition != std::string::npos ) {

                ContentText.replace( DividerPosition, 1, "\n" );

                DividerPosition += DividerShift; } }

        while ( DividerPosition != std::string::npos && DividerPosition < ( ContentText.length() - 12 ) );

        sf::Text PrototypeText;
        PrototypeText.setString( "Challenge #0" );
        PrototypeText.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
        PrototypeText.setCharacterSize( TitleFontSize );

        while ( PrototypeText.getLocalBounds().height > ( 0.08f * Graphics->getWindowHeight() ) ) {

            PrototypeText.setCharacterSize( --TitleFontSize ); }

        while ( PrototypeText.getLocalBounds().width > ( 0.75f * Graphics->getWindowWidth() ) ) {

            PrototypeText.setCharacterSize( --TitleFontSize ); }

        SubTitleFontSize = TitleFontSize;

        PrototypeText.setString( "Get into the game area" );
        PrototypeText.setCharacterSize( SubTitleFontSize );

        while ( PrototypeText.getLocalBounds().height > ( 0.05f * Graphics->getWindowHeight() ) ) {

            PrototypeText.setCharacterSize( --SubTitleFontSize ); }

        PrototypeText.setString( ContentText );
        PrototypeText.setCharacterSize( ContentFontSize );

        while ( PrototypeText.getLocalBounds().height > ContentHeight ) {

            PrototypeText.setCharacterSize( --ContentFontSize ); }

        while ( PrototypeText.getLocalBounds().width > ( 0.9f * Graphics->getWindowWidth() ) ) {

            PrototypeText.setCharacterSize( --ContentFontSize ); }

        MenuOptionFontSize = TitleFontSize;

        PrototypeText.setString( MenuOptionText[1] );
        PrototypeText.setCharacterSize( MenuOptionFontSize );

        while ( PrototypeText.getLocalBounds().height > ( 0.05f * Graphics->getWindowHeight() ) ) {

            PrototypeText.setCharacterSize( --MenuOptionFontSize ); } }

    else if ( ChallengeState == 2 ) { // Actual challenge

        Game->update();

        if ( Challenges[ ChallengeIndex ].EndingCondition == Challenge::EndingConditions::None ) { // No challenge

            ChallengeState = 5; }

        else if ( Game->getAlivePlayerCount() == 0 ) { // Player was destructed

            ChallengeState = 3; }

        else { // Check ending condition

            switch ( Challenges[ ChallengeIndex ].EndingCondition ) {

                case Challenge::EndingConditions::Time: {

                    ChallengeTime += ElapsedTime;

                    if ( ChallengeTime > Challenges[ ChallengeIndex ].TimeLimit ) {

                        Game->displayNotification( "Success!" );
                        Game->PlayerInterface[0]->beginFadeOut();

                        ChallengeState = 4; }

                    break; }

                case Challenge::EndingConditions::InAreaAndNoVelocity: {

                    float Distance = sqrtf( powf( Game->PlayerSpaceship[0]->getPosition().x, 2.f ) + powf( Game->PlayerSpaceship[0]->getPosition().y, 2.f ) );
                    float Velocity = sqrtf( powf( Game->PlayerSpaceship[0]->getVelocity().x, 2.f ) + powf( Game->PlayerSpaceship[0]->getVelocity().y, 2.f ) );

                    if ( Distance < Challenges[ ChallengeIndex ].AreaRadius && Velocity < 10.f ) {

                        Game->displayNotification( "Success!" );
                        Game->PlayerInterface[0]->beginFadeOut();

                        ChallengeState = 4; }

                    break; }

                case Challenge::EndingConditions::PowerUpCaught: {

                    if ( Game->PowerUps.empty() || ( Game->PowerUps.size() == 1 && Game->PowerUps.front()->isCaught() ) ) {

                        Game->displayNotification( "Success!" );
                        Game->PlayerInterface[0]->beginFadeOut();

                        ChallengeState = 4; }

                    break; }

                case Challenge::EndingConditions::PowerUpCaughtAndTime: {

                    if ( Game->PowerUps.empty() || ( Game->PowerUps.size() == 1 && Game->PowerUps.front()->isCaught() ) ) {

                        ChallengeTime += ElapsedTime;

                        if ( ChallengeTime > Challenges[ ChallengeIndex ].TimeLimit ) {

                            Game->displayNotification( "Success!" );
                            Game->PlayerInterface[0]->beginFadeOut();

                            ChallengeState = 4; } }

                    break; }

                case Challenge::EndingConditions::NoEnemies: {

                    if ( Game->Spaceships.size() == 1 ) {

                        Game->displayNotification( "Success!" );
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

    else if ( ChallengeState == 5 ) { // Load next challenge or lock and terminate

        if ( !loadNextChallenge() ) {

            Terminate = true;

            ChallengeState = 6; } // Lock

        else {

            update(); } } }

void TutorialModule::update ( sf::Event &Event ) {

    if ( ChallengeState == 1 ) { // Pre-challenge manual

        if ( Event.type == sf::Event::KeyPressed ) {

            switch ( Event.key.code ) {

                case sf::Keyboard::Up: {

                    if ( MenuOption == 1 ) {

                        MenuOption--; }

                    break; }

                case sf::Keyboard::Down: {

                    if ( MenuOption == 0 && ChallengeIndex != ( Challenges.size() - 1 ) ) {

                        MenuOption++; }

                    break; }

                case sf::Keyboard::W: {

                    if ( MenuOption == 1 ) {

                        MenuOption--; }

                    break; }

                case sf::Keyboard::S: {

                    if ( MenuOption == 0 && ChallengeIndex != ( Challenges.size() - 1 ) ) {

                        MenuOption++; }

                    break; }

                case sf::Keyboard::Return: {

                    if ( MenuOption == 0 ) {

                        ChallengeState = 2; }

                    else if ( MenuOption == 1 ) {

                        Terminate = true; }

                    break; }

                case sf::Keyboard::Space: {

                    if ( MenuOption == 0 ) {

                        ChallengeState = 2; }

                    else if ( MenuOption == 1 ) {

                        Terminate = true; }

                    break; }

                default: break; } } }

    else if ( ChallengeState == 2 ) { // Actual challenge

        Game->update( Event ); }

    else if ( ChallengeState == 3 || ChallengeState == 4 ) { // Failure / Success

        if ( Event.type == sf::Event::KeyPressed ) {

            if ( Event.key.code == sf::Keyboard::Escape || Event.key.code == sf::Keyboard::Enter || Event.key.code == sf::Keyboard::Space ) {

                Game->PlayerInterface[0]->endFadeOut(); } }

        Game->update( Event ); } }

void TutorialModule::render ( sf::RenderWindow &Window ) {

    if ( ChallengeState == 1 ) { // Pre-challenge manual

        sf::Text Text;

        Text.setString( TitleText );
        Text.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
        Text.setCharacterSize( TitleFontSize );
        Text.setPosition( ( Graphics->getWindowWidth() - Text.getLocalBounds().width ) / 2.f, TitlePosition );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
            Text.setFillColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

        #else

            Text.setColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

        #endif

        Window.draw( Text );

        Text.setString( SubTitleText );
        Text.setCharacterSize( SubTitleFontSize );
        Text.setPosition( ( Graphics->getWindowWidth() - Text.getLocalBounds().width ) / 2.f, SubTitlePosition );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
            Text.setFillColor( sf::Color( 189, 189, 189 ) ); // #BDBDBD

        #else

            Text.setColor( sf::Color( 189, 189, 189 ) ); // #BDBDBD

        #endif

        Window.draw( Text );

        Text.setString( ContentText );
        Text.setCharacterSize( ContentFontSize );
        Text.setPosition( ( Graphics->getWindowWidth() - Text.getLocalBounds().width ) / 2.f, ContentPosition );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
            Text.setFillColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

        #else

            Text.setColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

        #endif

        Window.draw( Text );

        for ( unsigned int i = 0; i < MenuOptionCount; i++ ) {

            Text.setString( MenuOptionText[i] );
            Text.setCharacterSize( MenuOptionFontSize );
            Text.setPosition( ( Graphics->getWindowWidth() - Text.getLocalBounds().width ) / 2.f, MenuOptionPosition[i] );

            #if ( SFML_VERSION_MINOR >= 4 )

                Text.setOutlineThickness( 1.f );
                Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121

                if ( MenuOption == i ) {

                    Text.setFillColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

                else if ( !( ChallengeIndex == ( Challenges.size() - 1 ) && i == 1 ) ) {

                    Text.setFillColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

                else {

                    Text.setFillColor( sf::Color( 66, 66, 66 ) ); } // #424242

            #else

                if ( MenuOption == i ) {

                    Text.setColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

                else if ( !( ChallengeIndex == ( Challenges.size() - 1 ) && i == 1 ) ) {

                    Text.setColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

                else {

                    Text.setColor( sf::Color( 66, 66, 66 ) ); } // #424242

            #endif

            Window.draw( Text ); } }

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

std::string TutorialModule::blankUnderscore ( std::string Text ) {

    size_t Position = Text.find( '_' );

    while ( Position != std::string::npos ) {

        Text.replace( Position, 1, " " );

        Position = Text.find( '_' ); }

    return Text; }

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
    TitleFontSize = 100;
    SubTitleFontSize = 100;
    ContentFontSize = 100;
    MenuOptionFontSize = 100;
    MenuOption = 0;

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

    loadNonStaticDescriptions();

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

void TutorialModule::loadNonStaticDescriptions ( ) {

    Challenges[1].Description = std::string(
                                "Great! Your first challenge will be to get back into the circular "
                                "game area before you die. As you may have guessed, being outside of it "
                                "slowly destroys your spaceship. Or fast, it depends. But don't worry, "
                                "the arrow will show you the way. To speed up press " )
                                + blankUnderscore( PlayerControllerSettings::encodeKey( Gameplay->getControllerSettings( 0 )->getForwardKey() ) ) +
                                ", to slow down "
                                + blankUnderscore( PlayerControllerSettings::encodeKey( Gameplay->getControllerSettings( 0 )->getBackwardKey() ) ) +
                                ", to turn left "
                                + blankUnderscore( PlayerControllerSettings::encodeKey( Gameplay->getControllerSettings( 0 )->getLeftKey() ) ) +
                                " and to turn right "
                                + blankUnderscore( PlayerControllerSettings::encodeKey( Gameplay->getControllerSettings( 0 )->getRightKey() ) ) +
                                ". It can be changed in settings section. And remember, the faster you move "
                                "the harder it is to turn your spaceship. Just like in real life. Ready?";

    Challenges[4].Description = std::string(
                                "I see you are well rested. So it's high time for something more exciting. "
                                "You will destroy your first enemy! Or he will destroy you... we will see. "
                                "Anyway, one way to do this is to shoot rays at him by pressing " )
                                + blankUnderscore( PlayerControllerSettings::encodeKey( Gameplay->getControllerSettings( 0 )->getRayShotKey() ) ) +
                                " a few times. It uses more energy than simple thrusting, so you have to "
                                "keep an eye on energy bar. With nothing left to say, fight or die!";

    Challenges[5].Description = std::string(
                                "Congrats, you won! Now you have to do the same thing, but with rays "
                                "turned off. Instead you will get 5 missiles. The are homing, so you "
                                "don't have to be perfectly precise when aiming, but the better your "
                                "aim the higher chance a missile will hit the target. To shoot a "
                                "missile press " )
                                + blankUnderscore( PlayerControllerSettings::encodeKey( Gameplay->getControllerSettings( 0 )->getMissileShotKey() ) ) +
                                ". Also a tip for future matches, missiles can be destroyed by rays "
                                "and other missiles. Well, you already know what to do, let's go!"; }
