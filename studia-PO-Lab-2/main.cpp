#include "Book.h"

#include <iostream>
#include <string>

using namespace std;

int main() {

	string a = "Henryk Sienkiewicz", t = "Ogniem i mieczem";
	Book e;
	cout << "e: " << e << endl;
	Book b1 = { a, t };
	cout << "b1: " << b1 << endl;
	Book b2 = { "Adam Mickiewicz","Dziady" };
	cout << "b2: " << b2 << endl;
	Book b3 = b1;
	cout << "b3: " << b3 << " b1: " << b1 << endl;
	e = std::move(b2);
	cout << "e: " << e << " b2:" << b2 << endl;
	e.setAuthor("Juliusz Slowacki");
	cout << "e: " << e << endl;
	e.setTitle("Dziady");
	cout << "e: " << e << endl;

	return 0;
}