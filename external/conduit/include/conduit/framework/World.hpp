#ifndef CONDUIT_WORLD_HPP
#define CONDUIT_WORLD_HPP
#include <entt/entt.hpp>
#include <algorithm>
#include <conduit/core/primitives.hpp>

namespace conduit {
class World {
private:
    // &engine
    entt::registry          m_registry;
    // systems
    entt::dispatcher        m_events;
    // commandBuffer

public:
    World() = default;
    ~World() = default;

    conduit::entity createEntity();

    void destroyEntity();

    template <typename T, typename... Args>
    T& emplaceComponent(conduit::entity entity, Args&&... args);

    template <typename T, typename... Args>
    T& emplaceOrReplaceComponent(conduit::entity entity, Args&&... args);

    template <typename T, typename... Args>
    T& replaceComponent(conduit::entity entity, Args&&... args);

    template <typename T>
    void removeComponent(conduit::entity entity);

    template <typename T>
    T& getComponent(conduit::entity entity);

    template <typename T>
    const T& getComponent(conduit::entity entity) const;

    template <typename T>
    T* tryGetComponent(conduit::entity entity);

    template <typename T>
    const T* tryGetComponent(conduit::entity entity) const;

    template <typename T, typename... Args>
    T& getOrEmplaceComponent(conduit::entity entity, Args&&... args);

    bool isOrphan(conduit::entity entity) const;

    template <typename To, typename From>
    void sort();

    bool isValid(conduit::entity entity) const;
}; // class World
} // namespace conduit

#endif // CONDUIT_WORLD_HPP