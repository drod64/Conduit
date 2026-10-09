#ifndef CONDUIT_TYPE_ID_GENERATOR_HPP
#define CONDUIT_TYPE_ID_GENERATOR_HPP
#include <conduit/framework/IDs/TypeID.hpp>
#include <atomic>

namespace conduit {
template <typename Category>
class TypeIDGenerator {
private:
    /**
     * @return the next ID in the Category namespace
     */
    static uint32 nextID()
    {
        static std::atomic<uint32> counter = {0};

        return counter.fetch_add(1, std::memory_order_relaxed);
    }

public:
    /**
     * Retrieves the ID for the passed type.
     * @tparam Type the type to get the ID for
     * @return the ID of the Type in the Category namespace
     */
    template <typename Type>
    static TypeID<Category> get()
    {
        static const uint32 ID = nextID();
        return {ID};
    }
}; // class TypeIDGenerator
} // namespace conduit

#endif // CONDUIT_TYPE_ID_GENERATOR_HPP