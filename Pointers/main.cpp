#include <iostream>

int main()
{
    int i = 3;
    const char* name = "Jeremiah";

    int* pi = nullptr; // &i;
    pi = &i;

    if (pi != nullptr)
    {
        *pi = 3;
    }

    std::cout << "Address of i: " << pi << std::endl;
    std::cout << "Value of i: " << *pi << std::endl;

    *pi = 4;

    std::cout << "Value of i: " << *pi << std::endl;

    if (*pi == i)
    {
        std::cout << "The values are both " << i << std::endl;
    }

    std::cout << "The first letter of " << name << " is " << name[0] << std::endl;

    const char* const lastName = "van Oosten";

    const unsigned char values[] = { 1, 2, 3, 4 };

    std::cout << *(values + 1) << std::endl;

    int* arr = new int[100];

    *(arr + 0) = 0;
    arr[0] = 0;
    arr[99] = 99;
    *(arr + 99) = 99;

    delete[] arr;

    int& ri = i;

    ri = i; // This will only set the value of i.

    ri = 5;

    std::cout << "Value of i: " << i << std::endl;

    return 0;
}