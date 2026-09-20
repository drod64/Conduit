#include <conduit/backend/glfw/input/GLFWInput.hpp>

void conduit::glfw::input::pollKeyboard(const conduit::glfw::window::GLFWWindow &pWindow, KeyboardState &keyboardState)
{
    // Update previous button state of keyboard
    keyboardState.updatePrevious();

    // Update current button state of keyboard
    for (sizet key = 0; key < static_cast<sizet>(Key::MAX_COUNT); ++key)
    {
        conduit::Key conduit_key = static_cast<conduit::Key>(key);
        conduit::glfw::input::glfwKey glfw_key = toGLFWKeyButton(conduit_key);

        keyboardState.setKey(conduit_key, glfwGetKey(pWindow.nativeHandle(), glfw_key) == GLFW_PRESS);
    }
}

void conduit::glfw::input::pollMouse(const conduit::glfw::window::GLFWWindow &pWindow, MouseState &mouseState)
{
    // Update previous button state of mouse
    mouseState.updatePrevious();

    // Update current button state of mouse
    for (sizet button = 0; button < static_cast<sizet>(MouseButton::MAX_COUNT); ++button)
    {
        conduit::MouseButton conduit_button = static_cast<conduit::MouseButton>(button);
        conduit::glfw::input::glfwMouseButton glfw_button = toGLFWMouseButton(conduit_button);

        mouseState.setButton(conduit_button, glfwGetMouseButton(pWindow.nativeHandle(), glfw_button) == GLFW_PRESS);
    }

    // Update mouse axes
    double x, y;
    glfwGetCursorPos(pWindow.nativeHandle(), &x, &y);

    sm::Vec2 current_pos(static_cast<real>(x), static_cast<real>(y));

    // Translate to sm::Vec2
    mouseState.updateDelta(current_pos - mouseState.position());
    mouseState.updatePosition(current_pos);
    // mouseState.updateWheel(m_wheel); TODO
    // m_wheel = {};
}

namespace {
    /**
     * Helper function that focuses on polling a gamepad's connection.
     * @param gamepad the gamepad index
     * @param state a gamepad's state to store the polled results in
     */
    void pollConnection(int gamepad, conduit::GamepadState &state)
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

    /**
     * Helper function that focuses on polling a gamepad's axes and buttons.
     * @param gamepad the gamepad index
     * @param state a gamepad's state to store the polled results in
     */
    void pollAxesAndButtons(int gamepad, conduit::GamepadState &state)
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
        for (conduit::sizet axis = 0; axis < static_cast<conduit::sizet>(conduit::GamepadAxis::MAX_COUNT); ++axis)
        {   
            conduit::GamepadAxis conduit_axis = static_cast<conduit::GamepadAxis>(axis);
            conduit::glfw::input::glfwGamepadAxis glfw_axis = conduit::glfw::input::toGLFWGamepadAxis(conduit_axis);

            state.setAxis(conduit_axis, glfw_state.axes[glfw_axis]);
        }

        // Poll buttons.
        for (conduit::sizet button = 0; button < static_cast<conduit::sizet>(conduit::GamepadButton::MAX_COUNT); ++button)
        {
            conduit::GamepadButton conduit_button = static_cast<conduit::GamepadButton>(button);
            conduit::glfw::input::glfwGamepadButton glfw_button = conduit::glfw::input::toGLFWGamepadButton(conduit_button);

            state.setButton(conduit_button, glfw_state.buttons[glfw_button] == GLFW_PRESS);
        }
    }
}

void conduit::glfw::input::pollGamepads(GamepadStates &gamepadStates)
{
    for (sizet gamepad = 0; gamepad < gamepadStates.size(); ++gamepad)
    {
        GamepadState &gamepad_state = gamepadStates[gamepad];
    
        pollConnection(static_cast<int>(gamepad), gamepad_state);
        if (!gamepad_state.isConnected()) continue;

        pollAxesAndButtons(static_cast<int>(gamepad), gamepad_state);
    }
}