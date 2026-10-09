#ifndef CONDUIT_ID_TESTER_HPP
#define CONDUIT_ID_TESTER_HPP
#include <conduit/framework/IDs/TypeIDGenerator.hpp>

namespace conduit {
class IDTester {
public:
    void test();

private:
    void testTypeIDs();
}; // class IDTester
} // namespace conduit

#endif // CONDUIT_ID_TESTER_HPP