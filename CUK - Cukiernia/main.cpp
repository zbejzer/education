#include <iostream>
#include <fstream>
#include <string>

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

int main()
{
    int n_gablot;
    cin >> n_gablot;
    gablota Gabloty[n_gablot];
    gablota* naj_drozdzowek = &Gabloty[0];
    gablota* naj_paczkow = &Gabloty[0];
    gablota* naj_rogalikow = &Gabloty[0];

    for(int i=0; i<n_gablot; i++)
    {
        cin >> Gabloty[i].n_drozdzowek >> Gabloty[i].n_paczkow >> Gabloty[i].n_rogalikow;
    }

    for(int i=0; i<n_gablot; i++)
    {
        if( Gabloty[i].n_drozdzowek > *naj_drozdzowek.n_drozdzowek )
        {
            naj_drozdzowek = &Gabloty[i];
        }
        if( Gabloty[i].n_paczkow > *naj_paczkow->n_paczkow )
        {
            naj_paczkow = &Gabloty[i];
        }
        if( Gabloty[i].n_rogalikow > *naj_rogalikow->n_rogalikow )
        {
            naj_rogalikow= &Gabloty[i];
        }
    }

    for(int i=0; i<n_gablot; i++)
    {
        cout << *naj_drozdzowek->n_drozdzowek << " " << *naj_drozdzowek->n_paczkow<< " " << *naj_drozdzowek->n_rogalikow << endl;
        cout << *naj_paczkow->n_drozdzowek << " " << *naj_paczkow->n_paczkow<< " " << *naj_paczkow->n_rogalikow << endl;
        cout << *naj_rogalikow->n_drozdzowek << " " << *naj_rogalikow->n_paczkow<< " " << *naj_rogalikow->n_rogalikow << endl;
    }

    getchar();
    return 0;
}