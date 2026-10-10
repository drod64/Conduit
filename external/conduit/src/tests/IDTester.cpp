#include <conduit/tests/IDTester.hpp>
#include <conduit/core/primitives.hpp>
#include <iostream>

void conduit::IDTester::test()
{
    testTypeIDs();
    testGenIDs();
    std::cout << "[IDTester]::test() -> Passed all unit tests.\n";
}

void conduit::IDTester::testTypeIDs()
{
    struct ResourceTag {};
    using ResourceIDGenerator = TypeIDGenerator<ResourceTag>;
    using ResourceID = TypeID<ResourceTag>;
    struct Input {};
    struct Time {};
    struct Audio {};

    ResourceID inputID   = ResourceIDGenerator::get<Input>();
    ResourceID timeID    = ResourceIDGenerator::get<Time>();
    ResourceID audioID   = ResourceIDGenerator::get<Audio>();

    assert(inputID.value == 0);
    assert(timeID.value == 1);
    assert(audioID.value == 2);

    std::cout << "[IDTester::testTypeIDs()] -> Passed...\n";
}

void conduit::IDTester::testGenIDs()
{
    struct EntityTag{};

    using EntityManager = GenIDGenerator<EntityTag, uint64, 1>;
    using Entity        = GenID<EntityTag, uint64>;

    EntityManager manager;

    Entity e0 = manager.createID();
    Entity e1 = manager.createID();
    Entity e2 = manager.createID();
    {
        assert(e0.value == 1);
        assert(e1 == Entity::INVALID);
        assert(e2 == Entity::INVALID);
    }

    manager.destroyID(e0);
    manager.destroyID(e1);
    manager.destroyID(e2);
    {
        assert(!manager.isValid(e0));
        assert(!manager.isValid(e1));
        assert(!manager.isValid(e2));
    }

    e0 = manager.createID();
    {
        assert(e0.value == 3);
    }
    manager.destroyID(e0);

    conduit::sizet iterations = 1'000'000;
    for (conduit::sizet i = 0; i < iterations; ++i)
    {
        Entity id = manager.createID();

        assert(manager.isValid(id));

        manager.destroyID(id);

        assert(!manager.isValid(id));
    }

    std::cout << "[IDTester]::testGenIDs() -> Passed...\n";
}