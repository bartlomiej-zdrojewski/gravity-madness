#ifndef GRAVITY_MADNESS_MAIN_MENU_HPP
#define GRAVITY_MADNESS_MAIN_MENU_HPP

#include <list>
#include <SFML/Graphics.hpp>
#include "definitions.hpp"
#include "gameplay-settings.hpp"
#include "graphics-module.hpp"

class MainMenu {

public:

    enum Modes {

        MenuMode,
        GameplayMode,
        SettingsMode

        };

    MainMenu ( GraphicsModule * Graphics, GameplaySettings * Gameplay );

    Modes getMode ( );
    void setMode ( Modes Mode );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );
    void reset ( );

    bool onLaunch ( );
    bool onTerminate ( );
    bool onVideoChanged ( );

private:

    float getRandomFloat ( );

    void renderSectionBackground ( sf::RenderWindow &Window, unsigned int Position );

    void updateMenu ( sf::Time ElapsedTime );
    void updateMenu ( sf::Event &Event );
    void renderMenu ( sf::RenderWindow &Window );

    void updateGameplaySection ( sf::Event &Event );
    void renderGameplaySection ( sf::RenderWindow &Window );

    void updateSettingsSection ( sf::Event &Event );
    void renderSettingsSection ( sf::RenderWindow &Window );

    void updateBackground ( sf::Time ElapsedTime );
    void renderBackground ( sf::RenderWindow &Window );

private:

    GraphicsModule * Graphics;
    GameplaySettings * Gameplay;

    bool Launch;
    bool Terminate;
    bool VideoChanged;
    Modes Mode;
    sf::Clock Clock;

    unsigned int MenuOption;
    unsigned int MenuOptionCount;
    std::string MenuOptionText [5];
    unsigned int MenuOptionFontSize;
    sf::Vector2f MenuOptionPosition [5];
    float MenuOptionPositionCenter [5];
    sf::Vector2f MenuOptionPointerPosition;
    float MenuOptionPointerVelocity;

    std::vector <sf::Vertex> Background;
    std::vector <unsigned int> ParticleIndexes;
    std::vector <sf::Vector2f> ParticleVelocities;
    sf::Time BackgroundPauseTime;
    sf::Time BackgroundPauseDuration;
    std::vector <sf::Color> FancyColors;

    };

#endif
