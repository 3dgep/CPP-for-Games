#pragma once

#include <cstring>

template<typename T>
struct Array
{
    Array(size_t size);
    ~Array();

    // Copy semantics.
    Array(const Array& copy);
    Array& operator=(const Array& rhs);

    // Move semantics.
    Array(Array&& other);
    Array& operator=(Array&& rhs);

    template<typename Self>
    auto&& operator[](this Self&& self, size_t i);

    size_t getSize() const { return size; }

private:
    T* data = nullptr;
    size_t size = 0;
};

template <typename T>
Array<T>::Array(size_t size)
    : size{size}
{
    data = new T[size];
}

template <typename T>
Array<T>::~Array()
{
    delete[] data;
}

template <typename T>
Array<T>::Array(const Array& copy)
    : size{copy.size}
{
    data = new T[size];
    std::memcpy(data, copy.data, size * sizeof(T));
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& rhs)
{
    if (this == &rhs) return *this;

    if (size != rhs.size)
    {
        delete[] data;
        data = new T[rhs.size];
        size = rhs.size;
    }
    std::memcpy(data, rhs.data, size * sizeof(T));

    return *this;
}

template <typename T>
Array<T>::Array(Array&& other)
    : size(other.size)
{
    data = other.data;

    other.data = nullptr;
    other.size = 0;
}

template <typename T>
Array<T>& Array<T>::operator=(Array&& rhs)
{
    if (this == &rhs) return *this;

    data = rhs.data;
    size = rhs.size;

    rhs.data = nullptr;
    rhs.size = 0;

    return *this;
}

template <typename T>
template <typename Self>
auto&& Array<T>::operator[](this Self&& self, size_t i)
{
    assert(i < self.size);
    return self.data[i];
}
