#include <cstdint>
#include <iostream>


int main()
{
    int i = 0; // Might be 16-bit (2 bytes), or 32-bits (or 4 bytes).
    int32_t j = 0;

    unsigned int k = 0xffffffff;

    long l = 0;
    unsigned long ul = +4.29e9;

    short s = 32767;

    long long ll = +9.22e18;
    unsigned long long ull = +1.85e19;

    int64_t i64 = +9.22e18;
    uint64_t u64 = +1.85e19;

    std::size_t sz = 0;

    std::cout << "Size of int: " << sizeof(int) << std::endl;
    std::cout << "Size of int32_t: " << sizeof(uint32_t) << std::endl;
    std::cout << "Size of long: " << sizeof(long) << std::endl;
    std::cout << "Size of short: " << sizeof(short) << std::endl;
    std::cout << "Size of long long: " << sizeof(long long) << std::endl;
    std::cout << "Size of size_t: " << sizeof(std::size_t) << std::endl;




    return 0;
}