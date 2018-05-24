#include <iostream>
#include "gameplay-settings.hpp"

GameplaySettings::~GameplaySettings ( ) {

    delete Score; }

void GameplaySettings::loadSpaceshipPrototypes ( Script * Config ) {

    if ( !Config ) {

        logWarning( "Failed to load spaceships config script!" );

        return; }

    pugi::xml_node * Root = Config->getRoot();

    if ( Root ) {

        auto SpaceshipsNode = Config->getChildren( *Root, "Spaceships" );

        if ( !SpaceshipsNode.empty() ) {

            if ( SpaceshipsNode.size() > 1 ) {

                logWarning( "Spaceships config script has unexpected structure, 'Spaceships' node is not unique." ); }

            auto SpaceshipNodes = Config->getChildren( SpaceshipsNode[0], "Spaceship" );

            if ( !SpaceshipNodes.empty() ) {

                for ( auto SpaceshipNode : SpaceshipNodes ) {

                    auto NameNode = Config->getChildren( SpaceshipNode, "Name" );
                    auto TextureNode = Config->getChildren( SpaceshipNode, "Texture" );
                    auto AccentTextureNode = Config->getChildren( SpaceshipNode, "AccentTexture" );
                    auto MassNode = Config->getChildren( SpaceshipNode, "Mass" );
                    auto RadiusNode = Config->getChildren( SpaceshipNode, "Radius" );
                    auto HealthLimitNode = Config->getChildren( SpaceshipNode, "HealthLimit" );
                    auto HealthRestorationNode = Config->getChildren( SpaceshipNode, "HealthRestoration" );
                    auto EnergyLimitNode = Config->getChildren( SpaceshipNode, "EnergyLimit" );
                    auto EnergyRestorationNode = Config->getChildren( SpaceshipNode, "EnergyRestoration" );
                    auto ThrustNode = Config->getChildren( SpaceshipNode, "Thrust" );
                    auto SuppressingFactorNode = Config->getChildren( SpaceshipNode, "SuppressingFactor" );
                    auto ExhaustColorNode = Config->getChildren( SpaceshipNode, "ExhaustColor" );
                    auto RayPowerNode = Config->getChildren( SpaceshipNode, "RayPower" );
                    auto RayColorNode = Config->getChildren( SpaceshipNode, "RayColor" );
                    auto MissileCountNode = Config->getChildren( SpaceshipNode, "MissileCount" );
                    auto MissileLimitNode = Config->getChildren( SpaceshipNode, "MissileLimit" );
                    auto ScoreMultiplierNode = Config->getChildren( SpaceshipNode, "ScoreMultiplier" );

                    const unsigned int NodesCount = 17;
                    std::vector <pugi::xml_node> * Nodes [NodesCount] = { &NameNode, &TextureNode, &AccentTextureNode,
                        &MassNode, &RadiusNode, &HealthLimitNode, &HealthRestorationNode, &EnergyLimitNode, &EnergyRestorationNode,
                        &ThrustNode, &SuppressingFactorNode, &ExhaustColorNode, &RayPowerNode, &RayColorNode, &MissileCountNode,
                        &MissileLimitNode, &ScoreMultiplierNode };
                    std::string NodeNames [NodesCount] = { "Name", "Texture", "AccentTexture", "Mass", "Radius", "HealthLimit",
                        "HealthRestoration", "EnergyLimit", "EnergyRestoration", "Thrust", "SuppressingFactor", "ExhaustColor",
                        "RayPower", "RayColor", "MissileCount", "MissileLimit", "ScoreMultiplier" };

                    bool Skip = false;

                    for ( unsigned int i = 0; i < NodesCount; i++ ) {

                        if ( Nodes[i]->empty() ) {

                            logWarning( "Spaceships config script is corrupted, 'Spaceships/Spaceship/" + NodeNames[i] + "' node was not found!" );

                            Skip = true;

                            break; } }

                    if ( Skip ) {

                        continue; }

                    SpaceshipPrototype Prototype;

                    Prototype.Name = Config->getTextValue( NameNode[0] );
                    Prototype.Texture = Config->getTextValue( TextureNode[0] );
                    Prototype.AccentTexture = Config->getTextValue( AccentTextureNode[0] );
                    Prototype.Mass = Config->getRealValue( MassNode[0] );
                    Prototype.Radius = Config->getRealValue( RadiusNode[0] );
                    Prototype.HealthLimit = Config->getRealValue( HealthLimitNode[0] );
                    Prototype.HealthRestoration = Config->getRealValue( HealthRestorationNode[0] );
                    Prototype.EnergyLimit = Config->getRealValue( EnergyLimitNode[0] );
                    Prototype.EnergyRestoration = Config->getRealValue( EnergyRestorationNode[0] );
                    Prototype.Thrust = Config->getRealValue( ThrustNode[0] );
                    Prototype.SuppressingFactor = Config->getRealValue( SuppressingFactorNode[0] );
                    Prototype.ExhaustColor = Config->getColorValue( ExhaustColorNode[0] );
                    Prototype.RayPower = Config->getRealValue( RayPowerNode[0] );
                    Prototype.RayColor = Config->getColorValue( RayColorNode[0] );
                    Prototype.MissileCount = (unsigned int) Config->getIntegerValue( MissileCountNode[0] );
                    Prototype.MissileLimit = (unsigned int) Config->getIntegerValue( MissileLimitNode[0] );
                    Prototype.ScoreMultiplier = Config->getRealValue( ScoreMultiplierNode[0] );

                    SpaceshipPrototypes.insert( SpaceshipPrototypes.begin(), Prototype ); } }

            else {

                logWarning( "Spaceships config script has unexpected structure, not single 'Spaceships/Spaceship' node was found." ); } }

        else {

            logWarning( "Spaceships config script is corrupted, 'Spaceships' node was not found!" ); } }

    else {

        logWarning( "Failed to load spaceships config script!" ); } }

void GameplaySettings::assignSpaceships ( std::vector <int> SpaceshipAssignment ) {

    this->SpaceshipAssignment = std::move( SpaceshipAssignment ); }

std::vector <GameplaySettings::SpaceshipPrototype> GameplaySettings::getSpaceshipPrototypes ( ) {

    return SpaceshipPrototypes; }

GameplaySettings::SpaceshipPrototype GameplaySettings::getSpaceshipPrototype ( unsigned int Index ) {

    unsigned int PrototypeIndex = 0;

    if ( Index < MaximumPlayerCount ) {

        if ( Index < SpaceshipAssignment.size() ) {

            return SpaceshipPrototypes[ SpaceshipAssignment[Index] ]; }

        else {

            PrototypeIndex = (unsigned int) ( rand() % SpaceshipPrototypes.size() );

            return SpaceshipPrototypes[ PrototypeIndex ]; } }

    Index -= MaximumPlayerCount;

    while ( PrototypeIndex < SpaceshipPrototypes.size() && PrototypeIndex < SpaceshipAssignment.size() ) {

        if ( Index < SpaceshipAssignment[ PrototypeIndex ] ) {

            return SpaceshipPrototypes[ PrototypeIndex ]; }

        Index -= SpaceshipAssignment[ PrototypeIndex ];

        PrototypeIndex++; }

    PrototypeIndex = (unsigned int) ( rand() % SpaceshipPrototypes.size() );

    return SpaceshipPrototypes[ PrototypeIndex ]; }

float GameplaySettings::getAreaSize ( ) {

    return AreaSize; }

std::string GameplaySettings::getAreaSizeText ( ) {

    switch ( AreaSize ) {

        case AreaSizes::Tiny: {

            return "Tiny"; }

        case AreaSizes::Small: {

            return "Small"; }

        case AreaSizes::Medium: {

            return "Medium"; }

        case AreaSizes::Big: {

            return "Big"; }

        case AreaSizes::Huge: {

            return "Huge"; }

        default: {

            break; } }

    return ""; }

void GameplaySettings::setAreaSize ( AreaSizes AreaSize ) {

    this->AreaSize = AreaSize; }

void GameplaySettings::setNextAreaSize ( ) {

    switch ( AreaSize ) {

        case AreaSizes::Tiny: {

            AreaSize = AreaSizes::Small;

            break; }

        case AreaSizes::Small: {

            AreaSize = AreaSizes::Medium;

            break; }

        case AreaSizes::Medium: {

            AreaSize = AreaSizes::Big;

            break; }

        case AreaSizes::Big: {

            AreaSize = AreaSizes::Huge;

            break; }

        case AreaSizes::Huge: {

            AreaSize = AreaSizes::Tiny;

            break; }

        default: {

            AreaSize = AreaSizes::Medium;

            break; } } }

void GameplaySettings::setPreviousAreaSize ( ) {

    switch ( AreaSize ) {

        case AreaSizes::Tiny: {

            AreaSize = AreaSizes::Huge;

            break; }

        case AreaSizes::Small: {

            AreaSize = AreaSizes::Tiny;

            break; }

        case AreaSizes::Medium: {

            AreaSize = AreaSizes::Small;

            break; }

        case AreaSizes::Big: {

            AreaSize = AreaSizes::Medium;

            break; }

        case AreaSizes::Huge: {

            AreaSize = AreaSizes::Big;

            break; }

        default: {

            AreaSize = AreaSizes::Medium;

            break; } } }

GameplaySettings::AsteroidFrequencies GameplaySettings::getAsteroidFrequency ( ) {

    return AsteroidFrequency; }

std::string GameplaySettings::getAsteroidFrequencyText ( ) {

    switch ( AsteroidFrequency ) {

        case AsteroidFrequencies::Rarely: {

            return "Rarely"; }

        case AsteroidFrequencies::Occasionally: {

            return "Occasionally"; }

        case AsteroidFrequencies::Often: {

            return "Often"; }

        default: {

            break; } }

    return ""; }

void GameplaySettings::setAsteroidFrequency ( AsteroidFrequencies AsteroidFrequency ) {

    this->AsteroidFrequency = AsteroidFrequency; }

void GameplaySettings::setNextAsteroidFrequency ( ) {

    switch ( AsteroidFrequency ) {

        case AsteroidFrequencies::Rarely: {

            AsteroidFrequency = AsteroidFrequencies::Occasionally;

            break; }

        case AsteroidFrequencies::Occasionally: {

            AsteroidFrequency = AsteroidFrequencies::Often;

            break; }

        case AsteroidFrequencies::Often: {

            AsteroidFrequency = AsteroidFrequencies::Rarely;

            break; }

        default: {

            AsteroidFrequency = AsteroidFrequencies::Occasionally;

            break; } } }

void GameplaySettings::setPreviousAsteroidFrequency ( ) {

    switch ( AsteroidFrequency ) {

        case AsteroidFrequencies::Rarely: {

            AsteroidFrequency = AsteroidFrequencies::Often;

            break; }

        case AsteroidFrequencies::Occasionally: {

            AsteroidFrequency = AsteroidFrequencies::Rarely;

            break; }

        case AsteroidFrequencies::Often: {

            AsteroidFrequency = AsteroidFrequencies::Occasionally;

            break; }

        default: {

            AsteroidFrequency = AsteroidFrequencies::Occasionally;

            break; } } }

unsigned int GameplaySettings::getMaximumPlayerCount ( ) {

    return MaximumPlayerCount; }

unsigned int GameplaySettings::getPlayerCount ( ) {

    return PlayerCount; }

void GameplaySettings::setPlayerCount ( unsigned int PlayerCount ) {

    this->PlayerCount = PlayerCount; }

unsigned int GameplaySettings::getSpaceshipCount ( ) {

    return SpaceshipCount; }

void GameplaySettings::setSpaceshipCount ( unsigned int SpaceshipCount ) {

    this->SpaceshipCount = SpaceshipCount; }

GameplaySettings::AIPersonalities GameplaySettings::getAIPersonality ( ) {

    return AIPersonality; }

std::string GameplaySettings::getAIPersonalityText ( ) {

    switch ( AIPersonality ) {

        case AIPersonalities::Random: {

            return "Random"; }

        case AIPersonalities::Aggressive: {

            return "Aggressive"; }

        case AIPersonalities::Reasonable: {

            return "Reasonable"; }

        case AIPersonalities::Passive: {

            return "Passive"; }

        default: {

            break; } }

    return ""; }

void GameplaySettings::setAIPersonality ( AIPersonalities AIPersonality ) {

    this->AIPersonality = AIPersonality; }

void GameplaySettings::setNextAIPersonality ( ) {

    switch ( AIPersonality ) {

        case AIPersonalities::Random: {

            AIPersonality = AIPersonalities::Aggressive;

            break; }

        case AIPersonalities::Aggressive: {

            AIPersonality = AIPersonalities::Reasonable;

            break; }

        case AIPersonalities::Reasonable: {

            AIPersonality = AIPersonalities::Passive;

            break; }

        case AIPersonalities::Passive: {

            AIPersonality = AIPersonalities::Random;

            break; }

        default: {

            AIPersonality = AIPersonalities::Random;

            break; } } }

void GameplaySettings::setPreviousAIPersonality ( ) {

    switch ( AIPersonality ) {

        case AIPersonalities::Random: {

            AIPersonality = AIPersonalities::Passive;

            break; }

        case AIPersonalities::Aggressive: {

            AIPersonality = AIPersonalities::Random;

            break; }

        case AIPersonalities::Reasonable: {

            AIPersonality = AIPersonalities::Aggressive;

            break; }

        case AIPersonalities::Passive: {

            AIPersonality = AIPersonalities::Reasonable;

            break; }

        default: {

            AIPersonality = AIPersonalities::Random;

            break; } } }

GameplaySettings::EndingConditions GameplaySettings::getEndingCondition ( ) {

    return EndingCondition; }

std::string GameplaySettings::getEndingConditionText ( ) {

    switch ( EndingCondition ) {

        case EndingConditions::Time: {

            return "Survive for certain time"; }

        case EndingConditions::NoEnemies: {

            return "Destroy all enemies"; }

        case EndingConditions::LastPlayer: {

            return "Destroy all players"; }

        case EndingConditions::LastSpaceship: {

            return "Destroy all spaceships"; }

        default: {

            break; } }

    return ""; }

void GameplaySettings::setEndingCondition ( EndingConditions EndingCondition ) {

    this->EndingCondition = EndingCondition; }

void GameplaySettings::setNextEndingCondition ( ) {

    switch ( EndingCondition ) {

        case EndingConditions::Time: {

            EndingCondition = EndingConditions::NoEnemies;

            break; }

        case EndingConditions::NoEnemies: {

            EndingCondition = EndingConditions::LastPlayer;

            break; }

        case EndingConditions::LastPlayer: {

            EndingCondition = EndingConditions::LastSpaceship;

            break; }

        case EndingConditions::LastSpaceship: {

            EndingCondition = EndingConditions::Time;

            break; }

        default: {

            EndingCondition = EndingConditions::NoEnemies;

            break; } } }

void GameplaySettings::setPreviousEndingCondition ( ) {

    switch ( EndingCondition ) {

        case EndingConditions::Time: {

            EndingCondition = EndingConditions::LastSpaceship;

            break; }

        case EndingConditions::NoEnemies: {

            EndingCondition = EndingConditions::Time;

            break; }

        case EndingConditions::LastPlayer: {

            EndingCondition = EndingConditions::NoEnemies;

            break; }

        case EndingConditions::LastSpaceship: {

            EndingCondition = EndingConditions::LastPlayer;

            break; }

        default: {

            EndingCondition = EndingConditions::NoEnemies;

            break; } } }

sf::Time GameplaySettings::getTimeLimit ( ) {

    return TimeLimit; }

void GameplaySettings::setTimeLimit ( sf::Time TimeLimit ) {

    this->TimeLimit = TimeLimit; }

unsigned int * GameplaySettings::getScore ( ) {

    return Score; }

void GameplaySettings::setScore ( unsigned int * Score ) {

    this->Score = Score; }

int GameplaySettings::getWinner ( ) {

    return Winner; }

void GameplaySettings::setWinner ( int Winner ) {

    this->Winner = Winner; }

void GameplaySettings::loadDefaultSpaceshipPrototypes ( ) {

    SpaceshipPrototype Prototype;

    Prototype.Name = "Hercules the Unbroken";
    Prototype.Texture = "default";
    Prototype.AccentTexture = "default";
    Prototype.Mass = 4.f;
    Prototype.Radius = 20.f;
    Prototype.HealthLimit = 200;
    Prototype.HealthRestoration = 2.f;
    Prototype.EnergyLimit = 2500;
    Prototype.EnergyRestoration = 20;
    Prototype.Thrust = 75;
    Prototype.SuppressingFactor = 0.6;
    Prototype.ExhaustColor = sf::Color::Blue;
    Prototype.RayPower = 20;
    Prototype.RayColor = sf::Color::Red;
    Prototype.MissileCount = 3;
    Prototype.MissileLimit = 3;
    Prototype.ScoreMultiplier = 2.0f;

    SpaceshipPrototypes.push_back( Prototype ); }
