#include "Kolo.h"

#define PI 3.14

using namespace std;
std::istream& operator>>(std::istream& is, Kolo& kolo) {
	double r;
	is >> r;
	kolo.SetR(r);

	return is;
}

Kolo::Kolo(double r)
	: r(r)
{
	cout << "Konstruktor Kola(" << r << ")" << endl;
}
double Kolo::GetR() const {
	return r;
}
void Kolo::SetR(double r) {
	this->r = r;
}
double Kolo::Obwod() {
	return 2 * PI * r;
}
double Kolo::Pole() {
	return PI * r * r;
}
void Kolo::Wypisz(std::ostream& out) const {
	out << "Kolo(" << r << ")";
}
Kolo::~Kolo() {
	cout << "Dekonstruktor obiektu " << *this << endl;
}