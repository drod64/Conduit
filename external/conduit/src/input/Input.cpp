#include <conduit/input/Input.hpp>

conduit::Input::Input(Input&& other)
{
    m_window = other.m_window;
    other.m_window = nullptr;

    m_gamepad_states    = std::move(other.m_gamepad_states);
    m_keyboard_state    = std::move(other.m_keyboard_state);
    m_mouse_state       = std::move(other.m_mouse_state);
}

conduit::Input& conduit::Input::operator=(Input&& other)
{
    if (this != &other)
    {
        m_window = other.m_window;
        other.m_window = nullptr;
    
        m_gamepad_states    = std::move(other.m_gamepad_states);
        m_keyboard_state    = std::move(other.m_keyboard_state);
        m_mouse_state       = std::move(other.m_mouse_state);
    }

    return *this;
}

conduit::Input::Input(const conduit::Window &window)
{
    m_window = &window;
}

const conduit::KeyboardState& conduit::Input::keyboard() const
{
    return m_keyboard_state;
}

conduit::KeyboardState& conduit::Input::keyboard()
{
    return m_keyboard_state;
}

const conduit::MouseState& conduit::Input::mouse() const
{
    return m_mouse_state;
}

conduit::MouseState& conduit::Input::mouse()
{
    return m_mouse_state;
}

const conduit::GamepadStates& conduit::Input::gamepads() const
{
    return m_gamepad_states;
}

conduit::GamepadStates& conduit::Input::gamepads()
{
    return m_gamepad_states;
}

void conduit::Input::poll()
{
    assert(m_window && "[conduit::Input]: Error. Uninitialized Input object. Try assigning a conduit::Window to it.");
    conduit::platform::input::poll(m_window->m_platform_window, *this);
}