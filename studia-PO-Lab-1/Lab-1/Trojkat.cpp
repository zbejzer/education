#include "Trojkat.h"
#include <cmath>

using namespace std;
std::istream& operator>>(std::istream& is, Trojkat& trojkat) {
	double a, b, c;
	is >> a >> b >> c;
	trojkat.SetA(a);
	trojkat.SetB(b);
	trojkat.SetC(c);

	return is;
}
Trojkat::Trojkat(double a, double b, double c)
	: a(a), b(b), c(c)
{
	cout << "Konstruktor Trojkata(" << a << "," << b << "," << c << ")" << endl;
}
double Trojkat::GetA() const {
	return a;
}
double Trojkat::GetB() const {
	return b;
}
double Trojkat::GetC() const {
	return c;
}
void Trojkat::SetA(double a) {
	this->a = a;
}
void Trojkat::SetB(double b) {
	this->b = b;
}
void Trojkat::SetC(double c) {
	this->c = c;
}
double Trojkat::Obwod() {
	return a + b + c;
}
double Trojkat::Pole() {
	double p = Obwod() / 2.0;
	return std::sqrt(p * (p - a) * (p - b) * (p - c));
}
void Trojkat::Wypisz(std::ostream& out) const {
	out << "Trojkat(" << a << ", " << b << ", " << c << ")";
}
Trojkat::~Trojkat() {
	cout << "Dekonstruktor obiektu " << *this << endl;
}