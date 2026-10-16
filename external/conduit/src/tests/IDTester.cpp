#include <conduit/tests/IDTester.hpp>
#include <conduit/core/primitives.hpp>
#include <iostream>
#include <random>
#include <cassert>

void conduit::IDTester::test()
{
    testTypeIDs();
    testGenIDs1();
    testGenIDs2();
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

    std::cout << "[IDTester]::testTypeIDs() -> Passed...\n";
}

void conduit::IDTester::testGenIDs1()
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

    std::cout << "[IDTester]::testGenIDs1() -> Passed...\n";
}

void conduit::IDTester::testGenIDs2()
{
    struct ConstraintTag {};
    using ConstraintManager = GenIDGenerator<ConstraintTag, uint64, 32>;
    using ConstraintID      = GenID<ConstraintTag, uint64>;

    ConstraintManager manager;

    constexpr uint32 ITERATIONS = 10000;
    constexpr size_t MAX_ALIVE_IDS = 256;

    // Fixed seed makes failures reproducible.
    std::mt19937_64 rng{0xC0FFEEULL};

    std::vector<ConstraintID> aliveIDs;
    std::vector<ConstraintID> staleIDs;

    for (uint32 iteration = 0; iteration < ITERATIONS; ++iteration)
    {
        // Select an operation: create, destroy, validate, or stale destroy.
        std::uniform_int_distribution<uint32> operationDist(0, 99);
        const uint32 operation = operationDist(rng);

        if (operation < 40 && aliveIDs.size() < MAX_ALIVE_IDS)
        {
            // Create an ID.
            ConstraintID id = manager.createID();

            assert(manager.isValid(id));

            // Previously destroyed IDs must not become valid again.
            for (const ConstraintID staleID : staleIDs)
                assert(!manager.isValid(staleID));

            aliveIDs.push_back(id);
        }
        else if (operation < 75 && !aliveIDs.empty())
        {
            // Destroy a randomly selected live ID.
            std::uniform_int_distribution<size_t> indexDist(
                0, aliveIDs.size() - 1);

            const size_t selected = indexDist(rng);
            const ConstraintID id = aliveIDs[selected];

            manager.destroyID(id);

            assert(!manager.isValid(id));

            staleIDs.push_back(id);
            aliveIDs.erase(aliveIDs.begin() + selected);
        }
        else if (operation < 95)
        {
            // Validate every currently live ID.
            for (const ConstraintID id : aliveIDs)
                assert(manager.isValid(id));
        }
        else if (!staleIDs.empty())
        {
            // Occasionally attempt to destroy an already stale ID.
            std::uniform_int_distribution<size_t> indexDist(
                0, staleIDs.size() - 1);

            const ConstraintID id = staleIDs[indexDist(rng)];

            manager.destroyID(id);
            assert(!manager.isValid(id));
        }

        // Periodically verify all lifecycle invariants.
        if (iteration % 100 == 0)
        {
            for (const ConstraintID id : aliveIDs)
                assert(manager.isValid(id));

            for (const ConstraintID id : staleIDs)
                assert(!manager.isValid(id));
        }
    }

    // Final cleanup.
    for (const ConstraintID id : aliveIDs)
    {
        manager.destroyID(id);
        assert(!manager.isValid(id));
    }

    for (const ConstraintID id : staleIDs)
        assert(!manager.isValid(id));

    std::cout << "[IDTester]::testGenIDs2() -> Passed...\n";
}