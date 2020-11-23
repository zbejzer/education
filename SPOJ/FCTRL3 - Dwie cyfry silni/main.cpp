#include <iostream>
using namespace std;

long long  silnia(long long  liczba){
    long long wynik=1;

    for(int i=2;i<liczba+1;i++){
        wynik=wynik*i;
    };
    return wynik;
};

int main(){
    int liczbaTestow;
    cin>>liczbaTestow;

    for(int i=0; i<liczbaTestow; i++){
        int pobranaLiczba;
        cin>>pobranaLiczba;
        if(pobranaLiczba>10){
            cout<<"0 0"<<endl;
        }else{
            if(pobranaLiczba<2){
                cout<<"0 1"<<endl;
            }else{
                long long wynik;
                wynik = silnia(pobranaLiczba);
                cout<<(wynik%100)/10<<" "<<wynik%10<<endl;
            };
        };
    };

    getchar();
    return 0;
}
