#ifndef CONDUIT_GLFW_INPUT_HPP
#define CONDUIT_GLFW_INPUT_HPP
#include <conduit/input/Input.hpp>
#include <conduit/backend/glfw/input/GLFWInputMapping.hpp>
#include <conduit/backend/glfw/input/GLFWGamepadInput.hpp>

namespace conduit::glfw {
class GLFWInput {
private:
    GLFWwindow &m_window;
    sm::Vec2    m_wheel;
    GLFWGamepadInput m_gamepad_input;

    /**
     * GLFW dependent callback for mouse scroll/wheel accumulation.
     * 
     * @param window a pointer to the GLFWWindow
     * @param x the x offset
     * @param y the y offset
     */
    static void scrollCallback(GLFWwindow *window, double x, double y);

    /**
     * Helper function that focuses on polling the keyboard.
     * 
     * @param keyboardState the keyboard state to poll and store the results in
     */
    void pollKeyboard(KeyboardState &keyboardState);

    /**
     * Helper function that focuses on polling the mouse.
     * 
     * @param mouseState the mouse state to poll and store the results in
     */
    void pollMouse(MouseState &mouseState);

    /**
     * Helper function that focuses on polling gamepads.
     * 
     * @param gamepadStates the gamepad states to poll and store the results in
     */
    void pollGamepads(GamepadStates &gamepadStates);

public:
    GLFWInput(GLFWwindow &window);
    ~GLFWInput() = default;

    /**
     * Polls input sources (keyboard, mouse, gamepads) using glfw specific functions.
     * 
     * @param input an Input class where the polled results will be stored
     */
    void poll(Input &input);
}; // class GLFWInput
} // namespace conduit::glfw

#endif // CONDUIT_GLFW_INPUT_HPP