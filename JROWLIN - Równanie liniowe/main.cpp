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

int main() {
    float a, b, c, x;
    cin>>a>>b>>c;
    cin.ignore(INT_MAX, '\n');

    if(a==0) {
        if(b==c) {
            cout<<"NWR";
        } else {
            cout<<"BR";
        }
    } else {
        x=c-b;
        x/=a;
        printf("%.2f", x);  
    }

    getchar();
    return 0;
};