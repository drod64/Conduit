#include <iostream>
#include <conduit/window/Window.hpp>
#include <conduit/tests/InputTester.hpp>

int main()
{
    conduit::InputTester tester;
    tester.test();
    std::cout << "Hello World!\n";
    return 0;
}