#include "message.hpp"

Message::Message ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    Close = false;
    Type = Types::None;

    Text[0] = "NONE";
    Text[1] = "During game initialisation one or more warnings have been reported.\n"
              "As a result, some of the game features may not work as expected.\n"
              "However the crucial ones should stay unaffected and fully functional.\n"
              "For more details check log file or contact support team.";
    Text[2] = "During game initialisation one or more errors have been reported.\n"
              "As a result, the game can not be continued and will be closed now.\n"
              "For more details check log file or contact support team.";
    Text[3] = "During game runtime one or more errors have been reported.\n"
              "As a result, the game can not be continued and will be closed now.\n"
              "For more details check log file or contact support team."; }

void Message::setType ( Types Type ) {

    this->Type = Type; }

void Message::update ( ) {

    if ( Type == Types::None ) {

        Close = true;

        return; }

    sf::Text TextPrototype;
    TextPrototype.setFont( Graphics->getFont( "Message" ) );

    switch ( Type ) {

        case Types::InitTimeWarning: {

            TextPrototype.setString( Text[1] );

            break; }

        case Types::InitTimeError: {

            TextPrototype.setString( Text[2] );

            break; }

        case Types::RunTimeError: {

            TextPrototype.setString( Text[3] );

            break; }

        default: {

            TextPrototype.setString( Text[0] );

            break; } }

    FontSize = 100;
    FrameSize = sf::Vector2f ( 0.8f * Graphics->getWindowWidth(), Graphics->getWindowHeight() );
    FrameMargin = sf::Vector2f ( 20.f, 25.f );

    TextPrototype.setCharacterSize( FontSize );

    while ( TextPrototype.getLocalBounds().height > ( 0.5f * FrameSize.y - 2 * FrameMargin.y ) ) {

        TextPrototype.setCharacterSize( --FontSize ); }

    while ( TextPrototype.getLocalBounds().width > ( FrameSize.x - 2 * FrameMargin.x ) ) {

        TextPrototype.setCharacterSize( --FontSize ); }

    size_t LineSeparator = 0;
    unsigned int LineCount = 0;

    do {

        LineCount++;
        LineSeparator = TextPrototype.getString().toAnsiString().find( '\n', LineSeparator + 1 ); }

    while ( LineSeparator != std::string::npos );

    LineHeight = TextPrototype.getLocalBounds().height / LineCount;
    FontFix = - 0.15f * LineHeight;
    FrameSize.y = TextPrototype.getLocalBounds().height + 2.f * FrameMargin.y;
    FramePosition.x = 0.5f * ( Graphics->getWindowWidth() - FrameSize.x );
    FramePosition.y = 0.5f * ( Graphics->getWindowHeight() - FrameSize.y );

    // TODO KEY TIP

    }

void Message::update ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Space: {

                Close = true;

                break; }

            case sf::Keyboard::Return: {

                Close = true;

                break; }

            default: {

                break; } } } }

void Message::render ( sf::RenderWindow &Window ) {

    sf::RectangleShape Frame;
    sf::Text TextPrototype;
    std::string FullText;

    Frame.setSize( FrameSize );
    Frame.setPosition( FramePosition );
    Frame.setOutlineThickness( 2.f );
    Frame.setFillColor( sf::Color( 0, 0, 0 ) );
    Frame.setOutlineColor( sf::Color ( 13, 71, 161 ) ); // #0D47A1

    Window.draw( Frame );

    TextPrototype.setFont( Graphics->getFont( "Message" ) );
    TextPrototype.setCharacterSize( FontSize );
    TextPrototype.setPosition( FramePosition + FrameMargin + sf::Vector2f( 0.f, FontFix ) );

    switch ( Type ) {

        case Types::InitTimeWarning: {

            FullText = Text[1];

            break; }

        case Types::InitTimeError: {

            FullText = Text[2];

            break; }

        case Types::RunTimeError: {

            FullText = Text[3];

            break; }

        default: {

            FullText = Text[0];

            break; } }

    size_t Begin = 0;
    size_t End = 0;
    sf::Vector2f Position;

    do {

        Begin = End + ( End > 0 ? 1 : 0 );
        End = FullText.find( '\n', End + 1 );
        Position = TextPrototype.getPosition();

        TextPrototype.setString( FullText.substr( Begin, End - Begin ) );
        Position.x += 0.5f *( FrameSize.x - 2.f * FrameMargin.x - TextPrototype.getLocalBounds().width );
        TextPrototype.setPosition( Position );

        Window.draw( TextPrototype );

        Position.x = FramePosition.x + FrameMargin.x;
        Position.y += LineHeight;
        TextPrototype.setPosition( Position ); }

    while ( End != std::string::npos );

    // TODO KEY TIP

    }

bool Message::onClose ( ) {

    if ( Close ) {

        Close = false;

        return true; }

    return false; }
