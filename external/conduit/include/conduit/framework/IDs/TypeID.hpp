#ifndef CONDUIT_TYPE_ID_HPP
#define CONDUIT_TYPE_ID_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
template <typename Type>
struct TypeID {
    uint32 value{};
}; // struct TypeID
} // namespace conduit

#endif // CONDUIT_TYPE_ID_HPP