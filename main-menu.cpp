#include <iostream>
#include "main-menu.hpp"

MainMenu::MainMenu ( GraphicsModule * Graphics, GameplaySettings * Gameplay ) {

    this->Graphics = Graphics;
    this->Gameplay = Gameplay;

    Launch = false;
    Terminate = false;
    VideoChanged = false;
    SettingsChanged = false;
    Mode = MenuMode;

    MenuOption = 0;
    MenuOptionCount = 5;
    MenuOptionText[0] = "Play now";
    MenuOptionText[1] = "Customize everything\nand play as you like";
    MenuOptionText[2] = "Beat the tutorial";
    MenuOptionText[3] = "Settings and stuff";
    MenuOptionText[4] = "Leave to prepare\nfor next challenge"; //

    SettingsOption = 0;
    SettingsOptionCount = 3;
    SettingsOptionText[0] = "Resolution";
    SettingsOptionText[1] = "Fullscreen";
    SettingsOptionText[2] = "Antialiasing";

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

        switch ( Mode ) {

            case MenuMode: {

                updateMenu( ElapsedTime );

                break; }

            case GameplayMode: {

                // updateGameplaySection( ElapsedTime );

                break; }

            case SettingsMode: {

                updateMenu( ElapsedTime );
                updateSettingsSection( ElapsedTime );

                break; }

            default: {

                break; } } } }

void MainMenu::update ( sf::Event &Event ) {

    switch ( Mode ) {

        case Modes::MenuMode: {

            updateMenu( Event );

            break; }

        case Modes::GameplayMode: {

            updateGameplaySection( Event );

            break; }

        case Modes::SettingsMode: {

            updateSettingsSection( Event );

            break; }

        default: {

            break; } } }

void MainMenu::render ( sf::RenderWindow &Window ) {

    renderBackground( Window );

    switch ( Mode ) {

        case Modes::MenuMode: {

            renderMenu( Window );

            break; }

        case Modes::GameplayMode: {

            renderGameplaySection( Window );

            break; }

        case Modes::SettingsMode: {

            renderMenu( Window );
            renderSettingsSection( Window );

            break; }

        default: {

            break; } } }

void MainMenu::reset ( ) {

    MenuOptionPointerVelocity = 50.f;
    MenuOptionPointerPosition.y = -25.f;

    if ( Graphics->getWindowHeight() < 600.f ) {

        MenuOptionPointerVelocity = 30.f; }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

        MenuOptionPointerVelocity = 70.f; }

    else if ( Graphics->getWindowHeight() > 1000 ) {

        MenuOptionPointerVelocity = 80.f; }

    Background.clear();
    ParticleIndexes.clear();
    ParticleVelocities.clear();

    // ...

    }

bool MainMenu::onLaunch ( ) {

    if ( Launch ) {

        Launch = false;
        Terminate = false;

        reset();
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

    if ( VideoChanged ) {

        VideoChanged = false;

        reset();

        return true; }

    return false; }

bool MainMenu::onSettingsChanged ( ) {

    if ( SettingsChanged ) {

        SettingsChanged = false;

        return true; }

    return false; }

float MainMenu::getRandomFloat ( ) {

    return ( static_cast <float> ( rand() ) / static_cast <float> ( RAND_MAX ) ); }

void MainMenu::renderSectionBackground ( sf::RenderWindow &Window, unsigned int Position ) {

    sf::RectangleShape Rectangle;

    if ( Position == 0 ) {

        Rectangle.setPosition( 0.1f * Graphics->getWindowWidth(), 0.f ); }

    else if ( Position == 1 ) {

        Rectangle.setPosition( 0.55f * Graphics->getWindowWidth(), 0.f ); }

    else {

        return; }

    Rectangle.setSize( sf::Vector2f( 0.35f * Graphics->getWindowWidth(), Graphics->getWindowHeight() ) );
    Rectangle.setFillColor( sf::Color( 0, 0, 0 ) );
    Rectangle.setOutlineThickness( 2.f );
    Rectangle.setOutlineColor( sf::Color ( 13, 71, 161 ) ); // #0D47A1

    Window.draw( Rectangle ); }

void MainMenu::updateMenu ( sf::Time ElapsedTime ) {

    sf::Vector2f SectionMargin = sf::Vector2f ( 20.f, 30.f );
    sf::Vector2f OptionMargin = sf::Vector2f ( 10.f, 15.f );

    if ( Graphics->getWindowHeight() < 600.f ) {

        SectionMargin = sf::Vector2f ( 12.f, 20.f );
        OptionMargin = sf::Vector2f ( 6.f, 10.f ); }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

        SectionMargin = sf::Vector2f ( 60.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    else if ( Graphics->getWindowHeight() > 1000 ) {

        SectionMargin = sf::Vector2f ( 100.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    sf::Text TextPrototype;
    sf::Vector2f SectionSize = sf::Vector2f ( 0.35f * Graphics->getWindowWidth() - 2.f * SectionMargin.x, Graphics->getWindowHeight() - 2.f * SectionMargin.y );
    sf::Vector2f OptionPosition = sf::Vector2f ( 0.1f * Graphics->getWindowWidth() + SectionMargin.x + OptionMargin.x, Graphics->getWindowHeight() - SectionMargin.y );
    float OptionHeight = 0.f;

    MenuOptionFontSize = 100;

    for ( unsigned int i = 0; i < MenuOptionCount; i++ ) {

        TextPrototype.setString( MenuOptionText[i] );
        TextPrototype.setFont( Graphics->getFont( "MainMenu" ) );
        TextPrototype.setCharacterSize( MenuOptionFontSize );

        while ( TextPrototype.getLocalBounds().height > ( 0.1f * SectionSize.y ) ) {

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

        float Factor = 10.f;
        float MaximumDistance = std::fabs( MenuOptionPosition[ MenuOption ].y - MenuOptionPositionCenter[ MenuOption ] );

        if ( Graphics->getWindowHeight() < 600.f ) {

            Factor = 8.f; }

        else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

            Factor = 20.f; }

        else if ( Graphics->getWindowHeight() > 1000 ) {

            Factor = 30.f; }

        if ( std::fabs( SignedDistance ) > MaximumDistance ) {

            if ( SignedDistance > 0.f && MenuOptionPointerVelocity < 0.f || SignedDistance < 0.f && MenuOptionPointerVelocity > 0.f ) {

                Factor *= 2.5; } }

        if ( std::fabs( MenuOptionPointerPosition.y ) > ( 1.25 * Graphics->getWindowHeight() ) ) {

            if ( SignedDistance > 0.f && MenuOptionPointerVelocity < 0.f || SignedDistance < 0.f && MenuOptionPointerVelocity > 0.f ) {

                MenuOptionPointerVelocity = 0.f; } }

        MenuOptionPointerVelocity += Factor / SignedDistance; }

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

                // ...

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

                break; } } }

    }

void MainMenu::renderMenu ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 0 );

    sf::Text Text;
    sf::CircleShape Circle;

    Text.setFont( Graphics->getFont( "MainMenu" ) );
    Text.setCharacterSize( MenuOptionFontSize );

    Circle.setRadius( 10.f );
    Circle.setOrigin( Circle.getRadius(), Circle.getRadius() );
    Circle.setPosition( MenuOptionPointerPosition - sf::Vector2f( 1.f, 0.f ) );
    Circle.setFillColor( sf::Color( 33, 150, 243 ) );

    if ( Graphics->getWindowHeight() < 600.f ) {

        Circle.setRadius( 8.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

        Circle.setRadius( 15.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    else if ( Graphics->getWindowHeight() > 1000 ) {

        Circle.setRadius( 20.f );
        Circle.setOrigin( Circle.getRadius(), Circle.getRadius() ); }

    Window.draw( Circle );

    for ( unsigned int i = 0; i < MenuOptionCount; i++ ) {

        Text.setString( MenuOptionText[i] );
        Text.setPosition( MenuOptionPosition[i] );
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

        Window.draw( Text ); }

    // TODO LOGO

    }

void MainMenu::updateGameplaySection ( sf::Event &Event ) {

    // TODO

    }

void MainMenu::renderGameplaySection ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 1 );

    // TODO

    }

void MainMenu::updateSettingsSection ( sf::Time ElapsedTime ) {

    SettingsOptionText[ SettingsOptionCount + 0 ] = std::to_string( Graphics->getWindowWidth() ) + " x " + std::to_string( Graphics->getWindowHeight() );
    SettingsOptionText[ SettingsOptionCount + 1 ] = Graphics->isFullScreenEnabled() ? "true" : "false";

    if ( Graphics->getAntialiasingLevel() == 0 ) {

        SettingsOptionText[ SettingsOptionCount + 2 ] = "none"; }

    else if ( Graphics->getAntialiasingLevel() == 1 ) {

        SettingsOptionText[ SettingsOptionCount + 2 ] = "1st level"; }

    else if ( Graphics->getAntialiasingLevel() == 2 ) {

        SettingsOptionText[ SettingsOptionCount + 2 ] = "2nd level"; }

    else { // 4th or 8th

        SettingsOptionText[ SettingsOptionCount + 2 ] = std::to_string( Graphics->getAntialiasingLevel() ) + "th level"; }

    sf::Vector2f SectionMargin = sf::Vector2f ( 20.f, 30.f );
    sf::Vector2f OptionMargin = sf::Vector2f ( 10.f, 15.f );

    if ( Graphics->getWindowHeight() < 600.f ) {

        SectionMargin = sf::Vector2f ( 12.f, 20.f );
        OptionMargin = sf::Vector2f ( 6.f, 10.f ); }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

        SectionMargin = sf::Vector2f ( 60.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    else if ( Graphics->getWindowHeight() > 1000 ) {

        SectionMargin = sf::Vector2f ( 100.f, 60.f );
        OptionMargin = sf::Vector2f ( 0.f, 30.f ); }

    sf::Text TextPrototype;
    sf::Vector2f SectionSize = sf::Vector2f ( 0.35f * Graphics->getWindowWidth() - 2.f * SectionMargin.x, Graphics->getWindowHeight() - 2.f * SectionMargin.y );
    sf::Vector2f OptionPosition = sf::Vector2f ( 0.55f * Graphics->getWindowWidth() + SectionMargin.x + OptionMargin.x, Graphics->getWindowHeight() - SectionMargin.y );
    float OptionHeight = 0.f;

    SettingsOptionFontSize = MenuOptionFontSize;
    float SmallFontScale = 0.75f;

    for ( unsigned int i = 0; i < ( 2 * SettingsOptionCount ); i++ ) {

        TextPrototype.setString( SettingsOptionText[i] );
        TextPrototype.setFont( Graphics->getFont( "MainMenu" ) );
        TextPrototype.setCharacterSize( i < SettingsOptionCount ? SettingsOptionFontSize : (unsigned int) ( SmallFontScale * SettingsOptionFontSize ) );

        while ( TextPrototype.getLocalBounds().height > ( 0.1f * SectionSize.y ) ) {

            TextPrototype.setCharacterSize( --SettingsOptionFontSize ); }

        while ( TextPrototype.getLocalBounds().width > SectionSize.x ) {

            TextPrototype.setCharacterSize( --SettingsOptionFontSize ); } }

    for ( unsigned int i = 0; i < ( 2 * SettingsOptionCount ); i++ ) {

        TextPrototype.setString( SettingsOptionText[i] );
        TextPrototype.setCharacterSize( i < SettingsOptionCount ? SettingsOptionFontSize : (unsigned int) ( SmallFontScale * SettingsOptionFontSize ) );

        OptionHeight = std::fmaxf( OptionHeight, TextPrototype.getLocalBounds().height ); }

    for ( unsigned int i = 0; i < SettingsOptionCount; i++ ) {

        size_t Index = SettingsOptionCount - i - 1;

        SettingsOptionPosition[ Index ] = sf::Vector2f( OptionPosition.x, OptionPosition.y - ( 1.f + SmallFontScale ) * OptionHeight );
        SettingsOptionPosition[ Index + SettingsOptionCount ] = sf::Vector2f( OptionPosition.x, OptionPosition.y - OptionHeight );

        OptionPosition.y -= ( 1.f + SmallFontScale ) * OptionHeight + 2.f * OptionMargin.y; }

    }

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

            case sf::Keyboard::W: {

                if ( SettingsOption > 0 ) {

                    SettingsOption--; }

                break; }

            case sf::Keyboard::S: {

                if ( SettingsOption < ( SettingsOptionCount - 1 ) ) {

                    SettingsOption++; }

                break; }

            // ...

            case sf::Keyboard::BackSpace: {

                setMode( Modes::MenuMode );

                break; }

            case sf::Keyboard::Escape: {

                setMode( Modes::MenuMode );

                break; }

            default: {

                break; } } }

    }

void MainMenu::renderSettingsSection ( sf::RenderWindow &Window ) {

    renderSectionBackground( Window, 1 );

    sf::Text Text;

    Text.setFont( Graphics->getFont( "MainMenu" ) );
    Text.setCharacterSize( SettingsOptionFontSize );

    for ( unsigned int i = 0; i < SettingsOptionCount; i++ ) {

        Text.setString( SettingsOptionText[i] );
        Text.setPosition( SettingsOptionPosition[i] );
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

        Window.draw( Text ); }

    Text.setCharacterSize( (unsigned int) ( 0.9f * SettingsOptionFontSize ) );

    for ( unsigned int i = SettingsOptionCount; i < ( 2 * SettingsOptionCount ); i++ ) {

        Text.setString( SettingsOptionText[i] );
        Text.setPosition( SettingsOptionPosition[i] );
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

        Window.draw( Text ); }

    // ...

    }

void MainMenu::updateBackground ( sf::Time ElapsedTime ) {

    unsigned int ParticlesCount = 10;

    if ( Graphics->getWindowHeight() < 600.f ) {

        ParticlesCount = 5; }

    else if ( Graphics->getWindowHeight() > 800 && Graphics->getWindowHeight() <= 1000 ) {

        ParticlesCount = 15; }

    else if ( Graphics->getWindowHeight() > 1000 ) {

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
