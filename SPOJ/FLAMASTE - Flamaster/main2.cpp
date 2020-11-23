#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
using namespace std;

string flamaster(string wejscie){
    wejscie+=" ";
    string wyjscie="";
    int licznikPowtorzen=1;

    for(int i=1; i<wejscie.length(); i++){
        if(wejscie[i]==wejscie[i-1]){
            licznikPowtorzen++;
        }
        if(wejscie[i]!=wejscie[i-1]||i+1==wejscie.length()){
            if(licznikPowtorzen>2){
                wyjscie+=wejscie[i-1];
                wyjscie+=to_string(licznikPowtorzen);
            }if(licznikPowtorzen==2){
                wyjscie+=wejscie[i-1];
                wyjscie+=wejscie[i-1];
            }if(licznikPowtorzen<2){
                wyjscie+=wejscie[i-1];
            }
            licznikPowtorzen=1;
        }
    }
    return wyjscie;
}

int main(){
    int liczbaTestow;

    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    string wejscie[liczbaTestow];

    for(int i=0; i<liczbaTestow; i++){
        getline(cin, wejscie[i]);
    }
    for(int i=0; i<liczbaTestow; i++){
        cout<<flamaster(wejscie[i])<<endl;
    }

    system("pause");
    return 0;
};