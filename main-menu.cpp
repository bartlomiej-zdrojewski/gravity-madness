#include "main-menu.hpp"

MainMenu::MainMenu ( GraphicsModule * Graphics, GameplaySettings * Gameplay ) {

    this->Graphics = Graphics;
    this->Gameplay = Gameplay;

    Launch = false;
    Terminate = false;
    VideoChanged = false;
    SettingsChanged = false;
    Mode = MenuMode;

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

    SettingsOptionCount = 4;
    SettingsOptionText[0] = "Resolution";
    SettingsOptionText[1] = "Fullscreen";
    SettingsOptionText[2] = "Antialiasing";
    SettingsOptionText[3] = "Check out controllers!";

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

    this->Mode = Mode; }

void MainMenu::update ( ) {

    sf::Time ElapsedTime = Clock.restart();

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

                break; } } } }

void MainMenu::update ( sf::Event &Event ) {

    switch ( getMode() ) {

        case Modes::MenuMode: {

            updateMenu( Event );

            break; }

        case Modes::GameplayMode: {

            updateGameplaySection( Event );

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

    WindowWidth = Graphics->getWindowWidth();
    WindowHeight = Graphics->getWindowHeight();
    FullScreen = Graphics->isFullScreenEnabled();
    AntialiasingLevel = Graphics->getAntialiasingLevel();

    MenuOption = 0;
    GameplayPage = 0;
    GameplayOption = 0;
    SettingsOption = 0;

    MenuOptionPointerPosition.y = -25.f;

    if ( Graphics->getWindowHeight() < 600.f ) {

        MenuOptionPointerVelocity = 30.f; }

    else if ( Graphics->getWindowHeight() >= 600 && Graphics->getWindowHeight() <= 800 ) {

        MenuOptionPointerVelocity = 50.f; }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

        MenuOptionPointerVelocity = 70.f; }

    else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

        MenuOptionPointerVelocity = 70.f; }

    else {

        MenuOptionPointerVelocity = 80.f; }

    Background.clear();
    ParticleIndexes.clear();
    ParticleVelocities.clear(); }

bool MainMenu::onLaunch ( ) {

    if ( Launch ) {

        Launch = false;
        Terminate = false;

        setMode( Modes::MenuMode );

        return true; }

    return false; }

bool MainMenu::onTerminate ( ) {

    if ( Terminate ) {

        Launch = false;
        Terminate = false;

        return true; }

    return false; }

bool MainMenu::onVideoChanged ( ) {

    if ( VideoChanged && getMode() != Modes::SettingsMode && getMode() != Modes::ControllersMode ) {

        Graphics->setWindowSize( WindowWidth, WindowHeight );
        FullScreen ? Graphics->enableFullScreen() : Graphics->disableFullScreen();
        Graphics->setAntialiasingLevel( AntialiasingLevel );
        reset();

        VideoChanged = false;

        return true; }

    return false; }

bool MainMenu::onSettingsChanged ( ) {

    if ( SettingsChanged && getMode() != Modes::SettingsMode && getMode() != Modes::ControllersMode ) {

        SettingsChanged = false;

        return true; }

    return false; }

float MainMenu::getRandomFloat ( ) {

    return ( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ); }

std::string MainMenu::getTimeText ( sf::Time Time ) {

    return std::to_string( (unsigned int) ( Time.asSeconds() / 60.f ) ) + " minutes"; }

void MainMenu::updateMenu ( sf::Time ElapsedTime ) {

    sf::Vector2f SectionMargin;
    sf::Vector2f OptionMargin;

    if ( Graphics->getWindowHeight() < 600.f ) {

        SectionMargin = sf::Vector2f ( 12.f, 20.f );
        OptionMargin = sf::Vector2f ( 6.f, 10.f ); }

    else if ( Graphics->getWindowHeight() >= 600 && Graphics->getWindowHeight() <= 800 ) {

        SectionMargin = sf::Vector2f ( 20.f, 30.f );
        OptionMargin = sf::Vector2f ( 10.f, 15.f ); }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

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
        TextPrototype.setFont( Graphics->getFont( "MainMenu" ) );
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

        else if ( Graphics->getWindowHeight() >= 600 && Graphics->getWindowHeight() <= 800 ) {

            Factor = 600.f; }

        else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

            Factor = 1200.f; }

        else if ( ( (float) Graphics->getWindowWidth() / Graphics->getWindowHeight() ) < 1.5f ) {

            Factor = 1200.f; }

        else {

            Factor = 1800.f; }

        if ( std::fabs( SignedDistance ) > MaximumDistance ) {

            if ( SignedDistance > 0.f && MenuOptionPointerVelocity < 0.f || SignedDistance < 0.f && MenuOptionPointerVelocity > 0.f ) {

                Factor *= 2.5; } }

        if ( std::fabs( MenuOptionPointerPosition.y ) > ( 1.25 * Graphics->getWindowHeight() ) ) {

            if ( SignedDistance > 0.f && MenuOptionPointerVelocity < 0.f || SignedDistance < 0.f && MenuOptionPointerVelocity > 0.f ) {

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

                        Launch = true;

                        break; }

                    case 1: {

                        setMode( Modes::GameplayMode );

                        break; }

                    case 2: {

                        // TODO TUTORIAL

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

                        Launch = true;

                        break; }

                    case 1: {

                        setMode( Modes::GameplayMode );

                        break; }

                    case 2: {

                        // TODO TUTORIAL

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
    Text.setFont( Graphics->getFont( "MainMenu" ) );
    Text.setCharacterSize( MenuOptionFontSize );

    sf::CircleShape Circle;
    Circle.setPosition( MenuOptionPointerPosition - sf::Vector2f( 1.f, 0.f ) );
    Circle.setFillColor( sf::Color( 33, 150, 243 ) );

    if ( Graphics->getWindowHeight() < 600.f ) {

        Circle.setRadius( 8.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    else if ( Graphics->getWindowHeight() >= 600 && Graphics->getWindowHeight() <= 800 ) {

        Circle.setRadius( 10.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

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
            Text.setOutlineColor( sf::Color( 0, 0, 0 ) );

            if ( i == MenuOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i + 1 ) == MenuOption || ( i - 1 ) == MenuOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i + 2 ) == MenuOption || ( i - 2 ) == MenuOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); }

        #else

            if ( i == MenuOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i + 1 ) == MenuOption || ( i - 1 ) == MenuOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i + 2 ) == MenuOption || ( i - 2 ) == MenuOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); }

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

    else if ( Graphics->getWindowHeight() >= 600 && Graphics->getWindowHeight() <= 800 ) {

        SectionMargin = sf::Vector2f ( 20.f, 30.f );
        OptionMargin = sf::Vector2f ( 0.f, 15.f ); }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

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
            TextPrototype.setFont( Graphics->getFont( "MainMenu" ) );
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

                if ( GameplayOption == 4 ) {

                    if ( GameplayPage == 0 ) {

                        GameplayPage++;
                        GameplayOption = 0; }

                    else if ( GameplayPage == 1 ) {

                        // TODO SPACESHIP SECTION

                        } }

                break; }

            case sf::Keyboard::Space: {

                if ( GameplayOption == 4 ) {

                    if ( GameplayPage == 0 ) {

                        GameplayPage++; }

                    else if ( GameplayPage == 1 ) {

                        // TODO SPACESHIP SECTION

                        } }

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

                if ( Gameplay->getPlayerCount() < 4 ) {

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
    Text.setFont( Graphics->getFont( "MainMenu" ) );
    Text.setCharacterSize( GameplayOptionFontSize );

    for ( unsigned int i = 0; i < GameplayOptionCount[ GameplayPage ]; i++ ) {

        Text.setString( GameplayOptionText[ GameplayPage ][i] );
        Text.setPosition( GameplayOptionPosition[ GameplayPage ][i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 0, 0, 0 ) );

            if ( i == GameplayOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i + 1 ) == GameplayOption || ( i - 1 ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i + 2 ) == GameplayOption || ( i - 2 ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); }

        #else

            if ( i == GameplayOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i + 1 ) == GameplayOption || ( i - 1 ) == GameplayOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i + 2 ) == GameplayOption || ( i - 2 ) == GameplayOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); }

        #endif

        Window.draw( Text ); }

    Text.setCharacterSize( (unsigned int) ( 0.85f * GameplayOptionFontSize ) );

    for ( unsigned int i = GameplayOptionCount[ GameplayPage ]; i < ( 2 * GameplayOptionCount[ GameplayPage ] - 1 ); i++ ) {

        Text.setString( GameplayOptionText[ GameplayPage ][i] );
        Text.setPosition( GameplayOptionPosition[ GameplayPage ][i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 0, 0, 0 ) );

            if ( ( i - GameplayOptionCount[ GameplayPage ] ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i - GameplayOptionCount[ GameplayPage ] + 1 ) == GameplayOption || ( i - GameplayOptionCount[ GameplayPage ] - 1 ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i - GameplayOptionCount[ GameplayPage ] + 2 ) == GameplayOption || ( i - GameplayOptionCount[ GameplayPage ] - 2 ) == GameplayOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); }

        #else

            if ( ( i - GameplayOptionCount[ GameplayPage ] ) == GameplayOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i - GameplayOptionCount[ GameplayPage ] + 1 ) == GameplayOption || ( i - GameplayOptionCount[ GameplayPage ] - 1 ) == GameplayOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i - GameplayOptionCount[ GameplayPage ] + 2 ) == GameplayOption || ( i - GameplayOptionCount[ GameplayPage ] - 2 ) == GameplayOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); }

        #endif

        Window.draw( Text ); } }

void MainMenu::updateSettingsSection ( sf::Time ElapsedTime ) {

    SettingsOptionText[ SettingsOptionCount + 0 ] = std::to_string( WindowWidth ) + " x " + std::to_string( WindowHeight );
    SettingsOptionText[ SettingsOptionCount + 1 ] = FullScreen ? "true" : "false";

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

    else if ( Graphics->getWindowHeight() >= 600 && Graphics->getWindowHeight() <= 800 ) {

        SectionMargin = sf::Vector2f ( 20.f, 30.f );
        OptionMargin = sf::Vector2f ( 0.f, 15.f ); }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

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
        TextPrototype.setFont( Graphics->getFont( "MainMenu" ) );
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

                if ( SettingsOption == 3 ) {

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

        default: {

            break; } } }

void MainMenu::renderSettingsSection ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 1 );

    sf::Text Text;
    Text.setFont( Graphics->getFont( "MainMenu" ) );
    Text.setCharacterSize( SettingsOptionFontSize );

    for ( unsigned int i = 0; i < SettingsOptionCount; i++ ) {

        Text.setString( SettingsOptionText[i] );
        Text.setPosition( SettingsOptionPosition[i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 0, 0, 0 ) );

            if ( i == SettingsOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i + 1 ) == SettingsOption || ( i - 1 ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i + 2 ) == SettingsOption || ( i - 2 ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); }

        #else

            if ( i == SettingsOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i + 1 ) == SettingsOption || ( i - 1 ) == SettingsOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i + 2 ) == SettingsOption || ( i - 2 ) == SettingsOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); }

        #endif

        Window.draw( Text ); }

    Text.setCharacterSize( (unsigned int) ( 0.85f * SettingsOptionFontSize ) );

    for ( unsigned int i = SettingsOptionCount; i < ( 2 * SettingsOptionCount - 1 ); i++ ) {

        Text.setString( SettingsOptionText[i] );
        Text.setPosition( SettingsOptionPosition[i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 0, 0, 0 ) );

            if ( ( i - SettingsOptionCount ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i - SettingsOptionCount + 1 ) == SettingsOption || ( i - SettingsOptionCount - 1 ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i - SettingsOptionCount + 2 ) == SettingsOption || ( i - SettingsOptionCount - 2 ) == SettingsOption ) {

                Text.setFillColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setFillColor( sf::Color( 66, 66, 66 ) ); }

        #else

            if ( ( i - SettingsOptionCount ) == SettingsOption ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); }

            else if ( ( i - SettingsOptionCount + 1 ) == SettingsOption || ( i - SettingsOptionCount - 1 ) == SettingsOption ) {

                Text.setColor( sf::Color( 189, 189, 189 ) ); }

            else if ( ( i - SettingsOptionCount + 2 ) == SettingsOption || ( i - SettingsOptionCount - 2 ) == SettingsOption ) {

                Text.setColor( sf::Color( 117, 117, 117 ) ); }

            else {

                Text.setColor( sf::Color( 66, 66, 66 ) ); }

        #endif

        Window.draw( Text ); } }

void MainMenu::updateControllersSection ( sf::Time ElapsedTime ) {

    sf::Vector2f SectionPosition = sf::Vector2f( 0.f, 0.2f * Graphics->getWindowHeight() );
    sf::Vector2f SectionSize = sf::Vector2f( Graphics->getWindowWidth(), 0.6f * Graphics->getWindowHeight() );

    float TableTop = 0.125f;
    float TableBottom = 0.875f;
    float TableLeft = 0.125f;
    float TableRight = 0.875f;
    float TableCellWidth = 0.136f;
    float TableCellHeight = 0.079f;
    float TableThickness = 1.5f;
    sf::Color TableColor = sf::Color( 13, 71, 161 ); // #0D47A1

    ControllersTable.clear();
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft, TableTop ), sf::Color() ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft, TableBottom ), sf::Color() ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft + 1.5f * TableCellWidth, TableTop ), sf::Color() ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft + 1.5f * TableCellWidth, TableBottom ), sf::Color() ) );

    for ( unsigned int i = 2; i <= 5; i++ ) {

        ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft + ( i + 0.5f ) * TableCellWidth, TableTop ), sf::Color() ) );
        ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft + ( i + 0.5f ) * TableCellWidth, TableBottom ), sf::Color() ) ); }

    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft, TableTop ), sf::Color() ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableRight, TableTop ), sf::Color() ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft, TableTop + 1.5f * TableCellHeight ), sf::Color() ) );
    ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableRight, TableTop + 1.5f * TableCellHeight ), sf::Color() ) );

    for ( unsigned int i = 2; i <= 9; i++ ) {

        ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableLeft, TableTop + ( i + 0.5f ) * TableCellHeight ), sf::Color() ) );
        ControllersTable.emplace_back( sf::Vertex( sf::Vector2f( TableRight, TableTop + ( i + 0.5f ) * TableCellHeight ), sf::Color() ) ); }

    size_t LinesCount = ControllersTable.size();

    for ( unsigned int i = 0; i < LinesCount; i += 2 ) {

        ControllersTable[ 2 * i ].position.x *= SectionSize.x;
        ControllersTable[ 2 * i ].position.y *= SectionSize.y;
        ControllersTable[ 2 * i ].position += SectionPosition;
        ControllersTable[ 2 * i ].color = TableColor;

        ControllersTable[ 2 * i + 1 ].position.x *= SectionSize.x;
        ControllersTable[ 2 * i + 1 ].position.y *= SectionSize.y;
        ControllersTable[ 2 * i + 1 ].position += SectionPosition;
        ControllersTable[ 2 * i + 1 ].color = TableColor;

        if ( i <= 10 ) {

            ControllersTable.emplace( ControllersTable.begin() + 2 * i + 2, sf::Vertex( sf::Vector2f( ControllersTable[ 2 * i ].position.x + TableThickness, ControllersTable[ 2 * i ].position.y ), ControllersTable[ 2 * i ].color ) );
            ControllersTable.emplace( ControllersTable.begin() + 2 * i + 2, sf::Vertex( sf::Vector2f( ControllersTable[ 2 * i + 1 ].position.x + TableThickness, ControllersTable[ 2 * i + 1 ].position.y ), ControllersTable[ 2 * i + 1 ].color ) ); }

        else {

            ControllersTable.emplace( ControllersTable.begin() + 2 * i + 2, sf::Vertex( sf::Vector2f( ControllersTable[ 2 * i ].position.x, ControllersTable[ 2 * i ].position.y + TableThickness ), ControllersTable[ 2 * i ].color ) );
            ControllersTable.emplace( ControllersTable.begin() + 2 * i + 2, sf::Vertex( sf::Vector2f( ControllersTable[ 2 * i + 1 ].position.x, ControllersTable[ 2 * i + 1 ].position.y + TableThickness ), ControllersTable[ 2 * i + 1 ].color ) ); } }

    unsigned int TableHeaderFontSize = 100;
    unsigned int TableContentFontSize = 100;
    sf::Color TableTextColor = sf::Color( 255, 255, 255 );
    sf::Color ConnectedJoystickColor = sf::Color( 0, 255, 0 );
    sf::Color DisconnectedJoystickColor = sf::Color( 255, 0, 0 );

    for ( unsigned int i = 0; i < ControllersTableHeader.size(); i++ ) {

        ControllersTableHeader[i].setFont( Graphics->getFont( "TableHeader" ) ); }

    for ( unsigned int i = 0; i < ControllersTableContent.size(); i++ ) {

        ControllersTableContent[i].setFont( Graphics->getFont( "TableContent" ) ); }

    // TODO HEADERS TEXTS

    for ( unsigned int i = 0; i < Gameplay->getMaximumPlayerCount(); i++ ) {

        auto Controller = Gameplay->getPlayerControllerSettings( i );

        if ( Controller->getDevice() == PlayerControllerSettings::Devices::Joystick ) {

            ControllersTableContent.emplace_back( sf::Text() );
            ControllersTableContent[ i * Gameplay->getMaximumPlayerCount() ].setString( "Joystick " + std::to_string( Controller->getJoystickIdentifier() ) ); }

        else {

            ControllersTableContent.emplace_back( sf::Text() );
            ControllersTableContent[ i * Gameplay->getMaximumPlayerCount() ].setString( "Keyboard" ); }

        ControllersTableContent.emplace_back( sf::Text() );
        ControllersTableContent[ i * Gameplay->getMaximumPlayerCount() + 1 ].setString( PlayerControllerSettings::encodeKey( Controller->getForwardKey() ) );

        ControllersTableContent.emplace_back( sf::Text() );
        ControllersTableContent[ i * Gameplay->getMaximumPlayerCount() + 2 ].setString( PlayerControllerSettings::encodeKey( Controller->getBackwardKey() ) );

        ControllersTableContent.emplace_back( sf::Text() );
        ControllersTableContent[ i * Gameplay->getMaximumPlayerCount() + 3 ].setString( PlayerControllerSettings::encodeKey( Controller->getLeftKey() ) );

        ControllersTableContent.emplace_back( sf::Text() );
        ControllersTableContent[ i * Gameplay->getMaximumPlayerCount() + 4 ].setString( PlayerControllerSettings::encodeKey( Controller->getRightKey() ) );

        ControllersTableContent.emplace_back( sf::Text() );
        ControllersTableContent[ i * Gameplay->getMaximumPlayerCount() + 5 ].setString( PlayerControllerSettings::encodeKey( Controller->getRayShotKey() ) );

        ControllersTableContent.emplace_back( sf::Text() );
        ControllersTableContent[ i * Gameplay->getMaximumPlayerCount() + 6 ].setString( PlayerControllerSettings::encodeKey( Controller->getMissileShotKey() ) ); }

    // TODO TableHeaderFontSize;
    // TODO TableContentFontSize

    // TODO TEXTS POSITIONS

    #if ( SFML_VERSION_MINOR >= 4 )

        for ( unsigned int i = 0; i < ControllersTableHeader.size(); i++ ) {

            ControllersTableHeader[i].setCharacterSize( TableHeaderFontSize );
            ControllersTableHeader[i].setFillColor( TableTextColor ); }

        for ( unsigned int i = 0; i < ControllersTableContent.size(); i++ ) {

            ControllersTableContent[i].setCharacterSize( TableContentFontSize );
            ControllersTableContent[i].setFillColor( TableTextColor ); }

        for ( unsigned int i = 0; i < 4; i++ ) {

            if ( Gameplay->getPlayerControllerSettings( i )->getDevice() == PlayerControllerSettings::Devices::Joystick ) {

                if ( sf::Joystick::isConnected( (unsigned int) Gameplay->getPlayerControllerSettings( i )->getJoystickIdentifier() ) ) {

                    ControllersTableContent[i].setFillColor( ConnectedJoystickColor ); }

                else {

                    ControllersTableContent[i].setFillColor( DisconnectedJoystickColor ); } } }

    #else

        for ( unsigned int i = 0; i < ControllersTableHeader.size(); i++ ) {

            ControllersTableHeader[i].setCharacterSize( TableHeaderFontSize );
            ControllersTableHeader[i].setColor( TableTextColor ); }

        for ( unsigned int i = 0; i < ControllersTableContent.size(); i++ ) {

            ControllersTableContent[i].setCharacterSize( TableContentFontSize );
            ControllersTableContent[i].setColor( TableTextColor ); }

        for ( unsigned int i = 0; i < 4; i++ ) {

            if ( Gameplay->getPlayerControllerSettings( i )->getDevice() == PlayerControllerSettings::Devices::Joystick ) {

                if ( sf::Joystick::isConnected( (unsigned int) Gameplay->getPlayerControllerSettings( i )->getJoystickIdentifier() ) ) {

                    ControllersTableContent[i].setColor( ConnectedJoystickColor ); }

                else {

                    ControllersTableContent[i].setColor( DisconnectedJoystickColor ); } } }

    #endif

    }

void MainMenu::updateControllersSection ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Up: {

                // ...

                break; }

            case sf::Keyboard::Down: {

                // ...

                break; }

            case sf::Keyboard::Left: {

                // ...

                break; }

            case sf::Keyboard::Right: {

                // ...

                break; }

            case sf::Keyboard::W: {

                // ...

                break; }

            case sf::Keyboard::S: {

                // ...

                break; }

            case sf::Keyboard::A: {

                // ...

                break; }

            case sf::Keyboard::D: {

                // ...

                break; }

            case sf::Keyboard::Return: {

                // ...

                break; }

            case sf::Keyboard::Space: {

                // ...

                break; }

            case sf::Keyboard::BackSpace: {

                //SettingsOption = 0;

                setMode( Modes::SettingsMode );

                break; }

            case sf::Keyboard::Escape: {

                //SettingsOption = 0;

                setMode( Modes::SettingsMode );

                break; }

            default: {

                break; } } } }

void MainMenu::renderControllersSection ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 2 );

    Window.draw( &ControllersTable[0], ControllersTable.size(), sf::Quads );

    for ( unsigned int i = 0; i < ControllersTableHeader.size(); i++ ) {

        Window.draw( ControllersTableHeader[i] ); }

    for ( unsigned int i = 0; i < ControllersTableContent.size(); i++ ) {

        Window.draw( ControllersTableContent[i] ); } }

void MainMenu::updateBackground ( sf::Time ElapsedTime ) {

    unsigned int ParticlesCount;

    if ( Graphics->getWindowHeight() < 600.f ) {

        ParticlesCount = 5; }

    else if ( Graphics->getWindowHeight() >= 600 && Graphics->getWindowHeight() <= 800 ) {

        ParticlesCount = 10; }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

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

        Box.setPosition( 0.f, 0.2f * Graphics->getWindowHeight() );
        Box.setSize( sf::Vector2f( Graphics->getWindowWidth(), 0.6f * Graphics->getWindowHeight() ) ); }

    else {

        return; }

    Box.setFillColor( sf::Color( 0, 0, 0 ) );
    Box.setOutlineThickness( 2.f );
    Box.setOutlineColor( sf::Color ( 13, 71, 161 ) ); // #0D47A1

    Shade.setPosition( 0.f, 0.f );
    Shade.setSize( sf::Vector2f( Graphics->getWindowWidth(), Graphics->getWindowHeight() ) );
    Shade.setFillColor( sf::Color( 0, 0, 0, 155 ) );

    if ( Position >= 2 ) {

        Window.draw( Shade ); }

    Window.draw( Box ); }
