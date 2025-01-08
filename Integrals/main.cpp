#include <iostream>
#include <cstdint>


int main()
{
    int min_int = -2147483647;
    int max_int = 2147483647;

    //unsigned int max_uint = 4294967295;
    unsigned int min_uint = 0u;
    unsigned int max_uint = -1;

    std::cout << "Sizeof int: " << sizeof(int) << std::endl;
    std::cout << "Min uint (-1): " << max_uint << std::endl;

    short max_short = 32767; // 2^16-1
    short min_short = -32768;

    unsigned max_ushort = 0xFFFF; // All bits on.

    std::cout << "Sizeof short: " << sizeof(short) << std::endl;

    long max_long = 2147483647l;
    long min_long = -2147483648l;

    long long max_ll = 9223372036854775807ll;
    long long min_ll = 9223372036854775807ll;

    unsigned long long max_ull = 18'446'744'073'709'551'615ull;

    std::int32_t i = 0; // always 32-bits
    std::uint32_t ui = 0; 
    std::int16_t i16 = 0; // alwasy be 16-bits
    std::int64_t i64 = 0; // alwasy going to be 64-bits.

    std::size_t sz = 0; // 64-bits on 64bit builds, 32-bits on 32-bit platforms.

    std::cout << "Sizeof size_t: " << sizeof(std::size_t) << std::endl;

    return 0;
}