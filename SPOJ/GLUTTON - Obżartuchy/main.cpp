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

int iloscPudelek(int ilosc_obzartuchow, int obzartuchy[], int pudelko)
{
    float ciastka=0;
    for(int i=0; i<ilosc_obzartuchow; i++)
    {
        ciastka+=86400/obzartuchy[i];
    }
    return ceil( ciastka/pudelko );
}

int main()
{
    int zestawyDanych;
    cin>>zestawyDanych;
    cin.ignore(INT_MAX, '\n');

    for(int i=0; i<zestawyDanych; i++)
    {   
        int ciastka, ilosc_obzartuchow;
        cin>>ilosc_obzartuchow>>ciastka;
        cin.ignore(INT_MAX, '\n');
        int obzartuchy[ilosc_obzartuchow];
        for(int i=0; i<ilosc_obzartuchow; i++)
        {   
            cin>>obzartuchy[i];
            cin.ignore(INT_MAX, '\n');
        }
        cout<<iloscPudelek(ilosc_obzartuchow, obzartuchy, ciastka)<<endl;
    }

    getchar();
    return 0;
}