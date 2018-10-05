#ifndef GRAVITY_MADNESS_SCORE_BOARD
#define GRAVITY_MADNESS_SCORE_BOARD

#include "gameplay-settings.hpp"
#include "graphics-module.hpp"

class ScoreBoard {

public:

    ScoreBoard ( GraphicsModule * Graphics, GameplaySettings * Gameplay );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

    bool onHighScore ( );
    bool onRestart ( );
    bool onClose ( );

private:

    std::string getFormattedText ( unsigned int Value );

private:

    GraphicsModule * Graphics;
    GameplaySettings * Gameplay;

    bool HighScore;
    bool SaveHighScore;
    bool Restart;
    bool Close;

    std::string HighScoreText;
    unsigned int HighScoreFontSize;
    float HighScorePosition;

    std::string ScoreText [ MAXIMUM_PLAYER_COUNT ] [2];
    unsigned int ScoreFontSize;
    sf::Vector2f ScorePosition [ MAXIMUM_PLAYER_COUNT ] [2];

    unsigned int MenuOptionCount;
    unsigned int MenuOption;
    std::string MenuOptionText [2];
    unsigned int MenuOptionFontSize;
    float MenuOptionPosition [2];

    };

#endif
