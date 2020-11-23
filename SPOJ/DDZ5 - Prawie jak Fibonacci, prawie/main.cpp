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

vector <string> parseStringInput(){
    vector <string> wyjscie;
    string wyraz="", wejscie;

    getline(cin, wejscie);

    for(int i=0; i<wejscie.length(); i++){
        if(wejscie[i]!=' '){
            wyraz+=wejscie[i];
        }
        if(wejscie[i]==' '||i+1==wejscie.length()){
            wyjscie.push_back(wyraz);
            wyraz="";
        }
    }

    return wyjscie;
}

int main(){
    int ilosc_liczb, licznik=0;
    vector <string> elementy;

    cin>>ilosc_liczb;
    cin.ignore(INT_MAX, '\n');

    elementy=parseStringInput();

    for(int i=2; i<ilosc_liczb; i++)
    {
        if( stoi(elementy[i-2])+stoi(elementy[i-1])==stoi(elementy[i]) )
        {
            licznik++;
        }
    }

    cout<<licznik<<endl;

    system("pause");
    return 0;
};
