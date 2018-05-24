#ifndef GRAVITY_MADNESS_MAIN_MENU_HPP
#define GRAVITY_MADNESS_MAIN_MENU_HPP

#include <cmath>
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
    bool onSettingsChanged ( );

private:

    float getRandomFloat ( );

    void updateMenu ( sf::Time ElapsedTime );
    void updateMenu ( sf::Event &Event );
    void renderMenu ( sf::RenderWindow &Window );

    void updateGameplaySection ( sf::Event &Event );
    void renderGameplaySection ( sf::RenderWindow &Window );

    void updateSettingsSection ( sf::Time ElapsedTime );
    void updateSettingsSection ( sf::Event &Event );
    void updateSettingsSection_BindLeft ( );
    void updateSettingsSection_BindRight ( );
    void renderSettingsSection ( sf::RenderWindow &Window );

    void updateBackground ( sf::Time ElapsedTime );
    void renderBackground ( sf::RenderWindow &Window );
    void renderSectionBackground ( sf::RenderWindow &Window, unsigned int Position );

private:

    GraphicsModule * Graphics;
    GameplaySettings * Gameplay;

    bool Launch;
    bool Terminate;
    bool VideoChanged;
    bool SettingsChanged;
    Modes Mode;
    sf::Clock Clock;

    unsigned int WindowWidth;
    unsigned int WindowHeight;
    bool FullScreen;
    unsigned int AntialiasingLevel;

    unsigned int MenuOption;
    unsigned int MenuOptionCount;
    std::string MenuOptionText [5];
    unsigned int MenuOptionFontSize;
    sf::Vector2f MenuOptionPosition [5];
    float MenuOptionPositionCenter [5];
    sf::Vector2f MenuOptionPointerPosition;
    float MenuOptionPointerVelocity;

    unsigned int SettingsOption;
    unsigned int SettingsOptionCount;
    std::string SettingsOptionText [6];
    unsigned int SettingsOptionFontSize;
    sf::Vector2f SettingsOptionPosition [6];

    std::vector <sf::Vertex> Background;
    std::vector <unsigned int> ParticleIndexes;
    std::vector <sf::Vector2f> ParticleVelocities;
    sf::Time BackgroundPauseTime;
    sf::Time BackgroundPauseDuration;
    std::vector <sf::Color> RedPalette;

    };

#endif
