#include "message.hpp"

Message::Message ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    Close = false;
    Type = Types::None;
    FontSize = 100;

    Texts[0] = "NONE";
    Texts[1] = "During game initialisation one or more warnings have been reported.\n"
               "As a result, some of the game features may not work as expected.\n"
               "However the crucial ones should stay unaffected and work properly.\n"
               "For more details check log file or contact support team.";
    Texts[2] = "During game initialisation one or more errors have been reported.\n"
               "As a result, the game can not be continued and will be closed now.\n"
               "For more details check log file or contact support team.";
    Texts[3] = "During game runtime one or more errors have been reported.\n"
               "As a result, the game can not be continued and will be closed now.\n"
               "For more details check log file or contact support team.";
    Texts[4] = "During game runtime significantly low performance has been detected (below 10 fps).\n"
               "It may cause some algorithms to crash, so game can not be continued and will closed now.\n"
               "Graphics settings have been lowered to minimum to prevent future performance problems.\n"
               "They can be changed in the settings section. For more details contact support team.";
    Texts[5] = "Hey! My name is Bartek and I'm a creator of this game. I've had lots of fun making it\n"
               "and I hope you'll have too, while playing it. But before that, I've got some tips for you:\n"
               "1) If you need it, there is an epilepsy protection that can be enabled in settings section.\n"
               "2) Remember to choose graphic card instead of cpu. Everything look so much cooler with that!\n"
               "3) I strongly recommend you to try the tutorial. The controls are not that obvious.\n"
               "That's all for now. Thanks again and have fun!"; }

void Message::setType ( Types Type ) {

    this->Type = Type;

    update(); }

void Message::update ( ) {

    if ( Type == Types::None ) {

        Close = true;

        return; }

    sf::Text TextPrototype;
    TextPrototype.setFont( Graphics->getFont( "RobotoCondensedLight" ) );

    switch ( Type ) {

        case Types::InitTimeWarning: {

            TextPrototype.setString( Texts[1] );

            break; }

        case Types::InitTimeError: {

            TextPrototype.setString( Texts[2] );

            break; }

        case Types::RunTimeError: {

            TextPrototype.setString( Texts[3] );

            break; }

        case Types::LowPerformanceError: {

            TextPrototype.setString( Texts[4] );

            break; }

        case Types::WelcomeMessage: {

            TextPrototype.setString( Texts[5] );

            break; }

        default: {

            TextPrototype.setString( Texts[0] );

            break; } }

    FontSize = 100;
    FrameSize = sf::Vector2f ( 0.9f * Graphics->getWindowWidth(), Graphics->getWindowHeight() );
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

    sf::Text Text;
    std::string TextString;
    sf::RectangleShape Frame;

    Frame.setSize( FrameSize );
    Frame.setPosition( FramePosition );
    Frame.setOutlineThickness( 2.f );
    Frame.setFillColor( sf::Color( 0, 0, 0 ) );
    Frame.setOutlineColor( sf::Color ( 13, 71, 161 ) ); // #0D47A1

    Window.draw( Frame );

    Text.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    Text.setCharacterSize( FontSize );
    Text.setPosition( FramePosition + FrameMargin + sf::Vector2f( 0.f, VerticalFontFix ) );

    switch ( Type ) {

        case Types::InitTimeWarning: {

            TextString = Texts[1];

            break; }

        case Types::InitTimeError: {

            TextString = Texts[2];

            break; }

        case Types::RunTimeError: {

            TextString = Texts[3];

            break; }

        case Types::LowPerformanceError: {

            TextString = Texts[4];

            break; }

        case Types::WelcomeMessage: {

            TextString = Texts[5];

            break; }

        default: {

            TextString = Texts[0];

            break; } }

    size_t Begin = 0;
    size_t End = 0;
    sf::Vector2f Position;

    do {

        Begin = End + ( End > 0 ? 1 : 0 );
        End = TextString.find( '\n', End + 1 );
        Position = Text.getPosition();

        Text.setString( TextString.substr( Begin, End - Begin ) );
        Position.x += 0.5f *( FrameSize.x - 2.f * FrameMargin.x - Text.getLocalBounds().width );
        Text.setPosition( Position );

        Window.draw( Text );

        Position.x = FramePosition.x + FrameMargin.x;
        Position.y += LineHeight;
        Text.setPosition( Position ); }

    while ( End != std::string::npos ); }

bool Message::onClose ( ) {

    if ( Close ) {

        Close = false;

        return true; }

    return false; }
