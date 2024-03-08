#include "Book.h"

#include <iostream>
#include <string>
#include "Library.h"

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
	e.setTitle("Kordian");
	cout << "e: " << e << endl;

	Library l;
	cout << "l: " << l << endl;
	//3-5 ksi¹¿ek
	Library l1 = { {"Fiodor Dostojewski", "Zbrodnia i Kara"},
	{"Sun Tzu", "Sztuka Wojny"},
	{"J.R.R. Tolkien", "Wladca Pierscieni"} };
	cout << "l1: " << l1 << endl;
	Library l2(2);
	cout << "l2: " << l2 << endl;
	l2[0] = { "Frank Herbert", "Diuna" };
	l2[1] = { "Joseph Conrad", "Jadro Ciemnosci" };
	cout << "l2: " << l2 << endl;
	l = std::move(l2);
	cout << "l: " << l << " l2: " << l2 << endl;
	l1[0] = std::move(l[1]);
	cout << "l1: " << l1 << " l: " << l << endl;

	return 0;
}