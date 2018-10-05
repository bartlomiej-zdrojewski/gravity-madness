#include "main-menu.hpp"

MainMenu::MainMenu ( GraphicsModule * Graphics, GameplaySettings * Gameplay ) {

    this->Graphics = Graphics;
    this->Gameplay = Gameplay;

    MenuOptionCount = 5;
    MenuOptionText[0] = "Play now";
    MenuOptionText[1] = "Customize everything\nand play as you like";
    MenuOptionText[2] = "Beat the tutorial";
    MenuOptionText[3] = "Settings and stuff";
    MenuOptionText[4] = "Leave to prepare\nfor next challenge";

    GameplayOptionCount[0] = 5;
    GameplayOptionCount[1] = 4;
    GameplayOptionText[0][0] = "Area size";
    GameplayOptionText[0][1] = "Asteroid strike";
    GameplayOptionText[0][2] = "Winning condition";
    GameplayOptionText[0][3] = "\"Certain time\"";
    GameplayOptionText[0][4] = "Please, more options!";
    GameplayOptionText[1][0] = "Player count";
    GameplayOptionText[1][1] = "Spaceship count";
    GameplayOptionText[1][2] = "Enemies personality";
    GameplayOptionText[1][3] = "Show the spaceships!";

    SettingsOptionCount = 5;
    SettingsOptionText[0] = "Resolution";
    SettingsOptionText[1] = "Fullscreen";
    SettingsOptionText[2] = "Antialiasing";
    SettingsOptionText[3] = "Epilepsy protection";
    SettingsOptionText[4] = "Check out controllers!";

    BackgroundPauseDuration = sf::seconds( 2.f );
    BackgroundPauseTime = BackgroundPauseDuration;

    RedPalette.emplace_back( sf::Color( 239, 83, 80 ) ); // #EF5350
    RedPalette.emplace_back( sf::Color( 244, 67, 54 ) ); // #F44336
    RedPalette.emplace_back( sf::Color( 229, 57, 53 ) ); // #E53935
    RedPalette.emplace_back( sf::Color( 211, 47, 47 ) ); // #D32F2F
    RedPalette.emplace_back( sf::Color( 198, 40, 40 ) ); // #C62828
    RedPalette.emplace_back( sf::Color( 183, 28, 28 ) ); // #B71C1C

    reset(); }

MainMenu::Modes MainMenu::getMode ( ) {

    return Mode; }

void MainMenu::setMode ( Modes Mode ) {

    this->Mode = Mode;

    if ( Mode == Modes::SpaceshipsMode ) {

        loadSpaceshipCards(); } }

void MainMenu::update ( ) {

    sf::Time ElapsedTime = Clock.restart();
    // TODO PerformanceTimer += ElapsedTime;

    if ( ElapsedTime.asSeconds() < 0.1f ) {

        updateBackground( ElapsedTime );

        switch ( getMode() ) {

            case MenuMode: {

                updateMenu( ElapsedTime );

                break; }

            case GameplayMode: {

                updateMenu( ElapsedTime );
                updateGameplaySection( ElapsedTime );

                break; }

            case SpaceshipsMode: {

                updateMenu( ElapsedTime );
                updateGameplaySection( ElapsedTime );
                updateSpaceshipsSection( ElapsedTime );

                break; }

            case SettingsMode: {

                updateMenu( ElapsedTime );
                updateSettingsSection( ElapsedTime );

                break; }

            case ControllersMode: {

                updateMenu( ElapsedTime );
                updateSettingsSection( ElapsedTime );
                updateControllersSection( ElapsedTime );

                break; }

            default: {

                break; } } }

    else {

        // TODO LOW PERFORMANCE MESSAGE

        /*

        if ( PerformanceTimer.asSeconds() > 10.f ) {

            PerformanceTimer = sf::seconds( 0.f );
            LowPerformanceTimer = sf::seconds( 0.f ); }

        else {

            LowPerformanceTimer += ElapsedTime;

            if ( LowPerformanceTimer.asSeconds() > 1.f ) {

                LowPerformance = true;
                LowPerformanceTimer = sf::seconds( 0.f ); } }

        */

        } }

void MainMenu::update ( sf::Event &Event ) {

    switch ( getMode() ) {

        case Modes::MenuMode: {

            updateMenu( Event );

            break; }

        case Modes::GameplayMode: {

            updateGameplaySection( Event );

            break; }

        case Modes::SpaceshipsMode: {

            updateSpaceshipsSection( Event );

            break; }

        case Modes::SettingsMode: {

            updateSettingsSection( Event );

            break; }

        case Modes::ControllersMode: {

            updateControllersSection( Event );

            break; }

        default: {

            break; } } }

void MainMenu::render ( sf::RenderWindow &Window ) {

    renderBackground( Window );

    switch ( getMode() ) {

        case Modes::MenuMode: {

            renderMenu( Window );

            break; }

        case Modes::GameplayMode: {

            renderMenu( Window );
            renderGameplaySection( Window );

            break; }

        case Modes::SpaceshipsMode: {

            renderMenu( Window );
            renderGameplaySection( Window );
            renderSpaceshipsSection( Window );

            break; }

        case Modes::SettingsMode: {

            renderMenu( Window );
            renderSettingsSection( Window );

            break; }

        case Modes::ControllersMode: {

            renderMenu( Window );
            renderSettingsSection( Window );
            renderControllersSection( Window );

            break; }

        default: {

            break; } } }

void MainMenu::reset ( ) {

    LaunchGame = false;
    LaunchTutorial = false;
    VideoChanged = false;
    SettingsChanged = false;
    LowPerformance = false;
    Terminate = false;
    Mode = MenuMode;

    WindowWidth = Graphics->getWindowWidth();
    WindowHeight = Graphics->getWindowHeight();
    FullScreen = Graphics->isFullScreenEnabled();
    AntialiasingLevel = Graphics->getAntialiasingLevel();
    EpilepsyProtection = Graphics->isEpilepsyProtectionEnabled();

    MenuOption = 0;
    GameplayPage = 0;
    GameplayOption = 0;
    SpaceshipIndex = 0;
    SpaceshipOption = 0;
    SpaceshipCardsOffset = 0.f;
    SpaceshipCardsOffsetDirection = 0.f;
    SettingsOption = 0;

    ControllersTablePointer = { 1, 1 };
    ControllersModificationMode = false;
    ControllersModificationState = 0;
    PreviousDevice = PlayerControllerSettings::Devices::Keyboard;
    PreviousIdentifier = -1;

    MenuOptionPointerPosition.y = -25.f;

    if ( Graphics->getWindowHeight() < 600.f ) {

        MenuOptionPointerVelocity = 30.f; }

    else if ( Graphics->getWindowHeight() >= 600.f && Graphics->getWindowHeight() <= 800.f ) {

        MenuOptionPointerVelocity = 50.f; }

    else if ( Graphics->getWindowHeight() > 800.f && Graphics->getWindowHeight() <= 1000.f ) {

        MenuOptionPointerVelocity = 70.f; }

    else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

        MenuOptionPointerVelocity = 70.f; }

    else {

        MenuOptionPointerVelocity = 80.f; }

    for ( unsigned int i = 0; i < 6; i++ ) {

        SpaceshipMaximumValues[i] = 0.f; }

    Background.clear();
    ParticleIndexes.clear();
    ParticleVelocities.clear();

    updateMenu( sf::seconds( ALMOST_NO_TIME ) );
    updateGameplaySection( sf::seconds( ALMOST_NO_TIME ) );
    updateSpaceshipsSection( sf::seconds( ALMOST_NO_TIME ) );
    updateSettingsSection( sf::seconds( ALMOST_NO_TIME ) );
    updateControllersSection( sf::seconds( ALMOST_NO_TIME ) );
    updateBackground( sf::seconds( ALMOST_NO_TIME ) ); }

bool MainMenu::onLaunchGame ( ) {

    if ( LaunchGame ) {

        reset();

        return true; }

    return false; }

bool MainMenu::onLaunchTutorial ( ) {

    if ( LaunchTutorial ) {

        reset();

        return true; }

    return false; }

bool MainMenu::onVideoChanged ( ) {

    if ( VideoChanged && getMode() != Modes::SettingsMode && getMode() != Modes::ControllersMode ) {

        Graphics->setWindowSize( WindowWidth, WindowHeight );
        FullScreen ? Graphics->enableFullScreen() : Graphics->disableFullScreen();
        Graphics->setAntialiasingLevel( AntialiasingLevel );

        reset();

        return true; }

    return false; }

bool MainMenu::onSettingsChanged ( ) {

    if ( SettingsChanged && getMode() != Modes::SettingsMode && getMode() != Modes::ControllersMode ) {

        Graphics->setWindowSize( WindowWidth, WindowHeight );
        FullScreen ? Graphics->enableFullScreen() : Graphics->disableFullScreen();
        Graphics->setAntialiasingLevel( AntialiasingLevel );
        EpilepsyProtection ? Graphics->enableEpilepsyProtection() : Graphics->disableEpilepsyProtection();

        SettingsChanged = false;

        return true; }

    return false; }

bool MainMenu::onLowPerformance ( ) {

    if ( LowPerformance ) {

        reset();

        return true; }

    return false; }

bool MainMenu::onTerminate ( ) {

    if ( Terminate ) {

        reset();

        return true; }

    return false; }

float MainMenu::getRandomFloat ( ) {

    return ( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ); }

std::string MainMenu::getTimeText ( sf::Time Time ) {

    return std::to_string( (unsigned int) ( Time.asSeconds() / 60.f ) ) + " minutes"; }

std::string MainMenu::blankUnderscore ( std::string Text ) {

    size_t Position = Text.find( '_' );

    while ( Position != std::string::npos ) {

        Text.replace( Position, 1, " " );

        Position = Text.find( '_' ); }

    return Text; }

std::vector <sf::Texture*> MainMenu::getBrakesTextures ( ) {

    std::vector <sf::Texture*> BrakesTextures;

    for ( unsigned int i = 0; i < 5; i++ ) {

        BrakesTextures.push_back( &Graphics->getTexture( "Brakes" + std::to_string( i + 1 ) ) ); }

    return BrakesTextures; }

void MainMenu::updateMenu ( sf::Time ElapsedTime ) {

    sf::Vector2f SectionMargin;
    sf::Vector2f OptionMargin;

    if ( Graphics->getWindowHeight() < 600.f ) {

        SectionMargin = sf::Vector2f ( 12.f, 20.f );
        OptionMargin = sf::Vector2f ( 6.f, 10.f ); }

    else if ( Graphics->getWindowHeight() >= 600.f && Graphics->getWindowHeight() <= 800.f ) {

        SectionMargin = sf::Vector2f ( 20.f, 30.f );
        OptionMargin = sf::Vector2f ( 10.f, 15.f ); }

    else if ( Graphics->getWindowHeight() > 800.f && Graphics->getWindowHeight() <= 1000.f ) {

        SectionMargin = sf::Vector2f ( 60.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

        SectionMargin = sf::Vector2f ( 60.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    else {

        SectionMargin = sf::Vector2f ( 100.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    sf::Text TextPrototype;
    sf::Vector2f SectionSize = sf::Vector2f ( 0.35f * Graphics->getWindowWidth() - 2.f * SectionMargin.x, Graphics->getWindowHeight() - 2.f * SectionMargin.y );
    sf::Vector2f OptionPosition = sf::Vector2f ( 0.1f * Graphics->getWindowWidth() + SectionMargin.x + OptionMargin.x, Graphics->getWindowHeight() - SectionMargin.y );
    float OptionHeight = 0.f;

    MenuOptionFontSize = 100;

    for ( unsigned int i = 0; i < MenuOptionCount; i++ ) {

        size_t LineSeparator = 0;
        unsigned int LineCount = 0;

        TextPrototype.setString( MenuOptionText[i] );
        TextPrototype.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
        TextPrototype.setCharacterSize( MenuOptionFontSize );

        do {

            LineCount++;
            LineSeparator = MenuOptionText[i].find( '\n', LineSeparator + 1 ); }

        while ( LineSeparator != std::string::npos );

        while ( TextPrototype.getLocalBounds().height > ( LineCount * 0.06f * SectionSize.y ) ) {

            TextPrototype.setCharacterSize( --MenuOptionFontSize ); }

        while ( TextPrototype.getLocalBounds().width > SectionSize.x ) {

            TextPrototype.setCharacterSize( --MenuOptionFontSize ); } }

    for ( unsigned int i = 0; i < MenuOptionCount; i++ ) {

        size_t LineSeparator = 0;
        unsigned int LineCount = 0;

        TextPrototype.setString( MenuOptionText[i] );
        TextPrototype.setCharacterSize( MenuOptionFontSize );

        do {

            LineCount++;
            LineSeparator = MenuOptionText[i].find( '\n', LineSeparator + 1 ); }

        while ( LineSeparator != std::string::npos );

        OptionHeight = std::fmaxf( OptionHeight, TextPrototype.getLocalBounds().height / LineCount ); }

    for ( unsigned int i = 0; i < MenuOptionCount; i++ ) {

        size_t Index = MenuOptionCount - i - 1;
        size_t LineSeparator = 0;
        unsigned int LineCount = 0;

        do {

            LineCount++;
            LineSeparator = MenuOptionText[ Index ].find( '\n', LineSeparator + 1 ); }

        while ( LineSeparator != std::string::npos );

        MenuOptionPosition[ Index ] = sf::Vector2f( OptionPosition.x, OptionPosition.y - LineCount * OptionHeight );
        MenuOptionPositionCenter[ Index ] = MenuOptionPosition[ Index ].y + 0.5f * ( LineCount * OptionHeight );

        OptionPosition.y -= LineCount * OptionHeight + OptionMargin.y; }

    float SignedDistance = MenuOptionPositionCenter[ MenuOption ] - MenuOptionPointerPosition.y;

    if ( std::fabs( SignedDistance ) > 5.f ) {

        float Factor;
        float MaximumDistance = std::fabs( MenuOptionPosition[ MenuOption ].y - MenuOptionPositionCenter[ MenuOption ] );

        if ( Graphics->getWindowHeight() < 600.f ) {

            Factor = 480.f; }

        else if ( Graphics->getWindowHeight() >= 600.f && Graphics->getWindowHeight() <= 800.f ) {

            Factor = 600.f; }

        else if ( Graphics->getWindowHeight() > 800.f && Graphics->getWindowHeight() <= 1000.f ) {

            Factor = 1200.f; }

        else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

            Factor = 1200.f; }

        else {

            Factor = 1800.f; }

        if ( std::fabs( SignedDistance ) > MaximumDistance ) {

            if ( ( SignedDistance > 0.f && MenuOptionPointerVelocity < 0.f ) || ( SignedDistance < 0.f && MenuOptionPointerVelocity > 0.f ) ) { // TODO sgn(A) != sgn(B) <=> ( A * B ) < 0 || ( A = 0 && B != 0 ) || ( A != 0 && B = 0 )

                Factor *= 2.5; } }

        if ( std::fabs( MenuOptionPointerPosition.y ) > ( 1.25 * Graphics->getWindowHeight() ) ) {

            if ( ( SignedDistance > 0.f && MenuOptionPointerVelocity < 0.f ) || ( SignedDistance < 0.f && MenuOptionPointerVelocity > 0.f ) ) { // TODO sgn(A) != sgn(B) <=> ( A * B ) < 0 || ( A = 0 && B != 0 ) || ( A != 0 && B = 0 )

                MenuOptionPointerVelocity = 0.f; } }

        MenuOptionPointerVelocity += ( Factor / SignedDistance ) * ElapsedTime.asSeconds(); }

    MenuOptionPointerPosition.x = 0.1f * Graphics->getWindowWidth();
    MenuOptionPointerPosition.y += MenuOptionPointerVelocity * ElapsedTime.asSeconds(); }

void MainMenu::updateMenu ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Up: {

                if ( MenuOption > 0 ) {

                    MenuOption--; }

                break; }

            case sf::Keyboard::Down: {

                if ( MenuOption < ( MenuOptionCount - 1 ) ) {

                    MenuOption++; }

                break; }

            case sf::Keyboard::W: {

                if ( MenuOption > 0 ) {

                    MenuOption--; }

                break; }

            case sf::Keyboard::S: {

                if ( MenuOption < ( MenuOptionCount - 1 ) ) {

                    MenuOption++; }

                break; }

            case sf::Keyboard::Return: {

                switch ( MenuOption ) {

                    case 0: {

                        LaunchGame = true;

                        break; }

                    case 1: {

                        setMode( Modes::GameplayMode );

                        break; }

                    case 2: {

                        LaunchTutorial = true;

                        break; }

                    case 3: {

                        setMode( Modes::SettingsMode );

                        break; }

                    case 4: {

                        Terminate = true; }

                    default: {

                        break; } }

                break; }

            case sf::Keyboard::Space: {

                switch ( MenuOption ) {

                    case 0: {

                        LaunchGame = true;

                        break; }

                    case 1: {

                        setMode( Modes::GameplayMode );

                        break; }

                    case 2: {

                        LaunchTutorial = true;

                        break; }

                    case 3: {

                        setMode( Modes::SettingsMode );

                        break; }

                    case 4: {

                        Terminate = true; }

                    default: {

                        break; } }

                break; }

            default: {

                break; } } } }

void MainMenu::renderMenu ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 0 );

    sf::Text Text;
    Text.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    Text.setCharacterSize( MenuOptionFontSize );

    sf::CircleShape Circle;
    Circle.setPosition( MenuOptionPointerPosition - sf::Vector2f( 1.f, 0.f ) );
    Circle.setFillColor( sf::Color( 33, 150, 243 ) ); // #2196F3

    if ( Graphics->getWindowHeight() < 600.f ) {

        Circle.setRadius( 8.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    else if ( Graphics->getWindowHeight() >= 600.f && Graphics->getWindowHeight() <= 800.f ) {

        Circle.setRadius( 10.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    else if ( Graphics->getWindowHeight() > 800.f && Graphics->getWindowHeight() <= 1000.f ) {

        Circle.setRadius( 15.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

        Circle.setRadius( 15.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    else {

        Circle.setRadius( 20.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    Window.draw( Circle );

    for ( unsigned int i = 0; i < MenuOptionCount; i++ ) {

        Text.setString( MenuOptionText[i] );
        Text.setPosition( MenuOptionPosition[i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121

            if ( i == MenuOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i + 1 ) == MenuOption || ( i - 1 ) == MenuOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i + 2 ) == MenuOption || ( i - 2 ) == MenuOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #else

            if ( i == MenuOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i + 1 ) == MenuOption || ( i - 1 ) == MenuOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i + 2 ) == MenuOption || ( i - 2 ) == MenuOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #endif

        Window.draw( Text ); } }

void MainMenu::updateGameplaySection ( sf::Time ElapsedTime ) {

    GameplayOptionText[0][ GameplayOptionCount[0] + 0 ] = Gameplay->getAreaSizeText();
    GameplayOptionText[0][ GameplayOptionCount[0] + 1 ] = Gameplay->getAsteroidFrequencyText();
    GameplayOptionText[0][ GameplayOptionCount[0] + 2 ] = Gameplay->getEndingConditionText();
    GameplayOptionText[0][ GameplayOptionCount[0] + 3 ] = getTimeText( Gameplay->getTimeLimit() );
    GameplayOptionText[1][ GameplayOptionCount[1] + 0 ] = std::to_string( Gameplay->getPlayerCount() );
    GameplayOptionText[1][ GameplayOptionCount[1] + 1 ] = std::to_string( Gameplay->getSpaceshipCount() ) +
                                                          " including " + std::to_string( Gameplay->getSpaceshipCount() - Gameplay->getPlayerCount() ) + " enemies";
    GameplayOptionText[1][ GameplayOptionCount[1] + 2 ] = Gameplay->getAIPersonalityText();

    if ( Gameplay->getPlayerCount() == 1 ) {

        GameplayOptionText[1][ GameplayOptionCount[1] + 0 ] = "One lone wolf"; }

    else if ( Gameplay->getPlayerCount() == 2 ) {

        GameplayOptionText[1][ GameplayOptionCount[1] + 0 ] = "Two mario bros"; }

    else if ( Gameplay->getPlayerCount() == 3 ) {

        GameplayOptionText[1][ GameplayOptionCount[1] + 0 ] = "Three musketeers"; }

    else {

        GameplayOptionText[1][ GameplayOptionCount[1] + 0 ] = "Four ninja turtles"; }

    sf::Vector2f SectionMargin;
    sf::Vector2f OptionMargin;

    if ( Graphics->getWindowHeight() < 600.f ) {

        SectionMargin = sf::Vector2f ( 12.f, 20.f );
        OptionMargin = sf::Vector2f ( 6.f, 10.f ); }

    else if ( Graphics->getWindowHeight() >= 600.f && Graphics->getWindowHeight() <= 800.f ) {

        SectionMargin = sf::Vector2f ( 20.f, 30.f );
        OptionMargin = sf::Vector2f ( 0.f, 15.f ); }

    else if ( Graphics->getWindowHeight() > 800.f && Graphics->getWindowHeight() <= 1000.f ) {

        SectionMargin = sf::Vector2f ( 60.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

        SectionMargin = sf::Vector2f ( 60.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    else {

        SectionMargin = sf::Vector2f ( 100.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    sf::Text TextPrototype;
    sf::Vector2f SectionSize = sf::Vector2f ( 0.35f * Graphics->getWindowWidth() - 2.f * SectionMargin.x, Graphics->getWindowHeight() - 2.f * SectionMargin.y );
    sf::Vector2f OptionPosition [2];
    OptionPosition [0] = sf::Vector2f ( 0.55f * Graphics->getWindowWidth() + SectionMargin.x + OptionMargin.x, Graphics->getWindowHeight() - SectionMargin.y );
    OptionPosition [1] = sf::Vector2f ( 0.55f * Graphics->getWindowWidth() + SectionMargin.x + OptionMargin.x, Graphics->getWindowHeight() - SectionMargin.y );
    float OptionHeight = 0.f;

    GameplayOptionFontSize = MenuOptionFontSize;
    float SmallFontScale = 0.85f;

    for ( unsigned int i = 0; i < 2; i++ ) {

        for ( unsigned int j = 0; j < ( 2 * GameplayOptionCount[i] - 1 ); j++ ) {

            TextPrototype.setString( GameplayOptionText[i][j] );
            TextPrototype.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
            TextPrototype.setCharacterSize( j < GameplayOptionCount[i] ? GameplayOptionFontSize : (unsigned int) ( SmallFontScale * GameplayOptionFontSize ) );

            while ( TextPrototype.getLocalBounds().height > ( 0.06f * SectionSize.y ) ) {

                TextPrototype.setCharacterSize( --GameplayOptionFontSize ); }

            while ( TextPrototype.getLocalBounds().width > SectionSize.x ) {

                TextPrototype.setCharacterSize( --GameplayOptionFontSize ); } } }

    for ( unsigned int i = 0; i < 2; i++ ) {

        for ( unsigned int j = 0; j < ( 2 * GameplayOptionCount[i] - 1 ); j++ ) {

            TextPrototype.setString( GameplayOptionText[i][j] );
            TextPrototype.setCharacterSize( j < GameplayOptionCount[i] ? GameplayOptionFontSize : (unsigned int) ( SmallFontScale * GameplayOptionFontSize ) );

            OptionHeight = std::fmaxf( OptionHeight, TextPrototype.getLocalBounds().height ); } }

    for ( unsigned int i = 0; i < 2; i++ ) {

        for ( unsigned int j = 0; j < GameplayOptionCount[i]; j++ ) {

            size_t Index = GameplayOptionCount[i] - j - 1;

            if ( ( Index + 1 ) != GameplayOptionCount[i] ) {

                GameplayOptionPosition[i][ Index ] = sf::Vector2f( OptionPosition[i].x, OptionPosition[i].y - 2.f * OptionHeight - 0.5f * OptionMargin.y );
                GameplayOptionPosition[i][ Index + GameplayOptionCount[i] ] = sf::Vector2f( OptionPosition[i].x, OptionPosition[i].y - OptionHeight );

                OptionPosition[i].y -= 2.f * OptionHeight + 1.5f * OptionMargin.y; }

            else {

                GameplayOptionPosition[i][ Index ] = sf::Vector2f( OptionPosition[i].x, OptionPosition[i].y - OptionHeight );

                OptionPosition[i].y -= OptionHeight + OptionMargin.y; } } } }

void MainMenu::updateGameplaySection ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Up: {

                if ( GameplayOption > 0 ) {

                    GameplayOption--; }

                break; }

            case sf::Keyboard::Down: {

                if ( GameplayOption < ( GameplayOptionCount[ GameplayPage ] - 1 ) ) {

                    GameplayOption++; }

                break; }

            case sf::Keyboard::Left: {

                updateGameplaySection_BindLeft();

                break; }

            case sf::Keyboard::Right: {

                updateGameplaySection_BindRight();

                break; }

            case sf::Keyboard::W: {

                if ( GameplayOption > 0 ) {

                    GameplayOption--; }

                break; }

            case sf::Keyboard::S: {

                if ( GameplayOption < ( GameplayOptionCount[ GameplayPage ] - 1 ) ) {

                    GameplayOption++;
                    GameplayOption = 0; }

                break; }

            case sf::Keyboard::A: {

                updateGameplaySection_BindLeft();

                break; }

            case sf::Keyboard::D: {

                updateGameplaySection_BindRight();

                break; }

            case sf::Keyboard::Return: {

                if ( GameplayPage == 0 && GameplayOption == 4 ) {

                    GameplayPage++;
                    GameplayOption = 0; }

                else if ( GameplayPage == 1 && GameplayOption == 3 ) {

                    setMode( Modes::SpaceshipsMode ); }

                break; }

            case sf::Keyboard::Space: {

                if ( GameplayPage == 0 && GameplayOption == 4 ) {

                    GameplayPage++;
                    GameplayOption = 0; }

                else if ( GameplayPage == 1 && GameplayOption == 3 ) {

                    setMode( Modes::SpaceshipsMode ); }

                break; }

            case sf::Keyboard::BackSpace: {

                if ( GameplayPage == 0 ) {

                    GameplayOption = 0;

                    setMode( Modes::MenuMode ); }

                else if ( GameplayPage == 1 ) {

                    GameplayPage = 0;
                    GameplayOption = 4; }

                break; }

            case sf::Keyboard::Escape: {

                if ( GameplayPage == 0 ) {

                    GameplayOption = 0;

                    setMode( Modes::MenuMode ); }

                else if ( GameplayPage == 1 ) {

                    GameplayPage = 0;
                    GameplayOption = 4; }

                break; }

            default: {

                break; } } } }

void MainMenu::updateGameplaySection_BindLeft ( ) {

    switch ( GameplayOption ) {

        case 0: {

            if ( GameplayPage == 0 ) {

                Gameplay->setPreviousAreaSize(); }

            else if ( GameplayPage == 1 ) {

                if ( Gameplay->getPlayerCount() > 1 ) {

                    Gameplay->setPlayerCount( Gameplay->getPlayerCount() - 1 ); } }

            break; }

        case 1: {

            if ( GameplayPage == 0 ) {

                Gameplay->setPreviousAsteroidFrequency(); }

            else if ( GameplayPage == 1 ) {

                if ( Gameplay->getSpaceshipCount() > 10 ) {

                    Gameplay->setSpaceshipCount( Gameplay->getSpaceshipCount() - 1 ); } }

            break; }

        case 2: {

            if ( GameplayPage == 0 ) {

                Gameplay->setPreviousEndingCondition(); }

            else if ( GameplayPage == 1 ) {

                Gameplay->setPreviousAIPersonality(); }

            break; }

        case 3: {

            if ( Gameplay->getTimeLimit() == sf::seconds( 3.f * 60.f ) ) {

                Gameplay->setTimeLimit( sf::seconds( 15.f * 60.f ) ); }

            else if ( Gameplay->getTimeLimit() == sf::seconds( 5.f * 60.f ) ) {

                Gameplay->setTimeLimit( sf::seconds( 3.f * 60.f ) ); }

            else if ( Gameplay->getTimeLimit() == sf::seconds( 10.f * 60.f ) ) {

                Gameplay->setTimeLimit( sf::seconds( 5.f * 60.f ) ); }

            else if ( Gameplay->getTimeLimit() == sf::seconds( 15.f * 60.f ) ) {

                Gameplay->setTimeLimit( sf::seconds( 10.f * 60.f ) ); }

            break; }

        default: {

            break; } } }

void MainMenu::updateGameplaySection_BindRight ( ) {

    switch ( GameplayOption ) {

        case 0: {

            if ( GameplayPage == 0 ) {

                Gameplay->setNextAreaSize(); }

            else if ( GameplayPage == 1 ) {

                if ( Gameplay->getPlayerCount() < MAXIMUM_PLAYER_COUNT ) {

                    Gameplay->setPlayerCount( Gameplay->getPlayerCount() + 1 ); } }

            break; }

        case 1: {

            if ( GameplayPage == 0 ) {

                Gameplay->setNextAsteroidFrequency(); }

            else if ( GameplayPage == 1 ) {

                if ( Gameplay->getSpaceshipCount() < 40 ) {

                    Gameplay->setSpaceshipCount( Gameplay->getSpaceshipCount() + 1 ); } }

            break; }

        case 2: {

            if ( GameplayPage == 0 ) {

                Gameplay->setNextEndingCondition(); }

            else if ( GameplayPage == 1 ) {

                Gameplay->setNextAIPersonality(); }

            break; }

        case 3: {

            if ( Gameplay->getTimeLimit() == sf::seconds( 3.f * 60.f ) ) {

                Gameplay->setTimeLimit( sf::seconds( 5.f * 60.f ) ); }

            else if ( Gameplay->getTimeLimit() == sf::seconds( 5.f * 60.f ) ) {

                Gameplay->setTimeLimit( sf::seconds( 10.f * 60.f ) ); }

            else if ( Gameplay->getTimeLimit() == sf::seconds( 10.f * 60.f ) ) {

                Gameplay->setTimeLimit( sf::seconds( 15.f * 60.f ) ); }

            else if ( Gameplay->getTimeLimit() == sf::seconds( 15.f * 60.f ) ) {

                Gameplay->setTimeLimit( sf::seconds( 3.f * 60.f ) ); }

            break; }

        default: {

            break; } } }

void MainMenu::renderGameplaySection ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 1 );

    sf::Text Text;
    Text.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    Text.setCharacterSize( GameplayOptionFontSize );

    for ( unsigned int i = 0; i < GameplayOptionCount[ GameplayPage ]; i++ ) {

        Text.setString( GameplayOptionText[ GameplayPage ][i] );
        Text.setPosition( GameplayOptionPosition[ GameplayPage ][i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121

            if ( i == GameplayOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i + 1 ) == GameplayOption || ( i - 1 ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i + 2 ) == GameplayOption || ( i - 2 ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #else

            if ( i == GameplayOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i + 1 ) == GameplayOption || ( i - 1 ) == GameplayOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i + 2 ) == GameplayOption || ( i - 2 ) == GameplayOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #endif

        Window.draw( Text ); }

    Text.setCharacterSize( (unsigned int) ( 0.85f * GameplayOptionFontSize ) );

    for ( unsigned int i = GameplayOptionCount[ GameplayPage ]; i < ( 2 * GameplayOptionCount[ GameplayPage ] - 1 ); i++ ) {

        Text.setString( GameplayOptionText[ GameplayPage ][i] );
        Text.setPosition( GameplayOptionPosition[ GameplayPage ][i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121

            if ( ( i - GameplayOptionCount[ GameplayPage ] ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i - GameplayOptionCount[ GameplayPage ] + 1 ) == GameplayOption || ( i - GameplayOptionCount[ GameplayPage ] - 1 ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i - GameplayOptionCount[ GameplayPage ] + 2 ) == GameplayOption || ( i - GameplayOptionCount[ GameplayPage ] - 2 ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #else

            if ( ( i - GameplayOptionCount[ GameplayPage ] ) == GameplayOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i - GameplayOptionCount[ GameplayPage ] + 1 ) == GameplayOption || ( i - GameplayOptionCount[ GameplayPage ] - 1 ) == GameplayOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i - GameplayOptionCount[ GameplayPage ] + 2 ) == GameplayOption || ( i - GameplayOptionCount[ GameplayPage ] - 2 ) == GameplayOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #endif

        Window.draw( Text ); } }

void MainMenu::loadSpaceshipCards ( ) {

    SpaceshipCards.clear();

    sf::Vector2f SectionSize = sf::Vector2f( Graphics->getWindowWidth(), 0.75f * Graphics->getWindowHeight() );
    sf::Vector2f CardSize = sf::Vector2f( 0.75f * SectionSize.y, 0.75f * SectionSize.y );
    sf::Vector2f CardMargin = sf::Vector2f( 0.05f * SectionSize.y ,0.2f * SectionSize.y );
    
    auto SpaceshipPrototypes = Gameplay->getSpaceshipPrototypes();

    for ( unsigned int i = 0; i < 6; i++ ) {

        SpaceshipMaximumValues[i] = 0.f; }

    for ( unsigned int i = 0; i < SpaceshipPrototypes.size(); i++ ) {

        SpaceshipCards.emplace_back( SpaceshipCard ( ) );

        SpaceshipCards.back().Index = i;
        SpaceshipCards.back().Prototype = SpaceshipPrototypes[i];
        SpaceshipCards.back().VisualizationSpaceship = new Spaceship ( SpaceshipCards.back().Prototype.Mass, SpaceshipCards.back().Prototype.Radius * 2.f );
        SpaceshipCards.back().VisualizationArea = new sf::RenderTexture ( );
        SpaceshipCards.back().VisualizationArea->setSmooth( true );
        SpaceshipCards.back().VisualizationWind = sf::Vector2f( 1.f / ( 5.f + 5.f * getRandomFloat() ), 1.f / ( 5.f + 5.f * getRandomFloat() ) );

        Spaceship * MySpaceship = SpaceshipCards.back().VisualizationSpaceship;
        GameplaySettings::SpaceshipPrototype * MyPrototype = &SpaceshipCards.back().Prototype;
        MySpaceship->setHealthLimit( MyPrototype->HealthLimit );
        MySpaceship->setHealth( MyPrototype->HealthLimit );
        MySpaceship->setHealthRestoration( MyPrototype->HealthRestoration );
        MySpaceship->setEnergyLimit( MyPrototype->EnergyLimit );
        MySpaceship->setEnergy( MyPrototype->EnergyLimit );
        MySpaceship->setEnergyRestoration( MyPrototype->EnergyRestoration );
        MySpaceship->setThrust( MyPrototype->Thrust );
        MySpaceship->setBrakingFactor( MyPrototype->BrakingFactor );
        MySpaceship->setRayPower( MyPrototype->RayPower );
        MySpaceship->setRayColor( MyPrototype->RayColor );
        MySpaceship->setMissileLimit( MyPrototype->MissileLimit );
        MySpaceship->setMissileCount( MyPrototype->MissileCount );
        MySpaceship->setTexture( Graphics->getTexture( MyPrototype->Texture ) );
        MySpaceship->setAccentTexture( Graphics->getTexture( MyPrototype->AccentTexture ), Gameplay->getPlayerColor( 0 ) );
        MySpaceship->setThrusterTexture( Graphics->getTexture( "Thruster" ), MyPrototype->FuelColor );
        MySpaceship->setBrakesTextures( getBrakesTextures(), MyPrototype->FuelColor );
        MySpaceship->setPosition( sf::Vector2f( 500.f, 150.f ) );
        MySpaceship->setVelocity( sf::Vector2f( 25.f, 0.f ) );
        MySpaceship->setController( new VisualizationController ( ) );
        ( (VisualizationController*) MySpaceship->getController() )->setDesiredPosition( sf::Vector2f( 500.f, 150.f ) );
        ( (VisualizationController*) MySpaceship->getController() )->setResetDistance( 250.f );

        #if ( SFML_VERSION_MINOR >= 5 )

            sf::ContextSettings Context;
            Context.antialiasingLevel = Graphics->getAntialiasingLevel();

            SpaceshipCards.back().VisualizationArea->create( 1000, 300, Context );

        #else

            SpaceshipCards.back().VisualizationArea->create( 1000, 300 );
        
        #endif

        SpaceshipMaximumValues[0] = fmaxf( SpaceshipMaximumValues[0], MyPrototype->HealthLimit );
        SpaceshipMaximumValues[1] = fmaxf( SpaceshipMaximumValues[1], MyPrototype->HealthRestoration );
        SpaceshipMaximumValues[2] = fmaxf( SpaceshipMaximumValues[2], MyPrototype->EnergyLimit );
        SpaceshipMaximumValues[3] = fmaxf( SpaceshipMaximumValues[3], MyPrototype->EnergyRestoration );
        SpaceshipMaximumValues[4] = fmaxf( SpaceshipMaximumValues[4], MyPrototype->Thrust );
        SpaceshipMaximumValues[5] = fmaxf( SpaceshipMaximumValues[5], MyPrototype->RayPower ); }

    SpaceshipOption = (unsigned int) ( SpaceshipPrototypes.size() / 2 );
    SpaceshipCardsOffset = SectionSize.x / 2.f - ( CardSize.x + CardMargin.x ) * SpaceshipOption;
    SpaceshipCardsOffsetDirection = 0.f;
    SpaceshipCardsTime = 0.f; }

void MainMenu::updateSpaceshipsSection ( sf::Time ElapsedTime ) {

    sf::Vector2f SectionPosition = sf::Vector2f( 0.f, 0.125f * Graphics->getWindowHeight() );
    sf::Vector2f SectionSize = sf::Vector2f( Graphics->getWindowWidth(), 0.75f * Graphics->getWindowHeight() );

    sf::Vector2f CardSize = sf::Vector2f( 0.75f * SectionSize.y, 0.75f * SectionSize.y );
    sf::Vector2f CardMargin = sf::Vector2f( 0.05f * SectionSize.y ,0.2f * SectionSize.y );
    sf::Color CardColor = sf::Color( 13, 71, 161 ); // #0D47A1
    float CardOutlineThickness = 1.5f;
    float NeutralPosition = SectionPosition.x + SectionSize.x / 2.f;

    SpaceshipCardsTime += ElapsedTime.asSeconds();

    for ( auto &Card : SpaceshipCards ) {

        Card.Size = CardSize;
        Card.Position.x = SectionPosition.x + ( CardSize.x + CardMargin.x ) * Card.Index + SpaceshipCardsOffset;
        Card.Position.y = SectionPosition.y + CardSize.y / 2.f + CardMargin.y;

        Card.Outline.clear();
        Card.Outline.setPrimitiveType( sf::PrimitiveType::Quads );
        Card.Outline.append( sf::Vertex( sf::Vector2f( Card.Position.x + Card.Size.x / 2.f + CardMargin.x / 2.f, Card.Position.y - Card.Size.y / 2.f ), CardColor ) );
        Card.Outline.append( sf::Vertex( sf::Vector2f( Card.Position.x + Card.Size.x / 2.f + CardMargin.x / 2.f, Card.Position.y + Card.Size.y / 2.f ), CardColor ) );
        Card.Outline.append( sf::Vertex( sf::Vector2f( Card.Position.x + Card.Size.x / 2.f + CardMargin.x / 2.f + CardOutlineThickness, Card.Position.y + Card.Size.y / 2.f ), CardColor ) );
        Card.Outline.append( sf::Vertex( sf::Vector2f( Card.Position.x + Card.Size.x / 2.f + CardMargin.x / 2.f + CardOutlineThickness, Card.Position.y - Card.Size.y / 2.f ), CardColor ) );

        if ( Card.Index == 0 ) {

            Card.Outline.append( sf::Vertex( sf::Vector2f( Card.Position.x - Card.Size.x / 2.f - CardMargin.x / 2.f, Card.Position.y - Card.Size.y / 2.f ), CardColor ) );
            Card.Outline.append( sf::Vertex( sf::Vector2f( Card.Position.x - Card.Size.x / 2.f - CardMargin.x / 2.f, Card.Position.y + Card.Size.y / 2.f ), CardColor ) );
            Card.Outline.append( sf::Vertex( sf::Vector2f( Card.Position.x - Card.Size.x / 2.f - CardMargin.x / 2.f + CardOutlineThickness, Card.Position.y + Card.Size.y / 2.f ), CardColor ) );
            Card.Outline.append( sf::Vertex( sf::Vector2f( Card.Position.x - Card.Size.x / 2.f - CardMargin.x / 2.f + CardOutlineThickness, Card.Position.y - Card.Size.y / 2.f ), CardColor ) ); }
        
        if ( Card.VisualizationSpaceship ) {

            sf::Vector2f Wind = Card.VisualizationSpaceship->getThrust() * ( sf::Vector2f( 0.75f, 0.f ) + sf::Vector2f( 0.25f * ( 1.f + sinf( Card.VisualizationWind.x * SpaceshipCardsTime ) ), 0.25f * sinf( Card.VisualizationWind.y * SpaceshipCardsTime ) ) );

            Card.VisualizationSpaceship->setAccentTextureColor( Gameplay->getPlayerColor( SpaceshipIndex ) );
            Card.VisualizationSpaceship->setHealth( Card.VisualizationSpaceship->getHealthLimit() );
            Card.VisualizationSpaceship->setEnergy( Card.VisualizationSpaceship->getEnergyLimit() );
            Card.VisualizationSpaceship->setMissileCount( Card.VisualizationSpaceship->getMissileLimit() );
            Card.VisualizationSpaceship->updateHealth( 0.f );
            Card.VisualizationSpaceship->updateEnergy( 0.f );
            Card.VisualizationSpaceship->setPosition( Card.VisualizationSpaceship->getPosition() - Wind * ElapsedTime.asSeconds() );
            Card.VisualizationSpaceship->update( ElapsedTime );

            if ( Card.VisualizationSpaceship->onRayShot() ) {

                auto RayShot = new Ray ( Card.VisualizationSpaceship->getPosition(), Card.VisualizationSpaceship->getVelocityAngle() );

                RayShot->setColor( Card.VisualizationSpaceship->getRayColor() );
                RayShot->enableRendering();

                Card.VisualizationRayShots.push_back( RayShot ); }

            if ( Card.VisualizationSpaceship->onMissileShot() ) {

                auto * NewMissile = new Missile ( );
                NewMissile->setRadius( NewMissile->getRadius() * 2.f );

                sf::Vector2f MissilePosition = Card.VisualizationSpaceship->getPosition();
                MissilePosition.x += ( Card.VisualizationSpaceship->getRadius() + NewMissile->getRadius() + 5.f ) * cosf( Card.VisualizationSpaceship->getVelocityAngle() );
                MissilePosition.y += ( Card.VisualizationSpaceship->getRadius() + NewMissile->getRadius() + 5.f ) * sinf( Card.VisualizationSpaceship->getVelocityAngle() );

                NewMissile->setPosition( MissilePosition );
                NewMissile->setVelocity( Card.VisualizationSpaceship->getVelocity() );
                NewMissile->setTexture( Graphics->getTexture( "Missile" ) );
                NewMissile->setThrusterTexture( Graphics->getTexture( "Thruster" ) );

                Card.VisualizationMissiles.push_back( NewMissile ); } }

        for ( auto ActiveRayShot : Card.VisualizationRayShots ) {

            ActiveRayShot->update( ElapsedTime ); }

        for ( auto ActiveMissile : Card.VisualizationMissiles ) {

            ActiveMissile->update( ElapsedTime ); }

        for ( auto i = Card.VisualizationRayShots.begin(); i != Card.VisualizationRayShots.end(); ) {

            if ( !(*i)->isRenderingEnabled() ) {

                delete (*i);
                i = Card.VisualizationRayShots.erase( i ); }

            else {

                ++i; } }

        for ( auto i = Card.VisualizationMissiles.begin(); i != Card.VisualizationMissiles.end(); ) {

            if ( (*i)->isDestructed() ) {

                delete (*i);
                i = Card.VisualizationMissiles.erase( i ); }

            else {

                ++i; } } }

    for ( auto &Card : SpaceshipCards ) {

        if ( Card.Index == SpaceshipOption ) {

            if ( Card.Position.x != NeutralPosition && SpaceshipCardsOffsetDirection * ( Card.Position.x - NeutralPosition ) >= 0.f ) {

                SpaceshipCardsOffsetDirection = Card.Position.x - NeutralPosition;

                if ( Card.Position.x < NeutralPosition ) {

                    SpaceshipCardsOffset += ( 1.f / 0.5f ) * Card.Size.x * ElapsedTime.asSeconds(); }

                else {

                    SpaceshipCardsOffset -= ( 1.f / 0.5f ) * Card.Size.x * ElapsedTime.asSeconds(); } }

            else {

                SpaceshipCardsOffset = SectionSize.x / 2.f - ( CardSize.x + CardMargin.x ) * SpaceshipOption;
                SpaceshipCardsOffsetDirection = 0.f; }

            break; } }

    SpaceshipCardsTitleText[0] = Gameplay->getPlayerName( SpaceshipIndex );
    SpaceshipCardsTitleText[1] = ", choose your spaceship!";
    SpaceshipCardsTitleFontSize = 100;
    SpaceshipCardsTitleColor = Gameplay->getPlayerColor( SpaceshipIndex );
    SpaceshipCardsContentFontSize[0] = 100;
    SpaceshipCardsContentFontSize[1] = 100;

    sf::Text TextPrototype;
    TextPrototype.setString( Gameplay->getTheLongestPlayerName().replace( 0, 2, "Xy" ) + ", choose your spaceship!" );
    TextPrototype.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    TextPrototype.setCharacterSize( SpaceshipCardsTitleFontSize );

    while ( TextPrototype.getLocalBounds().height > ( 0.06f * SectionSize.y ) ) {

        TextPrototype.setCharacterSize( --SpaceshipCardsTitleFontSize ); }

    TextPrototype.setString( SpaceshipCardsTitleText[0] + SpaceshipCardsTitleText[1] );
    SpaceshipCardsTitlePosition[0] = SectionPosition + sf::Vector2f( ( SectionSize.x - TextPrototype.getLocalBounds().width ) / 2.f, 0.07f * SectionSize.y );
    SpaceshipCardsTitlePosition[0].x += TextPrototype.getLocalBounds().width * CONTROLLERS_SPACESHIP_CARDS_FONT_HORIZONTAL_OFFSET_FIX; // Offset fix
    SpaceshipCardsTitlePosition[0].y += TextPrototype.getLocalBounds().height * CONTROLLERS_SPACESHIP_CARDS_FONT_VERTICAL_OFFSET_FIX; // Offset fix
    TextPrototype.setString( SpaceshipCardsTitleText[0] );
    SpaceshipCardsTitlePosition[1] = SpaceshipCardsTitlePosition[0];
    SpaceshipCardsTitlePosition[1].x += TextPrototype.getLocalBounds().width;
    SpaceshipCardsTitlePosition[1].x += 2.f;
    SpaceshipCardsTitlePosition[0].x -= 2.f;

    TextPrototype.setString( Gameplay->getTheLongestSpaceshipPrototypeName().replace( 0, 2, "Xy" ) );
    TextPrototype.setCharacterSize( SpaceshipCardsContentFontSize[0] );

    while ( TextPrototype.getLocalBounds().height > ( ( 0.7f * CardSize.y ) / 7.f - 0.03f * CardSize.y ) ) {

        TextPrototype.setCharacterSize( --SpaceshipCardsContentFontSize[0] ); }

    while ( TextPrototype.getLocalBounds().width > CardSize.x ) {

        TextPrototype.setCharacterSize( --SpaceshipCardsContentFontSize[0] ); }

    TextPrototype.setString( "Energy restoration" );
    TextPrototype.setCharacterSize( SpaceshipCardsContentFontSize[1] );

    while ( TextPrototype.getLocalBounds().height > ( ( 0.7f * CardSize.y ) / 7.f - 0.03f * CardSize.y ) ) {

        TextPrototype.setCharacterSize( --SpaceshipCardsContentFontSize[1] ); }

    while ( TextPrototype.getLocalBounds().width > ( CardSize.y / 2.f - 0.03f * CardSize.y ) ) {

        TextPrototype.setCharacterSize( --SpaceshipCardsContentFontSize[1] ); } }

void MainMenu::updateSpaceshipsSection ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Left: {

                if ( SpaceshipOption != 0 ) {

                    SpaceshipOption--;
                    SpaceshipCardsOffsetDirection = 0.f; }

                break; }

            case sf::Keyboard::Right: {

                if ( SpaceshipOption != ( SpaceshipCards.size() - 1 ) && !SpaceshipCards.empty() ) {

                    SpaceshipOption++;
                    SpaceshipCardsOffsetDirection = 0.f; }

                break; }

            case sf::Keyboard::A: {

                if ( SpaceshipOption != 0 ) {

                    SpaceshipOption--;
                    SpaceshipCardsOffsetDirection = 0.f; }

                break; }

            case sf::Keyboard::D: {

                if ( SpaceshipOption != ( SpaceshipCards.size() - 1 ) && !SpaceshipCards.empty() ) {

                    SpaceshipOption++;
                    SpaceshipCardsOffsetDirection = 0.f; }

                break; }

            case sf::Keyboard::Return: {

                Gameplay->assignSpaceship( SpaceshipIndex, SpaceshipOption );

                if ( SpaceshipIndex == ( Gameplay->getPlayerCount() - 1 ) ) {

                    SpaceshipIndex = 0;
                    SpaceshipOption = 0;
                    SpaceshipCardsOffsetDirection = 0.f;

                    LaunchGame = true; }

                else {

                    SpaceshipIndex++;
                    SpaceshipCardsOffsetDirection = 0.f; }

                break; }

            case sf::Keyboard::Space: {

                Gameplay->assignSpaceship( SpaceshipIndex, SpaceshipOption );

                if ( SpaceshipIndex == ( Gameplay->getPlayerCount() - 1 ) ) {

                    SpaceshipIndex = 0;
                    SpaceshipOption = 0;
                    SpaceshipCardsOffsetDirection = 0.f;

                    LaunchGame = true; }

                else {

                    SpaceshipIndex++;
                    SpaceshipCardsOffsetDirection = 0.f; }

                break; }

            case sf::Keyboard::BackSpace: {

                Gameplay->assignSpaceship( SpaceshipIndex, -1 );

                if ( SpaceshipIndex == 0 ) {

                    SpaceshipOption = 0;

                    setMode( Modes::GameplayMode ); }

                else {

                    SpaceshipIndex--;
                    SpaceshipOption = (unsigned int) Gameplay->getSpaceshipAssignment( SpaceshipIndex );
                    SpaceshipCardsOffsetDirection = 0.f; }

                break; }

            case sf::Keyboard::Escape: {

                for ( unsigned int i = 0; i < Gameplay->getPlayerCount(); i++ ) {

                    Gameplay->assignSpaceship( i, -1 ); }

                SpaceshipIndex = 0;
                SpaceshipOption = 0;

                setMode( Modes::GameplayMode );

                break; }

            default: {

                break; } } } }

void MainMenu::renderSpaceshipsSection ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 2 );

    sf::Text SpaceshipCardsTitle;
    SpaceshipCardsTitle.setString( SpaceshipCardsTitleText[0] );
    SpaceshipCardsTitle.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    SpaceshipCardsTitle.setCharacterSize( SpaceshipCardsTitleFontSize );
    SpaceshipCardsTitle.setPosition( SpaceshipCardsTitlePosition[0] );

    #if ( SFML_VERSION_MINOR >= 4 )

        SpaceshipCardsTitle.setOutlineThickness( 1.f );
        SpaceshipCardsTitle.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
        SpaceshipCardsTitle.setFillColor( SpaceshipCardsTitleColor );

    #else

        SpaceshipCardsTitle.setColor( SpaceshipCardsTitleColor );

    #endif

    Window.draw( SpaceshipCardsTitle );

    SpaceshipCardsTitle.setString( SpaceshipCardsTitleText[1] );
    SpaceshipCardsTitle.setPosition( SpaceshipCardsTitlePosition[1] );

    #if ( SFML_VERSION_MINOR >= 4 )

        SpaceshipCardsTitle.setFillColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

    #else

        SpaceshipCardsTitle.setColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

    #endif

    Window.draw( SpaceshipCardsTitle );

    for ( auto &Card : SpaceshipCards ) {

        Card.VisualizationArea->clear( sf::Color( 22, 22, 22 ) ); // #161616

        for ( auto ActiveRayShot : Card.VisualizationRayShots ) {

            ActiveRayShot->render( *Card.VisualizationArea ); }

        for ( auto ActiveMissile : Card.VisualizationMissiles ) {

            ActiveMissile->render( *Card.VisualizationArea ); }

        Card.VisualizationSpaceship->render( *Card.VisualizationArea );
        Card.VisualizationArea->display();

        sf::Sprite Visualization;
        Visualization.setPosition( Card.Position - Card.Size / 2.f );
        Visualization.setScale( Card.Size.x / Card.VisualizationArea->getSize().x, ( 0.3f * Card.Size.y ) / Card.VisualizationArea->getSize().y );
        Visualization.setTexture( Card.VisualizationArea->getTexture() );

        Window.draw ( Visualization ); }

    for ( auto &Card : SpaceshipCards ) {

        float Margin = 0.03f * Card.Size.y;
        float Offset = ( 0.7f * Card.Size.y ) / 7.f;
        sf::Vector2f Position = Card.Position - sf::Vector2f( Card.Size.x / 2.f, Card.Size.y / 2.f );
        Position.y += 0.3f * Card.Size.y + 0.67f * Margin;

        sf::Text Text;
        Text.setString( Card.Prototype.Name );
        Text.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
        Text.setCharacterSize( SpaceshipCardsContentFontSize[0] );
        Text.setPosition( Position );
        Text.move( ( Card.Size.x - Text.getLocalBounds().width ) / 2.f, 0.f );
        Text.move( Text.getLocalBounds().width * CONTROLLERS_SPACESHIP_CARDS_FONT_HORIZONTAL_OFFSET_FIX, Text.getLocalBounds().height * CONTROLLERS_SPACESHIP_CARDS_FONT_VERTICAL_OFFSET_FIX ); // Offset fix

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
            Text.setFillColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

        #else

            Text.setColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

        #endif

        Window.draw( Text );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setFillColor( sf::Color( 189, 189, 189 ) ); // #BDBDBD

        #else

            Text.setColor( sf::Color( 189, 189, 189 ) );  // #BDBDBD

        #endif

        Text.setCharacterSize( SpaceshipCardsContentFontSize[1] );

        for ( unsigned int i = 0; i < 6; i++ ) {

            Position.y += Offset;
            Text.setPosition( Position );
            Text.move( Text.getLocalBounds().width * CONTROLLERS_SPACESHIP_CARDS_FONT_HORIZONTAL_OFFSET_FIX, Text.getLocalBounds().height * CONTROLLERS_SPACESHIP_CARDS_FONT_VERTICAL_OFFSET_FIX );

            switch ( i ) {

                case 0: Text.setString( "Health limit" );  break;
                case 1: Text.setString( "Health restoration" ); break;
                case 2: Text.setString( "Energy limit" ); break;
                case 3: Text.setString( "Energy restoration" ); break;
                case 4: Text.setString( "Thrust" ); break;
                case 5: Text.setString( "Ray power" ); break;

                default: break; }

            sf::Vector2f BarPosition = Position + Card.Size.x * sf::Vector2f( 0.5f, 0.f ) + sf::Vector2f( Margin, 0.f );
            sf::Vector2f BarSize = sf::Vector2f( 0.5f * Card.Size.x - Margin, Offset - Margin );

            switch ( i ) {

                case 0: renderSpaceshipsSectionBar( Window, BarPosition, BarSize, sf::Color( 255, 23, 68 ), Card.Prototype.HealthLimit / SpaceshipMaximumValues[i] );  break; // #FF1744
                case 1: renderSpaceshipsSectionBar( Window, BarPosition, BarSize, sf::Color( 255, 23, 68 ), Card.Prototype.HealthRestoration / SpaceshipMaximumValues[i] ); break; // #FF1744
                case 2: renderSpaceshipsSectionBar( Window, BarPosition, BarSize, sf::Color( 61, 90, 254 ), Card.Prototype.EnergyLimit / SpaceshipMaximumValues[i] ); break; // #3D5AFE
                case 3: renderSpaceshipsSectionBar( Window, BarPosition, BarSize, sf::Color( 61, 90, 254 ), Card.Prototype.EnergyRestoration / SpaceshipMaximumValues[i] ); break; // #3D5AFE
                case 4: renderSpaceshipsSectionBar( Window, BarPosition, BarSize, sf::Color( 213, 0, 249 ), Card.Prototype.Thrust / SpaceshipMaximumValues[i] ); break; // #D500F9
                case 5: renderSpaceshipsSectionBar( Window, BarPosition, BarSize, sf::Color( 213, 0, 249 ), Card.Prototype.RayPower / SpaceshipMaximumValues[i] ); break; // #D500F9

                default: break; }

            Window.draw( Text ); }

        Window.draw( Card.Outline ); } }

void MainMenu::renderSpaceshipsSectionBar ( sf::RenderWindow &Window, sf::Vector2f Position, sf::Vector2f Size, sf::Color Color, float Value ) {

    Value = fminf( Value, 1.f );

    auto ElementsCount = (unsigned int) ( Size.x / ( 0.65f * Size.y ) );
    sf::Vector2f ElementSize = sf::Vector2f( 0.75f * ( Size.x / ElementsCount ),Size.y );
    float ElementMargin = ( Size.x - ElementSize.x * ElementsCount ) / ( ElementsCount - 1 );
    sf::Vector2f ElementPosition = Position;

    for ( unsigned int i = 0; i < ElementsCount; i++ ) {

        sf::RectangleShape Element;
        bool ElementActivated = ( Value >= ( (float) ( i + 1 ) / (float) ElementsCount ) );

        if ( i == 0 ) {

            ElementActivated = true; }

        Element.setSize( ElementSize );
        Element.setPosition( ElementPosition );
        Element.setOutlineThickness( 1.f );
        Element.setFillColor( sf::Color( Color.r, Color.g, Color.b, (sf::Uint8) ( ( ElementActivated ? 0.87f : 0.34f ) * 255.f ) ) );
        Element.setOutlineColor( sf::Color( Color.r, Color.g, Color.b, 127 ) );

        Window.draw( Element );

        ElementPosition.x += ElementSize.x + ElementMargin; } }

void MainMenu::updateSettingsSection ( sf::Time ElapsedTime ) {

    SettingsOptionText[ SettingsOptionCount + 0 ] = std::to_string( WindowWidth ) + " x " + std::to_string( WindowHeight );
    SettingsOptionText[ SettingsOptionCount + 1 ] = FullScreen ? "enable" : "disable";
    SettingsOptionText[ SettingsOptionCount + 3 ] = EpilepsyProtection ? "enable" : "disable";

    if ( AntialiasingLevel == 0 ) {

        SettingsOptionText[ SettingsOptionCount + 2 ] = "none"; }

    else if ( AntialiasingLevel == 1 ) {

        SettingsOptionText[ SettingsOptionCount + 2 ] = "1st level"; }

    else if ( AntialiasingLevel == 2 ) {

        SettingsOptionText[ SettingsOptionCount + 2 ] = "2nd level"; }

    else { // 4th or 8th

        SettingsOptionText[ SettingsOptionCount + 2 ] = std::to_string( AntialiasingLevel ) + "th level"; }

    sf::Vector2f SectionMargin;
    sf::Vector2f OptionMargin;

    if ( Graphics->getWindowHeight() < 600.f ) {

        SectionMargin = sf::Vector2f ( 12.f, 20.f );
        OptionMargin = sf::Vector2f ( 6.f, 10.f ); }

    else if ( Graphics->getWindowHeight() >= 600 && Graphics->getWindowHeight() <= 800.f ) {

        SectionMargin = sf::Vector2f ( 20.f, 30.f );
        OptionMargin = sf::Vector2f ( 0.f, 15.f ); }

    else if ( Graphics->getWindowHeight() > 800.f && Graphics->getWindowHeight() <= 1000.f ) {

        SectionMargin = sf::Vector2f ( 60.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

        SectionMargin = sf::Vector2f ( 60.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    else {

        SectionMargin = sf::Vector2f ( 100.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    sf::Text TextPrototype;
    sf::Vector2f SectionSize = sf::Vector2f ( 0.35f * Graphics->getWindowWidth() - 2.f * SectionMargin.x, Graphics->getWindowHeight() - 2.f * SectionMargin.y );
    sf::Vector2f OptionPosition = sf::Vector2f ( 0.55f * Graphics->getWindowWidth() + SectionMargin.x + OptionMargin.x, Graphics->getWindowHeight() - SectionMargin.y );
    float OptionHeight = 0.f;

    SettingsOptionFontSize = MenuOptionFontSize;
    float SmallFontScale = 0.85f;

    for ( unsigned int i = 0; i < ( 2 * SettingsOptionCount - 1 ); i++ ) {

        TextPrototype.setString( SettingsOptionText[i] );
        TextPrototype.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
        TextPrototype.setCharacterSize( i < SettingsOptionCount ? SettingsOptionFontSize : (unsigned int) ( SmallFontScale * SettingsOptionFontSize ) );

        while ( TextPrototype.getLocalBounds().height > ( 0.06f * SectionSize.y ) ) {

            TextPrototype.setCharacterSize( --SettingsOptionFontSize ); }

        while ( TextPrototype.getLocalBounds().width > SectionSize.x ) {

            TextPrototype.setCharacterSize( --SettingsOptionFontSize ); } }

    for ( unsigned int i = 0; i < ( 2 * SettingsOptionCount - 1 ); i++ ) {

        TextPrototype.setString( SettingsOptionText[i] );
        TextPrototype.setCharacterSize( i < SettingsOptionCount ? SettingsOptionFontSize : (unsigned int) ( SmallFontScale * SettingsOptionFontSize ) );

        OptionHeight = std::fmaxf( OptionHeight, TextPrototype.getLocalBounds().height ); }

    for ( unsigned int i = 0; i < SettingsOptionCount; i++ ) {

        size_t Index = SettingsOptionCount - i - 1;

        if ( ( Index + 1 ) != SettingsOptionCount ) {

            SettingsOptionPosition[ Index ] = sf::Vector2f( OptionPosition.x, OptionPosition.y - 2.f * OptionHeight - 0.5f * OptionMargin.y );
            SettingsOptionPosition[ Index + SettingsOptionCount ] = sf::Vector2f( OptionPosition.x, OptionPosition.y - OptionHeight );

            OptionPosition.y -= 2.f * OptionHeight + 1.5f * OptionMargin.y; }

        else {

            SettingsOptionPosition[ Index ] = sf::Vector2f( OptionPosition.x, OptionPosition.y - OptionHeight );

            OptionPosition.y -= OptionHeight + OptionMargin.y; } } }

void MainMenu::updateSettingsSection ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Up: {

                if ( SettingsOption > 0 ) {

                    SettingsOption--; }

                break; }

            case sf::Keyboard::Down: {

                if ( SettingsOption < ( SettingsOptionCount - 1 ) ) {

                    SettingsOption++; }

                break; }

            case sf::Keyboard::Left: {

                updateSettingsSection_BindLeft();

                break; }

            case sf::Keyboard::Right: {

                updateSettingsSection_BindRight();

                break; }

            case sf::Keyboard::W: {

                if ( SettingsOption > 0 ) {

                    SettingsOption--; }

                break; }

            case sf::Keyboard::S: {

                if ( SettingsOption < ( SettingsOptionCount - 1 ) ) {

                    SettingsOption++; }

                break; }

            case sf::Keyboard::A: {

                updateSettingsSection_BindLeft();

                break; }

            case sf::Keyboard::D: {

                updateSettingsSection_BindRight();

                break; }

            case sf::Keyboard::Return: {

                if ( SettingsOption == 4 ) {

                    setMode( Modes::ControllersMode ); }

                break; }

            case sf::Keyboard::Space: {

                if ( SettingsOption == 3 ) {

                    setMode( Modes::ControllersMode ); }

                break; }

            case sf::Keyboard::BackSpace: {

                SettingsOption = 0;

                setMode( Modes::MenuMode );

                break; }

            case sf::Keyboard::Escape: {

                SettingsOption = 0;

                setMode( Modes::MenuMode );

                break; }

            default: {

                break; } } } }

void MainMenu::updateSettingsSection_BindLeft ( ) {

    switch ( SettingsOption ) {

        case 0: {

            std::vector <sf::VideoMode> Resolutions = sf::VideoMode::getFullscreenModes();
            size_t Index = 0;

            for ( auto i = Resolutions.begin(); i != Resolutions.end(); ) {

                if ( i->height < 480 || i->height > 1080 ) {

                    i = Resolutions.erase( i ); }

                else {

                    ++i; } }

            while ( Index < Resolutions.size() && WindowWidth < Resolutions[Index].width ) {

                Index++; }

            while ( Index < Resolutions.size() && WindowHeight < Resolutions[Index].height ) {

                Index++; }

            if ( Index != Resolutions.size() && WindowWidth == Resolutions[Index].width && WindowHeight == Resolutions[Index].height ) {

                Index++; }

            if ( Index == Resolutions.size() ) {

                Index = 0; }

            WindowWidth = Resolutions[Index].width;
            WindowHeight = Resolutions[Index].height;

            VideoChanged = true;
            SettingsChanged = true;

            break; }

        case 1: {

            FullScreen = !FullScreen;

            VideoChanged = true;
            SettingsChanged = true;

            break; }

        case 2: {

            switch ( AntialiasingLevel ) {

                case 0: {

                    AntialiasingLevel = 8;

                    break; }

                case 1: {

                    AntialiasingLevel = 0;

                    break; }

                case 2: {

                    AntialiasingLevel = 1;

                    break; }

                case 4: {

                    AntialiasingLevel = 2;

                    break; }

                case 8: {

                    AntialiasingLevel = 4;

                    break; }

                default: {

                    AntialiasingLevel = 0;

                    break; } }

            VideoChanged = true;
            SettingsChanged = true;

            break; }

        case 3: {

            EpilepsyProtection = !EpilepsyProtection;

            SettingsChanged = true;

            break; }

        default: {

            break; } } }

void MainMenu::updateSettingsSection_BindRight ( ) {

    switch ( SettingsOption ) {

        case 0: {

            std::vector <sf::VideoMode> Resolutions = sf::VideoMode::getFullscreenModes();
            size_t Index = Resolutions.size();

            for ( auto i = Resolutions.begin(); i != Resolutions.end(); ) {

                if ( i->height < 480 || i->height > 1080 ) {

                    i = Resolutions.erase( i ); }

                else {

                    ++i; } }

            while ( Index > 0 && WindowWidth > Resolutions[ Index - 1 ].width ) {

                Index--; }

            while ( Index > 0 && WindowHeight > Resolutions[ Index - 1 ].height ) {

                Index--; }

            if ( Index != 0 && WindowWidth == Resolutions[ Index - 1 ].width && WindowHeight == Resolutions[ Index - 1 ].height ) {

                Index--; }

            if ( Index == 0 ) {

                Index = Resolutions.size(); }

            WindowWidth = Resolutions[ Index - 1 ].width;
            WindowHeight = Resolutions[ Index - 1 ].height;

            VideoChanged = true;
            SettingsChanged = true;

            break; }

        case 1: {

            FullScreen = !FullScreen;

            VideoChanged = true;
            SettingsChanged = true;

            break; }

        case 2: {

            switch ( AntialiasingLevel ) {

                case 0: {

                    AntialiasingLevel = 1;

                    break; }

                case 1: {

                    AntialiasingLevel = 2;

                    break; }

                case 2: {

                    AntialiasingLevel = 4;

                    break; }

                case 4: {

                    AntialiasingLevel = 8;

                    break; }

                case 8: {

                    AntialiasingLevel = 0;

                    break; }

                default: {

                    AntialiasingLevel = 0;

                    break; } }

            VideoChanged = true;
            SettingsChanged = true;

            break; }

        case 3: {

            EpilepsyProtection = !EpilepsyProtection;

            SettingsChanged = true;

            break; }

        default: {

            break; } } }

void MainMenu::renderSettingsSection ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 1 );

    sf::Text Text;
    Text.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    Text.setCharacterSize( SettingsOptionFontSize );

    for ( unsigned int i = 0; i < SettingsOptionCount; i++ ) {

        Text.setString( SettingsOptionText[i] );
        Text.setPosition( SettingsOptionPosition[i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121

            if ( i == SettingsOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i + 1 ) == SettingsOption || ( i - 1 ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i + 2 ) == SettingsOption || ( i - 2 ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #else

            if ( i == SettingsOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i + 1 ) == SettingsOption || ( i - 1 ) == SettingsOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i + 2 ) == SettingsOption || ( i - 2 ) == SettingsOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #endif

        Window.draw( Text ); }

    Text.setCharacterSize( (unsigned int) ( 0.85f * SettingsOptionFontSize ) );

    for ( unsigned int i = SettingsOptionCount; i < ( 2 * SettingsOptionCount - 1 ); i++ ) {

        Text.setString( SettingsOptionText[i] );
        Text.setPosition( SettingsOptionPosition[i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121

            if ( ( i - SettingsOptionCount ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i - SettingsOptionCount + 1 ) == SettingsOption || ( i - SettingsOptionCount - 1 ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i - SettingsOptionCount + 2 ) == SettingsOption || ( i - SettingsOptionCount - 2 ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #else

            if ( ( i - SettingsOptionCount ) == SettingsOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else if ( ( i - SettingsOptionCount + 1 ) == SettingsOption || ( i - SettingsOptionCount - 1 ) == SettingsOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

            else if ( ( i - SettingsOptionCount + 2 ) == SettingsOption || ( i - SettingsOptionCount - 2 ) == SettingsOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); } // #757575

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); } // #424242

        #endif

        Window.draw( Text ); } }

void MainMenu::updateControllersSection ( sf::Time ElapsedTime ) {

    std::string ManualText = "Use ARROWS to navigate and ENTER to modify.";

    if ( ControllersModificationMode ) {

        if ( ControllersTablePointer.y > 1 ) {

            ManualText = "Use ANY KEY to select a key and then repeat it to confirm.";

            int Key = -1;
            PlayerControllerSettings::Devices Device = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getDevice();

            if ( Device == PlayerControllerSettings::Devices::Keyboard ) {

                Key = PlayerControllerSettings::scanKeyboard(); }

            else if ( Device == PlayerControllerSettings::Devices::Joystick ) {

                Key = PlayerControllerSettings::scanJoystick( Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getJoystickIdentifier() ); }

            if ( ControllersModificationState == 0 ) {

                if ( Key == -1 ) {

                    ControllersModificationState = 1; }

                if ( Key < -1 ) { // Joystick is not connected

                    ManualText = "Joystick is not connected. Choose the one with a brighter color.";

                    if ( PlayerControllerSettings::scanKeyboard() == -1 ) {

                        ControllersModificationState = 5; } } }

            if ( ControllersModificationState == 1 ) {

                if ( Key != -1 ) {

                    switch ( ControllersTablePointer.y ) {

                        case 2: Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setForwardKey( Key ); break;
                        case 3: Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setBackwardKey( Key ); break;
                        case 4: Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setLeftKey( Key ); break;
                        case 5: Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setRightKey( Key ); break;
                        case 6: Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setRayShotKey( Key ); break;
                        case 7: Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setMissileShotKey( Key ); break;

                        default: break; }

                    ControllersModificationState = 2; } }

            else if ( ControllersModificationState == 2 ) {

                if ( Key == -1 ) {

                    ControllersModificationState = 3; } }

            else if ( ControllersModificationState == 3 ) {

                int LastKey;

                switch ( ControllersTablePointer.y ) {

                    case 2: LastKey = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getForwardKey(); break;
                    case 3: LastKey = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getBackwardKey(); break;
                    case 4: LastKey = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getLeftKey(); break;
                    case 5: LastKey = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getRightKey(); break;
                    case 6: LastKey = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getRayShotKey(); break;
                    case 7: LastKey = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getMissileShotKey(); break;

                    default: LastKey = -1; break; }

                if ( Key == LastKey ) {

                    ControllersModificationState = 4; }

                else if ( Key != -1 ) {

                    ControllersModificationState = 1; } }

            else if ( ControllersModificationState == 4 ) {

                if ( Key == -1 ) {

                    ControllersModificationState = 5; } } }

        else { // Devices

            ManualText = "Use ARROWS to select device and ENTER to confirm.";

            int Key = PlayerControllerSettings::scanKeyboard();
            PlayerControllerSettings::Devices Device = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getDevice();

            if ( ControllersModificationState == 0 ) {

                if ( Key == -1 ) {

                    ControllersModificationState = 1; } }

            else if ( ControllersModificationState == 1 ) {

                if ( Key == sf::Keyboard::Left || Key == sf::Keyboard::A ) {

                    if ( Device == PlayerControllerSettings::Devices::Keyboard ) {

                        Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setDevice( PlayerControllerSettings::Devices::Joystick );
                        Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setJoystickIdentifier( 7 ); }

                    else if ( Device == PlayerControllerSettings::Devices::Joystick ) {

                        int JoystickIdentifier = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getJoystickIdentifier();

                        if ( JoystickIdentifier == 0 ) {

                            Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setDevice( PlayerControllerSettings::Devices::Keyboard ); }

                        else {

                            Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setJoystickIdentifier( --JoystickIdentifier ); } }

                    ControllersModificationState = 0; }

                else if ( Key == sf::Keyboard::Right || Key == sf::Keyboard::D ) {

                    if ( Device == PlayerControllerSettings::Devices::Keyboard ) {

                        Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setDevice( PlayerControllerSettings::Devices::Joystick );
                        Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setJoystickIdentifier( 0 ); }

                    else if ( Device == PlayerControllerSettings::Devices::Joystick ) {

                        int JoystickIdentifier = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getJoystickIdentifier();

                        if ( JoystickIdentifier == 7 ) {

                            Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setDevice( PlayerControllerSettings::Devices::Keyboard ); }

                        else {

                            Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setJoystickIdentifier( ++JoystickIdentifier ); } }


                    ControllersModificationState = 0; }

                else if ( Key == sf::Keyboard::Return || Key == sf::Keyboard::Space ) {

                    ControllersModificationState = 2; }

                else if ( Key == sf::Keyboard::BackSpace ) {

                    ControllersModificationState = 3; } }

            else if ( ControllersModificationState == 2 ) {

                int JoystickIdentifier = Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->getJoystickIdentifier();

                if ( ( Device != PreviousDevice ) || ( Device == PlayerControllerSettings::Devices::Joystick && JoystickIdentifier != PreviousIdentifier) ) {

                    Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setForwardKey( KEY_NONE );
                    Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setBackwardKey( KEY_NONE );
                    Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setLeftKey( KEY_NONE );
                    Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setRightKey( KEY_NONE );
                    Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setRayShotKey( KEY_NONE );
                    Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setMissileShotKey( KEY_NONE ); }

                ControllersModificationState = 4; }

            else if ( ControllersModificationState == 3 ) {

                Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setDevice( PreviousDevice );

                if ( PreviousDevice == PlayerControllerSettings::Devices::Joystick ) {

                    Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setJoystickIdentifier( PreviousIdentifier ); }

                ControllersModificationState = 4; }

            else if ( ControllersModificationState == 4 ) {

                if ( Key == -1 ) {

                    ControllersModificationState = 5; } } }

        if ( ControllersModificationState == 5 ) {

            ControllersModificationMode = false; } }

    sf::Vector2f SectionPosition = sf::Vector2f( 0.f, 0.125f * Graphics->getWindowHeight() );
    sf::Vector2f SectionSize = sf::Vector2f( Graphics->getWindowWidth(), 0.75f * Graphics->getWindowHeight() );

    float TableTop = 0.125f;
    float TableBottom = 0.750f;
    float TableLeft = 0.125f;
    float TableRight = 0.875f;
    sf::Vector2f TableThickness = { 1.5f / SectionSize.x, 1.5f / SectionSize.y };
    sf::Color TableColor = sf::Color( 13, 71, 161 ); // #0D47A1

    unsigned int RowCount = 8;
    unsigned int ColumnCount = MAXIMUM_PLAYER_COUNT + 1;
    float TableCellWidth = ( TableRight - TableLeft ) / ( ColumnCount + 0.5f );
    float TableCellHeight = ( TableBottom - TableTop ) / ( RowCount + 0.5f );

    ControllersTable.clear();

    // Top line of the table
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft, TableTop ), TableColor ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableRight + TableThickness.x, TableTop ), TableColor ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableRight + TableThickness.x, TableTop + TableThickness.y ), TableColor ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft, TableTop + TableThickness.y ), TableColor ) );

    // Left line of the table
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft, TableTop ), TableColor ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft, TableBottom ), TableColor ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft + TableThickness.x, TableBottom + TableThickness.y ), TableColor ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft + TableThickness.x, TableTop + TableThickness.y ), TableColor ) );

    for ( unsigned int i = 0; i < RowCount; i++ ) {

        for ( unsigned int j = 0; j < ColumnCount; j++ ) {

            float Width = ( j > 0 ) ? TableCellWidth : 1.5f * TableCellWidth;
            float Height = ( i > 0 ) ? TableCellHeight : 1.5f * TableCellHeight;

            float PositionX = TableLeft + ( ( j > 0 ) ? ( 1.5f + ( j - 1 ) ) * TableCellWidth : 0.f );
            float PositionY = TableTop + ( ( i > 0 ) ? ( 1.5f + ( i - 1 ) ) * TableCellHeight : 0.f );

            // Bottom line of the cell
            ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( PositionX, PositionY + Height ), TableColor ) );
            ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( PositionX + Width + TableThickness.x, PositionY + Height ), TableColor ) );
            ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( PositionX + Width + TableThickness.x, PositionY + Height + TableThickness.y ), TableColor ) );
            ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( PositionX, PositionY + Height + TableThickness.y ), TableColor ) );

            // Right line of the cell
            ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( PositionX + Width, PositionY ), TableColor ) );
            ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( PositionX + Width, PositionY + Height + TableThickness.y ), TableColor ) );
            ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( PositionX + Width + TableThickness.x, PositionY + Height + TableThickness.y ), TableColor ) );
            ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( PositionX + Width + TableThickness.x, PositionY ), TableColor ) ); } }

    for ( unsigned int i = 0; i < ControllersTable.size(); i++ ) {

        ControllersTable[i].position.x *= SectionSize.x;
        ControllersTable[i].position.y *= SectionSize.y;
        ControllersTable[i].position += SectionPosition; }

    unsigned int TableColumnHeaderFontSize = 100;
    unsigned int TableRowHeaderFontSize = 100;
    unsigned int TableContentFontSize = 100;
    unsigned int TableManualFontSize = 100;

    sf::Text TextPrototype;
    TextPrototype.setString( Gameplay->getTheLongestPlayerName().replace( 0, 2, "Xy" ) );
    TextPrototype.setFont( Graphics->getFont( "SairaCondensedLight" ) );
    TextPrototype.setCharacterSize( TableColumnHeaderFontSize );

    while ( TextPrototype.getLocalBounds().width > ( SectionSize.x * 0.8f * TableCellWidth ) ) {

        TextPrototype.setCharacterSize( --TableColumnHeaderFontSize ); }

    while ( TextPrototype.getLocalBounds().height > ( SectionSize.y * 1.0f * TableCellHeight ) ) {

        TextPrototype.setCharacterSize( --TableColumnHeaderFontSize ); }

    TextPrototype.setString( "Thrust backward" );
    TextPrototype.setCharacterSize( TableRowHeaderFontSize );

    while ( TextPrototype.getLocalBounds().width > ( SectionSize.x * 1.4f * TableCellWidth ) ) {

        TextPrototype.setCharacterSize( --TableRowHeaderFontSize ); }

    while ( TextPrototype.getLocalBounds().height > ( SectionSize.y * 0.7f * TableCellHeight ) ) {

        TextPrototype.setCharacterSize( --TableRowHeaderFontSize ); }

    TextPrototype.setString( "SHIFT RIGHT" );
    TextPrototype.setCharacterSize( TableContentFontSize );

    while ( TextPrototype.getLocalBounds().width > ( SectionSize.x * 0.9f * TableCellWidth ) ) {

        TextPrototype.setCharacterSize( --TableContentFontSize ); }

    while ( TextPrototype.getLocalBounds().height > ( SectionSize.y * 0.7f * TableCellHeight ) ) {

        TextPrototype.setCharacterSize( --TableContentFontSize ); }

    TextPrototype.setString( "Joystick is not connected. Choose the one with a brighter color." );
    TextPrototype.setCharacterSize( TableManualFontSize );

    while ( TextPrototype.getLocalBounds().width > ( 0.9f * SectionSize.x * ( TableRight - TableLeft ) ) ) {

        TextPrototype.setCharacterSize( --TableManualFontSize ); }

    while ( TextPrototype.getLocalBounds().height > ( SectionSize.y * 0.5f * ( 1.f - TableBottom ) ) ) {

        TextPrototype.setCharacterSize( --TableManualFontSize ); }

    ControllersTableColumnHeader.resize( ColumnCount - 1 );

    for ( unsigned int c = 1; c < ColumnCount; c++ ) {

        ControllersTableColumnHeader[ c - 1 ].setString( Gameplay->getTheLongestPlayerName().replace( 0, 2, "Xy" ) );
        ControllersTableColumnHeader[ c - 1 ].setFont( Graphics->getFont( "SairaCondensedLight" ) );
        ControllersTableColumnHeader[ c - 1 ].setCharacterSize( TableColumnHeaderFontSize );

        sf::Vector2f Position;
        Position.x = TableLeft + ( 1.5f + ( c - 1 ) ) * TableCellWidth;
        Position.y = TableTop + 0.15f * TableCellHeight; // Offset fix
        Position.x *= SectionSize.x;
        Position.y *= SectionSize.y;
        Position += SectionPosition;
        Position.y += ( SectionSize.y * 1.5f * TableCellHeight - ControllersTableColumnHeader[ c - 1 ].getLocalBounds().height ) / 2.f;

        ControllersTableColumnHeader[ c - 1 ].setString( Gameplay->getPlayerName( c - 1 ) );

        Position.x += ( SectionSize.x * TableCellWidth - ControllersTableColumnHeader[ c - 1 ].getLocalBounds().width ) / 2.f;
        Position.x += ControllersTableColumnHeader[ c - 1 ].getLocalBounds().width * CONTROLLERS_TABLE_FONT_HORIZONTAL_OFFSET_FIX; // Offset fix
        Position.y += ControllersTableColumnHeader[ c - 1 ].getLocalBounds().height * CONTROLLERS_TABLE_FONT_VERTICAL_OFFSET_FIX; // Offset fix

        ControllersTableColumnHeader[ c - 1 ].setPosition( Position );

        #if ( SFML_VERSION_MINOR >= 4 )
    
            ControllersTableColumnHeader[ c - 1 ].setOutlineThickness( 1.f );
            ControllersTableColumnHeader[ c - 1 ].setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
            ControllersTableColumnHeader[ c - 1 ].setFillColor( Gameplay->getPlayerColor( c - 1 ) );
    
        #else
    
            ControllersTableColumnHeader[ c - 1 ].setColor( Gameplay->getPlayerColor( c - 1 ) );
    
        #endif
    
        }

    ControllersTableRowHeader.resize( RowCount - 1 );

    for ( unsigned int r = 1; r < RowCount; r++ ) {

        ControllersTableRowHeader[ r - 1 ].setString( "Thrust backward" );
        ControllersTableRowHeader[ r - 1 ].setFont( Graphics->getFont( "SairaCondensedLight" ) );
        ControllersTableRowHeader[ r - 1 ].setCharacterSize( TableRowHeaderFontSize );

        sf::Vector2f Position;
        Position.x = TableLeft + 0.05f * TableCellWidth;
        Position.y = TableTop + ( 1.5f + ( r - 1 ) ) * TableCellHeight;
        Position.x *= SectionSize.x;
        Position.y *= SectionSize.y;
        Position += SectionPosition;
        Position.y += ( SectionSize.y * TableCellHeight - ControllersTableRowHeader[ r - 1 ].getLocalBounds().height ) / 2.f;
        Position.x += ControllersTableRowHeader[ r - 1 ].getLocalBounds().width * CONTROLLERS_TABLE_FONT_HORIZONTAL_OFFSET_FIX; // Offset fix
        Position.y += ControllersTableRowHeader[ r - 1 ].getLocalBounds().height * CONTROLLERS_TABLE_FONT_VERTICAL_OFFSET_FIX; // Offset fix

        std::string Text;

        switch ( r ) {

            case 1: Text = "Device"; break;
            case 2: Text = "Thrust forward"; break;
            case 3: Text = "Thrust backward"; break;
            case 4: Text = "Turn left"; break;
            case 5: Text = "Turn right"; break;
            case 6: Text = "Ray shot"; break;
            case 7: Text = "Missile shot"; break;

            default: break; }

        ControllersTableRowHeader[ r - 1 ].setString( Text );
        ControllersTableRowHeader[ r - 1 ].setPosition( Position );

        #if ( SFML_VERSION_MINOR >= 4 )

            ControllersTableRowHeader[ r - 1 ].setOutlineThickness( 1.f );
            ControllersTableRowHeader[ r - 1 ].setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
            ControllersTableRowHeader[ r - 1 ].setFillColor( sf::Color( 189, 189, 189 ) ); // #BDBDBD

        #else

            ControllersTableRowHeader[ r - 1 ].setColor( sf::Color( 189, 189, 189 ) ); // #BDBDBD

        #endif

        }

    ControllersTableContent.resize( ( RowCount - 1 ) * ( ColumnCount - 1 ) );

    for ( unsigned int c = 1; c < ColumnCount; c++ ) {

        ControllersTableContent[ c - 1 ].setString( "SHIFT RIGHT" );
        ControllersTableContent[ c - 1 ].setFont( Graphics->getFont( "SairaCondensedLight" ) );
        ControllersTableContent[ c - 1 ].setCharacterSize( TableContentFontSize );

        sf::Vector2f Position;
        Position.x = TableLeft + ( 1.5f + 0.05f + ( c - 1 ) ) * TableCellWidth;
        Position.y = TableTop + ( 1.5f ) * TableCellHeight;
        Position.x *= SectionSize.x;
        Position.y *= SectionSize.y;
        Position += SectionPosition;
        Position.y += ( SectionSize.y * TableCellHeight - ControllersTableContent[ c - 1 ].getLocalBounds().height ) / 2.f;
        Position.x += ControllersTableContent[ c - 1 ].getLocalBounds().width * CONTROLLERS_TABLE_FONT_HORIZONTAL_OFFSET_FIX; // Offset fix
        Position.y += ControllersTableContent[ c - 1 ].getLocalBounds().height * CONTROLLERS_TABLE_FONT_VERTICAL_OFFSET_FIX; // Offset fix

        std::string Text;
        Text = "KEYBOARD";

        if ( Gameplay->getControllerSettings( c - 1 )->getDevice() == PlayerControllerSettings::Devices::Joystick ) {

            Text = "JOYSTICK " + std::to_string( Gameplay->getControllerSettings( c - 1 )->getJoystickIdentifier() ); }

        ControllersTableContent[ c - 1 ].setString( Text );
        ControllersTableContent[ c - 1 ].setPosition( Position );

        sf::Color FillColor = sf::Color( 189, 189, 189 ); // #BDBDBD
        sf::Color OutlineColor = sf::Color( 33, 33, 33 ); // #212121

        if ( ControllersTablePointer.x == c && ControllersTablePointer.y == 1 ) {

            if ( !ControllersModificationMode ) {

                FillColor = sf::Color( 250, 250, 250 ); } // #FAFAFA

            else {

                if ( Gameplay->getControllerSettings( c - 1 )->getDevice() == PlayerControllerSettings::Devices::Joystick ) {

                    if ( sf::Joystick::isConnected( (unsigned int) Gameplay->getControllerSettings( c - 1 )->getJoystickIdentifier() ) ) {

                        FillColor = sf::Color( 239, 83, 80 ); // #EF5350
                        OutlineColor = sf::Color( 0, 0, 0 ); } // #000000

                    else {

                        FillColor = sf::Color( 198, 40, 40 ); // #C62828
                        OutlineColor = sf::Color( 0, 0, 0 ); } } // #000000

                else {

                    FillColor = sf::Color( 239, 83, 80 ); // #EF5350
                    OutlineColor = sf::Color( 0, 0, 0 ); } } } // #000000

        else if ( Gameplay->getControllerSettings( c - 1 )->getDevice() == PlayerControllerSettings::Devices::Joystick ) {

            if ( !sf::Joystick::isConnected( (unsigned int) Gameplay->getControllerSettings( c - 1 )->getJoystickIdentifier() ) ) {

                FillColor = sf::Color( 117, 117, 117 ); } } // #757575

        #if ( SFML_VERSION_MINOR >= 4 )

                ControllersTableContent[ c - 1 ].setOutlineThickness( 1.f );
                ControllersTableContent[ c - 1 ].setOutlineColor( OutlineColor );
                ControllersTableContent[ c - 1 ].setFillColor( FillColor );

        #else

                ControllersTableContent[ c - 1 ].setColor( FillColor );

        #endif

        }

    for ( unsigned int r = 2; r < RowCount; r++ ) {

        for ( unsigned int c = 1; c < ColumnCount; c++ ) {

            ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].setString( "SHIFT RIGHT" );
            ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].setFont( Graphics->getFont( "SairaCondensedLight" ) );
            ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].setCharacterSize( TableContentFontSize );

            sf::Vector2f Position;
            Position.x = TableLeft + ( 1.5f + 0.05f + ( c - 1 ) ) * TableCellWidth;
            Position.y = TableTop + ( 1.5f + ( r - 1 ) ) * TableCellHeight;
            Position.x *= SectionSize.x;
            Position.y *= SectionSize.y;
            Position += SectionPosition;
            Position.y += ( SectionSize.y * TableCellHeight - ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].getLocalBounds().height ) / 2.f;
            Position.x += ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].getLocalBounds().width * CONTROLLERS_TABLE_FONT_HORIZONTAL_OFFSET_FIX; // Offset fix
            Position.y += ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].getLocalBounds().height * CONTROLLERS_TABLE_FONT_VERTICAL_OFFSET_FIX; // Offset fix

            int Key;

            switch ( r ) {

                case 2: Key = Gameplay->getControllerSettings( c - 1 )->getForwardKey(); break;
                case 3: Key = Gameplay->getControllerSettings( c - 1 )->getBackwardKey(); break;
                case 4: Key = Gameplay->getControllerSettings( c - 1 )->getLeftKey(); break;
                case 5: Key = Gameplay->getControllerSettings( c - 1 )->getRightKey(); break;
                case 6: Key = Gameplay->getControllerSettings( c - 1 )->getRayShotKey(); break;
                case 7: Key = Gameplay->getControllerSettings( c - 1 )->getMissileShotKey(); break;

                default: Key = -1; break; }

            ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].setString( blankUnderscore( PlayerControllerSettings::encodeKey( Key ) ) );
            ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].setPosition( Position );

            sf::Color FillColor = sf::Color( 189, 189, 189 ); // #BDBDBD
            sf::Color OutlineColor = sf::Color( 33, 33, 33 ); // #212121

            if ( ControllersTablePointer.x == c && ControllersTablePointer.y == r ) {

                if ( !ControllersModificationMode ) {

                    FillColor = sf::Color( 250, 250, 250 ); } // #FAFAFA

                else {

                    FillColor = sf::Color( 239, 83, 80 ); // #EF5350
                    OutlineColor = sf::Color( 0, 0, 0 ); } }

            else if ( Key == -1 ) {

                FillColor = sf::Color( 117, 117, 117 ); } // #757575

            #if ( SFML_VERSION_MINOR >= 4 )

                ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].setOutlineThickness( 1.f );
                ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].setOutlineColor( OutlineColor );
                ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].setFillColor( FillColor );

            #else

                ControllersTableContent[ ( r - 1 ) * ( ColumnCount - 1 ) + ( c - 1 ) ].setColor( FillColor );

            #endif

            } }

    ControllersTableManual.setString( "Joystick is not connected. Choose the one with a brighter color." );
    ControllersTableManual.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    ControllersTableManual.setCharacterSize( TableManualFontSize );

    sf::Vector2f Position;
    Position.y = SectionPosition.y + SectionSize.y * TableBottom + ( SectionSize.y * ( 1.f - TableBottom ) - ControllersTableManual.getLocalBounds().height ) / 2.f;

    ControllersTableManual.setString( ManualText );

    Position.x = SectionPosition.x + ( SectionSize.x - ControllersTableManual.getLocalBounds().width ) / 2.f;
    Position.x += ControllersTableManual.getLocalBounds().width * CONTROLLERS_MANUAL_FONT_HORIZONTAL_OFFSET_FIX; // Offset fix
    Position.y += ControllersTableManual.getLocalBounds().height * CONTROLLERS_MANUAL_FONT_VERTICAL_OFFSET_FIX; // Offset fix

    ControllersTableManual.setPosition( Position );

    #if ( SFML_VERSION_MINOR >= 4 )

        ControllersTableManual.setOutlineThickness( 1.f );
        ControllersTableManual.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
        ControllersTableManual.setFillColor( sf::Color( 189, 189, 189 ) ); // #BDBDBD

    #else

        ControllersTableManual.setColor( sf::Color( 189, 189, 189 ) ); // #BDBDBD

    #endif

    }

void MainMenu::updateControllersSection ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Up: {

                if ( !ControllersModificationMode ) {

                    ControllersTablePointer.y -= 1;

                    if ( ControllersTablePointer.y == 0 ) {

                        ControllersTablePointer.y = 7; } }

                break; }

            case sf::Keyboard::Down: {

                if ( !ControllersModificationMode ) {

                    ControllersTablePointer.y += 1;

                    if ( ControllersTablePointer.y == 8 ) {

                        ControllersTablePointer.y = 1; } }

                break; }

            case sf::Keyboard::Left: {

                if ( !ControllersModificationMode ) {

                    ControllersTablePointer.x -= 1;

                    if ( ControllersTablePointer.x == 0 ) {

                        ControllersTablePointer.x = MAXIMUM_PLAYER_COUNT; } }

                break; }

            case sf::Keyboard::Right: {

                if ( !ControllersModificationMode ) {

                    ControllersTablePointer.x += 1;

                    if ( ControllersTablePointer.x == ( MAXIMUM_PLAYER_COUNT + 1 ) ) {

                        ControllersTablePointer.x = 1; } }

                break; }

            case sf::Keyboard::W: {

                if ( !ControllersModificationMode ) {

                    ControllersTablePointer.y -= 1;

                    if ( ControllersTablePointer.y == 0 ) {

                        ControllersTablePointer.y = 7; } }

                break; }

            case sf::Keyboard::S: {

                if ( !ControllersModificationMode ) {

                    ControllersTablePointer.y += 1;

                    if ( ControllersTablePointer.y == 8 ) {

                        ControllersTablePointer.y = 1; } }

                break; }

            case sf::Keyboard::A: {

                if ( !ControllersModificationMode ) {

                    ControllersTablePointer.x -= 1;

                    if ( ControllersTablePointer.x == 0 ) {

                        ControllersTablePointer.x = MAXIMUM_PLAYER_COUNT; } }

                break; }

            case sf::Keyboard::D: {

                if ( !ControllersModificationMode ) {

                    ControllersTablePointer.x += 1;

                    if ( ControllersTablePointer.x == ( MAXIMUM_PLAYER_COUNT + 1 ) ) {

                        ControllersTablePointer.x = 1; } }

                break; }

            case sf::Keyboard::Return: {

                if ( !ControllersModificationMode ) {

                    ControllersModificationMode = true;
                    ControllersModificationState = 0;

                    if ( ControllersTablePointer.y == 1 ) {

                        PreviousDevice = Gameplay->getControllerSettings( (unsigned int) ControllersTablePointer.x - 1 )->getDevice();
                        PreviousIdentifier = Gameplay->getControllerSettings( (unsigned int) ControllersTablePointer.x - 1 )->getJoystickIdentifier(); }

                    SettingsChanged = true; }

                break; }

            case sf::Keyboard::Space: {

                if ( !ControllersModificationMode ) {

                    ControllersModificationMode = true;
                    ControllersModificationState = 0;

                    if ( ControllersTablePointer.y == 1 ) {

                        PreviousDevice = Gameplay->getControllerSettings( (unsigned int) ControllersTablePointer.x - 1 )->getDevice();
                        PreviousIdentifier = Gameplay->getControllerSettings( (unsigned int) ControllersTablePointer.x - 1 )->getJoystickIdentifier(); }

                    SettingsChanged = true; }

                break; }

            case sf::Keyboard::BackSpace: {

                if ( !ControllersModificationMode ) {

                    ControllersTablePointer = { 1, 1 };
                    ControllersModificationMode = false;

                    setMode( Modes::SettingsMode ); }

                break; }

            case sf::Keyboard::Escape: {

                if ( ControllersModificationMode && ControllersTablePointer.y == 1 ) {

                    Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setDevice( PreviousDevice );

                    if ( PreviousDevice == PlayerControllerSettings::Devices::Joystick ) {

                        Gameplay->getControllerSettings( (unsigned int) ( ControllersTablePointer.x - 1 ) )->setJoystickIdentifier( PreviousIdentifier ); } }

                ControllersTablePointer = { 1, 1 };
                ControllersModificationMode = false;

                setMode( Modes::SettingsMode );

                break; }

            default: {

                break; } } } }

void MainMenu::renderControllersSection ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 2 );

    Window.draw( &ControllersTable[0], ControllersTable.size(), sf::Quads );

    for ( unsigned int i = 0; i < ControllersTableColumnHeader.size(); i++ ) {

        Window.draw( ControllersTableColumnHeader[i] ); }

    for ( unsigned int i = 0; i < ControllersTableRowHeader.size(); i++ ) {

        Window.draw( ControllersTableRowHeader[i] ); }

    for ( unsigned int i = 0; i < ControllersTableContent.size(); i++ ) {

        Window.draw( ControllersTableContent[i] ); }

    Window.draw( ControllersTableManual ); }

void MainMenu::updateBackground ( sf::Time ElapsedTime ) {

    unsigned int ParticlesCount;

    if ( Graphics->getWindowHeight() < 600.f ) {

        ParticlesCount = 5; }

    else if ( Graphics->getWindowHeight() >= 600.f && Graphics->getWindowHeight() <= 800.f ) {

        ParticlesCount = 10; }

    else if ( Graphics->getWindowHeight() > 800.f && Graphics->getWindowHeight() <= 1000.f ) {

        ParticlesCount = 15; }

    else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

        ParticlesCount = 15; }

    else {

        ParticlesCount = 20; }

    sf::Vector2f Origin ( Graphics->getWindowWidth() / 2.f, Graphics->getWindowHeight() / 2.f );
    float MaximumDistance = 100.f + std::fmaxf( Origin.x + Graphics->getWindowWidth(), Origin.y + Graphics->getWindowHeight() ) / 2.f;

    for ( int i = 0; i < ParticleIndexes.size(); i++ ) {

        sf::Vector2f Position = Background[ ParticleIndexes[i] * 2 + 1 ].position;
        float Distance = sqrtf( powf( Graphics->getWindowWidth() / 2.f - Position.x, 2.f ) + powf( Graphics->getWindowHeight() / 2.f - Position.y, 2.f ) );

        if ( Distance > MaximumDistance ) {

            ParticleIndexes.erase( ParticleIndexes.begin() + i );
            ParticleVelocities.erase( ParticleVelocities.begin() + i );

            i--;
            continue; }

        Background[ ParticleIndexes[i] * 2 + 1 ].position += ParticleVelocities[i] * ElapsedTime.asSeconds(); }

    BackgroundPauseTime -= ElapsedTime;

    if ( BackgroundPauseTime.asSeconds() <= 0.f && ParticleIndexes.size() < ParticlesCount ) {

        BackgroundPauseTime = BackgroundPauseDuration;

        float PositionAngle = ( 3.f * PI / 4.f + getRandomFloat() * ( PI / 2.f ) );
        float PositionModule = MaximumDistance - 10.f;
        float VelocityAngle = PositionAngle + PI + ( ( - PI / 12.f ) + getRandomFloat() * ( PI / 6.f ) );
        float VelocityModule = getRandomFloat();

        sf::Vector2f Position ( Origin.x + PositionModule * cosf( PositionAngle ), Origin.y + PositionModule * sinf( PositionAngle ) );
        sf::Vector2f Velocity ( ( 50.f + VelocityModule * 50.f ) * cosf( VelocityAngle ), ( 50.f + VelocityModule * 50.f ) * sinf( VelocityAngle ) );
        sf::Color Color = RedPalette[ rand() % RedPalette.size() ];

        ParticleIndexes.push_back( (unsigned int) ( Background.size() / 2 ) );
        ParticleVelocities.push_back( Velocity );
        Background.emplace_back( sf::Vertex( Position, Color ) );
        Background.emplace_back( sf::Vertex( Position, Color ) ); } }

void MainMenu::renderBackground ( sf::RenderWindow &Window ) {

    Window.draw( &Background[0], Background.size(), sf::Lines );

    for ( unsigned int i = 0; i < ParticleIndexes.size(); i++ ) {

        sf::CircleShape Circle;

        Circle.setRadius( 5.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() );
        Circle.setPosition( Background[ ParticleIndexes[i] * 2 + 1 ].position );
        Circle.setFillColor( Background[ ParticleIndexes[i] * 2 + 1 ].color );

        Window.draw( Circle ); } }

void MainMenu::renderSectionBackground ( sf::RenderWindow &Window, unsigned int Position ) {

    sf::RectangleShape Box;
    sf::RectangleShape Shade;

    if ( Position == 0 ) {

        Box.setPosition( 0.1f * Graphics->getWindowWidth(), 0.f );
        Box.setSize( sf::Vector2f( 0.35f * Graphics->getWindowWidth(), Graphics->getWindowHeight() ) ); }

    else if ( Position == 1 ) {

        Box.setPosition( 0.55f * Graphics->getWindowWidth(), 0.f );
        Box.setSize( sf::Vector2f( 0.35f * Graphics->getWindowWidth(), Graphics->getWindowHeight() ) ); }

    else if ( Position == 2 ) {

        Box.setPosition( 0.f, 0.125f * Graphics->getWindowHeight() );
        Box.setSize( sf::Vector2f( Graphics->getWindowWidth(), 0.75f * Graphics->getWindowHeight() ) ); }

    else {

        return; }

    Box.setFillColor( sf::Color( 0, 0, 0 ) ); // #000000
    Box.setOutlineThickness( 2.f );
    Box.setOutlineColor( sf::Color ( 13, 71, 161 ) ); // #0D47A1

    Shade.setPosition( 0.f, 0.f );
    Shade.setSize( sf::Vector2f( Graphics->getWindowWidth(), Graphics->getWindowHeight() ) );
    Shade.setFillColor( sf::Color( 0, 0, 0, 155 ) ); // #000000

    if ( Position >= 2 ) {

        Window.draw( Shade ); }

    Window.draw( Box ); }
