#include <Int.hpp>

Int::Int(int i)
    : i{i}
{}

Int& Int::operator=(int _i)
{
    i = _i;
    return *this;
}

Int::operator int() const
{
    return i;
}
