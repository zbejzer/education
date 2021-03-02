// n - liczba wsi
// m - liczba drog
// k - myto, oplata
// w1 - wies poczatkowa
// w2 - wies koncowa
// p - liczbna zapytan

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

using namespace std;

string polaczenie(int, int);

class farmaTroli
{
public:
    unordered_map <int, vector <int>> miasta;
    unordered_map <string, int> koszta;
    int n, m;

    void wczytanie_mapy();
    void zapytania();
    void wypisz();
    void szukaj(int, int, unordered_map <int, bool>, unsigned int, unsigned int*);
};

void farmaTroli::wczytanie_mapy()
{
    cin >> n >> m;

    for(int i=0; i<m; i++)
    {
        int w1, w2, k;
        
        cin >> w1 >> w2 >> k;
        
        koszta[polaczenie(w1, w2)] = k;
        miasta[w1].push_back(w2);
        miasta[w2].push_back(w1);
    }    
}

void farmaTroli::wypisz()
{
    for( const auto& n : koszta ) {
        cout << " " << n.first << " " << n.second << "]\n";
    }
}

void farmaTroli::szukaj(int start, int cel, unordered_map <int, bool> sprawdzoneMiasta, unsigned int obecnyKoszt, unsigned int* najnizszyKoszt)
{
    sprawdzoneMiasta[start] = true;

    if(start == cel)
    {
        //cout << "[DEBUG] ZNALEZINO!\tOBECNY KOSZT: " << obecnyKoszt << endl;
        //cout << "[DEBUG] OBECNY NAJNIZSZY KOSZT: " << najnizszyKoszt << endl;

        if( obecnyKoszt < *najnizszyKoszt)
            *najnizszyKoszt = obecnyKoszt;
    }
    else
    {   
        for(int i = 0; i < miasta[start].size(); i++)
        {
            if( !sprawdzoneMiasta[miasta[start][i]] )
            {
                unsigned int nowyKoszt = obecnyKoszt;

                nowyKoszt += koszta[ polaczenie(start, miasta[start][i]) ];

                if (obecnyKoszt < *najnizszyKoszt)
                    szukaj( miasta[start][i], cel, sprawdzoneMiasta, nowyKoszt, najnizszyKoszt);
            }
        }
    }
}

int main()
{
    farmaTroli mojaFarma;

    mojaFarma.wczytanie_mapy();
    //mojaFarma.wypisz();
    mojaFarma.zapytania();

    return 0;
}

void farmaTroli::zapytania()
{
    int p;
    
    cin >> p;

    for(int i=0; i<p; i++)
    {
        int w1, w2;
        cin >> w1 >> w2;

        unordered_map <int, bool> mojeSprawdzoneMiasta;

        unsigned int najnizszyKoszt = numeric_limits<unsigned int>::max();
        szukaj(w1, w2, mojeSprawdzoneMiasta, 0, &najnizszyKoszt);

        cout << najnizszyKoszt << endl;
    }
}

string polaczenie(int w1, int w2)
{
    if(w2>w1) swap(w1, w2);
    string nowaPolaczenie = to_string(w1) + " " + to_string(w2);

    return nowaPolaczenie;
}