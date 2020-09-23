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
        int ostatnie_liczby[9];

        // Sprawdzanie rzędu
        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                ostatnie_liczby[j]=tablica[i][j];

                if( tablica[i][j]<1 || tablica[i][j]>9 ) {
                    is_correct=false;
                }
            }

            //cout<<"Sprawdzanie rzedu: ";
            for(int g=0; g<9; g++) {
                for(int h=0; h<9; h++) {
                    if( ostatnie_liczby[g]==ostatnie_liczby[h] && g!=h ) {
                        is_correct=false;
                    }
                }
                //cout<<ostatnie_liczby[g]<<" ";
            }
            //cout<<endl;
        }

        // Sprawdzanie kolumny
        for(int i=0; i<9; i++) {
            for(int j=0; j<9; j++) {
                ostatnie_liczby[j]=tablica[j][i];
            }

            //cout<<"Sprawdzanie kolumny: ";
            for(int g=0; g<9; g++) {
                for(int h=0; h<9; h++) {
                    if( ostatnie_liczby[g]==ostatnie_liczby[h] && g!=h ) {
                        is_correct=false;
                    }
                }
                //cout<<ostatnie_liczby[g]<<" ";
            }
            //cout<<endl;
        }

        // Sprawdzanie kwadratów 3x3
        for(int kwadrat_poziom=0; kwadrat_poziom<3; kwadrat_poziom++) {
            for(int kwadrat_pion=0; kwadrat_pion<3; kwadrat_pion++) {
                // dla każdego kwadratu
                int i=0;
                for(int poziom=0; poziom<3; poziom++) {
                    for(int pion=0; pion<3; pion++) {
                        ostatnie_liczby[i]=tablica[ kwadrat_poziom*3+poziom ][ kwadrat_pion*3+pion ];
                        i++;
                    }
                }

                //cout<<"Sprawdzanie kwadratow: ";
                for(int g=0; g<9; g++) {
                    for(int h=0; h<9; h++) {
                        if( ostatnie_liczby[g]==ostatnie_liczby[h] && g!=h ) {
                            is_correct=false;
                        }
                    }
                    //cout<<ostatnie_liczby[g]<<" ";
                }
                //cout<<endl;
            }
        }

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
    v

    for(int i=0; i<liczba_testow; i++) {
        sudoku mojeSudoku;
        mojeSudoku.wczytaj();
        //mojeSudoku.wypisz();
        mojeSudoku.sprawdzaj();
    }

    cin.ignore(INT_MAX, '\n');
    getchar();
    return 0;
};