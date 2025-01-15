#include <iostream>
#include <vector>

int main()
{
    auto i = 0;
    auto ui = 0u;
    auto ull = 0ull;
    auto ll = 0ll;

    auto d = 3.14;
    auto f = 3.14f;

    auto c = 'A';
    auto u8 = u8'A';
    auto u16 = u'A';
    auto u32 = U'A';

    auto code = 'CODE';

    std::vector<int> v = { 1, 2, 3, 4 };

    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        std::cout << *iter << std::endl;
    }

    return 0;
}