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

int countOccurrences(unsigned long long szukana, vector <unsigned long long> wejscie){
    int wystapienia=0;

    for(int i=0; i<wejscie.size(); i++){
        if(wejscie[i]==szukana){
            wystapienia++;
        }
    }

    return wystapienia;
}



int main(){
    int liczbaTestow;

    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    // Pętla uruchamia się tyle razy ile jest testów
    for(int i=0; i<liczbaTestow; i++){
        int iloscLiczb;

        // Ilość liczb do wczytania
        cin>>iloscLiczb;
        cin.ignore(INT_MAX, '\n');

        vector <unsigned long long> liczby;
        vector <unsigned long long> liczbyWyjsciowe;

        // Pętla wczytywania liczb do wektora
        for(int i=0; i<iloscLiczb; i++){
            unsigned long long liczba;

            cin>>liczba;
            cin.ignore(INT_MAX, '\n');

            liczby.push_back(liczba);
        }

        // Zwróć liczby które stanowiły n/2+1 liczb z zakresu
        for(int i=0; i<liczby.size(); i++){
            if( ( countOccurrences(liczby[i], liczby)>liczby.size()/2 )&&( countOccurrences(liczby[i], liczbyWyjsciowe)==0) ){
                liczbyWyjsciowe.push_back(liczby[i]);
                cout<<liczby[i]<<endl;
            }
        }

        if(liczbyWyjsciowe.size()==0){
            cout<<"-1"<<endl;
        }
    }

    getchar();
    return 0;
}