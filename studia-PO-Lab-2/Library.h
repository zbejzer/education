#pragma once
#include "Book.h"

#include <initializer_list>

class Library
{
	Book* books;
	size_t size;
	friend std::ostream& operator<<(std::ostream& os, const Library& library);
public:
	Library();
	Library(const int& _size);
	Library(std::initializer_list<Book> list);
	Library(const Library& orig);
	Library(Library&& orig) noexcept;
	Library& operator=(const Library& right);
	Library& operator=(Library&& right) noexcept;
	Book& operator[](std::size_t index);
	const Book& operator[](std::size_t index) const;
	size_t getSize() const;
	~Library();
};

