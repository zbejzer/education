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

class Polozenie
{
private:
    int x,y;
public:
    void update(int newX, int newY)
    {
        x=newX;
        y=newY;
    }

    void go(int kierunek, int liczba_krokow)
    {
        // 0 - północ
        // 1 - południe
        // 2 - zachód
        // 3 - wschód
        switch(kierunek)
        {
            case 0: y+=liczba_krokow; break;
            case 1: y-=liczba_krokow; break;
            case 2: x-=liczba_krokow; break;
            case 3: x+=liczba_krokow; break;
        }
    }

    void printLocation()
    {
        cout<<"x: "<<x<<endl;
        cout<<"y: "<<y<<endl;
    }

    void printRoute()
    {
        if(x==0 && y==0)    // nie porusza się
        {
            cout<<"studnia"<<endl;
        }
        if(y>0) // północ
        {
            cout<<"0 "<<y<<endl;
        }
        if(y<0) // południe
        {
            cout<<"1 "<<-y<<endl;
        }
        if(x>0) //wschód
        {
            cout<<"3 "<<x<<endl;
        }
        if(x<0) // zachód
        {
            cout<<"2 "<<-x<<endl;
        }
    }
};

int main()
{
    int zestawyDanych;
    cin>>zestawyDanych;
    cin.ignore(INT_MAX, '\n');

    for(int i=0; i<zestawyDanych; i++)
    {
        Polozenie Skarb;
        Skarb.update(0, 0);
        int liczba_wskazowek;
        cin>>liczba_wskazowek;
        cin.ignore(INT_MAX, '\n');

        for(int j=0; j<liczba_wskazowek; j++)
        {
            int kierunek, kroki;
            cin>>kierunek>>kroki;
            cin.ignore(INT_MAX, '\n');
            Skarb.go(kierunek, kroki);
        }
        Skarb.printRoute();        
    }

    getchar();
    return 0;
}