#include "graphics-module.hpp"

GraphicsModule::~GraphicsModule ( ) {

    for ( auto Element : Textures ) {

        delete Element.second; }

    for ( auto Element : Fonts ) {

        delete Element.second; }

    delete Config; }

void GraphicsModule::init ( ) {

    std::cout << "Graphic module start" << std::endl; // TODO TEMP

    std::vector <GraphicFile> TextureFiles;
    std::vector <GraphicFile> FontFiles;

    // TODO READ FROM CONFIG

    for ( auto File : TextureFiles ) {

        if ( !ImageBuffer.loadFromFile( File.Path ) ) {

            logError( "Failed to load texture from file '" + File.Path + "'." );

            continue; }

        ImageName = File.Name;
        ImageState = 1;

        while ( ImageState != 2 );

        ImageState = 0; }

    for ( auto File : FontFiles ) {

        auto * FontBuffer = new sf::Font;

        if ( !FontBuffer->loadFromFile( File.Path ) ) {

            logError( "Failed to load font from file '" + File.Path + "'." );

            continue; }

        if ( !Fonts.insert( { File.Name, FontBuffer } ).second ) {

            logError( "Failed to insert font '" + File.Name + "' into hash map." );

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

        logError( "Failed to insert texture '" + ImageName + "' into hash map." ); }

    ImageState = 2; }

sf::Texture * GraphicsModule::getTexture ( std::string Name ) {

    auto Element = Textures.find( Name );

    if ( Element == Textures.end() ) {

        logError( "Texture '" + Name + "' was not found." );

        throw; }

    return Element->second; }

sf::Font * GraphicsModule::getFont ( std::string Name ) {

    auto Element = Fonts.find( Name );

    if ( Element == Fonts.end() ) {

        logError( "Font '" + Name + "' was not found." );

        throw; }

    return Element->second; }