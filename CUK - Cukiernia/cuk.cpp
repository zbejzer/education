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

bool sort_d(gablota a, gablota b)
{
    if( (a.n_drozdzowek > b.n_drozdzowek) || (a.n_drozdzowek > b.n_drozdzowek && a.isSingleType() > b.isSingleType()) )
    {
        return true;
    }else{
        return false;
    }
}

bool sort_p(gablota a, gablota b)
{
    if( (a.n_paczkow > b.n_paczkow) || (a.n_paczkow > b.n_paczkow && a.isSingleType() > b.isSingleType()) )
    {
        return true;
    }else{
        return false;
    }
}

bool sort_r(gablota a, gablota b)
{
    if( (a.n_rogalikow > b.n_rogalikow) || (a.n_rogalikow > b.n_rogalikow && a.isSingleType() > b.isSingleType()) )
    {
        return true;
    }else{
        return false;
    }
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
    sort(Gabloty, Gabloty+n_gablot, sort_d);
    sort(Gabloty+1, Gabloty+n_gablot, sort_p);
    sort(Gabloty+2, Gabloty+n_gablot, sort_r);

    //sumowanie drozdzowek
    for(int i=0; i<n_gablot; i++)
    {
        if(i != 0 && !Gabloty[i].isSingleType() )
        {
            suma += Gabloty[i].n_drozdzowek;
        }
    }
    //sumowanie paczkow
    for(int i=0; i<n_gablot; i++)
    {
        if(i != 1 && !Gabloty[i].isSingleType() )
        {
            suma += Gabloty[i].n_paczkow;
        }
    }
    //sumowanie rogalikow
    for(int i=0; i<n_gablot; i++)
    {
        if(i != 2 && !Gabloty[i].isSingleType() )
        {
            suma += Gabloty[i].n_rogalikow;
        }
    }


    // Wypisanie gablot
    for(int i=0; i<n_gablot; i++){
        cout << Gabloty[i].n_drozdzowek << " " << Gabloty[i].n_paczkow << " " << Gabloty[i].n_rogalikow << "  id: " << Gabloty[i].id << endl;
    }

    cout << suma << endl;
    
    getchar();
    getchar();
    getchar();
    
    return 0;
}