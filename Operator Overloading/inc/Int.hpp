#pragma once

class Int
{
public:
    explicit Int(int i);
    ~Int() = default;

    Int& operator=(int i);
    explicit operator int() const; // Conversion operator.

private:
    int i = 0;
};

