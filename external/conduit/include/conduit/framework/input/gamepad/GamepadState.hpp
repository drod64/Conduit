#ifndef CONDUIT_GAMEPAD_STATE_HPP
#define CONDUIT_GAMEPAD_STATE_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/core/containers/array.hpp>
#include <conduit/core/containers/bitset.hpp>
#include <conduit/framework/input/gamepad/GamepadButton.hpp>
#include <conduit/framework/input/gamepad/GamepadAxis.hpp>

namespace conduit {
class GamepadState {
private:
    bool m_connected = false;
    bitset<static_cast<sizet>(GamepadButton::MAX_COUNT)> m_current{};
    bitset<static_cast<sizet>(GamepadButton::MAX_COUNT)> m_previous{};
    array<real, static_cast<sizet>(GamepadAxis::MAX_COUNT)> m_axes{};

public:
    GamepadState() = default;
    ~GamepadState() = default;

    bool isConnected() const;
    bool isDown(GamepadButton gamepad_button) const;
    bool wasPressed(GamepadButton gamepad_button) const;
    bool wasReleased(GamepadButton gamepad_button) const;
    real axisValue(GamepadAxis gamepad_axis) const;

    void reset();
    void setConnection(bool state);
    void setButton(GamepadButton gamepad_button, bool state);
    void setAxis(GamepadAxis gamepad_axis, real value);
    void updatePrevious();
}; // class GamepadState
} // namespace conduit

#endif // CONDUIT_GAMEPAD_STATE_HPP