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

    std::vector <GraphicFile> TextureFiles;
    std::vector <GraphicFile> FontFiles;

    pugi::xml_node * Root = Config->getRoot();

    if ( Root ) {

        auto GraphicsNode = Config->getChildren( *Root, "Graphics" );

        if ( !GraphicsNode.empty() ) {

            if ( GraphicsNode.size() > 1 ) {

                logWarning( "Graphics module config script has unexpected structure, 'Graphics' node is not unique." ); }

            auto TexturesNode = Config->getChildren( GraphicsNode[0], "Textures" );

            if ( !TexturesNode.empty() ) {

                if ( TexturesNode.size() > 1 ) {

                    logWarning( "Graphics module config script has unexpected structure, 'Graphics/Textures' node is not unique." ); }

                auto PrePathNode = Config->getChildren( TexturesNode[0], "Path" );
                auto TextureNodes = Config->getChildren( TexturesNode[0], "Texture" );

                if ( !PrePathNode.empty() ) {

                    if ( PrePathNode.size() > 1 ) {

                        logWarning( "Graphics module config script has unexpected structure, 'Graphics/Textures/Path' node is not unique." ); }

                    std::string PrePath = Config->getTextValue( PrePathNode[0] );

                    if ( !TextureNodes.empty() ) {

                        for ( auto TextureNode : TextureNodes ) {

                            auto NameNode = Config->getChildren( TextureNode, "Name" );
                            auto PathNode = Config->getChildren( TextureNode, "Path" );

                            if ( !NameNode.empty() && !PathNode.empty() ) {

                                GraphicFile File;

                                std::string Name = Config->getTextValue( NameNode[0] );
                                std::string Path = Config->getTextValue( PathNode[0] );

                                for ( size_t i = 0; i < Name.size(); i++ ) {

                                    Name[i] = (char) tolower( Name[i] ); }

                                File.Name = Name;
                                File.Path = PrePath + Path;

                                TextureFiles.push_back( File ); }

                            else {

                                if ( NameNode.empty() ) {

                                    logError( "Graphics module config script is corrupted, 'Graphics/Textures/Texture/Name' node was not found!" ); }

                                if ( PathNode.empty() ) {

                                    logError( "Graphics module config script is corrupted, 'Graphics/Textures/Texture/Path' node was not found!" ); } } } }

                    else {

                        logWarning( "Graphics module config script has unexpected structure, not single 'Graphics/Textures/Texture' node was found." ); } }

                else {

                    logError( "Graphics module config script is corrupted, 'Graphics/Textures/Path' node was not found!" ); } }

            else {

                logError( "Graphics module config script is corrupted, 'Graphics/Textures' node was not found!" ); }

            auto FontContainerNode = Config->getChildren( GraphicsNode[0], "Fonts" );

            if ( !FontContainerNode.empty() ) {

                if ( FontContainerNode.size() > 1 ) {

                    logWarning( "Graphics module config script has unexpected structure, 'Graphics/Fonts' node is not unique." ); }

                auto PrePathNode = Config->getChildren( FontContainerNode[0], "Path" );
                auto FontNodes = Config->getChildren( FontContainerNode[0], "Font" );

                if ( !PrePathNode.empty() ) {

                    if ( PrePathNode.size() > 1 ) {

                        logWarning( "Graphics module config script has unexpected structure, 'Graphics/Fonts/Path' node is not unique." ); }

                    std::string PrePath = Config->getTextValue( PrePathNode[0] );

                    if ( !FontNodes.empty() ) {

                        for ( auto FontNode : FontNodes ) {

                            auto NameNode = Config->getChildren( FontNode, "Name" );
                            auto PathNode = Config->getChildren( FontNode, "Path" );

                            if ( !NameNode.empty() && !PathNode.empty() ) {

                                GraphicFile File;

                                std::string Name = Config->getTextValue( NameNode[0] );
                                std::string Path = Config->getTextValue( PathNode[0] );

                                for ( size_t i = 0; i < Name.size(); i++ ) {

                                    Name[i] = (char) tolower( Name[i] ); }

                                File.Name = Name;
                                File.Path = PrePath + Path;

                                FontFiles.push_back( File ); }

                            else {

                                if ( NameNode.empty() ) {

                                    logError( "Graphics module config script is corrupted, 'Graphics/Fonts/Font/Name' node was not found!" ); }

                                if ( PathNode.empty() ) {

                                    logError( "Graphics module config script is corrupted, 'Graphics/Fonts/Font/Path' node was not found!" ); } } } }

                    else {

                        logWarning( "Graphics module config script has unexpected structure, not single 'Graphics/Fonts/Font' node was found." ); } }

                else {

                    logError( "Graphics module config script is corrupted, 'Graphics/Fonts/Path' node was not found!" ); } }

            else {

                logError( "Graphics module config script is corrupted, 'Graphics/Fonts' node was not found!" ); } }

        else {

            logError( "Graphics module config script is corrupted, 'Graphics' node was not found!" ); } }

    else {

        logError( "Failed to load graphics module config script!" ); }

    for ( auto File : TextureFiles ) {

        if ( !ImageBuffer.loadFromFile( File.Path ) ) {

            logError( "Failed to load texture from '" + File.Path + " file'!" );

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

    (*InitState)++; }

void GraphicsModule::initContext ( ) {

    if ( ImageState != 1 ) {

        return; }

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

sf::Texture& GraphicsModule::getTexture ( std::string Name ) {

    for ( size_t i = 0; i < Name.size(); i++ ) {

        Name[i] = (char) tolower( Name[i] ); }

    auto Element = Textures.find( Name );

    if ( Element == Textures.end() ) {

        logError( "Texture '" + Name + "' was not found!" );

        return getTexture( "Default" ); }

    return *Element->second; }

sf::Font& GraphicsModule::getFont ( std::string Name ) {

    for ( size_t i = 0; i < Name.size(); i++ ) {

        Name[i] = (char) tolower( Name[i] ); }

    auto Element = Fonts.find( Name );

    if ( Element == Fonts.end() ) {

        logError( "Font '" + Name + "' was not found!" );

        return getFont( "Default" ); }

    return *Element->second; }

void GraphicsModule::initDefault ( ) { // TODO Load from memory

    Textures.insert( { "Default", new sf::Texture () } );
    Fonts.insert( { "Default", new sf::Font () } );

    }