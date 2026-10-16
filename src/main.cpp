#include <iostream>
#include <conduit/window/Window.hpp>
#include <conduit/tests/WorldTester.hpp>

int main()
{
    conduit::WorldTester tester;
    tester.test();
    std::cout << "Hello World!\n";
    return 0;
}