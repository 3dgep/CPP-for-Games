#include <iostream>
#include <functional>

// A function that takes 2 ints and returns an int.
using add_func = std::function<int(int, int)>;

int call_func(add_func f, int a, int b)
{
    return f(a, b);
}

int main()
{
    auto f = [](int a, int b) { return a + b; };

    int c = f(5, 10);
    int l = call_func(f, 5, 10);

    int a = 5;
    int b = 10;
    int e = 0;
    auto g = [&]{return e + a + b; };

    a = 10;
    b = 15;
    e = 5;

    int d = g();
    std::cout << "g(): " << d << std::endl;

    // C++ 14: Generic lambdas.
    // C++ 20: explicit template parameters.
    auto h = [] <typename T> (T a, T b) { return a + b; };

    auto i = h(5, 10);
    auto j = h(5.0f, 10.0f);
    auto k = h(5.0f, 10.0f);

    return 0;
}