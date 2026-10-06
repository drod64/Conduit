#ifndef CONDUIT_ACTION_ENTRY_HPP
#define CONDUIT_ACTION_ENTRY_HPP
#include <conduit/core/containers/vector.hpp>
#include <conduit/input/Binding.hpp>
#include <conduit/input/ActionState.hpp>

namespace conduit {
struct ActionEntry {
    vector<Binding> bindings;
    ActionState     state;
}; // struct ActionAntry
} // namespace conduit

#endif // CONDUIT_ACTION_ENTRY_HPP