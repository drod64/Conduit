#ifndef CONDUT_GEN_ID_HPP
#define CONDUT_GEN_ID_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
template <typename Type, typename IDType = uint32>
struct GenID {
    static constexpr GenID<Type, IDType> INVALID = GenID<Type, IDType>{};

    IDType value{};

    bool operator==(GenID<Type, IDType> other) const
    {
        return value == other.value;
    }
}; // struct GenID
} // namespace conduit

#endif // CONDUT_GEN_ID_HPP