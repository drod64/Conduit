#ifndef CONDUIT_ACTION_MAP_HPP
#define CONDUIT_ACTION_MAP_HPP
#include <cassert>
#include <cstdlib>
#include <conduit/core/containers/unordered_map.hpp>
#include <conduit/core/containers/vector.hpp>
#include <conduit/framework/input/ActionState.hpp>
#include <conduit/framework/input/Binding.hpp>

namespace conduit {
// Forward declaration
class Input;

template <typename Action>
class ActionMap {
private:
    const Input&                                m_input;
    sizet                                       m_gamepad{};
    unordered_map<Action, vector<Binding>>      m_bindings{};
    unordered_map<Action, ActionState>          m_action_states{};

    real evaluate(const Binding &binding) const;
    real evaluate(GamepadAxis gamepad_axis) const;
    real evaluate(GamepadButton gamepad_button) const;
    real evaluate(Key key) const;
    real evaluate(MouseButton mouse_button) const;

public:
    ActionMap(const Input &input, sizet gamepad = 0);
    ~ActionMap() = default;

    void poll();
    bool isDown(Action action) const;
    bool wasPressed(Action action) const;
    bool wasReleased(Action action) const;
    real value(Action action) const;

    void bind(Action action, const Binding &binding);
    void bind(Action action, InputControl inputControl, real scale = static_cast<real>(1));
    void unbind(Action action, const Binding &binding);
}; // class ActionMap<Action>
} // namespace conduit

// Implementation
template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(const Binding &binding) const
{
    return std::visit(
        [this, &binding](const auto& control)
        {
            return evaluate(control) * binding.scale;
        },
        binding.control
    );
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(GamepadAxis gamepad_axis) const
{
    return m_input.gamepads()[m_gamepad].axisValue(gamepad_axis);
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(GamepadButton gamepad_button) const
{
    return (m_input.gamepads()[m_gamepad].isDown(gamepad_button)) ?
            static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(Key key) const
{
    return (m_input.keyboard().isDown(key)) ?
        static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
conduit::real conduit::ActionMap<Action>::evaluate(MouseButton mouse_button) const
{
    return (m_input.mouse().isDown(mouse_button)) ?
        static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
inline conduit::ActionMap<Action>::ActionMap(const Input &input, sizet gamepad) :
m_input(input),
m_gamepad(gamepad)
{}

template <typename Action>
inline void conduit::ActionMap<Action>::poll()
{
    for (const auto &[action, bindings] : m_bindings)
    {
        ActionState &action_state = m_action_states[action];

        action_state.previous = action_state.current;
        action_state.current = static_cast<real>(0);

        for (const Binding &binding : bindings)
        {
            action_state.current += evaluate(binding);
        }

        action_state.current = std::clamp(action_state.current, static_cast<real>(-1), static_cast<real>(1));
    }
}

template <typename Action>
inline bool conduit::ActionMap<Action>::isDown(Action action) const
{
    const ActionState &action_state = m_action_states.at(action);
    return action_state.current != static_cast<real>(0);
}

template <typename Action>
inline bool conduit::ActionMap<Action>::wasPressed(Action action) const
{
    const ActionState &action_state = m_action_states.at(action);
    return action_state.previous == 0 && action_state.current != 0;
}

template <typename Action>
inline bool conduit::ActionMap<Action>::wasReleased(Action action) const
{
    const ActionState &action_state = m_action_states.at(action);
    return action_state.previous != 0 && action_state.current == 0;
}

template <typename Action>
inline conduit::real conduit::ActionMap<Action>::value(Action action) const
{
    const ActionState &action_state = m_action_states.at(action);
    return action_state.current;
}

template <typename Action>
void conduit::ActionMap<Action>::bind(Action action, const Binding &binding)
{
    m_bindings[action].push_back(binding);
}

template <typename Action>
void conduit::ActionMap<Action>::bind(Action action, InputControl inputControl, real scale)
{
    bind(action, Binding(inputControl, scale));
}

template <typename Action>
void conduit::ActionMap<Action>::unbind(Action action, const Binding &binding)
{
    auto &bindings = m_bindings[action];

    auto it = std::erase_if(bindings, [&binding](const Binding &b) -> bool {
        return b.control == binding.control;
    });

    bindings.erase(it);
}

#endif // CONDUIT_ACTION_MAP_HPP