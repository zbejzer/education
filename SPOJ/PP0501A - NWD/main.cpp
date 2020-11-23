#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
using namespace std;

int fnwd(int liczbaA, int liczbaB){
    int nwd=1;
    for(int i=1; i>=min(liczbaA, liczbaB); i++){
        if(liczbaA%i==0&&liczbaB%i==0){
            nwd=i;
        }
    }
    return nwd;
}

int main(){
    int liczbaTestow, liczba[2];
    string obecnaLiczb, wejscie;
    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    for(int i=0; i<liczbaTestow; i++){
        obecnaLiczba="";
        getline(cin,wejscie);

        for(int i=0; i<wejscie.length(); i++){
            if(isspace(wejscie[i])){
                liczba[nLiczba]=stoi(obecnaLiczba);
                obecnaLiczba="";
                nLiczba++;
            }
        }else{
            obecnaLiczba+=wejscie[i];
        }

        if(obecnaLiczba!=""&&i+1==wejscie.length()){
            liczba[nLiczba]=stoi(obecnaLiczba);
            obecnaLiczba="";
            nLiczba++;
        }
    }

    for(int i=0; i<liczbaTestow; i++){
        cout<<fnwd()<<endl;
    }
    system("pause");
    return 0;
};