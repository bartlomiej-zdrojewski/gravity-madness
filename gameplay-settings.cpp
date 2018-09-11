#include "gameplay-settings.hpp"

GameplaySettings::~GameplaySettings ( ) {

    for ( unsigned int i = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

        delete PlayerControllerSettingsRegister[i]; } }

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

                    Prototype.Name = Script::getTextValue( NameNode[0] );
                    Prototype.Texture = Script::getTextValue( TextureNode[0] );
                    Prototype.AccentTexture = Script::getTextValue( AccentTextureNode[0] );
                    Prototype.Mass = Script::getRealValue( MassNode[0] );
                    Prototype.Radius = Script::getRealValue( RadiusNode[0] );
                    Prototype.HealthLimit = Script::getRealValue( HealthLimitNode[0] );
                    Prototype.HealthRestoration = Script::getRealValue( HealthRestorationNode[0] );
                    Prototype.EnergyLimit = Script::getRealValue( EnergyLimitNode[0] );
                    Prototype.EnergyRestoration = Script::getRealValue( EnergyRestorationNode[0] );
                    Prototype.Thrust = Script::getRealValue( ThrustNode[0] );
                    Prototype.SuppressingFactor = Script::getRealValue( SuppressingFactorNode[0] );
                    Prototype.ExhaustColor = Script::getColorValue( ExhaustColorNode[0] );
                    Prototype.RayPower = Script::getRealValue( RayPowerNode[0] );
                    Prototype.RayColor = Script::getColorValue( RayColorNode[0] );
                    Prototype.MissileCount = (unsigned int) Script::getIntegerValue( MissileCountNode[0] );
                    Prototype.MissileLimit = (unsigned int) Script::getIntegerValue( MissileLimitNode[0] );
                    Prototype.ScoreMultiplier = Script::getRealValue( ScoreMultiplierNode[0] );

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

    if ( Index < MAXIMUM_PLAYER_COUNT ) {

        if ( Index < SpaceshipAssignment.size() ) {

            return SpaceshipPrototypes[ SpaceshipAssignment[Index] ]; }

        else {

            PrototypeIndex = (unsigned int) ( rand() % SpaceshipPrototypes.size() );

            return SpaceshipPrototypes[ PrototypeIndex ]; } }

    Index -= MAXIMUM_PLAYER_COUNT;

    while ( PrototypeIndex < SpaceshipPrototypes.size() && PrototypeIndex < SpaceshipAssignment.size() ) {

        if ( Index < SpaceshipAssignment[ PrototypeIndex ] ) {

            return SpaceshipPrototypes[ PrototypeIndex ]; }

        Index -= SpaceshipAssignment[ PrototypeIndex ];

        PrototypeIndex++; }

    PrototypeIndex = (unsigned int) ( rand() % SpaceshipPrototypes.size() );

    return SpaceshipPrototypes[ PrototypeIndex ]; }

void GameplaySettings::loadPlayerControllerSettingsRegister ( std::string Config ) {

    for ( unsigned int i = 0; i < MAXIMUM_PLAYER_COUNT; i++ ) {

        PlayerControllerSettingsRegister[i] = new PlayerControllerSettings ( ); }

    unsigned int IndexA = 0;
    std::istringstream DataA ( Config );
    std::string ResultA;

    while ( getline( DataA, ResultA, '|' ) ) {

        if ( IndexA >= MAXIMUM_PLAYER_COUNT ) {

            break; }

        unsigned int IndexB = 0;
        std::istringstream DataB ( ResultA );
        std::string ResultB;

        while ( getline( DataB, ResultB, ',' ) ) {

            if ( IndexB > 6 ) {

                break; }

            switch ( IndexB ) {

                case 0: {

                    if ( ResultB.substr( 0, 9 ) == "JOYSTICK_" ) {

                        PlayerControllerSettingsRegister[IndexA]->setDevice( PlayerControllerSettings::Devices::Joystick );

                        try {

                            PlayerControllerSettingsRegister[IndexA]->setJoystickIdentifier( std::stoi( ResultB.substr( 9, 1 ) ) ); }

                        catch ( ... ) {

                            PlayerControllerSettingsRegister[IndexA]->setJoystickIdentifier( 0 ); } }

                    else {

                        PlayerControllerSettingsRegister[IndexA]->setDevice( PlayerControllerSettings::Devices::Keyboard ); }

                    break; }

                case 1: {

                    PlayerControllerSettingsRegister[IndexA]->setForwardKey( PlayerControllerSettings::decodeKey( ResultB ) );

                    break; }

                case 2: {

                    PlayerControllerSettingsRegister[IndexA]->setBackwardKey( PlayerControllerSettings::decodeKey( ResultB ) );

                    break; }

                case 3: {

                    PlayerControllerSettingsRegister[IndexA]->setLeftKey( PlayerControllerSettings::decodeKey( ResultB ) );

                    break; }

                case 4: {

                    PlayerControllerSettingsRegister[IndexA]->setRightKey( PlayerControllerSettings::decodeKey( ResultB ) );

                    break; }

                case 5: {

                    PlayerControllerSettingsRegister[IndexA]->setRayShotKey( PlayerControllerSettings::decodeKey( ResultB ) );

                    break; }

                case 6: {

                    PlayerControllerSettingsRegister[IndexA]->setMissileShotKey( PlayerControllerSettings::decodeKey( ResultB ) );

                    break; }

                default: {

                    break; } }

            IndexB++; }

        IndexA++; } }

PlayerControllerSettings ** GameplaySettings::getPlayerControllerSettingsRegister ( ) {

    return PlayerControllerSettingsRegister; }

PlayerControllerSettings * GameplaySettings::getPlayerControllerSettings ( unsigned int Index ) {

    if ( Index >= MAXIMUM_PLAYER_COUNT ) {

        return nullptr; }

    return PlayerControllerSettingsRegister[ Index ]; }

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

        case AIPersonalities::Passive: {

            return "Passive"; }

        case AIPersonalities::Reasonable: {

            return "Reasonable"; }

        case AIPersonalities::Aggressive: {

            return "Aggressive"; }

        default: {

            break; } }

    return ""; }

void GameplaySettings::setAIPersonality ( AIPersonalities AIPersonality ) {

    this->AIPersonality = AIPersonality; }

void GameplaySettings::setNextAIPersonality ( ) {

    switch ( AIPersonality ) {

        case AIPersonalities::Random: {

            AIPersonality = AIPersonalities::Passive;

            break; }

        case AIPersonalities::Passive: {

            AIPersonality = AIPersonalities::Reasonable;

            break; }

        case AIPersonalities::Reasonable: {

            AIPersonality = AIPersonalities::Aggressive;

            break; }

        case AIPersonalities::Aggressive: {

            AIPersonality = AIPersonalities::Random;

            break; }

        default: {

            AIPersonality = AIPersonalities::Random;

            break; } } }

void GameplaySettings::setPreviousAIPersonality ( ) {

    switch ( AIPersonality ) {

        case AIPersonalities::Random: {

            AIPersonality = AIPersonalities::Aggressive;

            break; }

        case AIPersonalities::Passive: {

            AIPersonality = AIPersonalities::Random;

            break; }

        case AIPersonalities::Reasonable: {

            AIPersonality = AIPersonalities::Passive;

            break; }

        case AIPersonalities::Aggressive: {

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

ScoreCounter * GameplaySettings::getScores ( ) {

    return Scores; }

unsigned char GameplaySettings::getWinner ( ) {

    return Winner; }

void GameplaySettings::setWinner ( unsigned char Winner ) {

    this->Winner = Winner; }

void GameplaySettings::loadDefaultSpaceshipPrototypes ( ) {

    SpaceshipPrototype Prototype;

    Prototype.Name = "Hercules the Unbroken";
    Prototype.Texture = "Spaceship";
    Prototype.AccentTexture = "SpaceshipAccent";
    Prototype.Mass = 400.f;
    Prototype.Radius = 20.f;
    Prototype.HealthLimit = 200;
    Prototype.HealthRestoration = 2.f;
    Prototype.EnergyLimit = 2500;
    Prototype.EnergyRestoration = 20;
    Prototype.Thrust = 75;
    Prototype.SuppressingFactor = 0.6;
    Prototype.ExhaustColor = sf::Color( 255, 82, 82 );
    Prototype.RayPower = 20;
    Prototype.RayColor = sf::Color( 255, 23, 68 );
    Prototype.MissileCount = 3;
    Prototype.MissileLimit = 3;
    Prototype.ScoreMultiplier = 2.0f;

    SpaceshipPrototypes.push_back( Prototype ); }
