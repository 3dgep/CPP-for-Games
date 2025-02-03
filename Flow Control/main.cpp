#include <iostream>

int main()
{
    // If condition.
    if (true)
    {
        std::cout << "This is true." << std::endl;
    }

    std::cout << "The code will continue here..." << std::endl;

    if (false)
    {
        std::cout << "The condition is true." << std::endl;
    }
    else
    {
        std::cout << "The condition is false." << std::endl;
    }

    int i = 10;

    if (i < 5)
    {
        std::cout << "The number is less than 5." << std::endl;
    }
    else if (i < 8 )
    {
        std::cout << "The number is less than 8." << std::endl;
    }
    else if (i >= 10)
    {
        std::cout << "The number is greater than or equal to 10." << std::endl;
    }
    else
    {
        std::cout << "The number is between 5 and 7" << std::endl;
    }

    switch (i)
    {
    case 0:
        std::cout << "You fail!" << std::endl;
        break;
    case 1:
        std::cout << "You almost failed." << std::endl;
        break;
    case 10:
        std::cout << "Excellent!" << std::endl;
        break;
    default:
        std::cout << "Your grade was: " << i << std::endl;
        break;
    }

    // While loops.
    i = 0;
    while (i < 10)
    {
        std::cout << "i: " << i << std::endl;
        ++i;
    }

    // Do-while loop.
    i = 0;
    do
    {
        std::cout << "i: " << i << std::endl;
        ++i;
    } while (i < 10);

    // For loops.
    for (int j = 0; j < 10; ++j)
    {
        std::cout << "j: " << j << std::endl;
        if (j > 5)
            break;
    }

    int arr[] = { 1, 2, 3, 4, 5 };
    // C++20 adds initialize.
    for (int i = 0; int v : arr)
    {
        std::cout << "v[" << i << "]: " << v << std::endl;
        ++i;        
    }

    return 0;
}