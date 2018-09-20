#ifndef GRAVITY_MADNESS_SCORE_COUNTER
#define GRAVITY_MADNESS_SCORE_COUNTER

#include <list>
#include <SFML/System.hpp>

class ScoreCounter {

public:

    enum Event {

        Time,
        ShotHit,
        ShotDestruction,
        MissileHit,
        MissileDestruction,
        Collision

        };

    ScoreCounter ( );

    unsigned int getScore ( );
    float getMultiplier ( );

    void addMultiplier ( float Multiplier, float Time = 0.f );

    void update ( Event ActiveEvent, float Data = 0.f );
    void update ( sf::Time ElapsedTime );

    void reset ( );

private:

    struct Tracker {

        Tracker ( float Multiplier, sf::Time Time ) : Multiplier ( Multiplier ), Time( Time ) { }

        float Multiplier;
        sf::Time Time;

        };

    float Score;
    float Multiplier;

    std::list <Tracker> Trackers;

    };

#endif
