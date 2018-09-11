#include "score-counter.hpp"

ScoreCounter::ScoreCounter ( ) {

    reset(); }

unsigned int ScoreCounter::getScore ( ) {

    return (unsigned int) Score; }

float ScoreCounter::getMultiplier ( ) {

    return Multiplier; }

void ScoreCounter::addMultiplier ( float Multiplier, float Time ) {

    this->Multiplier *= Multiplier;

    if ( Time > 0.f ) {

        Trackers.emplace_back( Tracker ( Multiplier, sf::seconds( Time ) ) ); } }

void ScoreCounter::update ( Event ActiveEvent, float Data ) {

    switch ( ActiveEvent ) {

        case Time: {

            Score += Multiplier * Data * 100.f;

            break; }

        case ShotHit: {

            Score += Multiplier * 1000.f;

            addMultiplier( 1.05f, 5.f );

            break; }

        case ShotDestruction: {

            Score += Multiplier * 10000.f;

            addMultiplier( 2.f, 15.f );

            break; }

        case MissileHit: {

            Score += Multiplier * 5000.f;

            addMultiplier( 1.25f, 10.f );

            break; }

        case MissileDestruction: {

            Score += Multiplier * 15000.f;

            addMultiplier( 3.f, 15.f );

            break; }

        default: {

            break; } } }

void ScoreCounter::update ( sf::Time ElapsedTime ) {

    for ( auto i = Trackers.begin(); i != Trackers.end(); ) {

        i->Time -= ElapsedTime;

        if ( i->Time.asSeconds() <= 0.f ) {

            Multiplier /= i->Multiplier;

            i = Trackers.erase( i ); }

        else {

            ++i; } } }

void ScoreCounter::reset ( ) {

    Score = 0.f;
    Multiplier = 1.f;

    Trackers.clear(); }
