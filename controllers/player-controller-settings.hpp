#ifndef GRAVITY_MADNESS_PLAYER_CONTROLLER_KEYS
#define GRAVITY_MADNESS_PLAYER_CONTROLLER_KEYS

#include <unordered_map>
#include <SFML/Graphics.hpp>

// None: -1
// Keyboard Keys: 0 - 199
// Joystick Axises: 200 - 249
// Joystick Buttons: 250 - 300
#define KEY_NONE                    (-1)
#define JOYSTICK_AXIS_X_POSITIVE    200
#define JOYSTICK_AXIS_X_NEGATIVE    201
#define JOYSTICK_AXIS_Y_POSITIVE    202
#define JOYSTICK_AXIS_Y_NEGATIVE    203
#define JOYSTICK_AXIS_Z_POSITIVE    204
#define JOYSTICK_AXIS_Z_NEGATIVE    205
#define JOYSTICK_AXIS_R_POSITIVE    206
#define JOYSTICK_AXIS_R_NEGATIVE    207
#define JOYSTICK_AXIS_U_POSITIVE    208
#define JOYSTICK_AXIS_U_NEGATIVE    209
#define JOYSTICK_AXIS_V_POSITIVE    210
#define JOYSTICK_AXIS_V_NEGATIVE    211
#define JOYSTICK_AXIS_POVX_POSITIVE 212
#define JOYSTICK_AXIS_POVX_NEGATIVE 213
#define JOYSTICK_AXIS_POVY_POSITIVE 214
#define JOYSTICK_AXIS_POVY_NEGATIVE 215
#define JOYSTICK_BUTTON             250

class PlayerControllerSettings {

public:

    enum Devices {

        Keyboard,
        Joystick

        };

    PlayerControllerSettings ( );

    Devices getDevice ( );
    void setDevice ( Devices Device );

    int getJoystickIdentifier ( );
    void setJoystickIdentifier ( int JoystickIdentifier );

    int getForwardKey ( );
    void setForwardKey ( int Key );

    int getBackwardKey ( );
    void setBackwardKey ( int Key );

    int getLeftKey ( );
    void setLeftKey ( int Key );

    int getRightKey ( );
    void setRightKey ( int Key );

    int getRayShotKey ( );
    void setRayShotKey ( int Key );

    int getMissileShotKey ( );
    void setMissileShotKey ( int Key );

    const bool isKeyboardKey ( int Key );
    const bool isJoystickKey ( int Key );
    bool isAvailableKey ( int Key );

    static std::string encodeKey ( int Key );
    static int decodeKey ( std::string Key );

    static int scanKeyboard ( );
    static int scanJoystick ( int JoystickIdentifier );

private:

    Devices Device;
    unsigned int JoystickIdentifier;

    int ForwardKey;
    int BackwardKey;
    int LeftKey;
    int RightKey;
    int RayShotKey;
    int MissileShotKey;

    static const std::unordered_map < int, std::string > Encoder;
    static const std::unordered_map < std::string, int > Decoder;

    };

#endif
