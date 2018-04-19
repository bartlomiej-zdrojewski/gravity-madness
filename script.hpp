#ifndef GRAVITY_MADNESS_SCRIPT
#define GRAVITY_MADNESS_SCRIPT

#include <string>
#include <vector>

#include "pugixml/pugixml.hpp"

class Script {

public:

    explicit Script ( std::string FilePath );
    ~ Script ( );

    std::string getFilePath ( );
    bool saveToFile ( std::string FilePath = "" );

    pugi::xml_node * getRoot ( );
    std::vector <pugi::xml_node> getChildren ( pugi::xml_node Node, std::string Filter = "" );

    std::string getTextValue ( pugi::xml_node Node );
    bool getBooleanValue ( pugi::xml_node Node );
    int getIntegerValue ( pugi::xml_node Node );

    void setValue ( pugi::xml_node Node, std::string Value );
    void setValue ( pugi::xml_node Node, bool Value );
    void setValue ( pugi::xml_node Node, int Value );

private:

    std::string FilePath;
    pugi::xml_document * Document;

    };

#endif