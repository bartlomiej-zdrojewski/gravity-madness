#include "script.hpp"

Script::Script ( std::string FilePath ) {

    this->FilePath = FilePath;
    Document = new pugi::xml_document;

    if ( !Document->load_file( FilePath.c_str() ) ) {

        delete Document;
        Document = nullptr; } }

Script::~Script ( ) { // TODO FIX - THROWS ERROR

    // delete Document;

    }

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

void Script::setValue ( pugi::xml_node Node, std::string Value ) {

    Node.set_value( Value.c_str() ); }

void Script::setValue ( pugi::xml_node Node, bool Value ) {

    if ( !Node ) {

        return; }

    if ( Value ) {

        Node.set_value( "true" ); }

    else {

        Node.set_value( "false" ); } }

void Script::setValue ( pugi::xml_node Node, int Value ) {

    Node.set_value( std::to_string( Value ).c_str() ); }