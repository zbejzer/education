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

    vector <string> mojePolaczenia() {
        vector <string> lista_polaczen;

        for(int i=0; i<polaczenia.size(); i++) {
            lista_polaczen.push_back(polaczenia[i]);
        }

        return lista_polaczen;   
    }

    // konstruktor
    Adres(string _ip) {
        ip=_ip;
        polaczenia.push_back(ip);
    };

    Adres() {};
};

class Siec{
private:
    vector <Adres> adresy;
public:
    Adres* szukajIP(string szukane_ip) {
        for(int i=0; i<adresy.size(); i++) {
            if( adresy[i].getIP()==szukane_ip ) {
                return &adresy[i];
            }
        }
    }

    bool zawieraIP(string szukane_ip) {
        bool zawiera=false;

        for(int i=0; i<adresy.size(); i++) {
            if(adresy[i].getIP()==szukane_ip) {
                zawiera=true;
            }
        }

        return zawiera;
    }

    void wypiszAdresy() {
        for(int i=0; i<adresy.size(); i++) {
            cout<<adresy[i].getIP()<<":"<<endl;
            adresy[i].wypiszPolaczenia();
        }
    };

    void dodajAdres(string wejscie) {
        // dodanie adresu
        if( !zawieraIP(wejscie) ) {
            Adres temp(wejscie);
            adresy.push_back(temp);
        }
    };

    void dodajPolaczenie(string pierwszy_adres, string drugi_adres) {
        Adres *p;
        Adres temp;

        //szukanie pierwszego adresu, dodanie do niego drugiego adresu, nadpisanie go
        p = szukajIP(pierwszy_adres);
        temp = *p;
        temp.dodajPolaczenie(drugi_adres);
        *p = temp;

        p = szukajIP(drugi_adres);
        temp = *p;
        temp.dodajPolaczenie(pierwszy_adres);
        *p = temp;
    };

    vector <string> polaczeniaAdresu(string moj_adres, vector <string> *p_przeszukane_adresy, vector <string> *p_polaczone_adresy) {
        vector <string> przeszukane_adresy;
        przeszukane_adresy = *p_przeszukane_adresy;

        if( count(przeszukane_adresy.begin(), przeszukane_adresy.end(), moj_adres) == 0 ) {
            przeszukane_adresy.push_back(moj_adres);
            *p_przeszukane_adresy = przeszukane_adresy;

            Adres temp;
            Adres *p_temp;
            vector <string> polaczone_adresy;
            vector <string> dodane_polaczenia;
            vector <string> nowe_polaczenia;

            polaczone_adresy = *p_polaczone_adresy;

            p_temp = szukajIP(moj_adres);
            temp = *p_temp;
            dodane_polaczenia = temp.mojePolaczenia();

            // dodanie nowych polaczen do listy polaczonych adresow
            for(int i=0; i<dodane_polaczenia.size(); i++) {
                if( count(polaczone_adresy.begin(), polaczone_adresy.end(), dodane_polaczenia[i]) == 0) {
                    nowe_polaczenia.push_back(dodane_polaczenia[i]);
                    polaczone_adresy.push_back(dodane_polaczenia[i]);
                }
            }

            cout<<"Uruchomiono listowanie adresow dla IP: "<<moj_adres<<endl;
            cout<<"Nowe polaczenia: "<<endl;
            for(int i=0; i<nowe_polaczenia.size(); i++) {
                cout<<"   "<<nowe_polaczenia[i]<<endl;
            }

            *p_polaczone_adresy=polaczone_adresy;
            
            // 
            for(int i=0; i<nowe_polaczenia.size(); i++) {
                polaczeniaAdresu(nowe_polaczenia[i], p_przeszukane_adresy, p_polaczone_adresy);
            }

            //polaczone_adresy=*p_polaczone_adresy;
        }

        return *p_polaczone_adresy;
    }

    bool isConnected(string pierwszy_adres, string drugi_adres) {
        bool jest_polaczona=false;

        if( zawieraIP(pierwszy_adres) && zawieraIP(drugi_adres) ){
            vector <string> wynik;
            vector <string> przeszukane_adresy;
            vector <string> polaczone_adresy;

            wynik=polaczeniaAdresu(pierwszy_adres, &przeszukane_adresy, &polaczone_adresy);

            for(int i=0; i<wynik.size(); i++) {
                cout<<wynik[i]<<endl;
            }

            jest_polaczona=count(wynik.begin(), wynik.end(), drugi_adres);
        }

        return jest_polaczona;
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
            if( moja_siec.isConnected(argument_1, argument_2) ) {
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

/*
B 100.100.100.1 100.100.100.2
B 100.100.100.1 100.100.100.3
B 100.100.100.11 100.100.100.2
T 100.100.100.1 100.100.100.3
*/

/*
100.100.100.1:
   100.100.100.2
   100.100.100.3
100.100.100.2:
   100.100.100.1
   100.100.100.11
100.100.100.3:
   100.100.100.1
100.100.100.10:
   100.100.100.11
100.100.100.11:
   100.100.100.10
   100.100.100.2
*/