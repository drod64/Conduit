#include <conduit/framework/input/raylib/RaylibGamepadInput.hpp>

void conduit::raylib::RaylibGamepadInput::pollConnection(int gamepad, GamepadState &state)
{
    const bool connected = IsGamepadAvailable(gamepad);

    // Disconnected controller
    if (!connected)
    {
        state.axes.fill(static_cast<real>(0));
        state.connected = false;
        state.current.reset();
        state.previous.reset();
        return;
    }

    // Newly connected controller
    if (!state.connected)
    {
        state.current.reset();
        state.previous.reset();
    }

    state.connected = true;
}

void conduit::raylib::RaylibGamepadInput::pollAxes(int gamepad, GamepadState &state)
{
    const int AXIS_COUNT = GetGamepadAxisCount(gamepad);

    for (sizet axis = 0; axis < static_cast<sizet>(GamepadAxis::MAX_COUNT); ++axis)
    {
        conduit::GamepadAxis gamepad_axis = static_cast<conduit::GamepadAxis>(axis);
        raylibGamepadAxis raylib_gamepad_axis = conduit::raylib::toRaylibGamepadAxis(gamepad_axis);

        if (raylib_gamepad_axis >= AXIS_COUNT)
        {
            state.axes[axis] = static_cast<real>(0);
            continue;
        }

        state.axes[axis] = static_cast<real>(GetGamepadAxisMovement(gamepad, raylib_gamepad_axis));
    }
}

void conduit::raylib::RaylibGamepadInput::pollButtons(int gamepad, GamepadState &state)
{
    // Update previous button state of gamepad
    state.previous = state.current;

    // Update current button state of gamepad
    for (sizet button = 0; button < static_cast<sizet>(GamepadButton::MAX_COUNT); ++button)
    {
        conduit::GamepadButton gamepad_button = static_cast<GamepadButton>(button);
        raylibGamepadButton raylib_gamepad_button = conduit::raylib::toRaylibGamepadButton(gamepad_button);

        state.current.set(button, IsGamepadButtonDown(gamepad, raylib_gamepad_button));
    }
}

void conduit::raylib::RaylibGamepadInput::poll(GamepadStates &gamepad_states)
{
    for (sizet gamepad = 0; gamepad < gamepad_states.size(); ++gamepad)
    {
        GamepadState &gamepad_state = gamepad_states[gamepad];
    
        pollConnection(static_cast<int>(gamepad), gamepad_state);
        if (!gamepad_state.connected) continue;

        pollAxes(static_cast<int>(gamepad), gamepad_state);
        
        pollButtons(static_cast<int>(gamepad), gamepad_state);
    }
}