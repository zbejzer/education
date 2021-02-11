#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Hrabstwo
{
private:
    // n - liczba mieszkancow
    vector < vector <bool> > mieszkancy;

public:
    int n;
    void wczytaj();
    void debug();
    set <int> KKK(int);
};

void Hrabstwo::wczytaj()
{
    cin >> n;

    for(int k=0; k<n; k++)
    {
        vector <bool> obecnyMieszkaniec;
        for(int j=0; j<n; j++)
        {
            char zaleznosc;
            cin >> zaleznosc;

            if(zaleznosc == '?' || zaleznosc == 'N')
                obecnyMieszkaniec.push_back(0);
            else
                obecnyMieszkaniec.push_back(1);
            
        }
        mieszkancy.push_back(obecnyMieszkaniec);
    }
}

void Hrabstwo::debug()
{
    for(int i=0; i<n; i++)
    {
        cout << endl;
        for(int j=0; j<n; j++)
            cout << mieszkancy[i][j]<<" ";
    }
}

// 3 stopien pokrewienstwa - Kolega Kolegi Kolegi
set <int> Hrabstwo::KKK(int osoba)
{
    set <int> pajace;

    for(int b=0; b<n; b++)
    {
        if(mieszkancy[osoba][b])
        {
            for(int c=0; c<n; c++)
            {
                if(mieszkancy[c][b] && !mieszkancy[c][osoba] && c != osoba)
                {
                    for(int d=0; d<n; d++)
                    {
                        if(!mieszkancy[d][osoba] && !mieszkancy[d][b] && mieszkancy[d][c] && d != osoba)
                        {
                            pajace.insert(d);
                        }
                    }
                }
            }                          
        }
    }

    return pajace;
}

int main()
{
    Hrabstwo noweHrabstwo;

    noweHrabstwo.wczytaj();
    //noweHrabstwo.debug();

    for(int i=0; i<noweHrabstwo.n; i++)
    {
        set <int> tempSet;
        tempSet = noweHrabstwo.KKK(i);
        vector <int> tab;
        
        // Zmiana set -> vector
        for(auto j = tempSet.begin(); j != tempSet.end(); j++)
            tab.push_back(*j);
        
        sort(tab.begin(), tab.end());

        // Wypisywanie
        cout << tempSet.size() << endl;

        for(int j=0; j<tab.size(); j++)
            cout << tab[j] + 1 << " ";

        cout << endl;
    }

    return 0;
}