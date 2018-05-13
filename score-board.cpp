#include "score-board.hpp"

ScoreBoard::ScoreBoard ( GraphicsModule * Graphics, GameplaySettings * Gameplay ) {

    this->Graphics = Graphics;
    this->Gameplay = Gameplay;

    Close = false;

    }

void ScoreBoard::update ( ) {

    // TODO
    Close = true;

    }

void ScoreBoard::update ( sf::Event &Event ) {

    // TODO
    Close = true;

    }

void ScoreBoard::render ( sf::RenderWindow &Window ) {

    // TODO

    }

bool ScoreBoard::onClose ( ) {

    if ( Close ) {

        Close = false;

        return Close; }

    return true; }
