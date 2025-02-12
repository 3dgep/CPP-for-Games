#pragma once

#include <cassert>

#include "VectorBase.hpp"

template<typename T, size_t N>
struct Vector : VectorBase<T, N>
{
    using base = VectorBase<T, N>;

    Vector<T, N> operator+(const Vector<T, N>& rhs) const;

    template<typename Self>
    auto&& operator[](this Self&& self, size_t i);
};

template <typename T, size_t N>
Vector<T, N> Vector<T, N>::operator+(const Vector<T, N>& rhs) const
{
    Vector<T, N> res;

    for (size_t i = 0; i < N; ++i)
    {
        res.data[i] = base::data[i] + rhs.data[i];
    }

    return res;
}

template <typename T, size_t N>
template <typename Self>
auto&& Vector<T, N>::operator[](this Self&& self, size_t i)
{
    assert(i < N);
    return self.data[i];
}

using vec2f = Vector<float, 2>;
using vec3f = Vector<float, 3>;

extern template struct Vector<float, 2>;
extern template struct Vector<float, 3>;
