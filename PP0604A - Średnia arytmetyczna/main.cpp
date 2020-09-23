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

int main() {
    int liczba_testow;

    cin>>liczba_testow;
    cin.ignore(INT_MAX, '\n');

    for(int i=0; i<liczba_testow; i++) {
        int ilosc_liczb, wynik, suma=0;
        float srednia, najmniejsza=UINT32_MAX;

        cin>>ilosc_liczb;
        cin.ignore(INT_MAX, '\n');
        int liczby[ilosc_liczb];

        for(int j=0; j<ilosc_liczb; j++) {
            cin>>liczby[j];
            suma+=liczby[j];
        }

        srednia=(float)suma/ilosc_liczb;

        for(int j=0; j<ilosc_liczb; j++) {
            float roznica=abs(srednia-liczby[j]);
            if(roznica<najmniejsza) {   
                wynik=liczby[j];
                najmniejsza=roznica;
            }
        }
        
        cout<<wynik<<endl;
    }

    system("pause");
    return 0;
};