#ifndef CONDUIT_GAMEPAD_INPUT_HPP
#define CONDUIT_GAMEPAD_INPUT_HPP
#include <raylib.h>
#include <conduit/core/primitives.hpp>
#include <conduit/core/config.hpp>
#include <conduit/framework/helpers/GamepadState.hpp>

namespace conduit {
class GamepadInput {
private:
    array<GamepadState, config::MAX_GAMEPADS> m_gamepad_states{};

    void pollConnection(int gamepad, GamepadState &state);
    void pollAxes(int gamepad, GamepadState &state);
    void pollButtons(int gamepad, GamepadState &state);

public:
    GamepadInput() = default;
    ~GamepadInput() = default;

    void poll();

    bool connected(sizet index) const;
    const GamepadState& state(sizet index) const;
}; 
} // namespace conduit

#endif // CONDUIT_GAMEPAD_INPUT_HPP