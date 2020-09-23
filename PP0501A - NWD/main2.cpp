#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
using namespace std;

int nwd(int liczbaA, int liczbaB){
    if(liczbaA==0||liczbaB==0){
        return 0;
    }else{
        int wynik;
        for(int i=1; i<=min(liczbaA, liczbaB); i++){
            if(liczbaA%i==0&&liczbaB%i==0){
                wynik=i;
            }
        }
        return wynik;
    }
}

/*int wejscieLiczby(int nLiczb, string fwejscie){
    int wyjscie[nLiczb], obecnaLiczba=0;
    string tempLiczba="";

    //Analiza linijki i wyjscie
    for(int i=0; i<fwejscie.length(); i++){
        if(isspace(fwejscie[i])){
            wyjscie[obecnaLiczba]=stoi(tempLiczba);
            tempLiczba="";
            obecnaLiczba++;
        }else{
            tempLiczba+=fwejscie[i];
        }
        if(tempLiczba!=""&&i+1==fwejscie.length()){
            wyjscie[obecnaLiczba]=stoi(tempLiczba);
            tempLiczba="";
            obecnaLiczba++;
        }
    }

    return wyjscie[];
}*/

int main(){
    int liczbaTestow, liczba[2];
    string obecnaLiczb, wejscie;

    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    int wynik[liczbaTestow];

    for(int i=0; i<liczbaTestow; i++){
        getline(cin, wejscie);

        int obecnaLiczba=0;
        string tempLiczba="";

        //Analiza linijki i wyjscie
        for(int i=0; i<wejscie.length(); i++){
            if(isspace(wejscie[i])){
                liczba[obecnaLiczba]=stoi(tempLiczba);
                tempLiczba="";
                obecnaLiczba++;
            }else{
                tempLiczba+=wejscie[i];
            }
            if(tempLiczba!=""&&i+1==wejscie.length()){
                liczba[obecnaLiczba]=stoi(tempLiczba);
                tempLiczba="";
                obecnaLiczba++;
            }
        }
        wynik[i]=nwd(liczba[0], liczba[1]);
    }
    for(int i=0; i<liczbaTestow; i++){
        cout<<wynik[i]<<endl;
    }
    system("pause");
    return 0;
};