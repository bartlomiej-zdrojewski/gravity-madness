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
              "For more details check log file or contact support team.";
    Text[4] = "LOW FPS"; // TODO LOW PERFORMANCE ERROR
    Text[5] = "Hey! My name is Bartek and I'm a creator of this game. I've had loads of fun making it\n"
              "and I hope you'll have too by playing it. But before that, I've got some tips for you:\n"
              "1) If you need it, there is an epilepsy protection that can be enabled in settings section.\n"
              "2) Remember to choose graphic card instead of cpu. Everything look so much cooler with it!\n"
              "3) I strongly recommend you to try the tutorial. The controls are not that obvious.\n"
              "That's all for now. Thanks again and have fun!"; }

void Message::setType ( Types Type ) {

    this->Type = Type; }

void Message::update ( ) {

    if ( Type == Types::None ) {

        Close = true;

        return; }

    sf::Text TextPrototype;
    TextPrototype.setFont( Graphics->getFont( "RobotoCondensedLight" ) );

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

        case Types::LowPerformanceError: {

            TextPrototype.setString( Text[4] );

            break; }

        case Types::WelcomeMessage: {

            TextPrototype.setString( Text[5] );

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
    VerticalFontFix = MESSAGE_FONT_VERTICAL_OFFSET_FIX * LineHeight;
    FrameSize.y = TextPrototype.getLocalBounds().height + 2.f * FrameMargin.y;
    FramePosition.x = 0.5f * ( Graphics->getWindowWidth() - FrameSize.x );
    FramePosition.y = 0.5f * ( Graphics->getWindowHeight() - FrameSize.y ); }

void Message::update ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Space: {

                Close = true;

                break; }

            case sf::Keyboard::Return: {

                Close = true;

                break; }

            case sf::Keyboard::BackSpace: {

                Close = true;

                break; }

            case sf::Keyboard::Escape: {

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

    TextPrototype.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    TextPrototype.setCharacterSize( FontSize );
    TextPrototype.setPosition( FramePosition + FrameMargin + sf::Vector2f( 0.f, VerticalFontFix ) );

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

        case Types::LowPerformanceError: {

            TextPrototype.setString( Text[4] );

            break; }

        case Types::WelcomeMessage: {

            TextPrototype.setString( Text[5] );

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

    while ( End != std::string::npos ); }

bool Message::onClose ( ) {

    if ( Close ) {

        Close = false;

        return true; }

    return false; }
