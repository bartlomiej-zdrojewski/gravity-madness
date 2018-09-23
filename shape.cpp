#include "shape.hpp"

Shape::Shape ( ) {

    Rotation = 0.f; }

void Shape::loadOutline ( std::string Config, float Radius ) {

    OutlinePrototype.clear();

    std::vector <sf::Vector2f> Points;
    std::istringstream Data ( Config );
    std::string Result, Begin;

    while ( getline( Data, Result, ',' ) ) {

        if ( Result.empty() ) {

            continue; }

        if ( Result.substr( 0, 1 ) == "(" ) {

            Begin = Result; }

        else if ( !Begin.empty() && !Result.empty() && Result.substr( Result.length() - 1, 1 ) == ")" ) {

            float Module, Angle;

            try {

                Module = std::stof( Begin.substr( 1, Begin.length() - 1 ) );
                Angle = DEG_TO_RAD * std::stof( Result.substr( 0, Result.length() - 1 ) ); }

            catch ( ... ) {

                Module = 0.f;
                Angle = 0.f; }

            Points.emplace_back( Module * Radius, Angle );

            Begin.clear(); }

        else {

            Begin.clear(); } }

    for ( unsigned int i = 0; i < Points.size(); i++ ) {

        SegmentPrototype NewSegment;

        NewSegment.PolarBegin = sf::Vector2f( Points[ i % Points.size() ].x, Points[ i % Points.size() ].y );
        NewSegment.PolarEnd = sf::Vector2f( Points[ ( i + 1 ) % Points.size() ].x, Points[ ( i + 1 ) % Points.size() ].y );

        OutlinePrototype.push_back( NewSegment ); } }

std::list <Shape::Segment> Shape::getOutline ( ) {

    std::list <Segment> Outline;

    for ( SegmentPrototype &MySegment : OutlinePrototype ) {

        sf::Vector2f Begin = Origin + MySegment.PolarBegin.x * sf::Vector2f( cosf( Rotation + MySegment.PolarBegin.y ), sinf( Rotation + MySegment.PolarBegin.y ) );
        sf::Vector2f End = Origin + MySegment.PolarEnd.x * sf::Vector2f( cosf( Rotation + MySegment.PolarEnd.y ), sinf( Rotation + MySegment.PolarEnd.y ) );

        Outline.emplace_back( Begin, End ); }

    return Outline; }

sf::Vector2f Shape::getOrigin ( ) {

    return Origin; }

void Shape::setOrigin ( sf::Vector2f Origin ) {

    this->Origin = Origin; }

float Shape::getRotation ( ) {

    return Rotation; }

void Shape::setRotation ( float Rotation ) {

    this->Rotation = Rotation; }

bool Shape::isIntersecting ( Shape * Other ) {

    auto OtherOutline = Other->getOutline();

    for ( Segment& OtherSegment : OtherOutline ) {

        if ( isIntersecting( { OtherSegment.Begin, OtherSegment.End } ) ) {

            return true; } }

    return false; }

bool Shape::isIntersecting ( sf::Vector2f Center, float Radius ) {

    float Angle = atan2f( Center.y - Origin.y, Center.x - Origin.x ) - 1.5f * PI;
    float AngleStep = PI / 12.f;

    for ( unsigned int i = 0; i < 12; i++ ) { // 50 for the whole planet, 12 for half of it with the half of vertexes

        Segment NewSegment;

        NewSegment.Begin = Center + Radius * sf::Vector2f( cosf( Angle ), sinf( Angle ) );
        NewSegment.End = Center + Radius * sf::Vector2f( cosf( Angle + AngleStep ), sinf( Angle + AngleStep ) );

        if ( isIntersecting( NewSegment ) ) {

            return true; }

        Angle += AngleStep; }

    return false; }

bool Shape::isIntersecting ( Segment OtherSegment ) {

    auto MyOutline = getOutline();

    for ( Segment& MySegment : MyOutline ) {

        if ( isIntersecting( { MySegment.Begin, MySegment.End }, OtherSegment ) ) {

            return true; } }

    return false; }

bool Shape::isIntersecting ( sf::Vector2f Begin, sf::Vector2f End ) {

    return isIntersecting( { Begin, End } ); }

bool Shape::getIntersection ( sf::Vector2f Begin, sf::Vector2f End, sf::Vector2f &Intersection, float &Distance ) {

    auto MyOutline = getOutline();
    float MinimumDistance = ALMOST_INFINITY;

    for ( Segment& MySegment : MyOutline ) {

        if ( isIntersecting( { MySegment.Begin, MySegment.End }, { Begin, End } ) ) {

            if ( ( MySegment.Begin.x - MySegment.End.x ) == 0.f ) {

                MySegment.Begin.x += ALMOST_ZERO; }
            
            float a1 = ( MySegment.Begin.y - MySegment.End.y ) / ( MySegment.Begin.x - MySegment.End.x );
            float b1 = MySegment.Begin.y - a1 * MySegment.Begin.x;
            
            if ( ( Begin.x - End.x ) == 0.f ) {

                Begin.x += ALMOST_ZERO; }

            float a2 = ( Begin.y - End.y ) / ( Begin.x - End.x );
            float b2 = Begin.y - a2 * Begin.x;

            if ( ( a1 - a2 ) == 0.f ) {

                a1 += ALMOST_ZERO; }

            float x = ( b2 - b1 ) / ( a1 - a2 );
            float y = a1 * Intersection.x + b1;
            float d = fminf( sqrtf( powf( x - Begin.x, 2.f ) + powf( y - Begin.y, 2.f ) ), sqrtf( powf( x - End.x, 2.f ) + powf( y - End.y, 2.f ) ) );

            if ( d < MinimumDistance ) {

                MinimumDistance = d;

                Intersection.x = x;
                Intersection.y = y;
                Distance = MinimumDistance; } } }

    if ( MinimumDistance < ALMOST_INFINITY ) {

        return true; }

    return false; }

float Shape::getDeterminant ( sf::Vector2f A, sf::Vector2f B, sf::Vector2f C ) {

    return A.x * B.y + B.x * C.y + C.x * A.y - C.x * B.y - C.y * A.x - A.y * B.x; }

bool Shape::isIntersecting ( Segment A, Segment B ) { // Skipping edge cases

    if ( getDeterminant( A.Begin, A.End, B.Begin ) * getDeterminant( A.Begin, A.End, B.End ) >= 0.f ) {

        return false; }

    if ( getDeterminant( B.Begin, B.End, A.Begin ) * getDeterminant( B.Begin, B.End, A.End ) >= 0.f ) {

        return false; }

    return true; }
