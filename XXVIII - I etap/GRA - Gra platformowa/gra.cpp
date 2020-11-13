#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <limits.h>

using namespace std;

class Platforma
{
    public:
    set <int> dziury;   // numer dziury od lewej strony
};

class Poziom
{
    public:
    vector <Platforma> platformy;
    size_t dlugosc_platform;
    
    void wypisz()
    {
        cout << "[WYPISYWANIE STRUKTURY]" << endl;

        for(int i=0; i<dlugosc_platform; i++)
            cout << i+1 << '|';
        cout << endl;

        for(int i=0; i<platformy.size(); i++){
            for(int j=1; j<=dlugosc_platform; j++){
                if(platformy[i].dziury.count(j) != 0){
                    cout << " ";
                }else{
                    cout << "-";
                }
            }
            cout << endl;
        }
        cout << "[KONIEC]" << endl;
    }

    void znajdz_droge(int start_x, int start_y, int start_droga, int *min_droga)
    {   
        // Optymalizacja
        if(start_droga < *min_droga){

            while(!graniczy_dziura(start_x, start_y)){
                    start_x++;
            }








                
                if (platformy[start_y-1].dziury.count(start_x+1) != 0){         // dziura przed
                    znajdz_droge(start_x+2, start_y, start_droga+1, min_droga);
                    znajdz_droge(start_x+1, start_y+1, start_droga, min_droga);
                }
                if (start_x == dlugosc_platform && start_droga < *min_droga){    // koniec drogi
                    *min_droga = start_droga;
                }
            } else if ( start_y == platformy.size() ) {     // Dolne piętro
                while(
                    // y-1 jako y; vector liczy platformy od 0
                    platformy[start_y-1].dziury.count(start_x+1) == 0 &&    // platforma na y, x+1
                    platformy[start_y-2].dziury.count(start_x) == 0 &&      // platforma na y-1, x
                    start_x < dlugosc_platform                              // nie jest końcem
                ){
                    start_x++;
                }
                
                if (platformy[start_y-1].dziury.count(start_x+1) != 0){         // dziura przed
                    znajdz_droge(start_x+2, start_y, start_droga+1, min_droga);
                }
                if (platformy[start_y-2].dziury.count(start_x) != 0){           // dziura nad
                    if (platformy[start_y-1].dziury.count(start_x+1) == 0){
                        znajdz_droge(start_x+1, start_y, start_droga, min_droga);
                    }
                    znajdz_droge(start_x+1, start_y-1, start_droga+1, min_droga);
                }
                if (start_x == dlugosc_platform && start_droga < *min_droga){    // koniec drogi
                    *min_droga = start_droga;
                }
                    
            } else {                                        // Piętra pomiędzy
                while(
                    // y-1 jako y; vector liczy platformy od 0
                    platformy[start_y-1].dziury.count(start_x+1) == 0 &&    // platforma na y, x+1
                    platformy[start_y-2].dziury.count(start_x) == 0 &&      // platforma na y-1, x
                    start_x < dlugosc_platform                              // nie jest końcem
                ){
                    start_x++;
                }
                
                if (platformy[start_y-1].dziury.count(start_x+1) != 0){         // dziura przed
                    znajdz_droge(start_x+2, start_y, start_droga+1, min_droga);
                    znajdz_droge(start_x+1, start_y+1, start_droga, min_droga);
                }
                if (platformy[start_y-2].dziury.count(start_x) != 0){           // dziura nad
                    if (platformy[start_y-1].dziury.count(start_x+1) == 0){
                        znajdz_droge(start_x+1, start_y, start_droga, min_droga);
                    }
                    znajdz_droge(start_x+1, start_y-1, start_droga+1, min_droga);
                }
                if (start_x == dlugosc_platform && start_droga < *min_droga){    // koniec drogi
                    *min_droga = start_droga;
                }
            }
        }
    }

    bool graniczy_dziura(int x, int y){
        bool graniczy = false;

        if(y==1){
            if(
                platformy[y-1].dziury.count(x+1)    // dziura na x+1
            ) graniczy = true;
        }

        if(y>1 && y<=platformy.size()){
            if(
                platformy[y-1].dziury.count(x+1) ||     // dziura na x+1
                platformy[y-2].dziury.count(x)          // dziura na y+1
            ) graniczy = true;
        }

        return graniczy;
    }
};

int main(){
    // n - ilość platform
    // X - długość platform
    // (i, x) - i - numer platformy licząc od góry. x - odległość od lewego krańca platformy
    // z - liczba zapytań

    // Entry zmienne
    size_t n_platform;
    unsigned int n_zapytan;
    Poziom gra;

    // wejście
    cin >> n_platform >> gra.dlugosc_platform >> n_zapytan;

    // Wczytanie danych
    for(int i = 0; i < n_platform; i++)
    {
        int n_dziur;
        Platforma temp_platforma;

        cin >> n_dziur;

        for(int j=0; j<n_dziur; j++)
        {
            int miejsce_dziura;
            cin >> miejsce_dziura;
            temp_platforma.dziury.insert(miejsce_dziura);
        }

        gra.platformy.push_back(temp_platforma);
    }

    //gra.wypisz();

    // Zapytania
    for(int i = 0; i < n_zapytan; i++)
    {
        int start_y, min_droga = INT_MAX;
        cin >> start_y;

        gra.znajdz_droge(1, start_y, 0, &min_droga);

        cout << min_droga << endl;
    }

    //getchar();
    //getchar();
    return 0;
}