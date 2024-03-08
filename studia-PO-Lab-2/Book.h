#pragma once
#include <string>

class Book {
	std::string author, title;
	friend std::ostream& operator<<(std::ostream& os, const Book& book);
public:
	Book();
	Book(const std::string& _author, const std::string& _title);
	Book(std::string&& _author, std::string&& _title);
	Book(const Book& book);
	Book(Book&& book) noexcept;
	std::string getAuthor() const;
	std::string getTitle() const;
	void setAuthor(const std::string& _author);
	void setAuthor(std::string&& _author);
	void setTitle(const std::string& _title);
	void setTitle(std::string&& _title);

	Book& operator=(const Book& book);
	Book& operator=(Book&& book);
};