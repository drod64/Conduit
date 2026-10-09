#include <conduit/tests/IDTester.hpp>
#include <iostream>

void conduit::IDTester::test()
{
    testTypeIDs();
    std::cout << "[IDTester]::test() -> Passed all tests.\n";
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