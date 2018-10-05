#ifndef GRAVITY_MADNESS_MAIN_MENU
#define GRAVITY_MADNESS_MAIN_MENU

#include <cmath>
#include <list>
#include "constants.hpp"
#include "controllers/visualization-controller.hpp"
#include "gameplay-settings.hpp"
#include "graphics-module.hpp"
#include "missile.hpp"
#include "ray.hpp"
#include "spaceship.hpp"

#define CONTROLLERS_SPACESHIP_CARDS_FONT_HORIZONTAL_OFFSET_FIX (-0.f)
#define CONTROLLERS_SPACESHIP_CARDS_FONT_VERTICAL_OFFSET_FIX (-0.2f)
#define CONTROLLERS_TABLE_FONT_HORIZONTAL_OFFSET_FIX (-0.f)
#define CONTROLLERS_TABLE_FONT_VERTICAL_OFFSET_FIX (-0.35f)
#define CONTROLLERS_MANUAL_FONT_HORIZONTAL_OFFSET_FIX (-0.f)
#define CONTROLLERS_MANUAL_FONT_VERTICAL_OFFSET_FIX (-0.2f)

class MainMenu {

public:

    enum Modes {

        MenuMode,
        GameplayMode,
        SpaceshipsMode,
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

    bool onLaunchGame ( );
    bool onLaunchTutorial ( );
    bool onVideoChanged ( );
    bool onSettingsChanged ( );
    bool onLowPerformance ( );
    bool onTerminate ( );

private:

    struct SpaceshipCard {

        ~ SpaceshipCard ( ) {

            if ( VisualizationSpaceship ) {

                if ( VisualizationSpaceship->getController() ) {

                    delete VisualizationSpaceship->getController();

                    VisualizationSpaceship->setController( nullptr ); } }

            delete VisualizationSpaceship;
            delete VisualizationArea;

            for ( auto i = VisualizationRayShots.begin(); i != VisualizationRayShots.end(); ) {

                delete (*i);
                i = VisualizationRayShots.erase( i ); }

            for ( auto i = VisualizationMissiles.begin(); i != VisualizationMissiles.end(); ) {

                delete (*i);
                i = VisualizationMissiles.erase( i );} }

        unsigned int Index = 0;
        GameplaySettings::SpaceshipPrototype Prototype;

        sf::Vector2f Size;
        sf::Vector2f Position; // The center of the card
        sf::VertexArray Outline;

        Spaceship * VisualizationSpaceship = nullptr;
        sf::RenderTexture * VisualizationArea = nullptr;
        sf::Vector2f VisualizationWind;
        std::list <Ray*> VisualizationRayShots;
        std::list <Missile*> VisualizationMissiles;

        };

    static float getRandomFloat ( );
    static std::string getTimeText ( sf::Time Time );
    static std::string blankUnderscore ( std::string Text );

    std::vector <sf::Texture*> getBrakesTextures ( );

    void updateMenu ( sf::Time ElapsedTime );
    void updateMenu ( sf::Event &Event );
    void renderMenu ( sf::RenderWindow &Window );

    void updateGameplaySection ( sf::Time ElapsedTime );
    void updateGameplaySection ( sf::Event &Event );
    void updateGameplaySection_BindLeft ( );
    void updateGameplaySection_BindRight ( );
    void renderGameplaySection ( sf::RenderWindow &Window );

    void loadSpaceshipCards ( );
    void updateSpaceshipsSection ( sf::Time ElapsedTime );
    void updateSpaceshipsSection ( sf::Event &Event );
    void renderSpaceshipsSection ( sf::RenderWindow &Window );
    void renderSpaceshipsSectionBar ( sf::RenderWindow &Window, sf::Vector2f Position, sf::Vector2f Size, sf::Color Color, float Value );

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

    bool LaunchGame;
    bool LaunchTutorial;
    bool VideoChanged;
    bool SettingsChanged;
    bool LowPerformance;
    bool Terminate;
    Modes Mode;
    sf::Clock Clock;
    // TODO sf::Time PerformanceTimer;
    // TODO sf::Time LowPerformanceTimer;

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

    unsigned int SpaceshipIndex;
    unsigned int SpaceshipOption;
    float SpaceshipMaximumValues [6];
    std::string SpaceshipCardsTitleText [2];
    unsigned int SpaceshipCardsTitleFontSize;
    sf::Color SpaceshipCardsTitleColor;
    sf::Vector2f SpaceshipCardsTitlePosition [2];
    unsigned int SpaceshipCardsContentFontSize [2];
    std::list <SpaceshipCard> SpaceshipCards;
    float SpaceshipCardsOffset;
    float SpaceshipCardsOffsetDirection;
    float SpaceshipCardsTime;

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
