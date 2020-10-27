#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

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
    };

    int reszta()
    {
        int temp[3] = {
            n_drozdzowek,
            n_paczkow,
            n_rogalikow
        };

        sort (temp, temp+3);

        return temp[0] + temp[1];
    };
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
    int n_gablot;
    long long int suma = 0;
    cin >> n_gablot;
    vector <gablota> Gabloty;
    gablota* naj_drozdzowek = &Gabloty[0];
    gablota* naj_paczkow = &Gabloty[0];
    gablota* naj_rogalikow = &Gabloty[0];

    // Wczytanie zawartości gablot
    for(int i=0; i<n_gablot; i++)
    {
        gablota temp_wczytanie;
        cin >> temp_wczytanie.n_drozdzowek >> temp_wczytanie.n_paczkow >> temp_wczytanie.n_rogalikow;
        Gabloty.push_back(temp_wczytanie);
    }

    // Szukanie gabloty do których należy przeniesc ciastka
    sort(Gabloty.begin(), Gabloty.end(), sort_d);
    sort(Gabloty.begin()+1, Gabloty.end(), sort_p);
    sort(Gabloty.begin()+2, Gabloty.end(), sort_r);

    //sumowanie 3 pierwszych stacków
    for(int i=0; i<3; i++)
    {
        if(i != 0 && !Gabloty[i].isSingleType() )
        {
            suma += Gabloty[i].n_drozdzowek;
            Gabloty[i].n_drozdzowek = 0;
        }
    }
    for(int i=0; i<3; i++)
    {
        if(i != 1 && !Gabloty[i].isSingleType() )
        {
            suma += Gabloty[i].n_paczkow;
            Gabloty[i].n_paczkow = 0;
        }
    }
    for(int i=0; i<3; i++)
    {
        if(i != 2 && !Gabloty[i].isSingleType() )
        {
            suma += Gabloty[i].n_rogalikow;
            Gabloty[i].n_rogalikow = 0;
        }
    }

    // sumowanie reszty
    for(int i=0; i<n_gablot; i++)
    {
        suma += Gabloty[i].reszta();
    }

    // Wypisanie gablot
    /*for(int i=0; i<n_gablot; i++){
        cout << Gabloty[i].n_drozdzowek << " " << Gabloty[i].n_paczkow << " " << Gabloty[i].n_rogalikow << "  id: " << Gabloty[i].id << endl;
    }*/

    cout << suma << endl;
    
    /*getchar();
    getchar();
    getchar();*/
    
    return 0;
}