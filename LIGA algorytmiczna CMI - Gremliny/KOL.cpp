#include <iostream>
#include <vector>

using namespace std;

class Osoba
{

};

class Hrabstwo
{
private:
    // n - liczba mieszkancow
    int n;

public:
    void wczytaj();
};

void Hrabstwo::wczytaj()
{
    cin >> n;
}

int main()
{
    Hrabstwo noweHrabstwo;

    noweHrabstwo.wczytaj();

    return 0;
}