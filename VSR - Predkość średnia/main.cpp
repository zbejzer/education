#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <math.h>
using namespace std;

int avgSpeed(int v1, int v2){
    float wynik;
    //cout<<"Uruchomiono funkcje avgSpeed!"<<endl<<"Argumenty: ";
    //cout<<"v1: "<<v1<<endl;
    //cout<<"v2: "<<v2<<endl;

    wynik=2.0/((1.0/v1)+(1.0/v2));

    //cout<<"Koniec funkcji avgSpeed!"<<endl<<"Wynik: "<<wynik<<endl;
    return (int)wynik;
}

int main(){
    int liczbaTestow, a, b;

    cin>>liczbaTestow;
    int wynik[liczbaTestow];

    for(int i=0; i<liczbaTestow; i++){
        cin>>a>>b;
        wynik[i]=avgSpeed(a, b);
    }
    for(int i=0; i<liczbaTestow; i++){
        cout<<wynik[i]<<endl;
    }
    

    system("pause");
    return 0;
}