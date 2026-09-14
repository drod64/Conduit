#include <conduit/framework/input/raylib/RaylibInput.hpp>

void conduit::raylib::RaylibInput::pollKeyboard(conduit::Input &input)
{
    // Update previous button state of keyboard
    input.m_keyboard_state.previous = input.m_keyboard_state.current;

    // Update current button state of keyboard
    for (sizet i = 0; i < static_cast<sizet>(Key::MAX_COUNT); ++i)
    {
        conduit::Key key = static_cast<conduit::Key>(i);
        raylibKeyButton raylib_key = conduit::raylib::toRaylibKeyButton(key);

        input.m_keyboard_state.current.set(i, IsKeyDown(raylib_key));
    }
}

void conduit::raylib::RaylibInput::pollMouse(conduit::Input &input)
{
    // Update previous button state of mouse
    input.m_mouse_state.previous = input.m_mouse_state.current;

    // Update current button state of mouse
    for (sizet i = 0; i < static_cast<sizet>(MouseButton::MAX_COUNT); ++i)
    {
        conduit::MouseButton mouseButton = static_cast<conduit::MouseButton>(i);

        raylibMouseButton raylib_mouse_button = conduit::raylib::toRaylibMouseButton(mouseButton);

        input.m_mouse_state.current.set(i, IsMouseButtonDown(raylib_mouse_button));
    }

    // Update mouse axes
    using raylibVec2 = Vector2;
    raylibVec2 rl_mouse_position = raylibVec2(GetMousePosition());
    raylibVec2 rl_mouse_delta = raylibVec2(GetMouseDelta());
    raylibVec2 rl_mouse_wheel = raylibVec2(GetMouseWheelMoveV());
    // Translate to sm::Vec2
    input.m_mouse_state.position = {rl_mouse_position.x, rl_mouse_position.y};
    input.m_mouse_state.delta    = {rl_mouse_delta.x, rl_mouse_delta.y};
    input.m_mouse_state.wheel    = {rl_mouse_wheel.x, rl_mouse_delta.y};
}

void conduit::raylib::RaylibInput::pollGamepads(Input &input)
{
    // TODO: this will return wrong results
    input.m_gamepads.poll();
}

void conduit::raylib::RaylibInput::poll(Input &input)
{
    pollKeyboard(input);
    pollMouse(input);
    pollGamepads(input);
}