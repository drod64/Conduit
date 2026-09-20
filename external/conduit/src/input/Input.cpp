#include <conduit/input/Input.hpp>

conduit::Input::Input(const conduit::Window &window) :
m_window(window)
{}

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

void conduit::Input::poll()
{
    conduit::platform::input::pollGamepads(m_gamepad_states);
    conduit::platform::input::pollKeyboard(m_window.m_platform_window, m_keyboard_state);
    conduit::platform::input::pollMouse(m_window.m_platform_window, m_mouse_state);
}