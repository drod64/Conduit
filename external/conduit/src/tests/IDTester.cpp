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

    // Test multiple creation calls.
    Entity e0 = manager.createID();
    Entity e1 = manager.createID();
    Entity e2 = manager.createID();
    {
        assert(e0.value == 1);
        assert(e1 == Entity::INVALID);
        assert(e2 == Entity::INVALID);
    }

    // Destroy IDs.
    manager.destroyID(e0);
    manager.destroyID(e1);
    manager.destroyID(e2);
    {
        assert(!manager.isValid(e0));
        assert(!manager.isValid(e1));
        assert(!manager.isValid(e2));
    }

    // Test next expected value (according to a 1 bit allocated index and allocation of 63 bits for generation).
    e0 = manager.createID();
    {
        assert(e0.value == 3);
    }
    manager.destroyID(e0);

    // Test life-cycle.
    sizet iterations = 1'000'000;
    for (sizet i = 0; i < iterations; ++i)
    {
        Entity id = manager.createID();

        assert(manager.isValid(id));

        manager.destroyID(id);

        assert(!manager.isValid(id));
    }

    // For overflow testing, explicitly set the generation to it's max valid value.
    const uint64 MAX_GENERATION = (uint64{1} << uint64{63}) - uint64{1};
    manager.setGeneration(1, MAX_GENERATION);

    // Create new ID and ensure the max generation value is valid.
    Entity maxID = manager.createID();
    {
        assert(maxID.value == std::numeric_limits<uint64>::max());
        assert(manager.isValid(maxID));
    }

    // Destroy ID. Index should now be retired.
    manager.destroyID(maxID);

    // With the index retired, we should get only invalid IDs for the next creation calls.
    for (sizet i = 0; i < 1'000; ++i)
    {
        Entity invalidID = manager.createID();
        {
            assert(invalidID.value == 0);
            assert(!manager.isValid(invalidID));
        }
    }

    std::cout << "[IDTester]::testGenIDs() -> Passed...\n";
}