#ifndef CONDUIT_GLFW_GAMEPAD_INPUT_HPP
#define CONDUIT_GLFW_GAMEPAD_INPUT_HPP
#include <glfw/glfw3.h>
#include <conduit/backend/glfw/input/GLFWInputMapping.hpp>
#include <conduit/input/gamepad/GamepadStates.hpp>

namespace conduit::glfw {
class GLFWGamepadInput {
private:
    /**
     * Helper function that focuses on polling a gamepad's connection.
     * @param gamepad the gamepad index
     * @param state a gamepad's state to store the polled results in
     */
    void pollConnection(int gamepad, GamepadState &state);

    /**
     * Helper function that focuses on polling a gamepad's axes and buttons.
     * @param gamepad the gamepad index
     * @param state a gamepad's state to store the polled results in
     */
    void pollAxesAndButtons(int gamepad, GamepadState &state);

public:
    GLFWGamepadInput() = default;
    ~GLFWGamepadInput() = default;

    /**
     * Polls gamepads using glfw specific functions.
     * 
     * @param gamepadStates a collection of gamepad states to poll and store the results in
     */
    void poll(GamepadStates &gamepadStates);
}; // class GLFWGamepadInput
} // namespace conduit::glfw

#endif // CONDUIT_GLFW_GAMEPAD_INPUT_HPP