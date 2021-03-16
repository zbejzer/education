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

    //cout << haslo1 << " " << haslo2 << " " << wynik << endl;

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
    vector <string> najmniejPodobone;
    vector <string> najbardziejPodobone;
    int najmniejszaRoznica = numeric_limits<int>::max();
    int najwiekszaRoznica = numeric_limits<int>::min();

    string wyraz1, wyraz2;
    int n;

    cin >> n;

    vector <array<string, 2>> uzytkownicy(n);

    // Wczytanie uzytkownikow
    for(int i=0; i<n; i++)
    {
        string uzytkownik, haslo;
        cin >> uzytkownik >> haslo;

        uzytkownicy[i][0] = uzytkownik;
        uzytkownicy[i][1] = haslo;
    }

    // Szukanie najmniej i najbardziej podobnych haseł
    // Zaadaptowany bubble sort
    for(int i=0; i<n-1; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            //cout << i << " -> " << j << endl;
            int obecnaRoznica = roznica(uzytkownicy[i][1], uzytkownicy[j][1]);

            if(obecnaRoznica >= najwiekszaRoznica)
            {
                array<string, 2> t = { uzytkownicy[i][0], uzytkownicy[j][0] };

                if( !isAlphabetical(t[0], t[1]) ) swap(t[0], t[1]);
                if(obecnaRoznica > najwiekszaRoznica) najmniejPodobone.clear();

                najmniejPodobone.push_back(t[0] + " " + t[1]);
                najwiekszaRoznica = obecnaRoznica;
            }

            if(obecnaRoznica <= najmniejszaRoznica)
            {
                array<string, 2> t = { uzytkownicy[i][0], uzytkownicy[j][0] };

                if( !isAlphabetical(t[0], t[1]) ) swap(t[0], t[1]);
                if(obecnaRoznica < najmniejszaRoznica) najbardziejPodobone.clear();

                najbardziejPodobone.push_back(t[0] + " " + t[1]);
                najmniejszaRoznica = obecnaRoznica;
            }
        }
    }

    // Sortowanie par w wektorach
    sort(najbardziejPodobone.begin(), najbardziejPodobone.end(), isAlphabetical);
    sort(najmniejPodobone.begin(), najmniejPodobone.end(), isAlphabetical);

    cout << najmniejszaRoznica << endl;
    for(int i=0; i<najbardziejPodobone.size(); i++)
        cout << najbardziejPodobone[i] << endl;

    cout << najwiekszaRoznica << endl;
    for(int i=0; i<najmniejPodobone.size(); i++)
        cout << najmniejPodobone[i] << endl;

    return 0;
}