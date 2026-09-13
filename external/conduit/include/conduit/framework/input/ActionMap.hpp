#ifndef CONDUIT_ACTION_MAP_HPP
#define CONDUIT_ACTION_MAP_HPP
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
    const Input &m_input;
    unordered_map<Action, vector<Binding>>      m_bindings;
    unordered_map<Action, ActionState>          m_action_states;

    void updateActionStates();
    void queryAxes(const Binding& binding, ActionState &state);
    void queryButtons(const Binding &binding, ActionState &state);

public:
    ActionMap(const Input &input);
    ~ActionMap() = default;

    void poll();
    bool isDown(Action action) const;
    bool wasPressed(Action action) const;
    bool wasReleased(Action action) const;
    real value(Action action) const;

    void bind(Action action, const Binding &binding);
    void unbind(Action action, const Binding &binding);
}; // class ActionMap<Action>
} // namespace conduit

// Implementation
template <typename Action>
inline void conduit::ActionMap<Action>::updateActionStates()
{
    for (const auto &[action, bindings] : m_bindings)
    {
        ActionState &action_state = m_action_states[action];

        action_state = {};

        for (const auto &binding : bindings)
        {
            switch (binding.type)
            {
                case InputControlType::AXIS:
                    queryAxes(binding, action_state);
                    break;
                
                case InputControlType::BUTTON:
                    queryButtons(binding, action_state);
                    break;
                
                default:
                    break;
            }

        }
    }
}

template <typename Action>
inline void conduit::ActionMap<Action>::queryAxes(const Binding &binding, ActionState &state)
{
    // TODO
}

template <typename Action>
inline void conduit::ActionMap<Action>::queryButtons(const Binding &binding, ActionState &state)
{
    // Local variables that tell us whether the current binding is...
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
            cur_binding_state = m_input.keyboard().current.test(binding.control);
            prev_binding_state = m_input.keyboard().previous.test(binding.control);
            break;

        case InputDevice::MOUSE:
            cur_binding_state = m_input.mouse().current.test(binding.control);
            prev_binding_state = m_input.mouse().previous.test(binding.control);
            break;

        case InputDevice::GAMEPAD:
            // TODO
            break;

        default:
            cur_binding_state = false;
            prev_binding_state = false;
            break;
    }

    // Update local binding state variables
    down = cur_binding_state;
    pressed = !prev_binding_state && cur_binding_state;
    released = prev_binding_state && !cur_binding_state;

    // Commutatively update action state
    state.down      |= down;
    state.pressed   |= pressed;
    state.released  |= released;
    state.value = (state.down) ? static_cast<real>(1) : static_cast<real>(0);
}

template <typename Action>
inline conduit::ActionMap<Action>::ActionMap(const Input &input) :
m_input(input)
{}

template <typename Action>
inline void conduit::ActionMap<Action>::poll()
{
    updateActionStates();
}

template <typename Action>
inline bool conduit::ActionMap<Action>::isDown(Action action) const
{
    return m_action_states.at(action).down;
}

template <typename Action>
inline bool conduit::ActionMap<Action>::wasPressed(Action action) const
{
    return m_action_states.at(action).pressed;
}

template <typename Action>
inline bool conduit::ActionMap<Action>::wasReleased(Action action) const
{
    return m_action_states.at(action).released;
}

template <typename Action>
inline conduit::real conduit::ActionMap<Action>::value(Action action) const
{
    return m_action_states.at(action).value;
}

template <typename Action>
void conduit::ActionMap<Action>::bind(Action action, const Binding &binding)
{
    m_bindings[action].push_back(binding);
}

template <typename Action>
void conduit::ActionMap<Action>::unbind(Action action, const Binding &binding)
{
    auto &bindings = m_bindings[action];

    auto it = std::erase_if(bindings, [&binding](const Binding &b) -> bool {
        return (b.control == binding.control) && (b.device == binding.device) && (b.type == binding.type);
    });

    bindings.erase(it);
}


#endif // CONDUIT_ACTION_MAP_HPP
