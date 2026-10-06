#ifndef INPUT_CONTROL_HPP
#define INPUT_CONTROL_HPP
#include <conduit/core/primitives.hpp>
#include <conduit/input/InputControlType.hpp>
#include <conduit/input/InputTypes.hpp>

namespace conduit {
/**
 * Packed representation of an input control.
 * It keeps track of it's input type and associated axis/button/key.
 */
class InputControl {
private:
    static constexpr uint32 TYPE_BITS = 2;
    static constexpr uint32 VALUE_BITS = (sizeof(uint32) * 8) - TYPE_BITS;
    
    static constexpr uint32 TYPE_SHIFT = VALUE_BITS;
    static constexpr uint32 VALUE_MASK = (1 << TYPE_SHIFT) - 1;
    
    uint32 m_control{};

    
public:
    InputControl() = default;
    ~InputControl() = default;
    
    InputControl(const InputControl &other) = default;
    InputControl& operator= (const InputControl &other) = default;
    
    constexpr InputControl(InputControl &&other) = default;
    constexpr InputControl& operator= (InputControl && other) = default;

    /**
     * Produces an InputControl that is associated with the gamepad axis input type.
     * @param axis the GamepadAxis to associate with this InputControl
     * @return an InputControl for a gamepad axis
     */
    static InputControl gamepadAxis(GamepadAxis axis);

    /**
     * Produces an InputControl that is associated with the gamepad button input type.
     * @param axis the GamepadButton to associate with this InputControl
     * @return an InputControl for a gamepad button
     */
    static InputControl gamepadButton(GamepadButton button);

    /**
     * Produces an InputControl that is associated with the key input type.
     * @param axis the Key to associate with this InputControl
     * @return an InputControl for a key
     */
    static InputControl key(Key key);
    
    /**
     * Produces an InputControl that is associated with the mouse button input type.
     * @param axis the MouseButton to associate with this InputControl
     * @return an InputControl for a mouse button
     */
    static InputControl mouseButton(MouseButton button);

    /**
     * Checks if this and other are equal.
     * @param other the other InputControl to compare to
     */
    bool operator== (const InputControl &other) const;

    /**
     * @return the associated input type of this InputControl
     */
    InputControlType type() const;

    /**
     * Cast the result of this function to a GamepadAxis, GamepadButton, Key, or MouseButton enum
     * (depending on it's type) to make use of it.
     * @return a conduit::uint32 that represents the associated input axis/button/key
     */
    uint32 value() const;
}; // class InputControl
} // namespace conduit
#endif // INPUT_CONTROL_HPP