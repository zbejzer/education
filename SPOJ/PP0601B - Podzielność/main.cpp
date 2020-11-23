#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
#include <vector>
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

bool podzielnosc(int wejscie, int dzielnik, int nieDzielnik){
    if(wejscie%dzielnik==0&&wejscie%nieDzielnik!=0){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    int liczbaTestow;
    vector <string> liczby;

    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    string wejscie[liczbaTestow];

    for(int i=0; i<liczbaTestow; i++){
        getline(cin, wejscie[i]);
    }

    liczby=parseStringInput(wejscie[0]);

    for(int i=0; i<liczbaTestow; i++){
        liczby=parseStringInput(wejscie[i]);
        for(int j=1; j<stoi(liczby[0]); j++){
            if(podzielnosc(j, stoi(liczby[1]), stoi(liczby[2]))){
                cout<<j<<" ";
            }
        }
        cout<<endl;
    }

    system("pause");
    return 0;
}