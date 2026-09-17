#include <conduit/framework/input/gamepad/GamepadState.hpp>

bool conduit::GamepadState::isConnected() const
{
    return m_connected;
}

bool conduit::GamepadState::isDown(GamepadButton gamepad_button) const
{
    const sizet index = static_cast<sizet>(gamepad_button);

    return m_current.test(index);
}

bool conduit::GamepadState::wasPressed(GamepadButton gamepad_button) const
{
    const sizet index = static_cast<sizet>(gamepad_button);

    return !m_previous.test(index) && m_current.test(index);
}

bool conduit::GamepadState::wasReleased(GamepadButton gamepad_button) const
{
    const sizet index = static_cast<sizet>(gamepad_button);

    return m_previous.test(index) && !m_current.test(index);
}

conduit::real conduit::GamepadState::axisValue(GamepadAxis gamepad_axis) const
{
    const sizet index = static_cast<sizet>(gamepad_axis);

    return m_axes[index];
}

void conduit::GamepadState::reset()
{
    m_axes.fill(static_cast<real>(0));
    m_current.reset();
    m_previous.reset();
}

void conduit::GamepadState::setConnection(bool state)
{
    m_connected = state;
}

void conduit::GamepadState::setButton(GamepadButton gamepad_button, bool state)
{
    sizet index = static_cast<sizet>(gamepad_button);

    m_current.set(index, state);
}

void conduit::GamepadState::setAxis(GamepadAxis gamepad_axis, real value)
{
    sizet index = static_cast<sizet>(gamepad_axis);
    m_axes[index] = value;
}

void conduit::GamepadState::updatePrevious()
{
    m_previous = m_current;
}