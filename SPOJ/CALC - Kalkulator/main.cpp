#include <iostream>
#include <string>
#include <climits>
using namespace std;

int main() {
    string in="null";
    getline(cin, in);
    
    while( in[0]!=0 ) {
        int liczba[2], pos1, pos2;

        pos1 = in.find(" ");
        pos2 = in.find(" ", pos1+1);
        liczba[0] = stoi(in.substr(pos1+1, pos2-pos1-1));
        liczba[1] = stoi(in.substr(pos2+1));

        switch(in[0]) {
        case '+':
            cout<<liczba[0]+liczba[1]<<endl;
            break;
        case '-':
            cout<<liczba[0]-liczba[1]<<endl;
            break;
        case '*':
            cout<<liczba[0]*liczba[1]<<endl;
            break;
        case '/':
            cout<<liczba[0]/liczba[1]<<endl;
            break;
        case '%':
            cout<<liczba[0]%liczba[1]<<endl;
            break;
        }

        in="";
        getline(cin, in);
    }
    return 0;
}