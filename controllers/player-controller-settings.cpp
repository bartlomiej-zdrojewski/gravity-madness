#include "player-controller-settings.hpp"

PlayerControllerSettings::PlayerControllerSettings ( ) {

    Device = Devices::Keyboard;
    JoystickIdentifier = 0;

    ForwardKey = -1;
    BackwardKey = -1;
    LeftKey = -1;
    RightKey = -1;
    RayShotKey = -1;
    MissileShotKey = -1; }

PlayerControllerSettings::Devices PlayerControllerSettings::getDevice ( ) {

    return Device; }

void PlayerControllerSettings::setDevice( PlayerControllerSettings::Devices Device ) {

    this->Device = Device; }

int PlayerControllerSettings::getJoystickIdentifier ( ) {

    if ( Device != Devices::Joystick ) {

        return -1; }

    return JoystickIdentifier; }

void PlayerControllerSettings::setJoystickIdentifier ( int JoystickIdentifier ) {

    if ( JoystickIdentifier < 0 ) {

         return; }

    this->JoystickIdentifier = (unsigned int) JoystickIdentifier; }

int PlayerControllerSettings::getForwardKey ( ) {

    return ForwardKey; }

void PlayerControllerSettings::setForwardKey ( int Key ) {

    if ( !isAvailableKey( Key ) ) {

        return; }

    ForwardKey = Key; }

int PlayerControllerSettings::getBackwardKey ( ) {

    return BackwardKey; }

void PlayerControllerSettings::setBackwardKey ( int Key ) {

    if ( !isAvailableKey( Key ) ) {

        return; }

    BackwardKey = Key; }

int PlayerControllerSettings::getLeftKey ( ) {

    return LeftKey; }

void PlayerControllerSettings::setLeftKey ( int Key ) {

    if ( !isAvailableKey( Key ) ) {

        return; }

    LeftKey = Key; }

int PlayerControllerSettings::getRightKey ( ) {

    return RightKey; }

void PlayerControllerSettings::setRightKey ( int Key ) {

    if ( !isAvailableKey( Key ) ) {

        return; }

    RightKey = Key; }

int PlayerControllerSettings::getRayShotKey ( ) {

    return RayShotKey; }

void PlayerControllerSettings::setRayShotKey ( int Key ) {

    if ( !isAvailableKey( Key ) ) {

        return; }

    RayShotKey = Key; }

int PlayerControllerSettings::getMissileShotKey ( ) {

    return MissileShotKey; }

void PlayerControllerSettings::setMissileShotKey ( int Key ) {

    if ( !isAvailableKey( Key ) ) {

        return; }

    MissileShotKey = Key; }

const bool PlayerControllerSettings::isKeyboardKey ( int Key ) {

    if ( Key >= sf::Keyboard::A && Key <= sf::Keyboard::Num9 ) {

        return true; }

    if ( Key >= sf::Keyboard::LControl && Key <= sf::Keyboard::LAlt ) {

        return true; }

    if ( Key >= sf::Keyboard::RControl && Key <= sf::Keyboard::RAlt ) {

        return true; }

    if ( Key >= sf::Keyboard::Menu && Key <= sf::Keyboard::Space ) {

        return true; }

    if ( Key >= sf::Keyboard::BackSpace && Key <= sf::Keyboard::Pause ) {

        return true; }

    return false; }

const bool PlayerControllerSettings::isJoystickKey ( int Key ) {

    if ( Key >= JOYSTICK_AXIS_X_POSITIVE && Key <= JOYSTICK_AXIS_Z_NEGATIVE ) {

        return true; }

    if ( Key >= ( JOYSTICK_BUTTON + 0 ) && Key <= ( JOYSTICK_BUTTON + 31 ) ) {

        return true; }

    return false; }

bool PlayerControllerSettings::isAvailableKey ( int Key ) {

    if ( Device == Devices::Keyboard ) {

        return isKeyboardKey( Key ); }

    if ( Device == Devices::Joystick ) {

        return isJoystickKey( Key ); }

    return false; }

std::string PlayerControllerSettings::encodeKey ( int Key ) {

    auto Data = Encoder.find( Key );

    if ( Data == Encoder.end() ) {

        return "NONE"; }

    return Data->second; }

int PlayerControllerSettings::decodeKey ( std::string Key ) {

    auto Data = Decoder.find( Key );

    if ( Data == Decoder.end() ) {

        return -1; }

    return Data->second; }

int PlayerControllerSettings::scanKeyboard ( ) { // Won't allow System, Enter and Escape keys

    for ( int i = sf::Keyboard::A; i <= sf::Keyboard::Num9; i++ ) {

        if ( sf::Keyboard::isKeyPressed( (sf::Keyboard::Key ) i ) ) {

            return i; } }

    for ( int i = sf::Keyboard::LControl; i <= sf::Keyboard::LAlt; i++ ) {

        if ( sf::Keyboard::isKeyPressed( (sf::Keyboard::Key ) i ) ) {

            return i; } }

    for ( int i = sf::Keyboard::RControl; i <= sf::Keyboard::RAlt; i++ ) {

        if ( sf::Keyboard::isKeyPressed( (sf::Keyboard::Key ) i ) ) {

            return i; } }

    for ( int i = sf::Keyboard::Menu; i <= sf::Keyboard::Space; i++ ) {

        if ( sf::Keyboard::isKeyPressed( (sf::Keyboard::Key ) i ) ) {

            return i; } }

    for ( int i = sf::Keyboard::BackSpace; i <= sf::Keyboard::Pause; i++ ) {

        if ( sf::Keyboard::isKeyPressed( (sf::Keyboard::Key ) i ) ) {

            return i; } }

    return -1; }

int PlayerControllerSettings::scanJoystick ( int JoystickIdentifier ) {

    if ( JoystickIdentifier < 0 ) {

        return -1; }

    if ( !sf::Joystick::isConnected( (unsigned int) JoystickIdentifier ) ) {

        return -2; }

    for ( unsigned int i = 0; i < sf::Joystick::getButtonCount( (unsigned int) JoystickIdentifier ); i++ ) {

        if ( sf::Joystick::isButtonPressed( (unsigned int) JoystickIdentifier, i ) ) {

            return ( JOYSTICK_BUTTON + i ); } }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::X ) > 50 ) {

        return JOYSTICK_AXIS_X_POSITIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::X ) < ( - 50 ) ) {

        return JOYSTICK_AXIS_X_NEGATIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::Y ) > 50 ) {

        return JOYSTICK_AXIS_Y_POSITIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::Y ) < ( - 50 ) ) {

        return JOYSTICK_AXIS_Y_NEGATIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::Z ) > 50 ) {

        return JOYSTICK_AXIS_Z_POSITIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::Z ) < ( - 50 ) ) {

        return JOYSTICK_AXIS_Z_NEGATIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::R ) > 50 ) {

        return JOYSTICK_AXIS_R_POSITIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::R ) < ( - 50 ) ) {

        return JOYSTICK_AXIS_R_NEGATIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::U ) > 50 ) {

        return JOYSTICK_AXIS_U_POSITIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::U ) < ( - 50 ) ) {

        return JOYSTICK_AXIS_U_NEGATIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::V ) > 50 ) {

        return JOYSTICK_AXIS_V_POSITIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::V ) < ( - 50 ) ) {

        return JOYSTICK_AXIS_V_NEGATIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::PovX ) > 50 ) {

        return JOYSTICK_AXIS_POVX_POSITIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::PovX ) < ( - 50 ) ) {

        return JOYSTICK_AXIS_POVX_NEGATIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::PovY ) > 50 ) {

        return JOYSTICK_AXIS_POVY_POSITIVE; }

    if ( sf::Joystick::getAxisPosition( (unsigned int) JoystickIdentifier, sf::Joystick::Axis::PovY ) < ( - 50 ) ) {

        return JOYSTICK_AXIS_POVY_NEGATIVE; }

    return -1; }

const std::unordered_map < int, std::string > PlayerControllerSettings::Encoder = {

    { sf::Keyboard::Unknown, "NONE" },

    { sf::Keyboard::A, "A" }, { sf::Keyboard::B, "B" }, { sf::Keyboard::C, "C" }, { sf::Keyboard::D, "D" },
    { sf::Keyboard::E, "E" }, { sf::Keyboard::F, "F" }, { sf::Keyboard::G, "G" }, { sf::Keyboard::H, "H" },
    { sf::Keyboard::I, "I" }, { sf::Keyboard::J, "J" }, { sf::Keyboard::K, "K" }, { sf::Keyboard::L, "L" },
    { sf::Keyboard::M, "M" }, { sf::Keyboard::N, "N" }, { sf::Keyboard::O, "O" }, { sf::Keyboard::P, "P" },
    { sf::Keyboard::Q, "Q" }, { sf::Keyboard::R, "R" }, { sf::Keyboard::S, "S" }, { sf::Keyboard::T, "T" },
    { sf::Keyboard::U, "U" }, { sf::Keyboard::V, "V" }, { sf::Keyboard::W, "W" }, { sf::Keyboard::X, "X" },
    { sf::Keyboard::Y, "Y" }, { sf::Keyboard::Z, "Z" },

    { sf::Keyboard::Num0, "0" }, { sf::Keyboard::Num1, "1" }, { sf::Keyboard::Num2, "2" }, { sf::Keyboard::Num3, "3" },
    { sf::Keyboard::Num4, "4" }, { sf::Keyboard::Num5, "5" }, { sf::Keyboard::Num6, "6" }, { sf::Keyboard::Num7, "7" },
    { sf::Keyboard::Num8, "8" }, { sf::Keyboard::Num9, "9" },

    { sf::Keyboard::Left, "LEFT" }, { sf::Keyboard::Right, "RIGHT" }, { sf::Keyboard::Up, "UP" }, { sf::Keyboard::Down, "DOWN" },

    { sf::Keyboard::LControl, "CONTROL_LEFT" }, { sf::Keyboard::LShift, "SHIFT_LEFT" }, { sf::Keyboard::LAlt, "ALT_LEFT" },
    { sf::Keyboard::RControl, "CONTROL_RIGHT" }, { sf::Keyboard::RShift, "SHIFT_RIGHT" }, { sf::Keyboard::RAlt, "ALT_RIGHT" },

    { sf::Keyboard::Menu, "MENU" }, { sf::Keyboard::LBracket, "[" }, { sf::Keyboard::RBracket, "]" },
    { sf::Keyboard::SemiColon, ";" }, { sf::Keyboard::Comma, "COMMA" }, { sf::Keyboard::Period, "PERIOD" },
    { sf::Keyboard::Quote, "QUOTE" }, { sf::Keyboard::Slash, "/" }, { sf::Keyboard::BackSlash, "\\" },
    { sf::Keyboard::Tilde, "~" }, { sf::Keyboard::Equal, "=" }, { sf::Keyboard::Dash, "-" },
    { sf::Keyboard::Space, "SPACE" }, { sf::Keyboard::BackSpace, "BACKSPACE" }, { sf::Keyboard::Tab, "TAB" },
    { sf::Keyboard::PageUp , "PAGE_UP" }, { sf::Keyboard::PageDown, "PAGE_DOWN" }, { sf::Keyboard::End, "END" },
    { sf::Keyboard::Home, "HOME" }, { sf::Keyboard::Insert, "INSERT" }, { sf::Keyboard::Delete, "DELETE" },
    { sf::Keyboard::Pause, "PAUSE" },

    { sf::Keyboard::Numpad0, "NUM_0" }, { sf::Keyboard::Numpad1, "NUM_1" }, { sf::Keyboard::Numpad2, "NUM_2" },
    { sf::Keyboard::Numpad3, "NUM_3" }, { sf::Keyboard::Numpad4, "NUM_4" }, { sf::Keyboard::Numpad5, "NUM_5" },
    { sf::Keyboard::Numpad6, "NUM_6" }, { sf::Keyboard::Numpad7, "NUM_7" }, { sf::Keyboard::Numpad8, "NUM_8" },
    { sf::Keyboard::Numpad9, "NUM_9" }, { sf::Keyboard::Add, "NUM_+" }, { sf::Keyboard::Subtract, "NUM_-" },
    { sf::Keyboard::Multiply, "NUM_*" }, { sf::Keyboard::Divide, "NUM_/" },

    { sf::Keyboard::F1, "F1" }, { sf::Keyboard::F2, "F2" }, { sf::Keyboard::F3, "F3" }, { sf::Keyboard::F4, "F4" },
    { sf::Keyboard::F5, "F5" }, { sf::Keyboard::F6, "F6" }, { sf::Keyboard::F7, "F7" }, { sf::Keyboard::F8, "F8" },
    { sf::Keyboard::F9, "F9" }, { sf::Keyboard::F10, "F10" }, { sf::Keyboard::F11, "F11" }, { sf::Keyboard::F12, "F12" },

    { JOYSTICK_AXIS_X_POSITIVE, "JS_XPOS" }, { JOYSTICK_AXIS_X_NEGATIVE, "JS_XNEG" }, { JOYSTICK_AXIS_Y_POSITIVE, "JS_YPOS" },
    { JOYSTICK_AXIS_Y_NEGATIVE, "JS_YNEG" }, { JOYSTICK_AXIS_Z_POSITIVE, "JS_ZPOS" }, { JOYSTICK_AXIS_Z_NEGATIVE, "JS_ZNEG" },
    { JOYSTICK_AXIS_R_POSITIVE, "JS_RPOS" }, { JOYSTICK_AXIS_R_NEGATIVE, "JS_RNEG" }, { JOYSTICK_AXIS_U_POSITIVE, "JS_UPOS" },
    { JOYSTICK_AXIS_U_NEGATIVE, "JS_UNEG" }, { JOYSTICK_AXIS_V_POSITIVE, "JS_VPOS" }, { JOYSTICK_AXIS_V_NEGATIVE, "JS_VNEG" },
    { JOYSTICK_AXIS_POVX_POSITIVE, "JS_POVXPOS" }, { JOYSTICK_AXIS_POVX_NEGATIVE, "JS_POVXNEG" },
    { JOYSTICK_AXIS_POVY_POSITIVE, "JS_POVYPOS" }, { JOYSTICK_AXIS_POVY_NEGATIVE, "JS_POVYNEG" },

    { JOYSTICK_BUTTON + 0, "JS_1" }, { JOYSTICK_BUTTON + 1, "JS_2" }, { JOYSTICK_BUTTON + 2, "JS_3" }, { JOYSTICK_BUTTON + 3, "JS_4" },
    { JOYSTICK_BUTTON + 4, "JS_5" }, { JOYSTICK_BUTTON + 5, "JS_6" }, { JOYSTICK_BUTTON + 6, "JS_7" }, { JOYSTICK_BUTTON + 7, "JS_8" },
    { JOYSTICK_BUTTON + 8, "JS_9" }, { JOYSTICK_BUTTON + 9, "JS_10" }, { JOYSTICK_BUTTON + 10, "JS_11" }, { JOYSTICK_BUTTON + 11, "JS_12" },
    { JOYSTICK_BUTTON + 12, "JS_13" }, { JOYSTICK_BUTTON + 13, "JS_14" }, { JOYSTICK_BUTTON + 14, "JS_15" }, { JOYSTICK_BUTTON + 15, "JS_16" },
    { JOYSTICK_BUTTON + 16, "JS_17" }, { JOYSTICK_BUTTON + 17, "JS_18" }, { JOYSTICK_BUTTON + 18, "JS_19" }, { JOYSTICK_BUTTON + 19, "JS_20" },
    { JOYSTICK_BUTTON + 20, "JS_21" }, { JOYSTICK_BUTTON + 21, "JS_22" }, { JOYSTICK_BUTTON + 22, "JS_23" }, { JOYSTICK_BUTTON + 23, "JS_24" },
    { JOYSTICK_BUTTON + 24, "JS_25" }, { JOYSTICK_BUTTON + 25, "JS_26" }, { JOYSTICK_BUTTON + 26, "JS_27" }, { JOYSTICK_BUTTON + 27, "JS_28" },
    { JOYSTICK_BUTTON + 28, "JS_29" }, { JOYSTICK_BUTTON + 29, "JS_30" }, { JOYSTICK_BUTTON + 30, "JS_31" }, { JOYSTICK_BUTTON + 31, "JS_32" }

    };

const std::unordered_map < std::string, int > PlayerControllerSettings::Decoder = {

    { "NONE", -1 },

    { "A", sf::Keyboard::A }, { "B", sf::Keyboard::B }, { "C", sf::Keyboard::C }, { "D", sf::Keyboard::D },
    { "E", sf::Keyboard::E }, { "F", sf::Keyboard::F }, { "G", sf::Keyboard::G }, { "H", sf::Keyboard::H },
    { "I", sf::Keyboard::I }, { "J", sf::Keyboard::J }, { "K", sf::Keyboard::K }, { "L", sf::Keyboard::L },
    { "M", sf::Keyboard::M }, { "N", sf::Keyboard::N }, { "O", sf::Keyboard::O }, { "P", sf::Keyboard::P },
    { "Q", sf::Keyboard::Q }, { "R", sf::Keyboard::R }, { "S", sf::Keyboard::S }, { "T", sf::Keyboard::T },
    { "U", sf::Keyboard::U }, { "V", sf::Keyboard::V }, { "W", sf::Keyboard::W }, { "X", sf::Keyboard::X },
    { "Y", sf::Keyboard::Y }, { "Z", sf::Keyboard::Z },

    { "0", sf::Keyboard::Num0 }, { "1", sf::Keyboard::Num1 }, { "2", sf::Keyboard::Num2 }, { "3", sf::Keyboard::Num3 },
    { "4", sf::Keyboard::Num4 }, { "5", sf::Keyboard::Num5 }, { "6", sf::Keyboard::Num6 }, { "7", sf::Keyboard::Num7 },
    { "8", sf::Keyboard::Num8 }, { "9", sf::Keyboard::Num9 },

    { "LEFT", sf::Keyboard::Left }, { "RIGHT", sf::Keyboard::Right }, { "UP", sf::Keyboard::Up }, { "DOWN", sf::Keyboard::Down },

    { "CONTROL_LEFT", sf::Keyboard::LControl }, { "SHIFT_LEFT", sf::Keyboard::LShift }, { "ALT_LEFT", sf::Keyboard::LAlt },
    { "CONTROL_RIGHT", sf::Keyboard::RControl }, { "SHIFT_RIGHT", sf::Keyboard::RShift }, { "ALT_RIGHT", sf::Keyboard::RAlt },

    { "MENU", sf::Keyboard::Menu }, { "[", sf::Keyboard::LBracket }, { "]", sf::Keyboard::RBracket },
    { ";", sf::Keyboard::SemiColon }, { "COMMA", sf::Keyboard::Comma }, { "PERIOD", sf::Keyboard::Period },
    { "QUOTE", sf::Keyboard::Quote }, { "/", sf::Keyboard::Slash }, { "\\", sf::Keyboard::BackSlash },
    { "~", sf::Keyboard::Tilde }, { "=", sf::Keyboard::Equal }, { "-", sf::Keyboard::Dash },
    { "SPACE", sf::Keyboard::Space }, { "BACKSPACE", sf::Keyboard::BackSpace }, { "TAB", sf::Keyboard::Tab },
    { "PAGE_UP", sf::Keyboard::PageUp }, { "PAGE_DOWN", sf::Keyboard::PageDown }, { "END", sf::Keyboard::End },
    { "HOME", sf::Keyboard::Home }, { "INSERT", sf::Keyboard::Insert }, { "DELETE", sf::Keyboard::Delete },
    { "PAUSE", sf::Keyboard::Pause },

    { "NUM_0", sf::Keyboard::Numpad0 }, { "NUM_1", sf::Keyboard::Numpad1 }, { "NUM_2", sf::Keyboard::Numpad2 },
    { "NUM_3", sf::Keyboard::Numpad3 }, { "NUM_4", sf::Keyboard::Numpad4 }, { "NUM_5", sf::Keyboard::Numpad5 },
    { "NUM_6", sf::Keyboard::Numpad5 }, { "NUM_7", sf::Keyboard::Numpad7 }, { "NUM_8", sf::Keyboard::Numpad8 },
    { "NUM_9", sf::Keyboard::Numpad9 }, { "NUM_+", sf::Keyboard::Add }, { "NUM_-", sf::Keyboard::Subtract },
    { "NUM_*", sf::Keyboard::Multiply }, { "NUM_/", sf::Keyboard::Divide },

    { "F1", sf::Keyboard::F1 }, { "F2", sf::Keyboard::F2 }, { "F3", sf::Keyboard::F3 }, { "F4", sf::Keyboard::F4 },
    { "F5", sf::Keyboard::F5 }, { "F6", sf::Keyboard::F6 }, { "F7", sf::Keyboard::F7 }, { "F8", sf::Keyboard::F8 },
    { "F9", sf::Keyboard::F9 }, { "F10", sf::Keyboard::F10 }, { "F11", sf::Keyboard::F11 }, { "F12", sf::Keyboard::F12 },

    { "JS_XPOS", JOYSTICK_AXIS_X_POSITIVE }, { "JS_XNEG", JOYSTICK_AXIS_X_NEGATIVE }, { "JS_YPOS", JOYSTICK_AXIS_Y_POSITIVE },
    { "JS_YNEG", JOYSTICK_AXIS_Y_NEGATIVE }, { "JS_ZPOS", JOYSTICK_AXIS_Z_POSITIVE }, { "JS_ZNEG", JOYSTICK_AXIS_Z_NEGATIVE },
    { "JS_RPOS", JOYSTICK_AXIS_R_POSITIVE }, { "JS_RNEG", JOYSTICK_AXIS_R_NEGATIVE }, { "JS_UPOS", JOYSTICK_AXIS_U_POSITIVE },
    { "JS_UNEG", JOYSTICK_AXIS_U_NEGATIVE }, { "JS_VPOS", JOYSTICK_AXIS_V_POSITIVE }, { "JS_VNEG", JOYSTICK_AXIS_V_NEGATIVE },
    { "JS_POVXPOS", JOYSTICK_AXIS_POVX_POSITIVE }, { "JS_POVXNEG", JOYSTICK_AXIS_POVX_NEGATIVE },
    { "JS_POVYPOS", JOYSTICK_AXIS_POVY_POSITIVE }, { "JS_POVYNEG", JOYSTICK_AXIS_POVY_NEGATIVE },

    { "JS_1", JOYSTICK_BUTTON + 0 }, { "JS_2", JOYSTICK_BUTTON + 1 }, { "JS_3", JOYSTICK_BUTTON + 2 }, { "JS_4", JOYSTICK_BUTTON + 3 },
    { "JS_5", JOYSTICK_BUTTON + 4 }, { "JS_6", JOYSTICK_BUTTON + 5 }, { "JS_7", JOYSTICK_BUTTON + 6 }, { "JS_8", JOYSTICK_BUTTON + 7 },
    { "JS_9", JOYSTICK_BUTTON + 8 }, { "JS_10", JOYSTICK_BUTTON + 9 }, { "JS_11", JOYSTICK_BUTTON + 10 }, { "JS_12", JOYSTICK_BUTTON + 11 },
    { "JS_13", JOYSTICK_BUTTON + 12 }, { "JS_14", JOYSTICK_BUTTON + 13 }, { "JS_15", JOYSTICK_BUTTON + 14 }, { "JS_16", JOYSTICK_BUTTON + 15 },
    { "JS_17", JOYSTICK_BUTTON + 16 }, { "JS_18", JOYSTICK_BUTTON + 17 }, { "JS_19", JOYSTICK_BUTTON + 18 }, { "JS_20", JOYSTICK_BUTTON + 19 },
    { "JS_21", JOYSTICK_BUTTON + 20 }, { "JS_22", JOYSTICK_BUTTON + 21 }, { "JS_23", JOYSTICK_BUTTON + 22 }, { "JS_24", JOYSTICK_BUTTON + 23 },
    { "JS_25", JOYSTICK_BUTTON + 24 }, { "JS_26", JOYSTICK_BUTTON + 25 }, { "JS_27", JOYSTICK_BUTTON + 26 }, { "JS_28", JOYSTICK_BUTTON + 27 },
    { "JS_29", JOYSTICK_BUTTON + 28 }, { "JS_30", JOYSTICK_BUTTON + 29 }, { "JS_31", JOYSTICK_BUTTON + 30 }, { "JS_32", JOYSTICK_BUTTON + 31 }

    };