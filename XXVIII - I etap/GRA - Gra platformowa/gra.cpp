#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>

using namespace std;

size_t dlugosc_platform;

class Platforma
{
    public:
    set <int> dziury;   // numer dziury od lewej strony
};

void wypisz(deque <Platforma> moje_platformy){
    cout << "[WYPISYWANIE STRUKTURY]" << endl;

    for(int i=0; i<dlugosc_platform; i++)
        cout << i+1 << '|';
    cout << endl;

    for(int i=0; i<moje_platformy.size(); i++){
        for(int j=1; j<=dlugosc_platform; j++){
            if(moje_platformy[i].dziury.count(j) != 0){
                cout << "  ";
            }else{
                cout << "- ";
            }
        }
        cout << endl;
    }

    cout << "[KONIEC]" << endl;
}

int main(){
    // n - ilość platform
    // X - długość platform
    // (i, x) - i - numer platformy licząc od góry. x - odległość od lewego krańca platformy
    // z - liczba zapytań

    // Entry zmienne
    size_t n_platform;
    unsigned int n_zapytan;

    // wejście
    cin >> n_platform >> dlugosc_platform >> n_zapytan;

    // Late zmienne
    vector <Platforma> platformy (n_platform);

    // Wczytanie danych
    for(int i = 0; i < n_platform; i++)
    {
        int n_dziur;
        cin >> n_dziur;

        for(int j=0; j<n_dziur; j++)
        {
            int miejsce_dziura;
            cin >> miejsce_dziura;
            platformy[i].dziury.insert(miejsce_dziura);
        }
    }

    wypisz(platformy);

    getchar();
    getchar();
    return 0;
}