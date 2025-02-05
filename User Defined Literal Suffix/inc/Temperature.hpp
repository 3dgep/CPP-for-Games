#pragma once

struct Temperature
{
    Temperature(long double k) : k{k}
    {}

    long double k = 0.0l; // Temperature in Kelvin.
};

Temperature operator""_C(long double c)
{
    return { c + 273.15l };
}

Temperature operator""_F(long double f)
{
    return { (f + 459.67l) * (5.0l / 9.0l) };
}