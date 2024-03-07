#include "FabrykaFigur.h"

Kolo FabrykaFigur::createFigure(double r)
{
    return Kolo(r);
}

Prostokat FabrykaFigur::createFigure(double a, double b)
{
    return Prostokat(a, b);
}

Trojkat FabrykaFigur::createFigure(double a, double b, double c)
{
    return Trojkat(a, b, c);
}

