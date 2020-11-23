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

bool samogloska(char litera)
{
    if(litera == 'a'||litera == 'e'||litera == 'y'||litera == 'o'||litera == 'i'||litera == 'u'||litera =='A'||litera =='E'||litera =='Y'||litera =='O'||litera =='I'||litera =='U')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

string skracanie(string wejscie, int liczbaznakow)
{
    string wyjscie;

    for(int j=wejscie.size()-1;j>=0;j--)
    {
        if(wejscie[j]=='_' && wejscie.size()>liczbaznakow)
        {
            wejscie.erase(j,1);
            j--;
        }
    }
    for(int j=wejscie.size()-1;j>=0;j--)
    {
        if(isdigit(wejscie[j]) && wejscie.size()>liczbaznakow)
        {
            wejscie.erase(j,1);
            j--;
        }
    }
    for(int j=1;j<wejscie.size();j++)
    {
        if(samogloska(wejscie[j])  && wejscie.size()>liczbaznakow )
        {
            wejscie.erase(j,1);
            j--;
        }
    }
    for(int j=wejscie.size()-2;j>=0;j--)
    {
        if(wejscie.size()>liczbaznakow)
        {
            wejscie.erase(j,1);
            j--;
        } 
    }
    return wejscie;
}

int main()
{
    int liczbaZna;
    string wyraz;
    cin>>liczbaZna;
    cin.ignore(INT_MAX, '\n');
    cin>>wyraz;
    cin.ignore(INT_MAX, '\n');
    cout<<skracanie(wyraz, liczbaZna);
    getchar();
    return 0;
}