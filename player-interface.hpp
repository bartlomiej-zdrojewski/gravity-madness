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
    void endFadeOut ( );
    bool isFadedOut ( );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

    void onDamage ( );

private:

    void updateHealthBar ( sf::Time ElapsedTime );
    void updateEnergyBar ( sf::Time ElapsedTime );
    void updateMissileTab ( sf::Time ElapsedTime );

    void renderHealthBar ( sf::RenderWindow &Window );
    void renderEnergyBar ( sf::RenderWindow &Window );
    void renderMissileTab ( sf::RenderWindow &Window );
    void renderScoreTab ( sf::RenderWindow &Window );
    void renderFade ( sf::RenderWindow &Window );

    void updateBar ( sf::Time ElapsedTime, std::vector <float> &Opacity, float BarMargin, float ElementSize, float ElementMargin, float Value, float Limit );
    void renderBar ( sf::RenderWindow &Window, std::vector <float> Opacity, sf::Color Color, sf::Vector2f BarMargin, sf::Vector2f ElementSize, sf::Vector2f ElementMargin );

private:

    GraphicsModule * Graphics;

    Spaceship * MySpaceship;
    sf::FloatRect Viewport;

    float Health;
    float HealthLimit;
    std::vector <float> HealthBarOpacity;

    float Energy;
    float EnergyLimit;
    std::vector <float> EnergyBarOpacity;

    unsigned int MissileCount;
    unsigned int MissileLimit;
    sf::Texture MissileTexture;
    std::vector <float> MissileTabOpacity;

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

    bool DamageFade;
    sf::Time DamageFadeTime;
    sf::Time DamageFadeDuration;

    };

#endif
