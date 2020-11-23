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

int main(){
    int liczba_testow;

    cin>>liczba_testow;
    cin.ignore(INT_MAX, '\n');

    for(int i=0; i<liczba_testow; i++)
    {   
        string wejscie;
        cin>>wejscie;
        cin.ignore(INT_MAX, '\n');

        for(int i=0; i<wejscie.size()/2; i++)
        {
            cout<<wejscie[i];
        }
        cout<<endl;
            
    }

    system("pause");
    return 0;
};