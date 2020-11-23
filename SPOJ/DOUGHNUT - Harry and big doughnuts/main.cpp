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
        int koty, harry, paczek;
        cin>>koty>>harry>>paczek;
        cin.ignore(INT_MAX, '\n');
        if(koty*paczek>harry)
        {
            cout<<"no"<<endl;
        }
        else
        {
            cout<<"yes"<<endl;
        }
            
    }

    system("pause");
    return 0;
};