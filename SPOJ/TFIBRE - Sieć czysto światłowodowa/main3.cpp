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
    void addConnection(string nowe_ip) {
        // zapobiegnie dublowaniu
        if( count(polaczenia.begin(), polaczenia.end(), nowe_ip) == 0 ) {
            polaczenia.push_back(nowe_ip);
        }
    };

    string getIP() {
        return ip;
    };

    vector <string> getConnections() {
        return polaczenia;   
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
    vector <Adres> IPs;
public:
    Adres * findIP(string szukane_ip) {
        Adres * p;
        
        for(int i=0; i<IPs.size(); i++) {
            if( IPs[i].getIP()==szukane_ip ) {
                p=&IPs[i];
            }
        }

        return p;
    }

    bool ipExsists(string szukane_ip) {
        bool exists=false;

        for(int i=0; i<IPs.size(); i++) {
            if(IPs[i].getIP()==szukane_ip) {
                exists=true;
            }
        }

        return exists;
    }

    void addIP(string nowe_ip) {
        // dodanie adresu
        if( !ipExsists(nowe_ip) ) {
            Adres temp(nowe_ip);
            IPs.push_back(temp);
        }
    }

    void addConnection(string pierwszy_adres, string drugi_adres) {
        Adres * p;
        Adres temp;

        //szukanie pierwszego adresu, dodanie do niego drugiego adresu, nadpisanie go
        p = findIP(pierwszy_adres);
        temp = *p;
        temp.addConnection(drugi_adres);
        *p = temp;

        p = findIP(drugi_adres);
        temp = *p;
        temp.addConnection(pierwszy_adres);
        *p = temp;
    }

    vector <string> getIpConnections(string moj_ip, vector <string> *p_przeszukane_ip, vector <string> *p_polaczone_ip) {
        vector <string> przeszukane_ip;
        przeszukane_ip = *p_przeszukane_ip;

        if( count(przeszukane_ip.begin(), przeszukane_ip.end(), moj_ip) == 0 ) {
            przeszukane_ip.push_back(moj_ip);
            *p_przeszukane_ip = przeszukane_ip;

            Adres temp;
            Adres *p_temp;
            vector <string> polaczone_ip;
            vector <string> dodane_polaczenia;
            vector <string> nowe_polaczenia;

            polaczone_ip = *p_polaczone_ip;

            p_temp = findIP(moj_ip);
            temp = *p_temp;
            dodane_polaczenia = temp.getConnections();

            // dodanie nowych polaczen do listy polaczonych adresow
            for(int i=0; i<dodane_polaczenia.size(); i++) {
                if( count(polaczone_ip.begin(), polaczone_ip.end(), dodane_polaczenia[i]) == 0) {
                    nowe_polaczenia.push_back(dodane_polaczenia[i]);
                    polaczone_ip.push_back(dodane_polaczenia[i]);
                }
            }

            /*cout<<"Uruchomiono listowanie adresow dla IP: "<<moj_ip<<endl;
            cout<<"Nowe polaczenia: "<<endl;
            for(int i=0; i<nowe_polaczenia.size(); i++) {
                cout<<"   "<<nowe_polaczenia[i]<<endl;
            }*/

            *p_polaczone_ip=polaczone_ip;
            
            // 
            for(int i=0; i<nowe_polaczenia.size(); i++) {
                getIpConnections(nowe_polaczenia[i], p_przeszukane_ip, p_polaczone_ip);
            }
        }

        return *p_polaczone_ip;
    }

    bool isConnected(string pierwszy_adres, string drugi_adres) {
        bool jest_polaczona=false;

        if( ipExsists(pierwszy_adres) && ipExsists(drugi_adres) ){
            vector <string> wynik;
            vector <string> przeszukane_adresy;
            vector <string> polaczone_adresy;

            wynik=getIpConnections(pierwszy_adres, &przeszukane_adresy, &polaczone_adresy);

            /*for(int i=0; i<wynik.size(); i++) {
                cout<<wynik[i]<<endl;
            }*/

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
            moja_siec.addIP(argument_1);
            moja_siec.addIP(argument_2);
            moja_siec.addConnection(argument_1, argument_2);
           // moja_siec.wypiszAdresy();
        } else 
        if( polecenie=="T" ) {
            if( moja_siec.isConnected(argument_1, argument_2) ) {
                cout<<"T"<<endl;
            } else {
                cout<<"N"<<endl;
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