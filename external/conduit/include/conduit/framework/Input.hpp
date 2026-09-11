#ifndef CONDUIT_INPUT_HPP
#define CONDUIT_INPUT_HPP
#include <raylib.h>
#include <conduit/core/containers/unordered_map.hpp>
#include <conduit/core/containers/vector.hpp>
#include <conduit/framework/helpers/ActionState.hpp>
#include <conduit/framework/helpers/Binding.hpp>
#include <conduit/framework/helpers/KeyboardState.hpp>
#include <conduit/framework/helpers/MouseState.hpp>
#include <conduit/framework/helpers/GamepadState.hpp>

namespace conduit {
template <typename Action>
class Input {
private:
    unordered_map<Action, vector<Binding>>      m_bindings;
    unordered_map<Action, ActionState>          m_action_states;
    KeyboardState                               m_keyboard_states;
    MouseState                                  m_mouse_states;
    GamepadState                                m_gamepad_states;

    real axisValue(const Binding &binding) const;
    void updatePhysicalStates();
    void updateActionStates();

public:
    Input() = default;
    ~Input() = default;

    void poll();
    bool isDown(Action action) const;
    bool wasPressed(Action action) const;
    bool wasReleased(Action action) const;
    real value(Action action) const;

    void bind(Action action, const Binding &binding);
    void unbind(Action action, const Binding &binding);
}; // class Input
} // namespace conduit

// Implementation

template <typename Action>
conduit::real conduit::Input<Action>::axisValue(const Binding &binding) const
{
    // TODO
    return static_cast<real>(0);
}

template <typename Action>
void conduit::Input<Action>::updatePhysicalStates()
{
    // Update previous states.
    m_keyboard_states.previous = m_keyboard_states.current;
    m_mouse_states.previous = m_mouse_states.current;
    m_gamepad_states.previous = m_gamepad_states.current;

    // Update current states.
    for (sizet i = 0; i < config::KEYBOARD_KEY_COUNT; ++i)
    {
        m_keyboard_states.current.set(i, IsKeyDown(static_cast<int>(i)));
    }

    for (sizet i = 0; i < config::MOUSE_BUTTON_COUNT; ++i)
    {
        m_mouse_states.current.set(i, IsMouseButtonDown(static_cast<int>(i)));
    }
    using raylibVec2 = Vector2;
    raylibVec2 rl_mouse_position = raylibVec2(GetMousePosition());
    raylibVec2 rl_mouse_delta = raylibVec2(GetMouseDelta());
    raylibVec2 rl_mouse_wheel = raylibVec2(GetMouseWheelMoveV());
    // Translate to sm::Vec2
    m_mouse_states.position = {rl_mouse_position.x, rl_mouse_position.y};
    m_mouse_states.delta    = {rl_mouse_delta.x, rl_mouse_delta.y};
    m_mouse_states.wheel    = {rl_mouse_wheel.x, rl_mouse_delta.y};

    for (sizet i = 0; i < config::GAMEPAD_BUTTON_COUNT; ++i)
    {
        m_gamepad_states.current.set(i, IsGamepadButtonDown(0, static_cast<int>(i)));
    }
}

template <typename Action>
void conduit::Input<Action>::updateActionStates()
{
    for (const auto &[action, bindings] : m_bindings)
    {
        ActionState &action_state = m_action_states[action];

        action_state = {};

        for (const auto &binding : bindings)
        {
            // Local variables that tell us whether the current action is...
            bool down = false;
            bool pressed = false;
            bool released = false;

            // Local variables that let us know the physical state of the binding
            bool cur_binding_state = false;
            bool prev_binding_state = false;

            // Acquire current and previous physical state of the binding (depending on the binding's device signature)
            switch (binding.device)
            {
                case InputDevice::KEYBOARD:
                    cur_binding_state = m_keyboard_states.current.test(binding.control);
                    prev_binding_state = m_keyboard_states.previous.test(binding.control);
                    break;

                case InputDevice::MOUSE:
                    cur_binding_state = m_mouse_states.current.test(binding.control);
                    prev_binding_state = m_mouse_states.previous.test(binding.control);
                    break;

                case InputDevice::GAMEPAD:
                    cur_binding_state = m_gamepad_states.current.test(binding.control);
                    prev_binding_state = m_gamepad_states.previous.test(binding.control);
                    break;

                default:
                    cur_binding_state = false;
                    prev_binding_state = false;
                    break;
            }

            down = cur_binding_state;
            pressed = !prev_binding_state && cur_binding_state;
            released = prev_binding_state && !cur_binding_state;

            action_state.down      |= down;
            action_state.pressed   |= pressed;
            action_state.released  |= released;
        }

        action_state.value = (action_state.down) ? static_cast<real>(1) : static_cast<real>(0);
    }
}

template <typename Action>
void conduit::Input<Action>::poll()
{
    updatePhysicalStates();

    updateActionStates();
}

template <typename Action>
bool conduit::Input<Action>::isDown(Action action) const
{
    return m_action_states.at(action).down;
}

template <typename Action>
bool conduit::Input<Action>::wasPressed(Action action) const
{
    return m_action_states.at(action).pressed;
}

template <typename Action>
bool conduit::Input<Action>::wasReleased(Action action) const
{
    return m_action_states.at(action).released;
}

template <typename Action>
conduit::real conduit::Input<Action>::value(Action action) const
{
    return m_action_states.at(action).value;
}

template <typename Action>
void conduit::Input<Action>::bind(Action action, const Binding &binding)
{
    m_bindings[action].push_back(binding);
}

template <typename Action>
void conduit::Input<Action>::unbind(Action action, const Binding &binding)
{
    auto &bindings = m_bindings[action];

    auto it = std::erase_if(bindings, [&binding](const Binding &b) -> bool {
        return (b.control == binding.control) && (b.device == binding.device) && (b.type == binding.type);
    });

    bindings.erase(it);
}

#endif // CONDUIT_INPUT_HPP