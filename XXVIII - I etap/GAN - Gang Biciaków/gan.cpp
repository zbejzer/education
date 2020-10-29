#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <array>

using namespace std;

int id = 1;

class Miasto
{
    public:
    int numer;
    vector <Miasto*> synowie;

    Miasto(){
        numer = id;
        id++;
    };
};

class Stacja
{
    public:
    int miasto_a, miasto_b, typ_bic;
};

int main()
{
    int n, m, z;
    // n - ilość miast
    // m - ilość rodzajów biciaków
    // z - liczba zapytań

    cin >> n >> m >> z;
    cout << "Wczytano zalozenia" << endl;
    Stacja stacje[n-1];
    Miasto miasta[n];

    for(int i = 0; i < n-1; i++) {
        int t_miasta[2];

        cin >> t_miasta[0] >> t_miasta[1] >> stacje[i].typ_bic;
        sort(t_miasta, t_miasta+2);

        // Wpisanie do tablicy stacji
        stacje[i].miasto_a = t_miasta[0];
        stacje[i].miasto_b = t_miasta[1];

        // Wpisanie do tablicy miast
        // Stosuje przesuniecie miejsc w tablicy o 1, stolica miejsce 0 (w poleceniu 1)
        miasta[t_miasta[0]-1].synowie.push_back(&miasta[t_miasta[1]-1]);
    }

    cout << "Wczytano polaczenia" << endl;

    for(int i = 0; i < n-1; i++)
    {
        cout << "Miasto: " << miasta[i].numer << endl;
        for(int j = 0; j < miasta[i].synowie.size(); j++)
        {
            Miasto temp = *miasta[i].synowie[j];
            cout << "   - " << temp.numer << endl;
        }    
    }

    char c = getchar();
    cout << (int)c << endl;

    getchar();
    getchar();
    return 0;
}