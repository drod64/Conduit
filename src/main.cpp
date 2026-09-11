#include <iostream>
#include <conduit/tests/InputTester.hpp>

int main()
{
    conduit::InputTester inputTester;
    inputTester.test();
    
    std::cout << "Hello World!\n";
    return 0;
}