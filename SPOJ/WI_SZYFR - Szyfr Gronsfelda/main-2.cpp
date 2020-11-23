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

// ascii 65-A
//       90-Z

string szyfruj(string klucz, string wejscie)
{
    string wyjscie="";
    int n=0;

    for(int i=0; i<wejscie.size(); i++)
    {
        int ascii_litera = (int)wejscie[i];
        string przesuniecie="";
        przesuniecie+=klucz[n];
        
        ascii_litera+=stoi(przesuniecie);
        if(ascii_litera>90)
        {
            ascii_litera-=25;
        }

        // dodanie litery do wyjscia
        wyjscie+=(char)ascii_litera;

        // przesuniecie cyfry szyfrującej
        n++; 
        if(n>=klucz.size())
        {
            n=0;
        }
    }

    return wyjscie;
}

string deszyfruj(string klucz, string wejscie)
{
    string wyjscie="";
    int n=0;

    for(int i=0; i<wejscie.size(); i++)
    {
        char litera = wejscie[i];
        int ascii_litera = (int)litera;
        string przesuniecie="";
        przesuniecie+=klucz[n];
        if(ascii_litera-stoi(przesuniecie)<65)
        {
            ascii_litera-=stoi(przesuniecie);
            ascii_litera+=25;
        }else{
            ascii_litera-=stoi(przesuniecie);
        }

        // dodanie litery do wyjscia
        litera=ascii_litera;
        wyjscie+=litera;

        // przesuniecie cyfry szyfrującej
        n++; 
        if(n>=klucz.size())
        {
            n=0;
        }
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
        cout<<szyfruj(klucz, wejscie);
    }
    if(polecenie=="DESZYFRUJ")
    {
        cout<<deszyfruj(klucz, wejscie);
    }

    getchar();
    return 0;
};