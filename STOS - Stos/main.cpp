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

int main()
{
    string wejscie, tablica[10]={"puste!","puste!","puste!","puste!","puste!","puste!","puste!","puste!","puste!","puste!"};

    // Pela wykonywana jest do czasu aż wejscie nie jest puste
    do
    {   
        // Jeżeli pobrano + dodajemy do stosu, a jeżeli - usuwamy ze stosu i wypisujemy wartosc
        getline(cin, wejscie);
        if(wejscie=="+")
        {
            string wartosc;
            cin>>wartosc;
            cin.ignore(INT_MAX, '\n');

            if(tablica[9]=="puste!")
            {   
                // Przeniesienie elemntów w tablicy o jeden w dól i położenie elementu na górę stosu
                for(int i=9; i>0; i--)
                {
                    tablica[i]=tablica[i-1];
                }
                tablica[0]=wartosc;
                cout<<":)"<<endl;
            }else{
                cout<<":("<<endl;
            }
        }
        if(wejscie=="-")
        {   
            if(tablica[0]!="puste!")
            {
                // Zdjęcie ze stosu i przeniesienie elementów w tablicy o jeden w górę
                cout<<tablica[0]<<endl;
                for(int i=0; i<9; i++)
                {
                    tablica[i]=tablica[i+1];
                    //cout<<tablica[i]<<endl;
                }
                tablica[9]="puste!";
            }else{
                cout<<":("<<endl;
            }
        }

    } while(wejscie!="\n"&&wejscie!="");
    

    getchar();
    return 0;
}