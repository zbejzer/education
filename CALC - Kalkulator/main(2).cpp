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

int main()
{
    char znak, c;
    int liczba1,liczba2,wynik;

    c = std::cin.peek();
    while((int)c!=10&&(int)c!=-1)
    {   
        cin>>znak>>liczba1>>liczba2;
        cin.ignore(INT_MAX, '\n');
        switch(znak){
        case '+':
            cout<<liczba1+liczba2<<endl;
            break;
        case '-':
            cout<<liczba1-liczba2<<endl;
            break;
        case '*':
            cout<<liczba1*liczba2<<endl;
            break;
        case '/':
            cout<<liczba1/liczba2<<endl;
            break;
        
        case '%':
            cout<<liczba1%liczba2<<endl;
            break;
        }
        c = std::cin.peek();
    }
    
    getchar();
    return 0;
}