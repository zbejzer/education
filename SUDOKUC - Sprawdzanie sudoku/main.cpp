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

class sudoku {
private:
    int tablica[9][9];
public:
    void wczytaj() {
        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                cin>>tablica[i][j];
            }
            cin.ignore(INT_MAX, '\n');
        }
    }

    void wypisz() {
        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                cout<<tablica[i][j]<<" ";
            }
            cout<<endl;
        }
    }

    void sprawdzaj() {
        bool is_correct=true;
        int wartosc_rzedu, wartosc_kolumny, /*wartosc_kwadratu*/ ostatnie_liczby[9];

        // Sprawdzanie wartości rzędu
        for(int i=0; i<9; i++) {
            wartosc_rzedu=0;
            for(int j=0; j<9; j++) {
                wartosc_rzedu+=tablica[i][j];
                ostatnie_liczby[j]=tablica[i][j];

                if( tablica[i][j]<1 || tablica[i][j]>9) {
                    is_correct=false;
                }
            }

            for(int g=0; g<9; g++) {
                for(int h=0; h<9; h++) {
                    if( ostatnie_liczby[g]==ostatnie_liczby[h] && g!=h ) {
                        is_correct=false;
                    }
                }
            }

            if(wartosc_rzedu!=45) {
                is_correct=false;
            }
        }

        // Sprawdzanie wartości kolumny
        for(int i=0; i<9; i++) {
            wartosc_kolumny=0;
            for(int j=0; j<9; j++) {
                wartosc_kolumny+=tablica[j][i];
                ostatnie_liczby[j]=tablica[j][i];
            }

            for(int g=0; g<9; g++) {
                for(int h=0; h<9; h++) {
                    if( ostatnie_liczby[g]==ostatnie_liczby[h] && g!=h ) {
                        is_correct=false;
                    }
                }
            }

            if(wartosc_kolumny!=45) {
                is_correct=false;
            }
        }

        // Sprawdzanie wartości kwadratów 3x3

        if(is_correct) {
            cout<<"TAK"<<endl;
        }else{
            cout<<"NIE"<<endl;            
        }
    }
};

int main() {
    int liczba_testow;
    cin>>liczba_testow;
    cin.ignore(INT_MAX, '\n');

    for(int i=0; i<liczba_testow; i++) {
        sudoku mojeSudoku;
        mojeSudoku.wczytaj();
        //mojeSudoku.wypisz();
        mojeSudoku.sprawdzaj();
    }

    getchar();
    return 0;
};