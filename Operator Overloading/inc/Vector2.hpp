#pragma once

#include <compare>

struct Vector2
{
    Vector2() = default;
    explicit Vector2(float x); // Initialize both components to x.
    Vector2(float x, float y);

    // Copy assignment operators.
    Vector2& operator=(const Vector2& rhs);

    // Compound addition assignment operator.
    Vector2& operator+=(const Vector2& rhs);
    // Compound subtraction assignment operator.
    Vector2& operator-=(const Vector2& rhs);

    Vector2 operator-() const;

    Vector2& operator++();
    Vector2 operator++(int);
    Vector2& operator--();
    Vector2 operator--(int);

    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;

    Vector2 operator*(float rhs) const;

    //float& operator[](size_t i);
    //float operator[](size_t i) const;

    template<typename Self>
    auto&& operator[](this Self&& self, size_t i);

    //bool operator<(const Vector2& rhs) const;
    //bool operator>(const Vector2& rhs) const;
    //bool operator<=(const Vector2& rhs) const;
    //bool operator>=(const Vector2& rhs) const;

    bool operator==(const Vector2& rhs) const;
    //bool operator!=(const Vector2& rhs) const;

    auto operator<=>(const Vector2&) const;

    float x = 0.0f;
    float y = 0.0f;
};

// Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
Vector2 operator*(float lhs, const Vector2& rhs);

template <typename Self>
auto&& Vector2::operator[](this Self&& self, size_t i)
{
    assert(i < 2);
    return i == 0 ? self.x : self.y;
}

inline auto Vector2::operator<=>(const Vector2& rhs) const
{
    if (auto order = x <=> rhs.x; std::is_neq(order)) return order;
    return y <=> rhs.y;
}
