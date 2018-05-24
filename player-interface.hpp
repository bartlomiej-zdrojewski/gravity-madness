#ifndef GRAVITY_MADNESS_PLAYER_INTERFACE
#define GRAVITY_MADNESS_PLAYER_INTERFACE

#include <SFML/Graphics.hpp>
#include "graphics-module.hpp"
#include "spaceship.hpp"

class PlayerInterface {

public:

    explicit PlayerInterface ( GraphicsModule * Graphics );

    void setSpaceship ( Spaceship * MySpaceship );
    void setViewport ( sf::FloatRect Viewport );

    void beginFadeOut ( );
    bool isFadedOut ( );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

    void onShot ( );

private:

    void updateHealthBar ( sf::Time ElapsedTime );
    void updateEnergyBar ( sf::Time ElapsedTime );

    void renderHealthBar ( sf::RenderWindow &Window );
    void renderEnergyBar ( sf::RenderWindow &Window );
    void renderMissileBar ( sf::RenderWindow &Window );
    void renderScoreBar ( sf::RenderWindow &Window );
    void renderFade ( sf::RenderWindow &Window );

    void updateBar ( sf::Time ElapsedTime, std::vector <float> &Opacity, float BarMargin, float ElementSize, float ElementMargin, float Value, float Limit );
    void renderBar ( sf::RenderWindow &Window, std::vector <float> Opacity, sf::Color Color, sf::Vector2f BarMargin, sf::Vector2f ElementSize, sf::Vector2f ElementMargin );

private:

    GraphicsModule * Graphics;

    Spaceship * MySpaceship;
    sf::FloatRect Viewport;

    float ActivatedOpacity;
    float UnactivatedOpacity;
    sf::Time TransitionDuration;

    bool FadeIn;
    sf::Time FadeInTime;
    sf::Time FadeInDuration;

    bool FadeOut;
    sf::Time FadeOutTime;
    sf::Time FadeOutDelay;
    sf::Time FadeOutDuration;

    float Health;
    float HealthLimit;
    std::vector <float> HealthBarOpacity;

    float Energy;
    float EnergyLimit;
    std::vector <float> EnergyBarOpacity;

    };

#endif
