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

void piramidka(string wejscie, int lenght)
{
    int a,b;
    a=b=lenght/2;
    while(a>=0)
    {
        for(int j=0; j<lenght; j++)
        {
            if(j>=a&&j<=b)
            {
                cout<<wejscie[j];
            }else{
                cout<<".";
            }
        }
        cout<<endl;
        a--;
        b++;
    }
}

int main()
{
    int lenght;
    string wejscie;
    cin>>lenght;
    cin>>wejscie;
    cin.ignore(INT_MAX, '\n');
    piramidka(wejscie, lenght);

    getchar();
    return 0;
}