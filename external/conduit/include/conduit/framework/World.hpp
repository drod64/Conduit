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
    entt::organizer         m_scheduler;
    entt::dispatcher        m_events;
    // commandBuffer

public:
    World() = default;
    ~World() = default;

    ///////////////////////////////
    //    Registry operations    //
    /////////////////////////////// 
    [[nodiscard]] entt::entity createEntity();

    uint16_t destroyEntity(const entt::entity entity);

    template <typename T, typename... Args>
    T& emplaceComponent(const entt::entity entity, Args&&... args);

    template <typename T, typename... Args>
    T& emplaceOrReplaceComponent(const entt::entity entity, Args&&... args);

    template <typename T, typename... Args>
    T& replaceComponent(const entt::entity entity, Args&&... args);

    template <typename T>
    void removeComponent(const entt::entity entity);

    template <typename T, typename... Args>
    [[nodiscard]] T& getOrEmplaceComponent(const entt::entity entity, Args&&... args);

    template <typename T>
    [[nodiscard]] T& getComponent(const entt::entity entity);

    template <typename T>
    [[nodiscard]] const T& getComponent(const entt::entity entity) const;

    template <typename T>
    [[nodiscard]] T* tryGetComponent(const entt::entity entity);

    template <typename T>
    [[nodiscard]] const T* tryGetComponent(const entt::entity entity) const;

    [[nodiscard]] bool isOrphan(const entt::entity entity) const;

    template <typename To, typename From>
    void sort();

    [[nodiscard]] bool isValid(const entt::entity entity) const;

    //////////////////////////////
    //    Context Operations    //
    //////////////////////////////
    template <typename T, typename... Args>
    T& emplaceContext(Args&&... args);

    template <typename T>
    bool removeContext();

    template <typename T>
    [[nodiscard]] T& getContext();

    template <typename T>
    [[nodiscard]] const T& getContext() const;

    template <typename T>
    T& insertOrAssignContext(T&& value);

}; // class World
} // namespace conduit

// Implementation

entt::entity conduit::World::createEntity()
{
    return m_registry.create();
}

uint16_t conduit::World::destroyEntity(const entt::entity entity)
{
    return m_registry.destroy(entity);
}

template <typename T, typename... Args>
T& conduit::World::emplaceComponent(const entt::entity entity, Args&&... args)
{
    return m_registry.emplace<T>(entity, std::forward<Args>(args)...);
}

template <typename T, typename... Args>
T& conduit::World::emplaceOrReplaceComponent(const entt::entity entity, Args&&... args)
{
    return m_registry.emplace_or_replace<T>(entity, std::forward<Args>(args)...);
}

template <typename T, typename... Args>
T& conduit::World::replaceComponent(const entt::entity entity, Args&&... args)
{
    return m_registry.replace<T>(entity, std::forward<Args>(args)...);
}

template <typename T>
void conduit::World::removeComponent(const entt::entity entity)
{
    m_registry.remove<T>(entity);
}

template <typename T, typename... Args>
T& conduit::World::getOrEmplaceComponent(const entt::entity entity, Args&&... args)
{
    return m_registry.get_or_emplace<T>(entity, std::forward<Args>(args)...);
}

template <typename T>
T& conduit::World::getComponent(const entt::entity entity)
{
    return m_registry.get<T>(entity);
}

template <typename T>
const T& conduit::World::getComponent(const entt::entity entity) const
{
    return m_registry.get<T>(entity);
}

template <typename T>
T* conduit::World::tryGetComponent(const entt::entity entity)
{
    return m_registry.try_get<T>(entity);
}

template <typename T>
const T* conduit::World::tryGetComponent(const entt::entity entity) const
{
    return m_registry.try_get<T>(entity);
}

bool conduit::World::isOrphan(const entt::entity entity) const
{
    return m_registry.orphan(entity);
}

template <typename To, typename From>
void conduit::World::sort()
{
    m_registry.sort<To, From>();
}

bool conduit::World::isValid(const entt::entity entity) const
{
    return m_registry.valid(entity);
}

template <typename T, typename... Args>
T& conduit::World::emplaceContext(Args&&... args)
{
    return m_registry.ctx().emplace<T>(std::forward<Args>(args)...);
}

template <typename T>
bool conduit::World::removeContext()
{
    return m_registry.ctx().erase<T>()
}

template <typename T>
T& conduit::World::getContext()
{
    return m_registry.ctx().get<T>();
}

template <typename T>
const T& conduit::World::getContext() const
{
    return m_registry.ctx().get<T>();
}

template <typename T>
T& conduit::World::insertOrAssignContext(T&& value)
{
    return m_registry.ctx().insert_or_assign(std::forward<T>(value));
}

#endif // CONDUIT_WORLD_HPP