#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <math.h>
using namespace std;


//Przyjmuje wejscie w formacie HH:MM
string dodajMinuty(string wejscie, int przesuniecie){
    int hour, minute;
    string wyjscie="", swap="";

    swap+=wejscie[0];
    swap+=wejscie[1];
    hour=stoi(swap);
    swap.clear();
    swap+=wejscie[3];
    swap+=wejscie[4];
    minute=stoi(swap);

    hour+=(minute+przesuniecie)/60;
    minute=(minute+przesuniecie)%60;

    if(hour>=24){
        hour-=24;
    }

    if(hour<10){
        wyjscie+="0";
    }
    wyjscie+=to_string(hour);
    wyjscie+=":";
    if(minute<10){
        wyjscie+="0";
    }
    wyjscie+=to_string(minute);

    return(wyjscie);
}

int main(){
    string rozpoczecie, wejscie;
    bool koniec=false;
    vector <string> dzwonki;

    cin>>rozpoczecie;
    cin.ignore(INT_MAX, '\n');
    dzwonki.push_back(rozpoczecie);
    dzwonki.push_back(dodajMinuty(dzwonki[dzwonki.size()-1], 45));

    while(!koniec){
        getline(cin, wejscie);
        if(wejscie==""||wejscie=="\n"){
            koniec=true;
        }else{
            dzwonki.push_back(dodajMinuty(dzwonki[dzwonki.size()-1], stoi(wejscie)));
            dzwonki.push_back(dodajMinuty(dzwonki[dzwonki.size()-1], 45));
        }
    }

    for(int i=0; i<dzwonki.size(); i++){
        if(1+i==dzwonki.size()){
            cout<<dzwonki[i]<<endl;
        }else{
            cout<<dzwonki[i]<<", ";
        }
    }

    system("pause");
    return 0;
};