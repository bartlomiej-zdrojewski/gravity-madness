#include "pause-menu.hpp"

PauseMenu::PauseMenu ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    Close = false;
    Terminate = false;

    }

void PauseMenu::update ( ) {

    // TODO
    Close = true;

    }

void PauseMenu::update ( sf::Event &Event ) {

    // TODO
    Close = true;

    }

void PauseMenu::render ( sf::RenderWindow &Window ) {

    // TODO

    }

bool PauseMenu::onClose ( ) {

    if ( Close ) {

        Close = false;
        Terminate = false;

        return true; }

    return false; }

bool PauseMenu::onTerminate ( ) {

    if ( Terminate ) {

        Close = false;
        Terminate = false;

        return true; }

    return false; }
