#ifndef CONDUIT_ACTION_STATE_HPP
#define CONDUIT_ACTION_STATE_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
struct ActionState {
    bool down       = false;
    bool pressed    = false;
    bool released   = false;
    real value      = static_cast<real>(0);
}; 
} // namespace conduit

#endif // CONDUIT_ACTION_STATE_HPP