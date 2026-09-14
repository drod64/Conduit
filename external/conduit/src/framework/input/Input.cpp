#include <conduit/framework/input/Input.hpp>

const conduit::KeyboardState& conduit::Input::keyboard() const
{
    return m_keyboard_state;
}

const conduit::MouseState& conduit::Input::mouse() const
{
    return m_mouse_state;
}

const conduit::GamepadStates& conduit::Input::gamepads() const
{
    return m_gamepad_states;
}