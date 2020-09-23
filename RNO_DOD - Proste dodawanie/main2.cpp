#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
using namespace std;

int dodawanie(){
    string wejscie, obecnaLiczba;
    int iloscLiczb, suma=0, nLiczba=0;
    cout<<"Uruchamienie funkcji dodawanie!"<<endl;
    cin>>iloscLiczb;
    cin.ignore(INT_MAX, '\n');
    cout<<"Wczytano ilosc liczb: "<<iloscLiczb<<endl;
    int liczba[iloscLiczb];
    getline(cin,wejscie);
    //cin.ignore(INT_MAX, '\n');
    
    obecnaLiczba="";
    for(int i=0; i<wejscie.length(); i++){
        if(isspace(wejscie[i])){
            liczba[nLiczba]=stoi(obecnaLiczba);
            obecnaLiczba="";
            nLiczba++;
        }else{
            obecnaLiczba+=wejscie[i];
        }
        if(obecnaLiczba!=""&&i+1==wejscie.length()){
            liczba[nLiczba]=stoi(obecnaLiczba);
            obecnaLiczba="";
            nLiczba++;
        }
    }

    for(int i=0; i<iloscLiczb; i++){
        cout<<"Liczba: "<<liczba[i]<<endl;
        suma+=liczba[i];
    }
    //cout<<"Suma wprowadzonych liczb to: "<<suma;
    return suma;
}

int main(){
    int liczbaTestow;
    cin.clear();
    cin>>liczbaTestow;
    //cin.ignore(INT_MAX, '\n');
    cout<<"Wczytano ilosc testow: "<<liczbaTestow<<endl;
    if(1<liczbaTestow<100){
        int suma[liczbaTestow];
        for(int i=0; i<liczbaTestow; i++){
            suma[i]=dodawanie();
        }
        for(int i=0; i<liczbaTestow; i++){
            cout<<suma[i]<<endl;
        }
    };
    system("pause");
    return 0;
};