#pragma once

#include <algorithm>
#include <cstdlib>
#include <cstring>

template <typename T> class Array2D
{
	T * _data;
	size_t _size;
public:
	Array2D();
	Array2D(size_t size);
	Array2D(const Array2D<T>& other);
	~Array2D();
	T& operator=(T other);
	T& operator()(const size_t& index);
	T& operator()(const size_t& col, const size_t& row);

	void fill(T const& val);
	void zero();
	T& end();
};

template<typename T>
Array2D<T>::Array2D() : _data(nullptr), _size(0)
{
}

template<typename T>
Array2D<T>::Array2D(size_t size) : _size(size)
{
	_data = static_cast<T*>(malloc(size * size * sizeof(T)));
}

template<typename T>
Array2D<T>::Array2D(const Array2D<T>& other)
{
	this->_size = other._size;
	if (_size > 0)
	{
		realloc(_data, _size * _size);
		memcpy(_data, other._data, sizeof(T) * _size * _size);
	}
	else
	{
		free(_data);
		_data = nullptr;
	}
}

template<typename T>
Array2D<T>::~Array2D()
{
	free(_data);
}

template<typename T>
T& Array2D<T>::operator=(T other)
{
	using std::swap;

	swap(_size, other.size);
	swap(_data, other.data);
}

template<typename T>
inline T& Array2D<T>::operator()(const size_t& index)
{
	return _data[index];
}

template<typename T>
T& Array2D<T>::operator()(const size_t& col, const size_t& row)
{
	return _data[col * _size + row];
}

template<typename T>
void Array2D<T>::fill(const T& val)
{
	for (size_t i = 0; i < _size * _size; i++)
	{
		_data[i] = val;
	}
}

template<typename T>
void Array2D<T>::zero()
{
	memset(_data, 0, sizeof(T) * _size * _size);
}

template<typename T>
T& Array2D<T>::end()
{
	return _data[_size * _size - 1];
}
