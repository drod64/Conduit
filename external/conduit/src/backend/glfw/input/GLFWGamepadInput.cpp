#include <conduit/backend/glfw/input/GLFWGamepadInput.hpp>

void conduit::glfw::GLFWGamepadInput::pollConnection(int gamepad, GamepadState &state)
{
    const int jid = GLFW_JOYSTICK_1 + gamepad;

    const bool connected =
    glfwJoystickPresent(jid) == GLFW_TRUE &&
    glfwJoystickIsGamepad(jid) == GLFW_TRUE;

    // Disconnected controller
    if (!connected)
    {
        state.reset();
        state.setConnection(false);
        return;
    }

    // Newly connected controller
    if (!state.isConnected())
    {
        state.reset();
    }

    state.setConnection(true);
}

void conduit::glfw::GLFWGamepadInput::pollAxesAndButtons(int gamepad, GamepadState &state)
{
    const int jid = GLFW_JOYSTICK_1 + gamepad;

    GLFWgamepadstate glfw_state{};

    // Gamepad isn't available or disconnected here.
    if (glfwGetGamepadState(jid, &glfw_state) == GLFW_FALSE)
    {
        state.reset();
        state.setConnection(false);
        return;
    }

    // Poll axes.
    for (sizet axis = 0; axis < static_cast<sizet>(GamepadAxis::MAX_COUNT); ++axis)
    {   
        conduit::GamepadAxis conduit_axis = static_cast<GamepadAxis>(axis);
        conduit::glfw::glfwGamepadAxis glfw_axis = toGLFWGamepadAxis(conduit_axis);

        state.setAxis(conduit_axis, glfw_state.axes[glfw_axis]);
    }

    // Poll buttons.
    for (sizet button = 0; button < static_cast<sizet>(GamepadButton::MAX_COUNT); ++button)
    {
        conduit::GamepadButton conduit_button = static_cast<GamepadButton>(button);
        conduit::glfw::glfwGamepadButton glfw_button = toGLFWGamepadButton(conduit_button);

        state.setButton(conduit_button, glfw_state.buttons[glfw_button] == GLFW_PRESS);
    }
}

void conduit::glfw::GLFWGamepadInput::poll(GamepadStates &gamepadStates)
{
    for (sizet gamepad = 0; gamepad < gamepadStates.size(); ++gamepad)
    {
        GamepadState &gamepad_state = gamepadStates[gamepad];
    
        pollConnection(static_cast<int>(gamepad), gamepad_state);
        if (!gamepad_state.isConnected()) continue;

        pollAxesAndButtons(static_cast<int>(gamepad), gamepad_state);
    }
}