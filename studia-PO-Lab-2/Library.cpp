#include "Library.h"

#include <iostream>

Library::Library()
	: size(0)
	, books(nullptr)
{
}

Library::Library(const int& _size)
	: size(_size)
	, books(new Book[_size])
{
}

Library::Library(std::initializer_list<Book> list)
	: size(list.size())
	, books(new Book[list.size()])
{
	size_t i = 0;
	for (Book b : list)
	{
		books[i] = b;
		i++;
	}
}

Library::Library(const Library& orig)
	: size(orig.size)
	, books(new Book[orig.size])
{
	for (size_t i = 0; i < size; i++)
	{
		books[i] = orig.books[i];
	}
}

Library::Library(Library&& orig) noexcept
{
	std::swap(size, orig.size);
	std::swap(books, orig.books);

	orig.size = 0;
	orig.books = nullptr;
}

Library& Library::operator=(const Library& right)
{
	Library tmp = right;
	std::swap(size, tmp.size);
	std::swap(books, tmp.books);

	return *this;
}

Library& Library::operator=(Library&& right) noexcept
{
	std::swap(size, right.size);
	std::swap(books, right.books);

	return *this;
}

Book& Library::operator[](std::size_t index)
{
	return books[index];
}

const Book& Library::operator[](std::size_t index) const
{
	return books[index];
}

size_t Library::getSize() const
{
	return size;
}

Library::~Library()
{
	if (books != nullptr)
	{
		delete[] books;
	}
}

std::ostream& operator<<(std::ostream& os, const Library& library)
{
	for (size_t i = 0; i < library.size; i++)
	{
		if (i > 0)
		{
			os << ", ";
		}
		os << library.books[i];
	}

	return os;
}
