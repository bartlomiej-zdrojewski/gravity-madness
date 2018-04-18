#include "graphics-module.hpp"

GraphicsModule::~GraphicsModule ( ) {

    for ( auto Element : Textures ) {

        delete Element.second; }

    for ( auto Element : Fonts ) {

        delete Element.second; }

    delete Config; }

void GraphicsModule::init ( ) {

    if ( !Config ) {

        logError( "Failed to load graphics module config script!" );
        (*InitState)++;

        return; }

    std::cout << "Graphic module start" << std::endl; // TODO TEMP

    std::vector <GraphicFile> TextureFiles;
    std::vector <GraphicFile> FontFiles;

    pugi::xml_node * Root = Config->getRoot();

    if ( Root ) {

        std::vector <pugi::xml_node*> TextureContainerNode = Config->getChildren( Root, "Textures" );

        if ( !TextureContainerNode.empty() ) {

            if ( TextureContainerNode.size() > 1 ) {

                logWarning( "Graphics module config script has unexpected structure, 'Textures' node is not unique." ); }

            std::vector <pugi::xml_node*> PathNode = Config->getChildren( Root, "Path" );
            std::vector <pugi::xml_node*> TextureNodes = Config->getChildren( Root, "Texture" );

            if ( !PathNode.empty() ) {

                if ( PathNode.size() > 1 ) {

                    logWarning( "Graphics module config script has unexpected structure, 'Textures/Path' node is not unique." ); }

                std::string Path = Config->getTextValue( PathNode[0] );

                if ( !TextureNodes.empty() ) {

                    for ( auto TextureNode : TextureNodes ) {

                        GraphicFile File;
                        
                        File.Name = Config->getTextValue( Config->getChildren( TextureNode, "Name" )[0] );
                        File.Path = Path + Config->getTextValue( Config->getChildren( TextureNode, "Path" )[0] );
                        
                        TextureFiles.push_back( File ); } }

                else {

                    logWarning( "Graphics module config script has unexpected structure, not single 'Textures/Texture' node was found." ); } }

            else {

                logError( "Graphics module config script is damaged, 'Textures/Path' node was not found!" ); } }

        else {

            logError( "Graphics module config script is damaged, 'Textures' node was not found!" ); }

        std::vector <pugi::xml_node*> FontContainerNode = Config->getChildren( Root, "Fonts" );

        if ( !FontContainerNode.empty() ) {

            if ( FontContainerNode.size() > 1 ) {

                logWarning( "Graphics module config script has unexpected structure, 'Fonts' node is not unique." ); }

            std::vector <pugi::xml_node*> PathNode = Config->getChildren( Root, "Path" );
            std::vector <pugi::xml_node*> FontNodes = Config->getChildren( Root, "Font" );

            if ( !PathNode.empty() ) {

                if ( PathNode.size() > 1 ) {

                    logWarning( "Graphics module config script has unexpected structure, 'Fonts/Path' node is not unique." ); }

                std::string Path = Config->getTextValue( PathNode[0] );

                if ( !FontNodes.empty() ) {

                    for ( auto FontNode : FontNodes ) {

                        GraphicFile File;

                        File.Name = Config->getTextValue( Config->getChildren( FontNode, "Name" )[0] );
                        File.Path = Path + Config->getTextValue( Config->getChildren( FontNode, "Path" )[0] );

                        FontFiles.push_back( File ); } }

                else {

                    logWarning( "Graphics module config script has unexpected structure, not single 'Fonts/Font' node was found." ); } }

            else {

                logError( "Graphics module config script is damaged, 'Fonts/Path' node was not found!" ); } }

        else {

            logError( "Graphics module config script is damaged, 'Fonts' node was not found!" ); } }

    else {

        logError( "Failed to load graphics module config script!" ); }

    for ( auto File : TextureFiles ) {

        if ( !ImageBuffer.loadFromFile( File.Path ) ) {

            logError( "Failed to load texture from file '" + File.Path + "'!" );

            continue; }

        ImageName = File.Name;
        ImageState = 1;

        while ( ImageState != 2 );

        ImageState = 0; }

    for ( auto File : FontFiles ) {

        auto * FontBuffer = new sf::Font;

        if ( !FontBuffer->loadFromFile( File.Path ) ) {

            logError( "Failed to load font from '" + File.Path + "' file!" );

            continue; }

        if ( !Fonts.insert( { File.Name, FontBuffer } ).second ) {

            logError( "Failed to insert '" + File.Name + "' font into hash map!" );

            continue; } }

    ImageBuffer.create( 0, 0 );

    std::cout << "Graphic module stop" << std::endl; // TODO TEMP

    (*InitState)++; }

void GraphicsModule::initContext ( ) {

    if ( ImageState != 1 ) {

        return; }

    std::cout << "Init context" << std::endl; // TODO TEMP

    auto * Texture = new sf::Texture;

    Texture->loadFromImage( ImageBuffer );
    Texture->setSmooth( true );

    if ( !Textures.insert( { ImageName, Texture } ).second ) {

        logError( "Failed to insert '" + ImageName + "' texture into hash map!" ); }

    ImageState = 2; }

unsigned int GraphicsModule::getWindowWidth ( ) {

    return WindowWidth; }

unsigned int GraphicsModule::getWindowHeight ( ) {

    return WindowHeight; }

void GraphicsModule::setWindowSize ( unsigned int Width, unsigned int Height ) {

    WindowWidth = Width;
    WindowHeight = Height; }

bool GraphicsModule::isFullScreenEnabled ( ) {

    return FullScreen; }

void GraphicsModule::enableFullScreen ( ) {

    FullScreen = true; }

void GraphicsModule::disableFullScreen ( ) {

    FullScreen = false; }

sf::Texture * GraphicsModule::getTexture ( std::string Name ) {

    auto Element = Textures.find( Name );

    if ( Element == Textures.end() ) {

        logError( "Texture '" + Name + "' was not found!" );

        return getTexture( "Default" ); }

    return Element->second; }

sf::Font * GraphicsModule::getFont ( std::string Name ) {

    auto Element = Fonts.find( Name );

    if ( Element == Fonts.end() ) {

        logError( "Font '" + Name + "' was not found!" );

        return getFont( "Default" ); }

    return Element->second; }

void GraphicsModule::initDefault ( ) { // TODO Load from memory

    Textures.insert( { "Default", new sf::Texture () } );
    Fonts.insert( { "Default", new sf::Font () } );

    }