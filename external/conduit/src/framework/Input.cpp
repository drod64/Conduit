#include <conduit/framework/Input.hpp>

void conduit::Input::updatePhysicalStates()
{
    // Update previous states.
    m_keyboard_states.previous = m_keyboard_states.current;
    m_mouse_states.previous = m_mouse_states.current;
    m_gamepad_states.previous = m_gamepad_states.current;

    // Update current states.
    for (sizet i = 0; i < config::KEYBOARD_KEY_COUNT; ++i)
    {
        m_keyboard_states.current.set(i, IsKeyDown(static_cast<int>(i)));
    }

    for (sizet i = 0; i < config::MOUSE_BUTTON_COUNT; ++i)
    {
        m_mouse_states.current.set(i, IsMouseButtonDown(static_cast<int>(i)));
    }
    using raylibVec2 = Vector2;
    raylibVec2 rl_mouse_position = raylibVec2(GetMousePosition());
    raylibVec2 rl_mouse_delta = raylibVec2(GetMouseDelta());
    raylibVec2 rl_mouse_wheel = raylibVec2(GetMouseWheelMoveV());
    // Translate to sm::Vec2
    m_mouse_states.position = {rl_mouse_position.x, rl_mouse_position.y};
    m_mouse_states.delta    = {rl_mouse_delta.x, rl_mouse_delta.y};
    m_mouse_states.wheel    = {rl_mouse_wheel.x, rl_mouse_delta.y};

    for (sizet i = 0; i < config::GAMEPAD_BUTTON_COUNT; ++i)
    {
        m_gamepad_states.current.set(i, IsGamepadButtonDown(0, static_cast<int>(i)));
    }
}

void conduit::Input::poll()
{
    updatePhysicalStates();
}

const conduit::KeyboardState& conduit::Input::keyboard() const
{
    return m_keyboard_states;
}

const conduit::MouseState& conduit::Input::mouse() const
{
    return m_mouse_states;
}

const conduit::GamepadState& conduit::Input::gamepad() const
{
    return m_gamepad_states;
}