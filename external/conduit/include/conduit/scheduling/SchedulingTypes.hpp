#ifndef CONDUIT_SCHEDULING_TYPES_HPP
#define CONDUIT_SCHEDULING_TYPES_HPP
#include <conduit/framework/IDs/GenID.hpp>
#include <conduit/framework/IDs/TypeID.hpp>
#include <conduit/core/containers/vector.hpp>

namespace conduit::scheduling {
    enum class AccessMode {
        READ = 0,
        WRITE
    }; // enum class AccessMode

    struct ResourceTag {};
    using ResourceID            = TypeID<ResourceTag, uint64>;
    struct ResourceAccess {
        ResourceID resource{};
        AccessMode mode{AccessMode::READ};
    }; // struct ResourceAccess

    struct WorkTag {};
    using WorkID                = GenID<WorkTag, uint64>;
    struct WorkDescription {
        WorkID                  id{};
        vector<ResourceAccess>  accesses;
        vector<WorkID>          dependencies;
    }; // struct WorkDescription

    using WorkFunction = void(*)(void *);

    struct StoredCallable {
        void *              context{};
        WorkFunction        invoke{};
        void                (*destroy)(void*){};
    }; // struct StoredCallable

    struct RegisteredWork {
        WorkDescription description;
        StoredCallable  callable;
    }; // struct RegisteredWork
} // namespace conduit::scheduling

#endif // CONDUIT_SCHEDULING_TYPES_HPP