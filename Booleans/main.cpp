#include <iostream>

int main()
{
    bool t = true;
    bool f = false;

    bool is_true = true;
    bool is_false = !is_true;

    bool _and = is_true && is_false; // this will always be false.
    bool _or = is_true || is_false; // this will always be true.

    std::cout << "Size of bool: " << sizeof(bool) << std::endl;

    return 0;
}