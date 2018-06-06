#ifndef GRAVITY_MADNESS_SCRIPT
#define GRAVITY_MADNESS_SCRIPT

#include <string>
#include <vector>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "pugixml/pugixml.hpp"

class Script {

public:

    explicit Script ( std::string FilePath );
    ~ Script ( );

    std::string getFilePath ( );
    bool saveToFile ( std::string FilePath = "" );

    pugi::xml_node * getRoot ( );
    std::vector <pugi::xml_node> getChildren ( pugi::xml_node Node, std::string Filter = "" );

    static std::string getTextValue ( pugi::xml_node Node );
    static bool getBooleanValue ( pugi::xml_node Node );
    static int getIntegerValue ( pugi::xml_node Node );
    static float getRealValue ( pugi::xml_node Node );
    static sf::Color getColorValue ( pugi::xml_node Node );

    static void setValue ( pugi::xml_node Node, std::string Value );
    static void setValue ( pugi::xml_node Node, bool Value );
    static void setValue ( pugi::xml_node Node, int Value );
    static void setValue ( pugi::xml_node Node, float Value );
    static void setColorValue ( pugi::xml_node Node, sf::Color Value );

private:

    static std::string toHex ( unsigned int Value );

private:

    std::string FilePath;
    pugi::xml_document * Document;

    };

#endif