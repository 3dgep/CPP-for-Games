#include <iostream>
#include <Temperature.hpp>

#include <chrono>

int main()
{
    Temperature _100c = 100.0_C;
    Temperature _212f = 212.0_F;

    std::cout << _100c.k << std::endl;
    std::cout << _212f.k << std::endl;

    using namespace std::chrono_literals;

    auto second = 1s;
    auto millisecond = 1ms;
    auto nanosecond = 1ns;

    return 0;
}