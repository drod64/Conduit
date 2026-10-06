#include <conduit/input/InputControl.hpp>

conduit::InputControl conduit::InputControl::gamepadAxis(conduit::GamepadAxis axis)
{
    uint32 type = (static_cast<uint32>(InputControlType::GAMEPAD_AXIS) << TYPE_SHIFT);

    uint32 axis_value = static_cast<uint32>(axis);
    
    InputControl result;
    result.m_control = (type | axis_value);

    return result;
}

conduit::InputControl conduit::InputControl::gamepadButton(conduit::GamepadButton button)
{
    uint32 type = (static_cast<uint32>(InputControlType::GAMEPAD_BUTTON) << TYPE_SHIFT);

    uint32 button_value = static_cast<uint32>(button);

    InputControl result;
    result.m_control = (type | button_value);

    return result;
}

conduit::InputControl conduit::InputControl::key(conduit::Key key)
{
    uint32 type = (static_cast<uint32>(InputControlType::KEY) << TYPE_SHIFT);

    uint32 key_value = static_cast<uint32>(key);

    InputControl result;
    result.m_control = (type | key_value);

    return result;
}

conduit::InputControl conduit::InputControl::mouseButton(conduit::MouseButton button)
{
    uint32 type = (static_cast<uint32>(InputControlType::MOUSE_BUTTON) << TYPE_SHIFT);

    uint32 button_value = static_cast<uint32>(button);

    InputControl result;
    result.m_control = (type | button_value);

    return result;
}

bool conduit::InputControl::operator== (const InputControl &other) const
{
    return m_control == other.m_control;
}

conduit::InputControlType conduit::InputControl::type() const
{
    return static_cast<InputControlType>(m_control >> TYPE_SHIFT);
}

conduit::uint32 conduit::InputControl::value() const
{
    return (m_control & VALUE_MASK);
}