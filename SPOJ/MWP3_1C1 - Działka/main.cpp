#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>

using namespace std;

int algEuklidesa(int liczbaA, int liczbaB){
    while((liczbaA!=0)&&(liczbaB!=0)){
        if(liczbaA>liczbaB){
            liczbaA-=liczbaB;
        }else{
            liczbaB-=liczbaA;
        }
    }
    return max(liczbaA, liczbaB);
}

int dzialka(int liczbaA, int liczbaB){
    if(liczbaA==liczbaB){
        int i=liczbaA-1;
        while((liczbaA%i)!=0){
            i--;
        }
        return i;
        //return algEuklidesa(liczbaA, liczbaB);
    }else{
        return algEuklidesa(liczbaA, liczbaB);
    }
}

int main(){
    int liczbatestow,liczba1,liczba2;
    cin>>liczbatestow;
    cin.ignore(INT_MAX, '\n');

    int wynik[liczbatestow];

    for(int i=0;i<liczbatestow;i++){
        cin>>liczba1>>liczba2;
        cin.ignore(INT_MAX, '\n');
        wynik[i]=dzialka(liczba1, liczba2);
    }

    for(int i=0;i<liczbatestow;i++){
        cout<<wynik[i]<<endl;
    }

    getchar();
    return 0;
}