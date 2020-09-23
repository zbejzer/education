#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <math.h>
#include <utility>
#include <algorithm>
#include <array>
#include <iterator>
#include <iomanip> 
using namespace std;

class Adres {
private:
    string ip;
    vector <string> polaczenia;
public:
    void dodajPolaczenie(string argument) {
        bool wystepuje=false;

        // skanowanie istniejacych polaczen w celu zapobiegnieciu zdublowania
        for(int i=0; i<polaczenia.size(); i++) {
            if(polaczenia[i]==argument) {
                wystepuje=true;
            }
        }


        if(!wystepuje) {
            polaczenia.push_back(argument);
        }
    };

    string getIP() {
        return ip;
    };

    void wypiszPolaczenia() {
        for(int i=0; i<polaczenia.size(); i++) {
            cout<<"   "<<polaczenia[i]<<endl;
        }
    }

    void dodajMojePolaczeniaDoWektora(vector <string> *wejscie, vector <string> *przeszukane_adresy) {
        vector <string> temp;
        vector <string> przeszukane_adresy_temp;
        temp=*wejscie;
        przeszukane_adresy_temp=*przeszukane_adresy;

        bool jest_na_liscie=false;

        // sprawdzam czy jest na liscie juz przeszukanych adresow
        for(int i=0; i<przeszukane_adresy_temp.size(); i++) {
            if( przeszukane_adresy_temp[i]==ip ) {
                jest_na_liscie=true;
            }
        }

        if( !jest_na_liscie ){
            // dodawanie polaczonych adresow do wektora
            for(int i=0; i<polaczenia.size(); i++) {
                bool jest_w_wektorze=false;

                // skanowanie istniejacych polaczen w celu zapobiegnieciu zdublowania
                for(int j=0; j<temp.size(); j++) {
                    if(temp[j]==polaczenia[i]) {
                        jest_w_wektorze=true;
                    }
                }

                if( !jest_w_wektorze ) {
                    temp.push_back(polaczenia[i]);
                }
            }

            // dodanie własnego adresu do listy już przeszukanych adresów
            przeszukane_adresy_temp.push_back(ip);
            *przeszukane_adresy=przeszukane_adresy_temp;
            *wejscie=temp;
        }      
    }

    // konstruktor
    Adres(string _ip) {
        ip=_ip;
    };

    Adres() {};
};

class Siec{
private:
    vector <Adres> adresy;
public:
    Adres szukajPoIP(string szukane_ip) {
        for(int i=0; i<adresy.size(); i++) {
            if( adresy[i].getIP()==szukane_ip ) {
                return adresy[i];
            }
        }
    }

    void wypiszAdresy() {
        for(int i=0; i<adresy.size(); i++) {
            cout<<adresy[i].getIP()<<":"<<endl;
            adresy[i].wypiszPolaczenia();
        }
    };

    void dodajAdres(string wejscie) {
        bool wystepuje=false;

        // skanowanie adresów w celu sprawdzenia czy podany adres już nie występuje
        for(int i=0; i<adresy.size(); i++) {
            if(adresy[i].getIP()==wejscie) {
                wystepuje=true;
            }
        }

        // dodanie adresu
        if(!wystepuje) {
            Adres temp(wejscie);
            adresy.push_back(temp);
        }
    };

    void dodajPolaczenie(string pierwszy_adres, string drugi_adres) {
        // skanowanie adresów w celu znalezienia pierwszego adresu
        for(int i=0; i<adresy.size(); i++) {
            if(adresy[i].getIP()==pierwszy_adres) {
               adresy[i].dodajPolaczenie(drugi_adres);
            }
        }

        // skanowanie adresów w celu znalezienia drugiego adresu
        for(int i=0; i<adresy.size(); i++) {
            if(adresy[i].getIP()==drugi_adres) {
               adresy[i].dodajPolaczenie(pierwszy_adres);
            }
        }
    };

    bool sprawdzPolaczenie(string pierwszy_adres, string drugi_adres) {
        bool jest_polaczona=false;
        
        // stworzenie wektora polaczen posrednich i bezposrednich pierwszego adresu

        vector <string> posrednie_polaczenia;
        vector <string> pusty;
        Adres temp;

        temp=szukajPoIP(pierwszy_adres);
        temp.dodajMojePolaczeniaDoWektora(&posrednie_polaczenia, &pusty);

        // Tymczasowe wypisanie wektora
        for(int i=0; i<posrednie_polaczenia.size(); i++) {
            cout<<posrednie_polaczenia[i]<<endl;
        }

        // przeszukanie wektora polaczen posrednich i bezposrednich
        // pierwszego adresu w celu znalezienia drugiego adresu

        for(int i=0; i<posrednie_polaczenia.size(); i++) {
            if( posrednie_polaczenia[i]==drugi_adres ) {
                jest_polaczona=true;
            }
        }

        if(jest_polaczona) {
            return 1;
        } else {
            return 0;
        }
    }
};

int main() {
    Siec moja_siec;
    char c;

    c = std::cin.peek();
    while( (int)c!=10 && (int)c!=-1 ) {
        string polecenie, argument_1, argument_2;
        cin>>polecenie>>argument_1>>argument_2;
        cin.ignore(INT_MAX, '\n');

        if( polecenie=="B" ) {
            moja_siec.dodajAdres(argument_1);
            moja_siec.dodajAdres(argument_2);
            moja_siec.dodajPolaczenie(argument_1, argument_2);
            moja_siec.wypiszAdresy();
        } else 
        if( polecenie=="T" ) {
            if( moja_siec.sprawdzPolaczenie(argument_1, argument_2) ) {
                cout<<"TAK"<<endl;
            } else {
                cout<<"NIE"<<endl;
            }
            
        }

        c = std::cin.peek();
    }
    
    cin.ignore(INT_MAX, '\n');
    return 0;
};


/*
    komenda sprawdzania polaczneia miedzy dwoma adresami w klasie siec,
    powodujaca stworzenie listy bezpośrednich i pośrednich polaczen adresu,
    nastepnie szukajaca w nim zadanego (jako drugi argument) adresu
*/

/*
B 100.100.100.1 100.100.100.2
B 100.100.100.1 100.100.100.3
B 100.100.100.10 100.100.100.11
B 100.100.100.11 100.100.100.2
T 100.100.100.1 100.100.100.3
*/