#include <iostream>

int main()
{
    char c = 'A';
    char name[] = "Jeremiah";

    signed char sc = 'A';
    unsigned char uc = 'A';

    wchar_t wc = L'A';

    std::cout << "Sizeof wchar_t: " << sizeof(wchar_t) << std::endl;

    char16_t c16 = u'A'; // UTF-16
    char32_t c32 = U'A'; // UTF-32

    char8_t c8 = u8'A'; // UTF-8 (C++20)

    // char, wchar_t.

    return 0;
}