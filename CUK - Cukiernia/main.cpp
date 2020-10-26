#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

int global_id = 0;

class gablota
{
    public:
    int id;
    int n_drozdzowek, n_paczkow, n_rogalikow;

    gablota()
    {
        id = global_id;
        global_id++;
    }
};

bool isGreater(gablota a, gablota b)
{
    bool warunek = false;

    cout << "Compare: " << a.id << " " << b.id << endl;

    if(a.n_paczkow + a.n_rogalikow < b.n_paczkow + b.n_rogalikow)
    {
        warunek = true;
    }
    if(a.n_drozdzowek + a.n_rogalikow < b.n_drozdzowek + b.n_rogalikow)
    {
        warunek = true;
    }
    if(a.n_paczkow + a.n_drozdzowek < b.n_paczkow + b.n_drozdzowek)
    {
        warunek = true;
    }

    return !warunek;
}

int main()
{
    int n_gablot;
    cin >> n_gablot;
    gablota Gabloty[n_gablot];
    gablota* naj_drozdzowek = &Gabloty[0];
    gablota* naj_paczkow = &Gabloty[0];
    gablota* naj_rogalikow = &Gabloty[0];

    // Wczytanie zawartości gablot
    for(int i=0; i<n_gablot; i++)
    {
        cin >> Gabloty[i].n_drozdzowek >> Gabloty[i].n_paczkow >> Gabloty[i].n_rogalikow;
    }

    // Szukanie gabloty do których należy przeniesc ciastka
    cout << "Szukanie gabloty do których należy przeniesc ciastka" << endl;
    sort(Gabloty, Gabloty+n_gablot, isGreater);

    // Wypisanie gablot
    cout << "Wypisanie top gablot" << endl;
    for(int i=0; i<n_gablot; i++){
        cout << Gabloty[i].n_drozdzowek << " " << Gabloty[i].n_paczkow << " " << Gabloty[i].n_rogalikow << "  id: " << Gabloty[i].id << endl;
    }

    getchar();
    getchar();
    return 0;
}