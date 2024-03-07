#include <iostream>

#include "FabrykaFigur.h"
#include "Prostokat.h"
#include "Trojkat.h"
#include "Kolo.h"

int main()
{
    Prostokat p(3, 4);
    Trojkat t(3, 4, 5);
    Kolo k(10);

    std::cout << "Kolo: " << k.Obwod() << ", " << k.Pole() << std::endl;
    std::cout << k << std::endl;
    std::cout << "Prostokat: " << p.Obwod() << ", " << p.Pole() << std::endl;
    std::cout << p << std::endl;
    std::cout << "Trojkat: " << t.Obwod() << ", " << t.Pole() << std::endl;
    std::cout << t << std::endl;

    Kolo k2 = FabrykaFigur::createFigure(5);
    std::cout << k2 << std::endl;
    Prostokat p2 = FabrykaFigur::createFigure(10, 20);
    std::cout << p2 << std::endl;
    Trojkat t2 = FabrykaFigur::createFigure(10, 20, 30);
    std::cout << t2 << std::endl;

    FiguraPlaska* figury[3] = { nullptr };
    figury[0] = &p;
    figury[1] = &t;
    figury[2] = &k;

    for (size_t i = 0; i < 3; i++)
    {
        std::cout << figury[i]->Obwod() << std::endl;
    }

    Prostokat p3(0,0);
    std::cin >> p3;
    std::cout << p3.Pole() << std::endl;
    Kolo k3(0);
    std::cin >> k3;
    std::cout << k3.Pole() << std::endl;

}