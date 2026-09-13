#include <conduit/framework/input/gamepad/GamepadInput.hpp>

void conduit::GamepadInput::pollConnection(int gamepad, GamepadState &state)
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

void conduit::GamepadInput::pollAxes(int gamepad, GamepadState &state)
{
    // TODO
}

void conduit::GamepadInput::pollButtons(int gamepad, GamepadState &state)
{
    // Update previous button state of gamepad
    state.previous = state.current;

    // Update current button state of gamepad
    for (sizet button = 0; button < config::GAMEPAD_BUTTON_COUNT; ++button)
    {
        state.current.set(button, IsGamepadButtonDown(gamepad, static_cast<int>(button)));
    }
}

void conduit::GamepadInput::poll()
{
    for (sizet gamepad = 0; gamepad < m_gamepad_states.size(); ++gamepad)
    {
        GamepadState &gamepad_state = m_gamepad_states[gamepad];
    
        pollConnection(static_cast<int>(gamepad), gamepad_state);
        if (!gamepad_state.connected) continue;

        pollAxes(static_cast<int>(gamepad), gamepad_state);
        
        pollButtons(static_cast<int>(gamepad), gamepad_state);
    }
}

bool conduit::GamepadInput::connected(sizet index) const
{
    return m_gamepad_states[index].connected;
}

const conduit::GamepadState& conduit::GamepadInput::state(sizet index) const
{
    return m_gamepad_states[index];
}