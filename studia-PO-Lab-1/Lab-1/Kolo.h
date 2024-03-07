#pragma once

#include "FiguraPlaska.h"
class Kolo : public FiguraPlaska {
	double r;
protected:
	friend std::istream& operator>>(std::istream& is, Kolo& kolo);
	void Wypisz(std::ostream& out) const override;
public:
	Kolo(double r);
	double GetR() const;
	void SetR(double r);
	double Obwod() override;
	double Pole() override;
	~Kolo() override;
private:
};