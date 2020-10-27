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

    bool isSingleType()
    {
        bool warunek = false;
        int counter = 0;

        if(n_drozdzowek == 0)
            counter++;
        if(n_paczkow == 0)
            counter++;
        if(n_rogalikow == 0)
            counter++;
        
        if(counter >= 2){
            warunek = true;
        }

        return warunek;
    }
};

bool isGreater(gablota a, gablota b)
{
    bool warunek = false;

    //cout << "Compare: " << a.id << " " << b.id << endl;

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
    int n_gablot, suma = 0;
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
    //cout << "Sortowanie gablot" << endl;
    sort(Gabloty, Gabloty+n_gablot, isGreater);

    //cout << endl;
    //sumowanie drozdzowek
    for(int i=0; i<n_gablot; i++)
    {
        if(i != 0 && !Gabloty[i].isSingleType() )
        {
            suma += Gabloty[i].n_drozdzowek;
        }
        //cout << suma << endl;
    }
    //cout << endl;
    //sumowanie paczkow
    for(int i=0; i<n_gablot; i++)
    {
        if(i != 1 && !Gabloty[i].isSingleType() )
        {
            suma += Gabloty[i].n_paczkow;
        }
        //cout << suma << endl;
    }
    //cout << endl;
    //sumowanie rogalikow
    for(int i=0; i<n_gablot; i++)
    {
        if(i != 2 && !Gabloty[i].isSingleType() )
        {
            suma += Gabloty[i].n_rogalikow;
        }
        //cout << suma << endl;
    }
    //cout << endl;

    // Wypisanie gablot
    for(int i=0; i<n_gablot; i++){
        cout << Gabloty[i].n_drozdzowek << " " << Gabloty[i].n_paczkow << " " << Gabloty[i].n_rogalikow << "  id: " << Gabloty[i].id << endl;
    }

    cout << suma << endl;

    getchar();
    getchar();
    return 0;
}