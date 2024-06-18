#pragma once

#include <algorithm>
#include <cstdlib>
#include <cstring>

template <typename T> class Array1D
{
    T *_data;
    size_t _size;

  public:
    Array1D();
    Array1D(size_t size);
    Array1D(const Array1D<T> &other);
    ~Array1D();
    T &operator=(T other);
    T &operator()(const size_t &index);

    void fill(T const &val);
    void zero();
    T &end();
};

template <typename T> Array1D<T>::Array1D() : _data(nullptr), _size(0)
{
}

template <typename T> Array1D<T>::Array1D(size_t size) : _size(size)
{
    _data = static_cast<T *>(malloc(size * sizeof(T)));
}

template <typename T> Array1D<T>::Array1D(const Array1D<T> &other)
{
    this->_size = other._size;
    if (_size > 0)
    {
        realloc(_data, _size);
        memcpy(_data, other._data, sizeof(T) * _size);
    }
    else
    {
        free(_data);
        _data = nullptr;
    }
}

template <typename T> Array1D<T>::~Array1D()
{
    free(_data);
}

template <typename T> T &Array1D<T>::operator=(T other)
{
    using std::swap;

    swap(_size, other.size);
    swap(_data, other.data);
}

template <typename T> inline T &Array1D<T>::operator()(const size_t &index)
{
    return _data[index];
}

template <typename T> void Array1D<T>::fill(const T &val)
{
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = val;
    }
}

template <typename T> void Array1D<T>::zero()
{
    memset(_data, 0, sizeof(T) * _size);
}

template <typename T> T &Array1D<T>::end()
{
    return _data[_size - 1];
}
