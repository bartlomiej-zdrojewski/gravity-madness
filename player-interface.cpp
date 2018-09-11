#include <iostream>
#include "player-interface.hpp"

PlayerInterface::PlayerInterface ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    MySpaceship = nullptr;
    MyScore = nullptr;
    Viewport = sf::FloatRect( 0.f, 0.f, Graphics->getWindowWidth(), Graphics->getWindowHeight() );

    Health = 0;
    HealthLimit = 100;
    Energy = 0;
    EnergyLimit = 100;

    MissileCount = 0;
    MissileLimit = 3;
    MissileTexture = Graphics->getTexture( "MissileIcon" );

    ScoreValue = 0;
    ScoreValueFloating = 0.f;
    ScoreValueSpeed = 5000.f;
    ScoreFontSize = 100;
    ScoreHorizontalOffset = 0.f;
    ScoreMultiplierTextWidth = 0.f;

    ScoreMultiplierValue = 1.f;
    ScoreMultiplierValueSpeed = 1.f;
    ScoreMultiplierFontSize = 100;
    ScoreMultiplierHorizontalOffset = 0.f;

    Arrow = false;
    ArrowAngle = 0.f;
    ArrowTexture = Graphics->getTexture( "Arrow" );

    NotificationOpacity = 0.f;
    NotificationFontSize = 100;
    NotificationDuration = sf::seconds( 3.5f );
    NotificationFadeInDuration = sf::seconds( 0.5f );
    NotificationFadeOutDuration = sf::seconds( 1.f );

    ActivatedOpacity = 0.87f;
    UnactivatedOpacity = 0.34f;
    TransitionDuration = sf::seconds( 0.3f );

    FadeIn = true;
    FadeInDuration = sf::seconds( 2.f );
    FadeInTime = FadeInDuration;

    FadeOut = false;
    FadeOutTime = sf::seconds( 0.f );
    FadeOutDelay = sf::seconds( 3.f );
    FadeOutDuration = sf::seconds( 8.f );

    DamageFade = false;
    DamageFadeTime = sf::seconds( 0.f );
    DamageFadeDuration = sf::seconds( 0.5f ); }

void PlayerInterface::setSpaceship ( Spaceship * MySpaceship ) {

    this->MySpaceship = MySpaceship; }

void PlayerInterface::setScoreCounter ( ScoreCounter * MyScore ) {

    this->MyScore = MyScore;

    if ( MyScore ) {

        ScoreValue = MyScore->getScore();
        ScoreValueFloating = ScoreValue;
        ScoreMultiplierValue = MyScore->getMultiplier(); } }

void PlayerInterface::setViewport ( sf::FloatRect Viewport ) {

    Viewport.left = Graphics->getWindowWidth() * Viewport.left;
    Viewport.top = Graphics->getWindowHeight() * Viewport.top;
    Viewport.width = Graphics->getWindowWidth() * Viewport.width;
    Viewport.height = Graphics->getWindowHeight() * Viewport.height;

    this->Viewport = Viewport; }

void PlayerInterface::enableArrow ( ) {

    Arrow = true; }

void PlayerInterface::disableArrow ( ) {

    Arrow = false; }

void PlayerInterface::displayNotification ( std::string Notification ) {

    NextNotification = Notification; }

void PlayerInterface::beginFadeOut ( ) {

    FadeOut = true; }

void PlayerInterface::endFadeOut ( ) {

    FadeOut = true;
    float FadeAlpha = 0.f;

    if ( FadeOutTime > FadeOutDelay ) {

        FadeAlpha = ( FadeOutTime.asSeconds() - FadeOutDelay.asSeconds() ) / ( FadeOutDuration.asSeconds() - FadeOutDelay.asSeconds() ); }

    FadeOutDuration = FadeOutDelay + sf::seconds( 1.f );
    FadeOutTime = FadeOutDelay + sf::seconds( FadeAlpha ); }

bool PlayerInterface::isFadedOut ( ) {

    return ( FadeOutTime >= ( FadeOutDuration + sf::seconds( 1.f ) ) ); }

void PlayerInterface::update ( sf::Time ElapsedTime ) {

    if ( MySpaceship ) {

        Health = MySpaceship->getHealth();
        HealthLimit = MySpaceship->getHealthLimit();

        Energy = MySpaceship->getEnergy();
        EnergyLimit = MySpaceship->getEnergyLimit();

        MissileCount = MySpaceship->getMissileCount();
        MissileLimit = MySpaceship->getMissileLimit(); }

    if ( DamageFade ) {

        DamageFadeTime -= ElapsedTime;

        if ( DamageFadeTime.asSeconds() <= 0.f ) {

            DamageFade = false; } }

    if ( FadeIn ) {

        FadeInTime -= ElapsedTime;

        if ( FadeInTime.asSeconds() <= 0.f ) {

            FadeIn = false; } }

    else if ( FadeOut ) {

        FadeOutTime += ElapsedTime; }

    updateHealthBar( ElapsedTime );
    updateEnergyBar( ElapsedTime );
    updateMissileTab( ElapsedTime );
    updateScoreTab( ElapsedTime );
    updateArrow( ElapsedTime );
    updateNotification( ElapsedTime ); }

void PlayerInterface::render ( sf::RenderWindow &Window ) {

    renderHealthBar( Window );
    renderEnergyBar( Window );
    renderMissileTab( Window );
    renderScoreTab( Window );
    renderArrow( Window );
    renderNotification( Window );
    renderFade( Window ); }

void PlayerInterface::onDamage ( ) {

    DamageFade = true;
    DamageFadeTime = DamageFadeDuration; }

std::string PlayerInterface::getScoreText ( ) {

    std::string Data = std::to_string( ScoreValue );

    Data = "00000000000" + Data;
    Data = Data.substr( Data.size() - 12, 12 );

    return Data; }

std::string PlayerInterface::getScoreMultiplierText ( ) {

    char Buffer [256];
    std::sprintf( Buffer, "%.2f", ScoreMultiplierValue );

    return "multiplier " + std::string( Buffer ); }

void PlayerInterface::updateHealthBar ( sf::Time ElapsedTime ) {

    float ElementSize = 10.f;
    float ElementMargin = 5.f;

    if ( Viewport.height < 600.f ) {

        ElementSize = 8.f;
        ElementMargin = 4.f; }

    else if ( Viewport.height > 800 ) {

        ElementSize = 15.f;
        ElementMargin = 6.f; }

    updateBar( ElapsedTime, HealthBarOpacity, 15.f, ElementSize, ElementMargin, Health, HealthLimit ); }

void PlayerInterface::updateEnergyBar ( sf::Time ElapsedTime ) {

    float ElementSize = 10.f;
    float ElementMargin = 5.f;

    if ( Viewport.height < 600.f ) {

        ElementSize = 8.f;
        ElementMargin = 4.f; }

    else if ( Viewport.height > 800.f ) {

        ElementSize = 15.f;
        ElementMargin = 6.f; }

    updateBar( ElapsedTime, EnergyBarOpacity, 15.f, ElementSize, ElementMargin, Energy, EnergyLimit ); }

void PlayerInterface::updateMissileTab ( sf::Time ElapsedTime ) {

    if ( MissileTabOpacity.size() != MissileLimit ) {

        MissileTabOpacity.resize( MissileLimit );

        for ( unsigned int i = 0; i < MissileLimit; i++ ) {

            MissileTabOpacity[i] = UnactivatedOpacity; } }

    for ( unsigned int i = 0; i < MissileCount; i++ ) {

        if ( MissileTabOpacity[i] < ActivatedOpacity ) {

            MissileTabOpacity[i] += ( ActivatedOpacity - UnactivatedOpacity ) * ( ElapsedTime.asSeconds() / TransitionDuration.asSeconds() ); }

        else {

            MissileTabOpacity[i] = ActivatedOpacity; } }

    for ( unsigned int i = MissileCount; i < MissileLimit; i++ ) {

        if ( MissileTabOpacity[i] > UnactivatedOpacity ) {

            MissileTabOpacity[i] -= ( ActivatedOpacity - UnactivatedOpacity ) * ( ElapsedTime.asSeconds() / TransitionDuration.asSeconds() ); }

        else {

            MissileTabOpacity[i] = UnactivatedOpacity; } } }

void PlayerInterface::updateScoreTab ( sf::Time ElapsedTime ) {

    float ElementSize = 35.f;

    if ( Viewport.height < 600.f ) {

        ElementSize = 25.f; }

    else if ( Viewport.height > 800.f ) {

        ElementSize = 50.f; }

    if ( MyScore ) {

        if ( ScoreValue < MyScore->getScore() ) {

            float SpeedMultiplier = 1.f;

            while ( ( MyScore->getScore() - ScoreValue ) > ( 3.f * SpeedMultiplier * ScoreValueSpeed ) ) {

                SpeedMultiplier *= 2.f; }

            ScoreValueFloating += SpeedMultiplier * ScoreValueSpeed * ElapsedTime.asSeconds(); }

        if ( ScoreValueFloating > MyScore->getScore() ) {

            ScoreValueFloating = MyScore->getScore(); }

        if ( ScoreMultiplierValue < MyScore->getMultiplier() ) {

            ScoreMultiplierValue += ScoreMultiplierValueSpeed * ElapsedTime.asSeconds();

            if ( ScoreMultiplierValue > MyScore->getMultiplier() ) {

                ScoreMultiplierValue = MyScore->getMultiplier(); } }

        if ( ScoreMultiplierValue > MyScore->getMultiplier() ) {

            ScoreMultiplierValue -= ScoreMultiplierValueSpeed * ElapsedTime.asSeconds();

            if ( ScoreMultiplierValue < MyScore->getMultiplier() ) {

                ScoreMultiplierValue = MyScore->getMultiplier(); } }

        ScoreValue = (unsigned int) ScoreValueFloating; }

    ScoreFontSize = 100;
    ScoreMultiplierFontSize = 100;

    sf::Text TextPrototype;
    TextPrototype.setString( "000123456789" );
    TextPrototype.setFont( Graphics->getFont( "Score" ) );
    TextPrototype.setCharacterSize( ScoreFontSize );

    while ( TextPrototype.getLocalBounds().height > ElementSize ) {

        TextPrototype.setCharacterSize( --ScoreFontSize ); }

    if ( fabsf( ScoreMultiplierTextWidth - ( 0.75f * TextPrototype.getLocalBounds().width ) ) > 10.f ) { // Shaking text fix

        ScoreMultiplierTextWidth = 0.75f * TextPrototype.getLocalBounds().width; }

    TextPrototype.setString( "multiplier 0.00" );
    TextPrototype.setFont( Graphics->getFont( "ScoreMultiplier" ) );
    TextPrototype.setCharacterSize( ScoreMultiplierFontSize );

    while ( TextPrototype.getLocalBounds().width > ScoreMultiplierTextWidth ) {

        TextPrototype.setCharacterSize( --ScoreMultiplierFontSize ); } }

void PlayerInterface::updateArrow ( sf::Time ElapsedTime ) {

    if ( MySpaceship ) {

        ArrowAngle = atan2f( - MySpaceship->getPosition().y, - MySpaceship->getPosition().x ); } }

void PlayerInterface::updateNotification ( sf::Time ElapsedTime ) {

    if ( Notification.empty() ) {

        Notification = NextNotification;
        NextNotification.clear();

        NotificationTime = sf::seconds( 0.f ); }

    if ( !Notification.empty() ) {

        NotificationTime += ElapsedTime;

        if ( NotificationTime < NotificationFadeInDuration ) {

            NotificationOpacity = NotificationTime / NotificationFadeInDuration; }

        else if ( NotificationTime < ( NotificationFadeInDuration + NotificationDuration ) ) {

            NotificationOpacity = 1.f; }

        else if ( NotificationTime < ( NotificationFadeInDuration + NotificationDuration + NotificationFadeOutDuration ) ) {

            NotificationOpacity = 1.f - ( ( NotificationTime - NotificationFadeInDuration - NotificationDuration ) / NotificationFadeOutDuration ); }

        else {

            Notification.clear();

            NotificationOpacity = 0.f; } }

    float ElementSize = 35.f;

    if ( Viewport.height < 600.f ) {

        ElementSize = 25.f; }

    else if ( Viewport.height > 800.f ) {

        ElementSize = 50.f; }

    NotificationFontSize = 100;

    sf::Text TextPrototype;
    TextPrototype.setString( "The quick brown fox jumps over the lazy dog." );
    TextPrototype.setFont( Graphics->getFont( "Notification" ) );
    TextPrototype.setCharacterSize( NotificationFontSize );

    while ( TextPrototype.getLocalBounds().height > ElementSize ) {

        TextPrototype.setCharacterSize( --NotificationFontSize ); }

    TextPrototype.setString( Notification );

    while ( TextPrototype.getLocalBounds().width > ( 0.75f * Viewport.width ) ) {

        TextPrototype.setCharacterSize( --NotificationFontSize ); } }

void PlayerInterface::renderHealthBar ( sf::RenderWindow &Window ) {

    sf::Vector2f ElementSize ( 30.f, 10.f );
    sf::Vector2f ElementMargin ( 20.f, 5.f );

    if ( Viewport.height < 600.f ) {

        ElementSize = sf::Vector2f ( 20.f, 8.f );
        ElementMargin = sf::Vector2f ( 20.f, 4.f ); }

    else if ( Viewport.height > 800.f ) {

        ElementSize = sf::Vector2f ( 40.f, 15.f );
        ElementMargin = sf::Vector2f ( 20.f, 6.f ); }

    renderBar( Window, HealthBarOpacity, sf::Color( 255, 23, 68 ), sf::Vector2f( 15.f, 15.f ), ElementSize, ElementMargin ); }

void PlayerInterface::renderEnergyBar ( sf::RenderWindow &Window ) {

    sf::Vector2f ElementSize ( 30.f, 10.f );
    sf::Vector2f ElementMargin ( 20.f, 5.f );

    if ( Viewport.height < 600.f ) {

        ElementSize = sf::Vector2f ( 20.f, 8.f );
        ElementMargin = sf::Vector2f ( 20.f, 4.f ); }

    else if ( Viewport.height > 800 ) {

        ElementSize = sf::Vector2f ( 40.f, 15.f );
        ElementMargin = sf::Vector2f ( 20.f, 6.f ); }

    renderBar( Window, EnergyBarOpacity, sf::Color( 61, 90, 254 ), sf::Vector2f( ElementSize.x + ElementMargin.y + 15.f, 15.f ), ElementSize, ElementMargin ); }

void PlayerInterface::renderMissileTab ( sf::RenderWindow &Window ) {

    float ElementSize = 40.f;
    float ElementMargin = 5.f;

    if ( Viewport.height < 600.f ) {

        ElementSize = 30.f;
        ElementMargin = 3.f; }

    else if ( Viewport.height > 800.f ) {

        ElementSize = 60.f;
        ElementMargin = 7.f; }

    sf::Sprite MissileSprite ( MissileTexture );

    MissileSprite.setScale( ElementSize / MissileTexture.getSize().x, ElementSize / MissileTexture.getSize().y );
    MissileSprite.setPosition( sf::Vector2f( Viewport.left + Viewport.width - 15.f, Viewport.top + Viewport.height - 15.f - ElementSize ) );

    for ( unsigned int i = 0; i < MissileTabOpacity.size(); i++ ) {

        MissileSprite.move( sf::Vector2f( - ElementSize, 0.f ) );

        MissileSprite.setColor( sf::Color( 255, 255, 255, (sf::Uint8) ( MissileTabOpacity[i] * 255 ) ) );
        Window.draw( MissileSprite );

        MissileSprite.move( sf::Vector2f( - ElementMargin, 0.f ) ); } }

void PlayerInterface::renderScoreTab ( sf::RenderWindow &Window ) {

    sf::Text ScoreText;
    ScoreText.setString( getScoreText() );
    ScoreText.setFont( Graphics->getFont( "Score" ) );
    ScoreText.setCharacterSize( ScoreFontSize );

    sf::Text ScoreMultiplierText;
    ScoreMultiplierText.setString( getScoreMultiplierText() );
    ScoreMultiplierText.setFont( Graphics->getFont( "ScoreMultiplier" ) );
    ScoreMultiplierText.setCharacterSize( ScoreMultiplierFontSize );

    #if ( SFML_VERSION_MINOR > 4 )

        ScoreText.setLetterSpacing( 0.35f );
        ScoreMultiplierText.setLetterSpacing( 0.35f );

    #endif

    ScoreText.setPosition( sf::Vector2f( Viewport.width - ScoreText.getLocalBounds().width - 15.f, 15.f ) );
    ScoreMultiplierText.setPosition( sf::Vector2f( Viewport.width - ScoreMultiplierText.getLocalBounds().width - 15.f, ScoreText.getPosition().y + ScoreText.getLocalBounds().height + 15.f ) );
    ScoreText.move( - ( ScoreText.getLocalBounds().width * 0.025f ), - ScoreText.getLocalBounds().height * 0.45f ); // Offset fix
    ScoreMultiplierText.move( - ( ScoreMultiplierText.getLocalBounds().width * 0.025f ), - ScoreMultiplierText.getLocalBounds().height * 0.45f ); // Offset fix

    if ( fabsf( ScoreHorizontalOffset - ScoreText.getPosition().x ) > 5.f ) { // Shaking text fix

        ScoreHorizontalOffset = ScoreText.getPosition().x; }

    else {

        ScoreText.setPosition( ScoreHorizontalOffset, ScoreText.getPosition().y ); }

    if ( fabsf( ScoreMultiplierHorizontalOffset - ScoreMultiplierText.getPosition().x ) > 5.f ) { // Shaking text fix

        ScoreMultiplierHorizontalOffset = ScoreMultiplierText.getPosition().x; }

    else {

        ScoreMultiplierText.setPosition( ScoreMultiplierHorizontalOffset, ScoreMultiplierText.getPosition().y ); }

    #if ( SFML_VERSION_MINOR >= 4 )

        ScoreText.setOutlineThickness( 1.f );
        ScoreText.setOutlineColor( sf::Color( 33, 33, 33 ) );
        ScoreText.setFillColor( sf::Color( 250, 250, 250 ) );

        ScoreMultiplierText.setOutlineThickness( 1.f );
        ScoreMultiplierText.setOutlineColor( sf::Color( 33, 33, 33 ) );
        ScoreMultiplierText.setFillColor( sf::Color( 238, 238, 238 ) );

    #else

        ScoreText.setColor( sf::Color( 250, 250, 250 ) );
        ScoreMultiplierText.setColor( sf::Color( 238, 238, 238 ) );

    #endif

    Window.draw( ScoreText );
    Window.draw( ScoreMultiplierText ); }

void PlayerInterface::renderArrow ( sf::RenderWindow &Window ) {

    if ( Arrow ) {

        float ArrowSize = Viewport.height * 0.1f;
        float ArrowModule = Viewport.height * 0.25f;

        sf::Sprite Sprite ( ArrowTexture );
        Sprite.setOrigin( ArrowTexture.getSize().x / 2.f, ArrowTexture.getSize().y / 2.f );
        Sprite.setScale( ArrowSize / ArrowTexture.getSize().x, ArrowSize / ArrowTexture.getSize().y );
        Sprite.setPosition( ( Viewport.width * 0.5f ) + ArrowModule * cosf( ArrowAngle ), ( Viewport.height * 0.5f ) + ArrowModule * sinf( ArrowAngle ) );
        Sprite.setRotation( RAD_TO_DEG * ArrowAngle + 90.f );

        Window.draw( Sprite ); } }

void PlayerInterface::renderNotification ( sf::RenderWindow &Window ) {

    sf::Text Text;

    Text.setString( Notification );
    Text.setFont( Graphics->getFont( "Notification" ) );
    Text.setCharacterSize( NotificationFontSize );
    Text.setPosition( ( Viewport.width - Text.getLocalBounds().width ) / 2.f, 0.25f * Viewport.height );
    Text.setFillColor( sf::Color( 255, 255, 255, (sf::Uint8) ( 255 * NotificationOpacity ) ) );

    Window.draw( Text ); }

void PlayerInterface::renderFade ( sf::RenderWindow &Window ) {

    sf::RectangleShape Fade;

    Fade.setPosition( Viewport.left, Viewport.top );
    Fade.setSize( sf::Vector2f( Viewport.width, Viewport.height ) );

    if ( DamageFade ) {

        Fade.setFillColor( sf::Color( 255, 0, 0, (sf::Uint8) ( 200.f * DamageFadeTime.asSeconds() / DamageFadeDuration.asSeconds() ) ) );

        if ( !Graphics->isEpilepsyProtectionEnabled() ) {

            Window.draw( Fade ); } }

    if ( FadeIn ) {

        Fade.setFillColor( sf::Color( 0, 0, 0, (sf::Uint8) ( 255.f * FadeInTime.asSeconds() / FadeInDuration.asSeconds() ) ) ); }

    else if ( FadeOut ) {

        if ( FadeOutTime.asSeconds() < FadeOutDelay.asSeconds() ) {

            return; }

        if ( FadeOutTime < FadeOutDuration ) {

            Fade.setFillColor( sf::Color( 0, 0, 0, (sf::Uint8) ( 255.f * ( FadeOutTime.asSeconds() - FadeOutDelay.asSeconds() ) / ( FadeOutDuration.asSeconds() - FadeOutDelay.asSeconds() ) ) ) ); }

        else {

            Fade.setFillColor( sf::Color( 0, 0, 0, 255 ) ); } }

    else {

        return; }

    Window.draw( Fade ); }

void PlayerInterface::updateBar ( sf::Time ElapsedTime, std::vector <float> &Opacity, float BarMargin, float ElementSize, float ElementMargin, float Value, float Limit ) {

    if ( ( Viewport.height - 2.f * BarMargin ) < 0.f ) {

        Opacity.clear();

        return; }

    auto BarSize = (unsigned int) ( ( Viewport.height - 2.f * BarMargin ) / ( ElementSize + ElementMargin ) );

    if ( Opacity.size() != BarSize ) {

        Opacity.resize( BarSize );

        for ( unsigned int i = 0; i < BarSize; i++ ) {

            Opacity[i] = UnactivatedOpacity; } }

    auto BarActivation = (unsigned int) roundf( ( Value / Limit ) * BarSize );

    for ( unsigned int i = 0; i < BarActivation; i++ ) {

        if ( Opacity[i] < ActivatedOpacity ) {

            Opacity[i] += ( ActivatedOpacity - UnactivatedOpacity ) * ( ElapsedTime.asSeconds() / TransitionDuration.asSeconds() ); }

        else {

            Opacity[i] = ActivatedOpacity; } }

    for ( unsigned int i = BarActivation; i < BarSize; i++ ) {

        if ( Opacity[i] > UnactivatedOpacity ) {

            Opacity[i] -= ( ActivatedOpacity - UnactivatedOpacity ) * ( ElapsedTime.asSeconds() / TransitionDuration.asSeconds() ); }

        else {

            Opacity[i] = UnactivatedOpacity; } } }

void PlayerInterface::renderBar ( sf::RenderWindow &Window, std::vector <float> Opacity, sf::Color Color, sf::Vector2f BarMargin, sf::Vector2f ElementSize, sf::Vector2f ElementMargin ) {

    ElementSize.y = ( Viewport.height - 2 * BarMargin.y + ElementMargin.y ) / Opacity.size() - ElementMargin.y;

    for ( unsigned int i = 0; i < Opacity.size(); i++ ) {

        sf::Vector2f ElementPosition;
        sf::RectangleShape Element;

        ElementPosition.x = Viewport.left + BarMargin.x;
        ElementPosition.y = Viewport.top + Viewport.height - BarMargin.y + ElementMargin.y - ( i + 1 ) * ( ElementMargin.y + ElementSize.y );

        Element.setPosition( ElementPosition );
        Element.setSize( ElementSize );
        Element.setOutlineThickness( 1.f );
        Element.setFillColor( sf::Color( Color.r, Color.g, Color.b, (sf::Uint8) ( Opacity[i] * 255.f ) ) );
        Element.setOutlineColor( sf::Color( Color.r, Color.g, Color.b, 127 ) );

        Window.draw( Element ); } }
