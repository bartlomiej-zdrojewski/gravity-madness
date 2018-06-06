#include "gravity-madness.hpp"

int main ( ) {

    srand( (unsigned int) time( nullptr ) );

    Script Config ( "assets/scripts/settings.xml" );
    WorldModule World ( &Config );

    if ( World.getMode() != WorldModule::Modes::IdleMode ) {

        sf::RenderWindow Window ( World.getVideoMode(), "Gravity Madness", World.getVideoStyle(), World.getVideoContext() );

        Window.setFramerateLimit( 60 );
        Window.setVerticalSyncEnabled( true );
        Window.setMouseCursorVisible( false );

        while ( Window.isOpen() ) {

            sf::Event Event {};

            while ( Window.pollEvent( Event ) ) {

                if ( Event.type == sf::Event::Closed ) {

                    Window.close(); }

                else {

                    World.update( Event ); } }

            if ( Window.isOpen() ) {

                if ( World.getMode() != WorldModule::Modes::IdleMode ) {

                    World.update();

                    if ( World.hasVideoChanged() ) {

                        Window.create( World.getVideoMode(), "Gravity Madness", World.getVideoStyle(), World.getVideoContext() );

                        Window.setFramerateLimit( 60 );
                        Window.setVerticalSyncEnabled( true );
                        Window.setMouseCursorVisible( false ); }

                    Window.clear();
                    World.render( Window );
                    Window.display(); }

                else {

                    Window.close(); } } } }

    else {

        std::string Message = "Essential configuration file couldn't be loaded. It may be corrupted or unreachable. "
                              "Check 'scripts/settings.xml' file or contact support team.";

        #if defined(WIN32)

            MessageBox( nullptr, Message.c_str(), "Gravity Madness", MB_OK | MB_ICONSTOP );

        #elif defined(unix) || defined(__unix) || defined(__unix__)

            std::cerr << Message;

        #endif

        }

    return 0; }