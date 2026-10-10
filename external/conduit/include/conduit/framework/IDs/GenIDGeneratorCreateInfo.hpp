#ifndef CONDUIT_GEN_ID_GENERATOR_CREATE_INFO_HPP
#define CONDUIT_GEN_ID_GENERATOR_CREATE_INFO_HPP
#include <conduit/core/primitives.hpp>

namespace conduit {
struct GenIDGeneratorCreateInfo {
public:
    uint32 initialCapacity = 64;
    uint32 maxCapacity = 0;
}; // struct GenIDGeneratorCreateInfo
} // namespace conduit

#endif // CONDUIT_GEN_ID_GENERATOR_CREATE_INFO_HPP