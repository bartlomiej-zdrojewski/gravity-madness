#ifndef GRAVITY_MADNESS_PLAYER_INTERFACE
#define GRAVITY_MADNESS_PLAYER_INTERFACE

#include <cmath>
#include "graphics-module.hpp"
#include "score-counter.hpp"
#include "spaceship.hpp"

#define SCORE_TAB_FONT_HORIZONTAL_OFFSET_FIX (-0.025f)
#define SCORE_TAB_FONT_VERTICAL_OFFSET_FIX (-0.45f)

class PlayerInterface {

public:

    explicit PlayerInterface ( GraphicsModule * Graphics );

    void setSpaceship ( Spaceship * MySpaceship );
    void setScoreCounter ( ScoreCounter * Score );
    void setViewport ( sf::FloatRect Viewport );

    void enableArrow ( );
    void disableArrow ( );

    void displayNotification ( std::string Notification );

    void beginFadeOut ( );
    void endFadeOut ( );
    bool isFadedOut ( );
    float getFadeInAlpha ( );
    float getFadeOutAlpha ( );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

    void onDamage ( );

private:

    std::string getScoreText ( );
    std::string getScoreMultiplierText ( );

    void updateHealthBar ( sf::Time ElapsedTime );
    void updateEnergyBar ( sf::Time ElapsedTime );
    void updateMissileTab ( sf::Time ElapsedTime );
    void updateScoreTab ( sf::Time ElapsedTime );
    void updateArrow ( sf::Time ElapsedTime );
    void updateNotification ( sf::Time ElapsedTime );

    void renderHealthBar ( sf::RenderWindow &Window );
    void renderEnergyBar ( sf::RenderWindow &Window );
    void renderMissileTab ( sf::RenderWindow &Window );
    void renderScoreTab ( sf::RenderWindow &Window );
    void renderArrow ( sf::RenderWindow &Window );
    void renderFade ( sf::RenderWindow &Window );
    void renderNotification ( sf::RenderWindow &Window );

    void updateBar ( sf::Time ElapsedTime, std::vector <float> &Opacity, float BarMargin, float ElementSize, float ElementMargin, float Value, float Limit );
    void renderBar ( sf::RenderWindow &Window, std::vector <float> Opacity, sf::Color Color, sf::Vector2f BarMargin, sf::Vector2f ElementSize, sf::Vector2f ElementMargin );

private:

    GraphicsModule * Graphics;

    Spaceship * MySpaceship;
    ScoreCounter * MyScore;
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

    unsigned int ScoreValue;
    float ScoreValueFloating;
    float ScoreValueSpeed;
    unsigned int ScoreFontSize;
    float ScoreHorizontalOffset;

    float ScoreMultiplierValue;
    float ScoreMultiplierValueSpeed;
    unsigned int ScoreMultiplierFontSize;
    float ScoreMultiplierHorizontalOffset;
    float ScoreMultiplierTextWidth;

    bool Arrow;
    float ArrowAngle;
    sf::Texture ArrowTexture;

    std::string Notification;
    std::string NextNotification;
    float NotificationOpacity;
    unsigned int NotificationFontSize;
    sf::Time NotificationTime;
    sf::Time NotificationDuration;
    sf::Time NotificationFadeInDuration;
    sf::Time NotificationFadeOutDuration;

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
