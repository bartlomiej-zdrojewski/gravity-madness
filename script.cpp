#include "script.hpp"

Script::Script ( std::string FilePath ) {

    this->FilePath = FilePath;
    Document = new pugi::xml_document;

    if ( !Document->load_file( FilePath.c_str() ) ) {

        delete Document;
        Document = nullptr; } }

Script::~Script ( ) { // Document can't be deleted

    if ( Document ) {

        Document->reset(); } }

std::string Script::getFilePath ( ) {

    return FilePath; }

bool Script::saveToFile ( std::string FilePath ) {

    if ( !Document ) {

        return false; }

    if ( FilePath.empty() ) {

        FilePath = this->FilePath; }

    return Document->save_file( FilePath.c_str() ); }

pugi::xml_node * Script::getRoot ( ) {

    return Document; }

std::vector <pugi::xml_node> Script::getChildren ( pugi::xml_node Node, std::string Filter ) {

    if ( !Node ) {

        return std::vector <pugi::xml_node> ();}

    std::vector <pugi::xml_node> Children;

    for ( auto Child : Node.children() ) {

        if ( Filter.empty() || Filter == std::string( Child.name() ) ) {

            Children.push_back( Child ); } }

    return Children; }

std::string Script::getTextValue ( pugi::xml_node Node ) {

    return Node.text().get(); }

bool Script::getBooleanValue ( pugi::xml_node Node ) {

    std::string Value = Node.text().get();

    for ( size_t i = 0; i < Value.size(); i++ ) {

        Value[i] = (char) tolower( Value[i] ); }

    return Value == "true"; }

int Script::getIntegerValue ( pugi::xml_node Node ) {

    int Value;

    try {

        Value = std::stoi( Node.text().get() ); }

    catch ( ... ) {

        Value = 0; }

    return Value; }

float Script::getRealValue ( pugi::xml_node Node ) {

    float Value;

    try {

        Value = std::stof( Node.text().get() ); }

    catch ( ... ) {

        Value = 0.f; }

    return Value; }

sf::Color Script::getColorValue ( pugi::xml_node Node ) {

    int Red, Green, Blue, Alpha;
    std::string Text = Node.text().get();

    if ( Text.size() != 7 && Text.size() != 9 ) {

        return { 0, 0, 0, 0 }; }

    try {

        Red = std::stoi( Text.substr( 1, 2 ), nullptr, 16 );
        Green = std::stoi( Text.substr( 3, 2 ), nullptr, 16 );
        Blue = std::stoi( Text.substr( 5, 2 ), nullptr, 16 );

        if ( Text.size() == 9 ) {

            Alpha = std::stoi( Text.substr( 7, 2 ), nullptr, 16 ); }

        else {

            Alpha = 255; } }

    catch ( ... ) {

        Red = 0;
        Green = 0;
        Blue = 0;
        Alpha = 0; }

    return { (sf::Uint8) Red, (sf::Uint8) Green, (sf::Uint8) Blue, (sf::Uint8) Alpha }; }

void Script::setValue ( pugi::xml_node Node, std::string Value ) {

    Node.text().set( Value.c_str() ); }

void Script::setValue ( pugi::xml_node Node, bool Value ) {

    if ( !Node ) {

        return; }

    if ( Value ) {

        setValue( Node, std::string( "true" ) ); }

    else {

        setValue( Node, std::string( "false" ) ); } }

void Script::setValue ( pugi::xml_node Node, int Value ) {

    setValue( Node, std::to_string( Value ) ); }

void Script::setValue ( pugi::xml_node Node, float Value ) {

    setValue( Node, std::to_string( Value ) ); }

void Script::setColorValue ( pugi::xml_node Node, sf::Color Value ) {

    std::string Red, Green, Blue, Alpha;

    Red = toHex( Value.r );
    Green = toHex( Value.g );
    Blue = toHex( Value.b );
    Alpha = toHex( Value.a );

    Red = ( Red.size() == 1 ? "0" : "" ) + Red;
    Green = ( Green.size() == 1 ? "0" : "" ) + Green;
    Blue = ( Blue.size() == 1 ? "0" : "" ) + Blue;
    Alpha = ( Alpha.size() == 1 ? "0" : "" ) + Alpha;

    Red = ( Red.size() == 2 ? Red : "00" );
    Green = ( Green.size() == 2 ? Green : "00" );
    Blue = ( Blue.size() == 2 ? Blue : "00" );
    Alpha = ( Alpha.size() == 2 ? Alpha : "00" );

    setValue( Node, std::string( Red + Green + Blue + Alpha ) ); }

std::string Script::toHex ( unsigned int Value ) {

    std::stringstream Stream;

    Stream << std::uppercase << std::hex << Value;

    return Stream.str(); }
