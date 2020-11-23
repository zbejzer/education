#include<iostream>
#include<vector>


// dla danego przedziału [a...b]  suma liczb w tym przedziale jest równa  sum_pref[b+1] - sum_pref[a]


using namespace std;

int main()
{
    vector <int> grzyby {2, 3, 7, 5, 1, 3, 9};
    vector <int> S_pre = {0};
    int m=6, pozycja_g=4, najw_suma=0,suma=0;

    for(int i=0; i<=grzyby.size(); i++) cout << i << '\t';
    cout << endl;

    for(int i=0; i<grzyby.size(); i++) cout << grzyby[i] << '\t';
    cout << endl << "0" << '\t';

    for(int i=1; i<=grzyby.size(); i++)
    {
        S_pre.push_back( S_pre[i-1] + grzyby[i-1] );
        cout<< S_pre[i] << '\t';
    }
    cout << endl;

    suma = abs(S_pre[pozycja_g+1] - S_pre[0]);
    if(suma>najw_suma) najw_suma=suma;

    suma = abs(S_pre[6+1] - S_pre[pozycja_g]);
    if(suma>najw_suma) najw_suma=suma;

    for(int i=pozycja_g - (m/2); (pozycja_g + (m - (pozycja_g-i)*2)) < grzyby.size(); i++)
    {
        suma = S_pre[ pozycja_g + (m - (pozycja_g-i)*2) +1 ] - S_pre[i];
        if(suma>najw_suma) najw_suma=suma;

        cout << "Sumowanie od pozycji " << i << " do " << pozycja_g + (m - (pozycja_g-i)*2) << "\tSuma: " << suma << endl;
    }

    for(int i=6; pozycja_g - (m - (i-pozycja_g)*2) >= 0; i--)
    {
        suma = S_pre[i+1] - S_pre[ pozycja_g - (m - (i-pozycja_g)*2) ];
        if(suma>najw_suma) najw_suma=suma;

        cout << "Sumowanie od pozycji " << i << " do " << pozycja_g - (m - (i-pozycja_g)*2) << "\tSuma: " << suma << endl;
    }
    
    cout<<endl<<najw_suma;

    getchar();
    getchar();
    return 0;

    // A MNIE KURWA BOLI NIE
    // KURWA TAK MOCNO JAPIERDOLE AAAAAAAAAA
}