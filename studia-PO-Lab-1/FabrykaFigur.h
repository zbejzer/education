#pragma once

#include <iostream>
#include "Prostokat.h"
#include "Trojkat.h"
#include "Kolo.h"

class FabrykaFigur {
public:
	static Kolo createFigure(double r);
	static Prostokat createFigure(double a, double b);
	static Trojkat createFigure(double a, double b, double c);
};