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

vector <string> parseStringInput(string wejscie){
    vector <string> wyjscie;
    string wyraz="";

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
    int zestawyDanych;
    cin>>zestawyDanych;
    cin.ignore(INT_MAX, '\n');

    for(int i=0; i<zestawyDanych; i++)
    {
        string wejscie;
        getline(cin, wejscie);

        vector <string> wektor_liczby;
        wektor_liczby=parseStringInput(wejscie);

        int rozmiar=stoi(wektor_liczby[0]);

        int liczby[rozmiar];

        for(int i=0; i<rozmiar-1; i++)
        {
           liczby[i]=stoi(wektor_liczby[i+2]);
        }

        liczby[rozmiar-1]=stoi(wektor_liczby[1]);

        for(int i=0; i<rozmiar; i++)
        {
           cout<<liczby[i]<<" ";
        }
        
        cout<<endl;
    }


    getchar();
    return 0;
};