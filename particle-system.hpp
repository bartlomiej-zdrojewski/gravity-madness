#ifndef GRAVITY_MADNESS_PARTICLE_SYSTEM
#define GRAVITY_MADNESS_PARTICLE_SYSTEM

#include <cmath>
#include <list>
#include <SFML/Graphics.hpp>
#include "definitions.hpp"

class ParticleSystem { // TODO ERROR CHECK

public:

    ParticleSystem ( );

    sf::FloatRect getInfluenceArea ( );

    void setOriginPosition ( sf::Vector2f Position );
    void setOriginVelocity ( sf::Vector2f Velocity );

    void setAngleRange ( float AxisAngle, float AngleRange );
    void setVelocityRange ( float MinVelocity, float MaxVelocity );
    void setColorRange ( sf::Color MinColor, sf::Color MaxColor );
    void setDuration ( sf::Time MinDuration, sf::Time MaxDuration );

    unsigned int getParticleCount ( );
    void generateParticles ( unsigned int Count );

    void update ( sf::Time ElapsedTime );
    void render ( sf::RenderWindow &Window );

private:

    float getRandomFloat ( );

private:

    sf::FloatRect InfluenceArea;

    sf::Vector2f OriginPosition;
    sf::Vector2f OriginVelocity;

    float AxisAngle;
    float AngleRange;
    float MinVelocity;
    float MaxVelocity;
    sf::Color MinColor;
    sf::Color MaxColor;
    sf::Time MinDuration;
    sf::Time MaxDuration;

    struct Particle {

        sf::Vector2f Position;
        sf::Vector2f Velocity;
        sf::Color Color;
        sf::Time Time;

        };

    std::list <Particle> Particles;
    std::vector <sf::Vertex> Vertices;

    };

#endif
