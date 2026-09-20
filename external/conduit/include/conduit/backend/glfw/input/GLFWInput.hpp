#ifndef CONDUIT_GLFW_INPUT_HPP
#define CONDUIT_GLFW_INPUT_HPP
#include <conduit/backend/glfw/input/GLFWInputMapping.hpp>
#include <conduit/backend/glfw/window/GLFWWindow.hpp>
#include <conduit/input/keyboard/KeyboardState.hpp>
#include <conduit/input/mouse/MouseState.hpp>
#include <conduit/input/gamepad/GamepadStates.hpp>

namespace conduit::glfw::input {
    /** TODO
    //  * GLFW dependent callback for mouse scroll/wheel accumulation.
    //  * 
    //  * @param window a pointer to the GLFWWindow
    //  * @param x the x offset
    //  * @param y the y offset
    //  */
    // void scrollCallback(GLFWwindow *window, double x, double y);

    /**
     * Helper function that focuses on polling the keyboard.
     * 
     * @param keyboardState the keyboard state to poll and store the results in
     */
    void pollKeyboard(const conduit::glfw::GLFWWindow &pWindow, KeyboardState &keyboardState);

    /**
     * Helper function that focuses on polling the mouse.
     * 
     * @param mouseState the mouse state to poll and store the results in
     */
    void pollMouse(const conduit::glfw::GLFWWindow &pWindow, MouseState &mouseState);

    /**
     * Helper function that focuses on polling gamepads.
     * 
     * @param gamepadStates the gamepad states to poll and store the results in
     */
    void pollGamepads(GamepadStates &gamepadStates);
} // namespace conduit::glfw::input

#endif // CONDUIT_GLFW_INPUT_HPP