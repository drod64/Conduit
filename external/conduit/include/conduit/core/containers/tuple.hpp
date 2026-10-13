#ifndef CONDUIT_TUPLE_HPP
#define CONDUIT_TUPLE_HPP
#include <tuple>

namespace conduit {
    template <typename... Args>
    using tuple = std::tuple<Args...>;
} // namespace conduit

#endif // CONDUIT_TUPLE_HPP