#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
using namespace std;

string flamaster(string wejscie){
    string wyjscie="";
    int licznikPowtorzen=1;
    //cout<<"Uruchomiono funkcje! wejscie: "<<wejscie<<endl;
    //cout<<"Dlugosc wejscia: "<<wejscie.length()<<endl;

    for(int i=1; i<wejscie.length(); i++){
        if(wejscie[i]==wejscie[i-1]){
            licznikPowtorzen++;
            //cout<<"Powtorzono litere: "<<wejscie[i]<<endl;
            //cout<<"Licznik powtorzen: "<<licznikPowtorzen<<endl;
        }else{
            //cout<<"Litera rozni sie!: "<<wejscie[i]<<" "<<wejscie[i-1]<<endl;
            if(licznikPowtorzen>2){
                wyjscie+=wejscie[i-1];
                wyjscie+=to_string(licznikPowtorzen);
                //cout<<"Powtorzenie > 2: "<<wyjscie<<endl;
            }if(licznikPowtorzen==2){
                wyjscie+=wejscie[i-1];
                wyjscie+=wejscie[i-1];
                //cout<<"Powtorzenie == 2: "<<wyjscie<<endl;
            }if(licznikPowtorzen<2){
                wyjscie+=wejscie[i-1];
                //cout<<"Powtorzenie < 2: "<<wyjscie<<endl;
            }
            licznikPowtorzen=1;
        }
        if(wejscie.length()==i+1){
            //cout<<"Koniec petli!"<<endl;
            if(licznikPowtorzen>2){
                wyjscie+=wejscie[i-1];
                wyjscie+=to_string(licznikPowtorzen);
                //cout<<"Powtorzenie > 2: "<<wyjscie<<endl;
            }if(licznikPowtorzen==2){
                wyjscie+=wejscie[i-1];
                wyjscie+=wejscie[i-1];
                //cout<<"Powtorzenie == 2: "<<wyjscie<<endl;
            }if(licznikPowtorzen<2){
                wyjscie+=wejscie[i-1];
                //cout<<"Powtorzenie < 2: "<<wyjscie<<endl;
            }
            licznikPowtorzen=1;
        }
    }

    //cout<<"Koniec funkcje! wyjscie: "<<wyjscie<<endl;
    return wyjscie;
}

int main(){
    int liczbaTestow;
    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    if(1<=liczbaTestow<=50){
        string wejscie[liczbaTestow];

        for(int i=0; i<liczbaTestow; i++){
            getline(cin, wejscie[i]);
        }
        for(int i=0; i<liczbaTestow; i++){
            cout<<flamaster(wejscie[i])<<endl;
        }
    };

    system("pause");
    return 0;
};