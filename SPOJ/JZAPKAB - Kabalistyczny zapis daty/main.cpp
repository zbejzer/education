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
using namespace std;

int getCharValue(char c) {   
    switch(toupper(c)) {
        case 'A': return 1; break;
        case 'B': return 2; break;
        case 'C': return 3; break;
        case 'D': return 4; break;
        case 'E': return 5; break;
        case 'F': return 6; break;
        case 'G': return 7; break;
        case 'H': return 8; break;
        case 'I': return 9; break;
        case 'K': return 10; break;
        case 'L': return 20; break;
        case 'M': return 30; break;
        case 'N': return 40; break;
        case 'O': return 50; break;
        case 'P': return 60; break;
        case 'Q': return 70; break;
        case 'R': return 80; break;
        case 'S': return 90; break;
        case 'T': return 100; break;
        case 'V': return 200; break;
        case 'X': return 300; break;
        case 'Y': return 400; break;
        case 'Z': return 500; break;
        default: return 0; break;
    }
}

int main() {
    string wejscie;
    int wartosc=0;
    cin>>wejscie;
    cin.ignore(INT_MAX, '\n');

    for(int i=0; i<wejscie.size(); i++) {
        wartosc+=getCharValue(wejscie[i]);
    }

    cout<<wartosc;

    getchar();
    return 0;
};