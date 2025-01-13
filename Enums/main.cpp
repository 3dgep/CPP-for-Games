#include <iostream>
#include <cstdint>
#include <type_traits>
template<typename Enum>
constexpr std::underlying_type_t<Enum> to_underlying_t(Enum e)
{
    return static_cast<std::underlying_type_t<Enum>>(e);
}

enum class Color : uint32_t
{
    Black = 0x000000,
    Red = 0xFF0000,
    Green = 0x00FF00,
    Blue = 0x0000FF,
    White = Red | Green | Blue
};
constexpr uint32_t white = to_underlying_t(Color::White);// OK
Color green = 1;            // Error!
Color blue = Color::Blue; // OK.
// std::underlying_type_t<Color> color = 0; // int
// Color color = Color::Red;

enum Day
{
    Monday = 1,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Sunday
};

enum class MouseButton : uint8_t
{
    Left = 1 << 0,
    Right = 1 << 1,
    Middle = 1 << 2,
};

int main()
{

    for (int i = Monday; i <= Sunday; ++i)
    {
        switch (i)
        {
        case Monday:
            std::cout << "Monday";
            break;
        case Tuesday:
            std::cout << "Tuesday";
            break;
        case Wednesday:
            std::cout << "Wednesday";
            break;
        case Thursday:
            std::cout << "Thursday";
            break;
        case Friday:
            std::cout << "Friday";
            break;
        case Saturday:
            std::cout << "Saturday";
            break;
        case Sunday:
            std::cout << "Sunday";
            break;
        }

        std::cout << std::endl;
    }

    return 0;
}