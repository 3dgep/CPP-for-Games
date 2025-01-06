#include "Config.hpp"
#include "Game.hpp"

#include <iostream>

class Base
{
public:
    Base() = default;
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    Derived() = default;
    ~Derived() override = default;
};

class Other
{
public:
    Other() = default;
    ~Other() = default;
};


int main()
{

    {

        float f = 3.14f;
        double d = f; // Implicit conversion.
    }
    {
        char c = 'A';
        int i = c; // Implicit conversion.
    }
    {
        int i = 42;
        bool b = i; // Implicit conversion.
    }

    {
        // Narrowing conversion.
        double d = 3.14;
        float f = static_cast<float>(d);
    }
    {
        // Narrowing conversion.
        int i = 65;
        char c = static_cast<char>(i);
    }
    {
        // Signed to unsigned conversion.
        int i = 42;
        unsigned int ui = static_cast<unsigned int>(i);
    }

    {
        int i = 42;
        double d = i; // Implicit conversion
    }
    {
        int i = 42;
        float f = static_cast<float>(i);
    }
    {
        short s = 42;
        float f = s; // Implicit conversion
    }

    {
        double d = 3.14;
        float f = (float)d; // c-Style cast.
    }
    {
        int i = 42;
        char c = (char)i; // C-style cast.
    }

{
    // Const cast.
    const int ci = 42;
    int* i = const_cast<int*>(&ci);
}
{
    // Dynamic cast.
    Base* b = new Derived();
    Derived* d = dynamic_cast<Derived*>(b);
}
{
    // Reinterpret cast
    Derived* d = new Derived();
    Other* o = reinterpret_cast<Other*>(d);
}

    {
        int i = 0b1111111111111111111111111;
        std::cout << "i: " << i << " (0x" << std::hex << i << ")" << std::endl;
        float f = i;
        std::cout << "f: " << f << std::endl;
        int j = f;
        std::cout << "i: " << std::dec << j << " (0x" << std::hex << j << ")" << std::endl;

    }

    std::cout << "JumpHeight: " << JumpHeight << std::endl;
    std::cout << "JumpDuration: " << JumpDuration << std::endl;

    Update();

    return 0;
}