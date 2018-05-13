#include "message.hpp"

Message::Message ( GraphicsModule * Graphics ) {

    this->Graphics = Graphics;

    Close = false;
    Type = Types::None;

    Text[0] = "";
    Text[1] = "";
    Text[2] = ""; }

void Message::setType ( Types Type ) {

    this->Type = Type; }

void Message::update ( ) {

    if ( Type == Types::None ) {

        Close = true;

        return; }

    // TODO
    Close = true;

    }

void Message::update ( sf::Event &Event ) {

    if ( Type == Types::None ) {

        Close = true;

        return; }

    // TODO
    Close = true;

    }

void Message::render ( sf::RenderWindow &Window ) {

    // TODO

    }

bool Message::onClose ( ) {

    if ( Close ) {

        Close = false;

        return true; }

    return false; }
