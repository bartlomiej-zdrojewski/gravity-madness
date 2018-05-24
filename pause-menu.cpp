#include "pause-menu.hpp"

PauseMenu::PauseMenu ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    Close = false;
    Reset = false;
    Terminate = false;

    Option = 0;
    OptionCount = 3;

    OptionText[0] = "Let's get back to fun";
    OptionText[1] = "Try once again";
    OptionText[2] = "Give up and leave"; }

void PauseMenu::update ( ) {

    sf::Vector2f SectionMargin = sf::Vector2f ( 20.f, 30.f );
    sf::Vector2f OptionMargin = sf::Vector2f ( 0.f, 15.f );

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
    sf::Vector2f MyOptionPosition = sf::Vector2f ( 0.1f * Graphics->getWindowWidth() + SectionMargin.x + OptionMargin.x, Graphics->getWindowHeight() - SectionMargin.y );
    float OptionHeight = 0.f;

    OptionFontSize = 100;

    for ( unsigned int i = 0; i < OptionCount; i++ ) {

        size_t LineSeparator = 0;
        unsigned int LineCount = 0;

        TextPrototype.setString( OptionText[i] );
        TextPrototype.setFont( Graphics->getFont( "PauseMenu" ) );
        TextPrototype.setCharacterSize( OptionFontSize );

        do {

            LineCount++;
            LineSeparator = OptionText[i].find( '\n', LineSeparator + 1 ); }

        while ( LineSeparator != std::string::npos );

        while ( TextPrototype.getLocalBounds().height > ( LineCount * 0.06f * SectionSize.y ) ) {

            TextPrototype.setCharacterSize( --OptionFontSize ); }

        while ( TextPrototype.getLocalBounds().width > SectionSize.x ) {

            TextPrototype.setCharacterSize( --OptionFontSize ); } }

    for ( unsigned int i = 0; i < OptionCount; i++ ) {

        size_t LineSeparator = 0;
        unsigned int LineCount = 0;

        TextPrototype.setString( OptionText[i] );
        TextPrototype.setCharacterSize( OptionFontSize );

        do {

            LineCount++;
            LineSeparator = OptionText[i].find( '\n', LineSeparator + 1 ); }

        while ( LineSeparator != std::string::npos );

        OptionHeight = std::fmaxf( OptionHeight, TextPrototype.getLocalBounds().height / LineCount ); }

    for ( unsigned int i = 0; i < OptionCount; i++ ) {

        size_t Index = OptionCount - i - 1;
        size_t LineSeparator = 0;
        unsigned int LineCount = 0;

        do {

            LineCount++;
            LineSeparator = OptionText[ Index ].find( '\n', LineSeparator + 1 ); }

        while ( LineSeparator != std::string::npos );

        OptionPosition[ Index ] = sf::Vector2f( MyOptionPosition.x, MyOptionPosition.y - LineCount * OptionHeight );
        MyOptionPosition.y -= LineCount * OptionHeight + OptionMargin.y; }

    }

void PauseMenu::update ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Up: {

                if ( Option > 0 ) {

                    Option--; }

                break; }

            case sf::Keyboard::Down: {

                if ( Option < ( OptionCount - 1 ) ) {

                    Option++; }

                break; }

            case sf::Keyboard::W: {

                if ( Option > 0 ) {

                    Option--; }

                break; }

            case sf::Keyboard::S: {

                if ( Option < ( OptionCount - 1 ) ) {

                    Option++; }

                break; }

            case sf::Keyboard::Space: {

                switch ( Option ) {

                    case 0: {

                        Close = true;

                        break; }

                    case 1: {

                        Reset = true;

                        break; }

                    case 2: {

                        Terminate = true;

                        break; }

                    default: {

                        break; } }

                break; }

            case sf::Keyboard::Return: {

                switch ( Option ) {

                    case 0: {

                        Close = true;

                        break; }

                    case 1: {

                        Reset = true;

                        break; }

                    case 2: {

                        Terminate = true;

                        break; }

                    default: {

                        break; } }

                break; }

            case sf::Keyboard::Escape: {

                Close = true;

                break; }

            default: {

                break; } } } }

void PauseMenu::render ( sf::RenderWindow &Window ) {

    renderBackground( Window );

    sf::Text Text;

    Text.setFont( Graphics->getFont( "PauseMenu" ) );
    Text.setCharacterSize( OptionFontSize );

    for ( unsigned int i = 0; i < OptionCount; i++ ) {

        Text.setString( OptionText[i] );
        Text.setPosition( OptionPosition[i] );
        Text.setOutlineThickness( 1.f );
        Text.setOutlineColor( sf::Color( 0, 0, 0 ) );

        if ( i == Option ) {

            Text.setFillColor( sf::Color( 250, 250, 250 ) ); }

        else if ( ( i + 1 ) == Option || ( i - 1 ) == Option ) {

            Text.setFillColor( sf::Color( 189, 189, 189 ) ); }

        else if ( ( i + 2 ) == Option || ( i - 2 ) == Option ) {

            Text.setFillColor( sf::Color( 117, 117, 117 ) ); }

        else {

            Text.setFillColor( sf::Color( 66, 66, 66 ) ); }

        Window.draw( Text ); }

    // TODO LOGO

    }

bool PauseMenu::onClose ( ) {

    if ( Close ) {

        Close = false;
        Reset = false;
        Terminate = false;
        Option = 0;

        return true; }

    return false; }

bool PauseMenu::onReset ( ) {

    if ( Reset ) {

        Close = false;
        Reset = false;
        Terminate = false;
        Option = 0;

        return true; }

    return false; }

bool PauseMenu::onTerminate ( ) {

    if ( Terminate ) {

        Close = false;
        Reset = false;
        Terminate = false;
        Option = 0;

        return true; }

    return false; }

void PauseMenu::renderBackground ( sf::RenderWindow &Window ) {

    sf::RectangleShape Fade;
    sf::RectangleShape Rectangle;

    Fade.setPosition( 0.f, 0.f );
    Fade.setSize( sf::Vector2f( Graphics->getWindowWidth(), Graphics->getWindowHeight() ) );
    Fade.setFillColor( sf::Color( 0, 0, 0, 150 ) );

    Rectangle.setPosition( 0.1f * Graphics->getWindowWidth(), 0.f );
    Rectangle.setSize( sf::Vector2f( 0.35f * Graphics->getWindowWidth(), Graphics->getWindowHeight() ) );
    Rectangle.setFillColor( sf::Color( 0, 0, 0 ) );
    Rectangle.setOutlineThickness( 2.f );
    Rectangle.setOutlineColor( sf::Color ( 13, 71, 161 ) ); // #0D47A1

    Window.draw( Fade );
    Window.draw( Rectangle ); }
