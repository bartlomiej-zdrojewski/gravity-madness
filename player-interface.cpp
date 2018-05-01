#include "player-interface.hpp"

PlayerInterface::PlayerInterface ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    MySpaceship = nullptr;
    Viewport = sf::FloatRect( 0.f, 0.f, Graphics->getWindowWidth(), Graphics->getWindowHeight() );

    ActivatedOpacity = 0.87f;
    UnactivatedOpacity = 0.34f;
    TransitionDuration = sf::seconds( 0.3f );

    }

void PlayerInterface::setSpaceship ( Spaceship * MySpaceship ) {

    this->MySpaceship = MySpaceship; }

void PlayerInterface::setViewport ( sf::FloatRect Viewport ) {

    this->Viewport = Viewport; }

void PlayerInterface::update ( sf::Time ElapsedTime ) {

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

    sf::View ViewCopy = Window.getView();
    Window.setView( Window.getDefaultView() );

    renderHealthBar( Window );
    renderEnergyBar( Window );
    renderMissileBar( Window );
    renderScoreBar( Window );

    Window.setView( ViewCopy ); }

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

void PlayerInterface::updateBar ( sf::Time ElapsedTime, std::vector <float> &Opacity, float BarMargin, float ElementSize, float ElementMargin, float Value, float Limit ) {

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

    ElementSize.y = ( Viewport.height - 2 * BarMargin.y + ElementMargin.y ) / HealthBarOpacity.size() - ElementMargin.y;

    for ( unsigned int i = 0; i < HealthBarOpacity.size(); i++ ) {

        sf::Vector2f ElementPosition;
        sf::RectangleShape Element;

        ElementPosition.x = Viewport.left + BarMargin.x;
        ElementPosition.y = Viewport.top + Viewport.height - BarMargin.y + ElementMargin.y - ( i + 1 ) * ( ElementMargin.y + ElementSize.y );

        Element.setPosition( ElementPosition );
        Element.setSize( ElementSize );
        Element.setFillColor( sf::Color( Color.r, Color.g, Color.b, (sf::Uint8) ( Opacity[i] * 255.f ) ) );

        Window.draw( Element ); } }