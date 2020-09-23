#include <iostream>
#include <string>
#include <climits>
#include <stdio.h>
#include <ctype.h>
#include <vector>
#include <math.h>
using namespace std;

int main(){
    int n[2], k[2];
    cin>>n[0]>>k[0]>>n[1]>>k[1];

    cout<<(n[0]*k[0])+(n[1]*k[1])<<endl;

    system("pause");
    return 0;
}