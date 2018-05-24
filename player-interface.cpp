#include "player-interface.hpp"

PlayerInterface::PlayerInterface ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    MySpaceship = nullptr;
    Viewport = sf::FloatRect( 0.f, 0.f, Graphics->getWindowWidth(), Graphics->getWindowHeight() );

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

    Health = 0;
    HealthLimit = 100;
    Energy = 0;
    EnergyLimit = 100;

    }

void PlayerInterface::setSpaceship ( Spaceship * MySpaceship ) {

    this->MySpaceship = MySpaceship; }

void PlayerInterface::setViewport ( sf::FloatRect Viewport ) {

    Viewport.left = Graphics->getWindowWidth() * Viewport.left;
    Viewport.top = Graphics->getWindowHeight() * Viewport.top;
    Viewport.width = Graphics->getWindowWidth() * Viewport.width;
    Viewport.height = Graphics->getWindowHeight() * Viewport.height;

    this->Viewport = Viewport; }

void PlayerInterface::beginFadeOut ( ) {

    FadeOut = true; }

bool PlayerInterface::isFadedOut ( ) {

    return ( FadeOutTime >= ( FadeOutDuration + sf::seconds( 1.f ) ) ); }

void PlayerInterface::update ( sf::Time ElapsedTime ) {

    if ( FadeIn ) {

        FadeInTime -= ElapsedTime;

        if ( FadeInTime.asSeconds() <= 0.f ) {

            FadeIn = false; } }

    else if ( FadeOut ) {

        FadeOutTime += ElapsedTime; }

    if ( MySpaceship ) {

        Health = MySpaceship->getHealth();
        HealthLimit = MySpaceship->getHealthLimit();

        Energy = MySpaceship->getEnergy();
        EnergyLimit = MySpaceship->getEnergyLimit(); }

    updateHealthBar( ElapsedTime );
    updateEnergyBar( ElapsedTime );
    // ...

    }

void PlayerInterface::render ( sf::RenderWindow &Window ) {

    renderHealthBar( Window );
    renderEnergyBar( Window );
    renderMissileBar( Window );
    renderScoreBar( Window );
    renderFade( Window ); }

void PlayerInterface::onShot ( ) {

    // TODO

    }

void PlayerInterface::updateHealthBar ( sf::Time ElapsedTime ) {

    float ElementSize = 10.f;
    float ElementMargin = 5.f;

    if ( Viewport.height < 600.f ) {

        ElementSize = 8.f; }

    else if ( Viewport.height > 800 ) {

        ElementSize = 15.f; }

    updateBar( ElapsedTime, HealthBarOpacity, 15.f, ElementSize, ElementMargin, Health, HealthLimit ); }

void PlayerInterface::updateEnergyBar ( sf::Time ElapsedTime ) {

    float ElementSize = 10.f;
    float ElementMargin = 5.f;

    if ( Viewport.height < 600.f ) {

        ElementSize = 8.f; }

    else if ( Viewport.height > 800.f ) {

        ElementSize = 15.f; }

    updateBar( ElapsedTime, EnergyBarOpacity, 15.f, ElementSize, ElementMargin, Energy, EnergyLimit ); }

void PlayerInterface::renderHealthBar ( sf::RenderWindow &Window ) {

    sf::Vector2f ElementSize ( 30.f, 10.f );
    sf::Vector2f ElementMargin ( 20.f, 5.f );

    if ( Viewport.height < 600.f ) {

        ElementSize = sf::Vector2f ( 20.f, 8.f ); }

    else if ( Viewport.height > 800.f ) {

        ElementSize = sf::Vector2f ( 40.f, 15.f ); }

    renderBar( Window, HealthBarOpacity, sf::Color( 255, 23, 68 ), sf::Vector2f( 15.f, 15.f ), ElementSize, ElementMargin ); }

void PlayerInterface::renderEnergyBar ( sf::RenderWindow &Window ) {

    sf::Vector2f ElementSize ( 30.f, 10.f );
    sf::Vector2f ElementMargin ( 20.f, 5.f );

    if ( Viewport.height < 600.f ) {

        ElementSize = sf::Vector2f ( 20.f, 8.f ); }

    else if ( Viewport.height > 800 ) {

        ElementSize = sf::Vector2f ( 40.f, 15.f ); }

    renderBar( Window, EnergyBarOpacity, sf::Color( 61, 90, 254 ), sf::Vector2f( ElementSize.x + ElementMargin.y + 15.f, 15.f ), ElementSize, ElementMargin ); }

void PlayerInterface::renderMissileBar ( sf::RenderWindow &Window ) {

    // ...

    }

void PlayerInterface::renderScoreBar ( sf::RenderWindow &Window ) {

    // ...

    }

void PlayerInterface::renderFade ( sf::RenderWindow &Window ) {

    sf::RectangleShape Fade;

    Fade.setPosition( 0.f, 0.f );
    Fade.setSize( sf::Vector2f( Viewport.width, Viewport.height ) );

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
