#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <array>
#include <numeric>

using namespace std;

int roznica(string haslo1, string haslo2)
{
    int wynik;

    if(haslo1.size() > haslo2.size())
        swap(haslo1, haslo2);

    for(int i=0; i<haslo1.size(); i++)
    {
        if( haslo1[i] == haslo2[i] )
        {
            haslo1.erase(haslo1.begin() + i);
            haslo2.erase(haslo2.begin() + i);
            i--;
        }
    }

    wynik = max(haslo1.size(), haslo2.size());

    cout << haslo1 << " " << haslo2 << " " << wynik << endl;

    return wynik;
}

bool isAlphabetical(string nazwa1, string nazwa2)
{
    for(int i=0; i<min(nazwa1.size(), nazwa2.size()); i++)
        if(nazwa1[i] < nazwa2[i])
            return true;
        else if(nazwa1[i] > nazwa2[i])
            return false;

    if(nazwa1.size() < nazwa2.size())
        return true;
    else
        return false;
}

int main()
{
    vector <array<string, 2>> uzytkownicy;
    vector <array<string, 2>> najmniejPodobone;
    vector <array<string, 2>> najbardziejPodobone;
    int najmniejszaRoznica = numeric_limits<int>::max();
    int najwieksza = numeric_limits<int>::min();

    string wyraz1, wyraz2;
    int n;

    cin >> n;    

    // Wczytanie uzytkownikow
    for(int i=0; i<n; i++)
    {
        string uzytkownik, haslo;
        cin >> uzytkownik >> haslo;

        uzytkownicy[i][0] = uzytkownik;
        uzytkownicy[i][1] = haslo;
    }
    
    // Szukanie najmniej i najbardziej podobnych haseł
    for(int i=0; i<n; i++)
    {
        
    }

    return 0;
}