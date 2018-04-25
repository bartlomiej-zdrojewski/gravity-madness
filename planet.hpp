#ifndef GRAVITY_MADNESS_PLANET
#define GRAVITY_MADNESS_PLANET

#include "body.hpp"

class Planet : public Body {

public:

    explicit Planet ( float Mass, float Radius ) : Body ( Mass, Radius ) { }

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

private:

    // TODO

    };

#endif
