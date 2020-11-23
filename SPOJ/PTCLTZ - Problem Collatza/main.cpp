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

int collatz(int s)
{
    int n=0, x=s;

    while(x!=1)
    {   
        n++;
        if(x%2==0) //jest parzyste
        {
            x=x/2;
        }else{  //nie jest parzyste
            x=3*x+1;
        }
    }
    
    return n;
}

int main()
{
    int zestawyDanych;
    cin>>zestawyDanych;
    cin.ignore(INT_MAX, '\n');

    for(int i=0; i<zestawyDanych; i++)
    {
        int s;
        cin>>s;
        cin.ignore(INT_MAX, '\n');
        cout<<collatz(s)<<endl;
    }

    getchar();
    return 0;
}