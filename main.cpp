#include "gravity-madness.hpp"

int main ( ) {

    Script Config ( "config/config.xml" );
    WorldModule World ( Config );

    if ( World.getMode() != WorldModule::Modes::Idle ) {

        sf::RenderWindow Window ( World.getVideoMode(), "Gravity Madness", World.getVideoStyle(), World.getVideoContext() );

        World.setMode( WorldModule::Modes::Init );

        while ( Window.isOpen() ) {

            sf::Event Event {};

            while ( Window.pollEvent( Event ) ) {

                if ( Event.type == sf::Event::Closed ) {

                    Window.close(); } }

            World.update();

            if ( World.hasVideoChanged() ) {

                Window.create( World.getVideoMode(), "Gravity Madness", World.getVideoStyle(), World.getVideoContext() ); }

            if ( World.getMode() == WorldModule::Modes::Idle ) {

                Window.close(); }

            else {

                Window.clear();
                World.render();
                Window.display(); } } }

    else {

        #if defined(WIN32)

            // ...

        #elif defined(unix) || defined(__unix) || defined(__unix__)

            // ...

        #endif

        }

    return 0; }