#ifndef GRAVITY_MADNESS_MESSAGE
#define GRAVITY_MADNESS_MESSAGE

#include "graphics-module.hpp"

class Message {

public:

    enum Types {

        None,
        InitTimeWarning,
        InitTimeError,
        RunTimeError,
        LowPerformanceError,
        WelcomeMessage

        };

    explicit Message ( GraphicsModule * Graphics );

    void setType ( Types Type );

    void update ( );
    void update ( sf::Event &Event );
    void render ( sf::RenderWindow &Window );

    bool onClose ( );

private:

    GraphicsModule * Graphics;

    bool Close;
    Types Type;

    std::string Text [6];
    unsigned int FontSize;
    float FontFix;
    float LineHeight;
    sf::Vector2f FrameSize;
    sf::Vector2f FramePosition;
    sf::Vector2f FrameMargin;

    };

#endif
