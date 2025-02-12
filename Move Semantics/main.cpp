#include <iostream>
#include <cassert>

#include <Array.hpp>

int main()
{
    Array<float> a{ 100 };
    Array<float> b{ 50 };

    Array<float> c = a; // Copy constructor.
    assert(c.getSize() == a.getSize());

    // Move constructor.
    Array<float> d = std::move(b);
    assert(d.getSize() == 50);
    assert(b.getSize() == 0);


    return 0;
}
