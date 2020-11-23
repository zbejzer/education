#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
using namespace std;

bool liczbaPierwsza(int liczba){
    bool isPrime=1;

    if(liczba!=0&&liczba!=1&&liczba!=-1){
        for(int i=2; i<abs(liczba); i++){
            if(liczba%i==0){
                isPrime=0;
            }
        }
    }else{
        isPrime=0;
    }

    return isPrime;
}

int main(){
    int liczbaTestow;

    cin>>liczbaTestow;
    cin.ignore(INT_MAX, '\n');

    int wejscie[liczbaTestow];

    for(int i=0; i<liczbaTestow; i++){
        cin>>wejscie[i];
        cin.ignore(INT_MAX, '\n');
    }
    for(int i=0; i<liczbaTestow; i++){
        if(liczbaPierwsza(wejscie[i])){
            cout<<"TAK"<<endl;
        }else{
            cout<<"NIE"<<endl;
        }
    }

    system("pause");
    return 0;
};