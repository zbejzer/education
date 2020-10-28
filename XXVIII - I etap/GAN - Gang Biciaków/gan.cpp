#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <array>

using namespace std;

class Polaczenie
{
    public:
    int rodzaj_bic;
    Polaczenie * ojciec;
    Polaczenie * syn;
};

int main()
{
    int n, m, z;
    // n - ilość miast
    // m - ilość rodzajów biciaków
    // z - liczba zapytań
    // c - rodzaj biciaka
    char c;

    cin >> n >> m >> z;
    cout << "Wczytano zalozenia" << endl;
    array <Polaczenie, n-1> polaczenia;

    for(int i = 0; i < n-1; i++) {
        Polaczenie temp;
        int a, b;

        cin >> a >> b >> temp.rodzaj_bic;

        temp.ojciec = &polaczenia[a];
        temp.syn = &polaczenia[b];

        // Przesuniecie miejsc w tablicy o 1, stolica miejsce 0 (w poleceniu 1)
        polaczenia[i-1]=temp;
    }

    cout << "Wczytano polaczenia" << endl;

    c = getchar();

    cout << (int)c << endl;

    getchar();
    getchar();
    return 0;
}