#include "gravity-madness.hpp"

int main ( ) {

    Script Config ( "config/config.xml" );
    WorldModule World ( Config );

    if ( World.getMode() != WorldModule::Modes::Idle ) {

        sf::RenderWindow Window ( World.getVideoMode(), "Gravity Madness", World.getVideoStyle(), World.getVideoContext() );

        while ( Window.isOpen() ) {

            sf::Event Event {};

            while ( Window.pollEvent( Event ) ) {

                if ( Event.type == sf::Event::Closed ) {

                    Window.close(); }

                else {

                    World.update( Event ); } }

            if ( Window.isOpen() ) {

                if ( World.getMode() != WorldModule::Modes::Idle ) {

                    World.update();

                    if ( World.hasVideoChanged() ) {

                        Window.create( World.getVideoMode(), "Gravity Madness", World.getVideoStyle(), World.getVideoContext() ); }

                    Window.clear();
                    World.render( Window );
                    Window.display(); }

                else {

                    Window.close(); } } } }

    else {

        #if defined(WIN32)

            // ...

        #elif defined(unix) || defined(__unix) || defined(__unix__)

            // ...

        #endif

        }

    return 0; }