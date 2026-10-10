#ifndef CONDUIT_TYPE_ID_HPP
#define CONDUIT_TYPE_ID_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
template <typename Type, typename IDType = uint32>
struct TypeID {
    IDType value{};
}; // struct TypeID
} // namespace conduit

#endif // CONDUIT_TYPE_ID_HPP