#include <iostream>

decltype(auto) max(const auto& a, const auto& b)
{
    return a > b ? a : b;
}

void swap(auto& a, auto& b)
{
    auto tmp = std::move(a);
    a = std::move(b);
    b = std::move(tmp);
}

int main()
{
    {
        int a = 5;
        int b = 10;

        int c = max(5, 10);
    }

    {
        int a = 5;
        double b = 10.0;

        auto c = max(a, b);
    }

    {
        int a = 5;
        int b = 10;
        swap(a, b);
        std::cout << "a: " << a << std::endl;
        std::cout << "b: " << b << std::endl;

    }

    return 0;
}