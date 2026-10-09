#include <iostream>
#include <conduit/window/Window.hpp>
#include <conduit/tests/IDTester.hpp>

int main()
{
    conduit::IDTester tester;
    tester.test();
    std::cout << "Hello World!\n";
    return 0;
}