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

// Funkcja szuka najmniejszej wspólnej wielokrotności
int nww(int a, int b)
{
    int wspWiel = max(a,b);

    while( (wspWiel%min(a,b)) != 0 )
    {
        wspWiel += max(a,b);
    }

    return wspWiel;
}


int main(){
    int liczbaTestow;

    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    // Pętla uruchamia się tyle razy ile jest testów
    for(int i=0; i<liczbaTestow; i++)
    {
        int grupa1, grupa2;
        cin>>grupa1>>grupa2;
        cin.ignore(INT_MAX, '\n');
        cout<<nww(grupa1, grupa2)<<endl;
    }

    getchar();
    return 0;
}