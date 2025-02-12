#pragma once

template<typename T, size_t N>
struct VectorBase
{
    T data[N];
};

template<typename T>
struct VectorBase<T, 2>
{
    union 
    {
        struct
        {
            T x, y;
        };
        T data[2];
    };
};

template<typename T>
struct VectorBase<T, 3>
{
    union
    {
        struct
        {
            T x, y, z;
        };
        T data[3];
    };
};

template<typename T>
struct VectorBase<T, 4>
{
    union
    {
        struct
        {
            T x, y, z, w;
        };
        T data[4];
    };
};