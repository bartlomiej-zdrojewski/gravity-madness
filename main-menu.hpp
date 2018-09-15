#ifndef GRAVITY_MADNESS_MAIN_MENU
#define GRAVITY_MADNESS_MAIN_MENU

#include <cmath>
#include <list>
#include "constants.hpp"
#include "gameplay-settings.hpp"
#include "graphics-module.hpp"

#define CONTROLLERS_TABLE_FONT_HORIZONTAL_OFFSET_FIX (-0.f)
#define CONTROLLERS_TABLE_FONT_VERTICAL_OFFSET_FIX (-0.4f)
#define CONTROLLERS_MANUAL_FONT_HORIZONTAL_OFFSET_FIX (-0.f)
#define CONTROLLERS_MANUAL_FONT_VERTICAL_OFFSET_FIX (-0.2f)

class MainMenu {

public:

    enum Modes {

        MenuMode,
        GameplayMode,
        SettingsMode,
        ControllersMode

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

    static float getRandomFloat ( );
    static std::string getTimeText ( sf::Time Time );
    static std::string blankUnderscore ( std::string Text );

    void updateMenu ( sf::Time ElapsedTime );
    void updateMenu ( sf::Event &Event );
    void renderMenu ( sf::RenderWindow &Window );

    void updateGameplaySection ( sf::Time ElapsedTime );
    void updateGameplaySection ( sf::Event &Event );
    void updateGameplaySection_BindLeft ( );
    void updateGameplaySection_BindRight ( );
    void renderGameplaySection ( sf::RenderWindow &Window );

    void updateSettingsSection ( sf::Time ElapsedTime );
    void updateSettingsSection ( sf::Event &Event );
    void updateSettingsSection_BindLeft ( );
    void updateSettingsSection_BindRight ( );
    void renderSettingsSection ( sf::RenderWindow &Window );

    void updateControllersSection ( sf::Time ElapsedTime );
    void updateControllersSection ( sf::Event &Event );
    void renderControllersSection ( sf::RenderWindow &Window );

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
    bool EpilepsyProtection;

    unsigned int MenuOption;
    unsigned int MenuOptionCount;
    std::string MenuOptionText [5];
    unsigned int MenuOptionFontSize;
    sf::Vector2f MenuOptionPosition [5];
    float MenuOptionPositionCenter [5];
    sf::Vector2f MenuOptionPointerPosition;
    float MenuOptionPointerVelocity;

    unsigned int GameplayPage;
    unsigned int GameplayOption;
    unsigned int GameplayOptionCount [2];
    std::string GameplayOptionText [2][9];
    unsigned int GameplayOptionFontSize;
    sf::Vector2f GameplayOptionPosition [2][9];

    unsigned int SettingsOption;
    unsigned int SettingsOptionCount;
    std::string SettingsOptionText [9];
    unsigned int SettingsOptionFontSize;
    sf::Vector2f SettingsOptionPosition [9];

    std::vector <sf::Vertex> ControllersTable;
    std::vector <sf::Text> ControllersTableColumnHeader;
    std::vector <sf::Text> ControllersTableRowHeader;
    std::vector <sf::Text> ControllersTableContent;
    sf::Text ControllersTableManual;
    sf::Vector2i ControllersTablePointer;
    bool ControllersModificationMode;
    uint8_t ControllersModificationState;
    PlayerControllerSettings::Devices PreviousDevice;
    int PreviousIdentifier;

    std::vector <sf::Vertex> Background;
    std::vector <unsigned int> ParticleIndexes;
    std::vector <sf::Vector2f> ParticleVelocities;
    sf::Time BackgroundPauseTime;
    sf::Time BackgroundPauseDuration;
    std::vector <sf::Color> RedPalette;

    };

#endif
