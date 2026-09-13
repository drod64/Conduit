#include <conduit/framework/input/Input.hpp>

void conduit::Input::pollKeyboard()
{
    // Update previous button state of keyboard
    m_keyboard_state.previous = m_keyboard_state.current;

    // Update current button state of keyboard
    for (sizet i = 0; i < config::KEYBOARD_KEY_COUNT; ++i)
    {
        m_keyboard_state.current.set(i, IsKeyDown(static_cast<int>(i)));
    }
}

void conduit::Input::pollMouse()
{
    // Update previous button state of mouse
    m_mouse_state.previous = m_mouse_state.current;

    // Update current button state of mouse
    for (sizet i = 0; i < config::MOUSE_BUTTON_COUNT; ++i)
    {
        m_mouse_state.current.set(i, IsMouseButtonDown(static_cast<int>(i)));
    }

    // Update mouse axes
    using raylibVec2 = Vector2;
    raylibVec2 rl_mouse_position = raylibVec2(GetMousePosition());
    raylibVec2 rl_mouse_delta = raylibVec2(GetMouseDelta());
    raylibVec2 rl_mouse_wheel = raylibVec2(GetMouseWheelMoveV());
    // Translate to sm::Vec2
    m_mouse_state.position = {rl_mouse_position.x, rl_mouse_position.y};
    m_mouse_state.delta    = {rl_mouse_delta.x, rl_mouse_delta.y};
    m_mouse_state.wheel    = {rl_mouse_wheel.x, rl_mouse_delta.y};
}

void conduit::Input::pollGamepads()
{
    m_gamepads.poll();
}

void conduit::Input::poll()
{
    pollKeyboard();

    pollMouse();
    
    pollGamepads();
}

const conduit::KeyboardState& conduit::Input::keyboard() const
{
    return m_keyboard_state;
}

const conduit::MouseState& conduit::Input::mouse() const
{
    return m_mouse_state;
}

const conduit::GamepadInput& conduit::Input::gamepads() const
{
    return m_gamepads;
}