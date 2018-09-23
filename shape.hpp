#ifndef GRAVITY_MADNESS_SHAPE
#define GRAVITY_MADNESS_SHAPE

#include <SFML/System.hpp>
#include <cmath>
#include <list>
#include <sstream>
#include <vector>
#include "constants.hpp"

class Shape {

public:

    struct Segment {

        Segment ( ) { }

        Segment ( sf::Vector2f Begin, sf::Vector2f End ) {

            this->Begin = Begin;
            this->End = End; }

        sf::Vector2f Begin;
        sf::Vector2f End;

        };

    Shape ( );

    void loadOutline ( std::string Config, float Radius );
    std::list <Segment> getOutline ( );

    sf::Vector2f getOrigin ( );
    void setOrigin ( sf::Vector2f Origin );

    float getRotation ( );
    void setRotation ( float Rotation );

    bool isIntersecting ( Shape * Other );
    bool isIntersecting ( sf::Vector2f Center, float Radius );
    bool isIntersecting ( Segment OtherSegment );
    bool isIntersecting ( sf::Vector2f Begin, sf::Vector2f End );
    bool getIntersection ( sf::Vector2f Begin, sf::Vector2f End, sf::Vector2f &Intersection, float &Distance );

private:

    static float getDeterminant ( sf::Vector2f A, sf::Vector2f B, sf::Vector2f C );
    static bool isIntersecting ( Segment A, Segment B );

private:

    struct SegmentPrototype {

        sf::Vector2f PolarBegin;
        sf::Vector2f PolarEnd;

        };

    sf::Vector2f Origin;
    float Rotation;

    std::list <SegmentPrototype> OutlinePrototype;

    };

#endif
