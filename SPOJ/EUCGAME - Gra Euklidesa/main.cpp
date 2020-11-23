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

// Funkcja prowadzi odejmowanie do póki jest ono możliwe
void eucgame(int a, int b)
{
    while( max(a,b)-min(a,b)>0 )
    {
        if(a>b)
        {
            a-=b;
        }else{
            b-=a;
        }
    }
    cout<<a+b<<endl;
}


int main(){
    int liczbaTestow;

    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    // Pętla uruchamia się tyle razy ile jest testów
    for(int i=0; i<liczbaTestow; i++)
    {
        int a, b;
        cin>>a>>b;
        cin.ignore(INT_MAX, '\n');
        eucgame(a, b);
    }

    getchar();
    return 0;
}