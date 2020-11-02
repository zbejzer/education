#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <array>

using namespace std;

int global_id = 1;

class Miasto
{
    public:
    int numer;
    vector <Miasto*> synowie;

    Miasto(){
        numer = global_id;
        global_id++;
    };

    void szukaj_miasta(int docelowe_miasto, vector <int> *odbyta_droga, vector <int> moja_droga)
    {
        if(count(moja_droga.begin(), moja_droga.end(), numer) == 0)
        {
            moja_droga.push_back(numer);
            if(numer==docelowe_miasto) {
                *odbyta_droga = moja_droga;
            } else {
                for(int i=0; i<synowie.size(); i++)
                {
                    synowie[i]->szukaj_miasta(docelowe_miasto, odbyta_droga, moja_droga);
                }
            }
        }
    }
};

class Stacja
{
    public:
    int miasto_a, miasto_b, typ_bic, id;
};

class SiecStacji
{
    public:
    vector <Stacja> stacje;
    int id;

    SiecStacji():
    id(1){};

    Stacja *szukaj_stacji(int miasto1, int miasto2)
    {
        Stacja *szukana_stacja;

        for(int i=0;  i<stacje.size(); i++){
            if(stacje[i].miasto_a == miasto1 && stacje[i].miasto_b == miasto2){
                szukana_stacja = &stacje[i];
            }
            if(stacje[i].miasto_b == miasto1 && stacje[i].miasto_a == miasto2){
                szukana_stacja = &stacje[i];
            }
        }

        return szukana_stacja;
    }

    void zmiana(int stacja, int nowy_bic){
        stacje[stacja-1].typ_bic = nowy_bic;
    }
};

int main()
{
    int n, m, z;
    // n - ilość miast
    // m - ilość rodzajów biciaków
    // z - liczba zapytań

    ofstream recovery("OUTPUT.txt");

    cin >> n >> m >> z;
    recovery << "Wczytano zalozenia" << endl;
    recovery << flush;

    SiecStacji stacje;
    vector <Miasto> miasta;

    for(int i=0; i<n; i++){
        Miasto temp_miasto;

        miasta.push_back(temp_miasto);
    }

    for(int i = 0; i < n-1; i++) {
        int t_miasta[2];
        Stacja t_stacja;
        t_stacja.id = stacje.id;
        stacje.id = stacje.id+1;

        // Wczytanie danych
        cin >> t_miasta[0] >> t_miasta[1] >> t_stacja.typ_bic;
        sort(t_miasta, t_miasta+2);

        // Wpisanie do tablicy stacji
        t_stacja.miasto_a = t_miasta[0];
        t_stacja.miasto_b = t_miasta[1];
        stacje.stacje.push_back(t_stacja);

        // Wpisanie do tablicy miast
        // Stosuje przesuniecie miejsc w tablicy o 1, stolica miejsce 0 (w poleceniu 1)
        //cout << "Dodawanie polaczenia " << t_miasta[0]-1 << " - " << t_miasta[1]-1 << " przez: " << t_stacja.typ_bic << endl;
        miasta[t_miasta[0]-1].synowie.push_back(&miasta[t_miasta[1]-1]);
        miasta[t_miasta[1]-1].synowie.push_back(&miasta[t_miasta[0]-1]);
    }

    recovery << "Wczytano polaczenia" << endl;
    recovery << flush;

    for(int i=0; i<z; i++){
        char operacja;
        cin >> operacja;

        // Zmiana biciaka przy danej stacji
        if(operacja == 'B'){
            int wczytana_stacja, wczytany_bic;
            cin >> wczytana_stacja >> wczytany_bic;

            stacje.zmiana(wczytana_stacja, wczytany_bic);
        }
        // Podanie ilości różnych rodzajów biciaków po drodze do danego miasta
        if(operacja == 'Z'){
            int do_miasta;
            cin >> do_miasta;
            vector <int> droga;
            vector <int> pusta_droga;
            vector <int> unikatowe_bic;
            miasta[0].szukaj_miasta(do_miasta, &droga, pusta_droga);

            for(int i=1; i<droga.size(); i++){
                Stacja temp_stacja = *stacje.szukaj_stacji(droga[i-1], droga[i]);

                if(count(unikatowe_bic.begin(), unikatowe_bic.end(), temp_stacja.typ_bic)==0)
                    unikatowe_bic.push_back(temp_stacja.typ_bic);
            }

            cout << unikatowe_bic.size() << endl;
        }

        //Wypisanie
        if(operacja == 'W'){
            for(int i = 0; i < n; i++)
            {
                cout << "Miasto: " << miasta[i].numer << endl;
                for(int j = 0; j < miasta[i].synowie.size(); j++)
                {
                    Stacja temp_stacja;
                    cout << "   -" << miasta[i].synowie[j]->numer << " via: ";
                    temp_stacja = *stacje.szukaj_stacji(miasta[i].numer, miasta[i].synowie[j]->numer);
                    cout << temp_stacja.typ_bic << endl;

                }
            }
        }
        recovery << "Obliczono: " << i+1 << "/" << z << endl;
        recovery << flush;
    }

    recovery << "Koniec!" << endl;
    recovery << flush;

    getchar();
    getchar();
    return 0;
}