#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <math.h>
#include <utility>
#include <algorithm>
#include <array>
#include <iterator>
using namespace std;

// Funkcja liczy odległość dwóch punktów na układzie współrzędnych
float fOdleglosc(int x1, int y1, int x2, int y2){
    return sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
}

// Obiekt posiadający nazwę i wspołrzędne
struct punkt{
    float odleglosc;
    int x,y;
    string nazwa;
};

// Zwraca czy odległość pierwszego punktu jest większa niż odległość drugiego punktu
bool sortbydistance(punkt a, punkt b){ 
    return (a.odleglosc < b.odleglosc); 
}

int main(){
    int liczbaTestow;

    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    //Pętla uruchamia się tyle razy ile jest testów
    for(int i=0; i<liczbaTestow; i++){
        int liczbaPunktow;
        cin>>liczbaPunktow;
        cin.ignore(INT_MAX, '\n');

        vector <punkt> wektorPunkty;

        //Pętla wczytywania punktow
        for(int i=0; i<liczbaPunktow; i++){
            punkt myPoint;
            
            // Wpisanie do tymczasowego punktu nazwy i współrzędnych 
            cin>>myPoint.nazwa>>myPoint.x>>myPoint.y;
            cin.ignore(INT_MAX, '\n');

            // Obliczenie odległości punktu od środka układu
            myPoint.odleglosc=fOdleglosc(myPoint.x, myPoint.y, 0, 0);

            wektorPunkty.push_back(myPoint);
        }

        // Sortowanie wektora
        sort(wektorPunkty.begin(), wektorPunkty.end(), sortbydistance);

        // Wypisanie wektora NAZWA X Y
        for(int i=0; i<liczbaPunktow; i++){
            cout<<wektorPunkty[i].nazwa<<" "<<wektorPunkty[i].x<<" "<<wektorPunkty[i].y<<endl;
        }

        // Miejsce na pustą linijkę po każdym teście
        if(1+i!=liczbaTestow){
            getchar();
        }
    }

    getchar();
    return 0;
}