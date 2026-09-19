#include <conduit/backend/glfw/input/GLFWInput.hpp>

void conduit::glfw::GLFWInput::scrollCallback(GLFWwindow *window, double x, double y)
{
    auto input = static_cast<GLFWInput*>(glfwGetWindowUserPointer(window));

    input->m_wheel += sm::Vec2(static_cast<real>(x), static_cast<real>(y));
}

void conduit::glfw::GLFWInput::pollKeyboard(KeyboardState &keyboardState)
{
    // Update previous button state of keyboard
    keyboardState.updatePrevious();

    // Update current button state of keyboard
    for (sizet key = 0; key < static_cast<sizet>(Key::MAX_COUNT); ++key)
    {
        conduit::Key conduit_key = static_cast<conduit::Key>(key);
        conduit::glfw::glfwKey glfw_key = toGLFWKeyButton(conduit_key);

        keyboardState.setKey(conduit_key, glfwGetKey(&m_window, glfw_key) == GLFW_PRESS);
    }
}

void conduit::glfw::GLFWInput::pollMouse(MouseState &mouseState)
{
    // Update previous button state of mouse
    mouseState.updatePrevious();

    // Update current button state of mouse
    for (sizet button = 0; button < static_cast<sizet>(MouseButton::MAX_COUNT); ++button)
    {
        conduit::MouseButton conduit_button = static_cast<conduit::MouseButton>(button);
        conduit::glfw::glfwMouseButton glfw_button = toGLFWMouseButton(conduit_button);

        mouseState.setButton(conduit_button, glfwGetMouseButton(&m_window, glfw_button) == GLFW_PRESS);
    }

    // Update mouse axes
    double x, y;
    glfwGetCursorPos(&m_window, &x, &y);

    sm::Vec2 current_pos(static_cast<real>(x), static_cast<real>(y));

    // Translate to sm::Vec2
    mouseState.updateDelta(current_pos - mouseState.position());
    mouseState.updatePosition(current_pos);
    mouseState.updateWheel(m_wheel);

    m_wheel = {};
}

void conduit::glfw::GLFWInput::pollGamepads(GamepadStates &gamepadStates)
{
    m_gamepad_input.poll(gamepadStates);
}

conduit::glfw::GLFWInput::GLFWInput(GLFWwindow &window) :
m_window(window)
{
    glfwSetWindowUserPointer(&m_window, this);
    glfwSetScrollCallback(&m_window, GLFWInput::scrollCallback);
}

void conduit::glfw::GLFWInput::poll(Input &input)
{
    pollKeyboard(input.m_keyboard_state);
    pollMouse(input.m_mouse_state);
    pollGamepads(input.m_gamepad_states);
}