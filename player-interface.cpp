#include "player-interface.hpp"

PlayerInterface::PlayerInterface ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    MySpaceship = nullptr;
    Viewport = sf::FloatRect( 0.f, 0.f, Graphics->getWindowWidth(), Graphics->getWindowHeight() );
    Orientation = Orientations::Left;

    }

void PlayerInterface::setSpaceship ( Spaceship * MySpaceship ) {

    this->MySpaceship = MySpaceship; }

void PlayerInterface::setViewport ( sf::FloatRect Viewport ) {

    this->Viewport = Viewport; }

void PlayerInterface::setOrientation ( Orientations Orientation ) {

    this->Orientation = Orientation; }

void PlayerInterface::update ( ) {

    if ( !MySpaceship ) {

        return; }

    Energy = MySpaceship->getEnergy();

    }

void PlayerInterface::render ( sf::RenderWindow &Window ) {

    sf::View ViewCopy = Window.getView();
    Window.setView( Window.getDefaultView() );

    renderEnergyBar( Window );
    renderMissileBar( Window );
    renderScoreBar( Window );

    Window.setView( ViewCopy ); }

void PlayerInterface::renderEnergyBar ( sf::RenderWindow &Window ) {

    sf::RectangleShape EnergyBar;

    EnergyBar.setPosition( Viewport.left + 20.f, Viewport.top + 20.f );
    EnergyBar.setSize( sf::Vector2f( 30.f, Viewport.height - 40.f ) );

    EnergyBar.setFillColor( sf::Color( 13, 71, 161 ) );
    Window.draw( EnergyBar );

    EnergyBar.setPosition( Viewport.left + 20.f, Viewport.top + 20.f + ( Viewport.height - 40.f ) * ( 1.f - Energy / 10000.f ) );
    EnergyBar.setSize( sf::Vector2f( 30.f, ( Viewport.height - 40.f ) * ( Energy / 10000.f ) ) );
    EnergyBar.setFillColor( sf::Color( 41, 98, 255 ) );
    Window.draw( EnergyBar );

    }

void PlayerInterface::renderMissileBar ( sf::RenderWindow &Window ) {

    // ...

    }

void PlayerInterface::renderScoreBar ( sf::RenderWindow &Window ) {

    // ...

    }