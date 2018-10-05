#include "score-board.hpp"

ScoreBoard::ScoreBoard ( GraphicsModule * Graphics, GameplaySettings * Gameplay ) {

    this->Graphics = Graphics;
    this->Gameplay = Gameplay;

    HighScore= false;
    SaveHighScore = false;
    Restart = false;
    Close = false;

    HighScoreFontSize = 100;
    ScoreFontSize = 100;
    MenuOptionCount = 2;
    MenuOption = 0;
    MenuOptionText[0] = "Cool! I wanna play again.";
    MenuOptionText[1] = "Okay, let's get back to menu.";
    MenuOptionFontSize = 100;

    update(); }

void ScoreBoard::update ( ) {

    for ( unsigned int i  = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

        if ( Gameplay->getScores()[i].getScore() > Gameplay->getHighScore() ) {

            Gameplay->setHighScore( Gameplay->getScores()[i].getScore() );

            HighScore = true;
            SaveHighScore = true; } }

    HighScoreText = std::string( HighScore ? "NEW " : "" ) + "HIGH SCORE: " + getFormattedText( Gameplay->getHighScore() );

    unsigned char Bit = 0x01;

    for ( unsigned int i  = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

        ScoreText[i][0] = Gameplay->getPlayerName( i );

        if ( Gameplay->getWinner() & Bit ) {

            ScoreText[i][1] =  " has won with " + getFormattedText( Gameplay->getScores()[i].getScore() ) + " points"; }

        else {

            ScoreText[i][1] = " has lost with " + getFormattedText( Gameplay->getScores()[i].getScore() ) + " points"; }

        Bit *= 2; }

    HighScoreFontSize = 100;
    ScoreFontSize = 100;
    MenuOptionFontSize = 100;

    HighScorePosition = 0.05f * Graphics->getWindowHeight();
    MenuOptionPosition[0] = 0.8f * Graphics->getWindowHeight();
    MenuOptionPosition[1] = 0.87f * Graphics->getWindowHeight();

    auto Margin = (float) ( ( 0.37 - MAXIMUM_PLAYER_COUNT * 0.06f ) / ( MAXIMUM_PLAYER_COUNT - 1 ) );

    for ( unsigned int i = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

        ScorePosition[i][0].y = 0.28f * Graphics->getWindowHeight() + i * ( 0.06f + Margin ) * Graphics->getWindowHeight();
        ScorePosition[i][1].y = 0.28f * Graphics->getWindowHeight() + i * ( 0.06f + Margin ) * Graphics->getWindowHeight(); }

    sf::Text PrototypeText;
    PrototypeText.setString( HighScoreText );
    PrototypeText.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    PrototypeText.setCharacterSize( HighScoreFontSize );

    while ( PrototypeText.getLocalBounds().height > ( 0.08f * Graphics->getWindowHeight() ) ) {

        PrototypeText.setCharacterSize( --HighScoreFontSize ); }

    while ( PrototypeText.getLocalBounds().width > ( 0.9f * Graphics->getWindowWidth() ) ) {

        PrototypeText.setCharacterSize( --HighScoreFontSize ); }

    ScoreFontSize = HighScoreFontSize;

    PrototypeText.setString( Gameplay->getTheLongestPlayerName() + " has lost with " + getFormattedText( Gameplay->getHighScore() ) + " points" );
    PrototypeText.setCharacterSize( ScoreFontSize );

    while ( PrototypeText.getLocalBounds().height > ( 0.06f * Graphics->getWindowHeight() ) ) {

        PrototypeText.setCharacterSize( --ScoreFontSize ); }

    while ( PrototypeText.getLocalBounds().width > ( 0.75f * Graphics->getWindowWidth() ) ) {

        PrototypeText.setCharacterSize( --ScoreFontSize ); }

    MenuOptionFontSize = HighScoreFontSize;

    PrototypeText.setString( MenuOptionText[0] );
    PrototypeText.setCharacterSize( MenuOptionFontSize );

    while ( PrototypeText.getLocalBounds().height > ( 0.05f * Graphics->getWindowHeight() ) ) {

        PrototypeText.setCharacterSize( --MenuOptionFontSize ); }

    while ( PrototypeText.getLocalBounds().width > ( 0.5f * Graphics->getWindowWidth() ) ) {

        PrototypeText.setCharacterSize( --MenuOptionFontSize ); }


    PrototypeText.setCharacterSize( ScoreFontSize );

    for ( unsigned int i = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

        PrototypeText.setString( ScoreText[i][0] + ScoreText[i][1] );
        ScorePosition[i][0].x = ( Graphics->getWindowWidth() - PrototypeText.getLocalBounds().width ) / 2.f;

        PrototypeText.setString( ScoreText[i][0] );
        ScorePosition[i][1].x = ScorePosition[i][0].x + 4.f + PrototypeText.getLocalBounds().width; } }

void ScoreBoard::update ( sf::Event &Event ) {

    if ( Event.type == sf::Event::KeyPressed ) {

        switch ( Event.key.code ) {

            case sf::Keyboard::Up: {

                if ( MenuOption == 1 ) {

                    MenuOption--; }

                break; }

            case sf::Keyboard::Down: {

                if ( MenuOption == 0 ) {

                    MenuOption++; }

                break; }

            case sf::Keyboard::W: {

                if ( MenuOption == 1 ) {

                    MenuOption--; }

                break; }

            case sf::Keyboard::S: {

                if ( MenuOption == 0 ) {

                    MenuOption++; }

                break; }

            case sf::Keyboard::Return: {

                if ( MenuOption == 0 ) {

                    Restart = true; }

                else if ( MenuOption == 1 ) {

                    Close = true; }

                break; }

            case sf::Keyboard::Space: {

                if ( MenuOption == 0 ) {

                    Restart = true; }

                else if ( MenuOption == 1 ) {

                    Close = true; }

                break; }

            default: break; } } }

void ScoreBoard::render ( sf::RenderWindow &Window ) {

    sf::Text Text;
    Text.setString( HighScoreText );
    Text.setFont( Graphics->getFont( "RobotoCondensedLight" ) );
    Text.setCharacterSize( HighScoreFontSize );
    Text.setPosition( ( Graphics->getWindowWidth() - Text.getLocalBounds().width ) / 2.f, HighScorePosition );

    #if ( SFML_VERSION_MINOR >= 4 )

        Text.setOutlineThickness( 1.f );
        Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121

        if ( HighScore ) {

            Text.setFillColor( sf::Color( 239, 83, 80 ) ); } // #EF5350

        else {

            Text.setFillColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

    #else

        Text.setColor( sf::Color( 250, 250, 250 ) );

    #endif

    Window.draw( Text );

    for ( unsigned int i = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

        Text.setString( ScoreText[i][0] );
        Text.setCharacterSize( ScoreFontSize );
        Text.setPosition( ScorePosition[i][0] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
            Text.setFillColor( Gameplay->getPlayerColor( i ) );

        #else

            Text.setColor( Gameplay->getPlayerColor( i ) );

        #endif

        Window.draw( Text );

        Text.setString( ScoreText[i][1] );
        Text.setPosition( ScorePosition[i][1] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121
            Text.setFillColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

        #else

            Text.setColor( sf::Color( 250, 250, 250 ) ); // #FAFAFA

        #endif

        Window.draw( Text ); }

    for ( unsigned int i = 0; i < MenuOptionCount; i++ ) {

        Text.setString( MenuOptionText[i] );
        Text.setCharacterSize( MenuOptionFontSize );
        Text.setPosition( ( Graphics->getWindowWidth() - Text.getLocalBounds().width ) / 2.f, MenuOptionPosition[i] );

        #if ( SFML_VERSION_MINOR >= 4 )

            Text.setOutlineThickness( 1.f );
            Text.setOutlineColor( sf::Color( 33, 33, 33 ) ); // #212121

            if ( MenuOption == i ) {

                Text.setFillColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else {

                Text.setFillColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

        #else

            if ( MenuOption == i ) {

                Text.setColor( sf::Color( 250, 250, 250 ) ); } // #FAFAFA

            else {

                Text.setColor( sf::Color( 189, 189, 189 ) ); } // #BDBDBD

        #endif

            Window.draw( Text ); } }

bool ScoreBoard::onHighScore ( ) {

    if ( SaveHighScore ) {

        SaveHighScore = false;

        return true; }

    return false; }

bool ScoreBoard::onRestart ( ) {

    if ( Restart ) {

        HighScore = false;
        Restart = false;
        Close = false;
        MenuOption = 0;

        return true; }

    return false; }

bool ScoreBoard::onClose ( ) {

    if ( Close ) {

        HighScore = false;
        Restart = false;
        Close = false;
        MenuOption = 0;

        return true; }

    return false; }

std::string ScoreBoard::getFormattedText ( unsigned int Value ) {

    std::string Result = std::to_string( Value );
    size_t Position = Result.size();

    while ( Position > 3 ) {

        Position -= 3;

        Result = Result.substr( 0, Position ) + "," + Result.substr( Position, Result.size() - Position ); }

    return Result; }
