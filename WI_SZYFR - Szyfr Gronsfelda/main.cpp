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

string szyfruj(string klucz, string wejscie)
{
    string wyjscie="";

    for(int i=0; i<wejscie.size(); i++)
    {

    }

    return wyjscie;
}

string deszyfruj(string klucz, string wejscie)
{
    string wyjscie="";

    for(int i=0; i<wejscie.size(); i++)
    {
        
    }

    return wyjscie;
}

int main(){
    string polecenie, klucz, wejscie;
    cin>>polecenie;
    cin.ignore(INT_MAX, '\n');
    cin>>klucz;
    cin.ignore(INT_MAX, '\n');
    cin>>wejscie;
    cin.ignore(INT_MAX, '\n');

    if(polecenie=="SZYFRUJ")
    {
        szyfruj(klucz, wejscie);
    }
    if(polecenie=="DESZYFRUJ")
    {
        deszyfruj(klucz, wejscie);
    }

    getchar();
    return 0;
};