#pragma once

template <typename T> T** createCopy2DArray(T** const& arr, const size_t& size)
{
	T** new_arr = new T * [size];
	for (size_t i = 0; i < size; i++)
	{
		new_arr[i] = new T[size];
		for (size_t j = 0; j < size; j++)
		{
			new_arr[i][j] = arr[i][j];
		}
	}

	return new_arr;
}

template <typename T> T** create2DArray(const size_t& size)
{
	T** arr = new T * [size];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = new T[size];
	}

	return arr;
}

template <typename T> T** create2DArray(const size_t& size, const T& val)
{
	T** arr = new T * [size];
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = new T[size];
		for (size_t j = 0; j < size; j++)
		{
			arr[i][j] = val;
		}
	}

	return arr;
}

template <typename T> void destroy2DArray(T**& arr, const size_t& size)
{
	if (arr != nullptr)
	{
		for (size_t i = 0; i < size; i++)
		{
			delete[] arr[i];
		}
		delete[] arr;

		arr = nullptr;
	}
}