#include "gameplay-settings.hpp"

GameplaySettings::GameplaySettings ( ) {

    Score = nullptr; }

GameplaySettings::~GameplaySettings ( ) {

    delete Score; }

void GameplaySettings::loadSpaceshipPrototypes ( Script * Config ) {

    // TODO

    }

void GameplaySettings::assignSpaceshipPrototypes ( std::vector <int> SpaceshipPrototypesAssignment ) {

    this->SpaceshipPrototypesAssignment = SpaceshipPrototypesAssignment; }

std::vector <GameplaySettings::SpaceshipPrototype> GameplaySettings::getSpaceshipPrototypes ( ) {

    return SpaceshipPrototypes; }

GameplaySettings::SpaceshipPrototype GameplaySettings::getSpaceshipPrototype ( unsigned int Index ) {

    unsigned int PrototypeIndex = 0;

    while ( PrototypeIndex < SpaceshipPrototypes.size() && PrototypeIndex < SpaceshipPrototypesAssignment.size() ) {

        if ( Index < SpaceshipPrototypesAssignment[ PrototypeIndex ] ) {

            return SpaceshipPrototypes[ PrototypeIndex ]; }

        Index -= SpaceshipPrototypesAssignment[ PrototypeIndex ];

        PrototypeIndex++; }

    PrototypeIndex = (unsigned int) ( rand() % SpaceshipPrototypes.size() );

    return SpaceshipPrototypes[ PrototypeIndex ]; }

float GameplaySettings::getAreaSize ( ) {

    return AreaSize; }

void GameplaySettings::setAreaSize ( AreaSizes AreaSize ) {

    this->AreaSize = AreaSize; }

unsigned int GameplaySettings::getAsteroidCount ( ) {

    return AsteroidCount; }

void GameplaySettings::setAsteroidCount ( unsigned int AsteroidCount ) {

    this->AsteroidCount = AsteroidCount; }

unsigned int GameplaySettings::getSpaceshipCount ( ) {

    return SpaceshipCount; }

void GameplaySettings::setSpaceshipCount ( unsigned int SpaceshipCount ) {

    this->SpaceshipCount = SpaceshipCount; }

unsigned int GameplaySettings::getPlayerCount ( ) {

    return PlayerCount; }

void GameplaySettings::setPlayerCount ( unsigned int PlayerCount ) {

    this->PlayerCount = PlayerCount; }

GameplaySettings::AIPersonalities GameplaySettings::getAIPersonality ( ) {

    return AIPersonality; }

void GameplaySettings::setAIPersonality ( AIPersonalities AIPersonality ) {

    this->AIPersonality = AIPersonality; }

GameplaySettings::EndingConditions GameplaySettings::getEndingCondition ( ) {

    return EndingCondition; }

void GameplaySettings::setEndingCondition ( EndingConditions EndingCondition ) {

    this->EndingCondition = EndingCondition; }

unsigned int * GameplaySettings::getScore ( ) {

    return Score; }

void GameplaySettings::setScore ( unsigned int * Score ) {

    this->Score = Score; }
