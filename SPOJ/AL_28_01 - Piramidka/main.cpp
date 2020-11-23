#include <iostream>
#include <string>
using namespace std;

int main()
{
    int lenght, a, b;
    string wejscie;
    cin.sync();
    cin>>lenght;
    cin.sync();
    cin>>wejscie;

    a=b=lenght/2;

    while(a>=0) {
        for(int j=0; j<lenght; j++) {
            if( j>=a && j<=b ) {
                cout<<wejscie[j];
            } else {
                cout<<".";
            }
        }
        cout<<endl;
        a--;
        b++;
    }

    cin.sync();
    getchar();
    return 0;
}