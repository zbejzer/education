#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include<algorithm>

using namespace std;

int roznica(string haslo1, string haslo2)
{
    int wynik;

    if(haslo1.size() > haslo2.size())
        swap(haslo1, haslo2);

    for(int i=0; i<haslo1.size(); i++)
    {
        if( haslo1[i] == haslo2[i] )
        {
            haslo1.erase(haslo1.begin() + i);
            haslo2.erase(haslo2.begin() + i);
            i--;
        }
    }
    
    cout << haslo1 << " " << haslo2 << " ";

    wynik = max(haslo1.size(), haslo2.size());
    return wynik;
}


int main()
{
    // basic roznica function driver
    string wyraz1, wyraz2;
    int n;

    cin >> n;

    for(int i=0; i<n; i++)
    {
        cin >> wyraz1 >> wyraz2;
        cout << roznica(wyraz1, wyraz2) << endl;
    }
    
    return 0;
}