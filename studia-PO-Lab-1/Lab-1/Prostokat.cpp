#include "Prostokat.h"
using namespace std;
std::istream& operator>>(std::istream& is, Prostokat& prostokat) {
	double a, b;
	is >> a >> b;
	prostokat.SetA(a);
	prostokat.SetB(b);

	return is;
}

Prostokat::Prostokat(double a, double b)
	: a(a), b(b)
{
	cout << "Konstruktor Prostokata(" << a << "," << b << ")" << endl;
}
double Prostokat::GetA() const {
	return a;
}
double Prostokat::GetB() const {
	return b;
}
void Prostokat::SetA(double a) {
	this->a = a;
}
void Prostokat::SetB(double b) {
	this->b = b;
}
double Prostokat::Obwod() {
	return 2 * (a + b);
}
double Prostokat::Pole() {
	return a * b;
}
void Prostokat::Wypisz(std::ostream& out) const {
	out << "Prostokat(" << a << ", " << b << ")";
}
Prostokat::~Prostokat() {
	cout << "Dekonstruktor obiektu " << *this << endl;
}