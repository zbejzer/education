#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <math.h>
#include <utility>
#include <algorithm>
#include <iterator>
#include <iomanip> 
#include <utility>
using namespace std;

int main() {
    int x1, y1, x2, y2, x3, y3, x, y;
    cin>>x1>>y1>>x2>>y2>>x3>>y3>>x>>y;

    while ( !( (x1==0) && (y1==0) && (x2==0) && (y2==0) && (x3==0) && (y3==0) && (x==0) && (y==0) ) ) {
        unsigned int p = 0.5*abs( (x2-x1)*(y3-y1) - (y2-y1)*(x3-x1) );
        unsigned int p1 = 0.5*abs( (x1-x)*(y3-y) - (y1-y)*(x3-x) );
        unsigned int p2 = 0.5*abs( (x2-x)*(y3-y) - (y2-y)*(x3-x) );
        unsigned int p3 = 0.5*abs( (x1-x)*(y2-y) - (y1-y)*(x2-x) );

        if ( (p1+p2+p3)>p ) {
            cout<<"O"<<endl;
        } else if (p1==0 || p2==0 || p3==0) {
            cout<<"E"<<endl;
        } else {
            cout<<"I"<<endl;
        }

        cin>>x1>>y1>>x2>>y2>>x3>>y3>>x>>y;
    }

    cin.ignore(INT_MAX, '\n');
    getchar();
    return 0;
};