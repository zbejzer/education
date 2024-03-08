#include "Book.h"

#include <iostream>

Book::Book()
	: author("")
	, title("")
{
}

Book::Book(const std::string& _author, const std::string& _title)
	: author(_author)
	, title(_title)
{
}

Book::Book(std::string&& _author, std::string&& _title)
	: author(std::move(_author))
	, title(std::move(_title))
{
}

Book::Book(const Book& book)
	: author(book.author)
	, title(book.title)
{
}

Book::Book(Book&& book) noexcept
{
	std::swap(author, book.author);
	std::swap(title, book.title);

	book.author = "";
	book.title = "";
}

std::string Book::getAuthor() const
{
	return author;
}

std::string Book::getTitle() const
{
	return title;
}

void Book::setAuthor(const std::string& _author)
{
	author = _author;
}

void Book::setAuthor(std::string&& _author)
{
	author = std::move(_author);
}

void Book::setTitle(const std::string& _title)
{
	title = _title;
}

void Book::setTitle(std::string&& _title)
{
	title = std::move(_title);
}

Book& Book::operator=(const Book& book)
{
	author = book.author;
	title = book.title;

	return *this;
}

Book& Book::operator=(Book&& book) noexcept
{
	author = std::move(book.author);
	title = std::move(book.title);

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Book& book)
{
	os << "Book( Author: " << book.author << ", Title: " << book.title << " )";
	return os;
}
