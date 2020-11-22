#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Tablica
{
    public:
    vector <unsigned short> dlug_wew;
    vector <unsigned short> dlug_zew;
    vector <unsigned short> suma;

    void set_lenght(unsigned int nowy_rozmiar)
    {
        dlug_wew.reserve(nowy_rozmiar-1);
        dlug_wew.resize(nowy_rozmiar-1, 0);
        dlug_zew.reserve(nowy_rozmiar-1);
        dlug_zew.resize(nowy_rozmiar-1, 0);
        suma.reserve(nowy_rozmiar);
        suma.resize(nowy_rozmiar, 0);
    }

    void przelicz_sume()
    {
        suma[0] = 0;

        for(int i=1; i<=dlug_wew.size(); i++)
            suma[suma.size() - i] = dlug_wew[dlug_wew.size()-i] + dlug_zew[dlug_zew.size()-i];

        for(int i=1; i<suma.size(); i++)
        {
            if(suma[suma.size() - i] >= 10)
            {
                suma[suma.size() - i] = suma[suma.size() - i]%10;
                suma[suma.size() - i - 1]++;
            }
        }
    }

    void wypisz()
    {
        for(int i=0; i<dlug_wew.size(); i++)
            cout << dlug_wew[i];
        cout << endl;

        for(int i=0; i<dlug_zew.size(); i++)
            cout << dlug_zew[i];
        cout << endl;

        for(int i=0; i<suma.size(); i++)
            cout << suma[i];
        cout << endl;
    }
};

int main()
{
    // n - dlugosc wyswietlacza
    // z - liczba opracji do wykonania
    int n, z;
    string s_d_wewnetrzny, s_d_zewnetrzny;

    Tablica moja_tablica;

    cin >> n >> z;
    cin >> s_d_wewnetrzny >> s_d_zewnetrzny;

    moja_tablica.set_lenght(n);

    for(int i=0; i<n-1; i++){
        moja_tablica.dlug_wew[i] = s_d_wewnetrzny[i] - '0';
        moja_tablica.dlug_zew[i] = s_d_zewnetrzny[i] - '0';
    }

    for(int i=0; i<z; i++)
    {
        char polecenie;
        cin >> polecenie;
        
        switch (polecenie)
        {
        case 'W':
            {
            unsigned int pozycja, cyfra;
            cin >> pozycja >> cyfra;

            moja_tablica.dlug_wew[n-pozycja-1] = cyfra;
            break;
            }

        case 'Z':
            {
            unsigned int pozycja, cyfra;
            cin >> pozycja >> cyfra;

            moja_tablica.dlug_zew[n-pozycja-1] = cyfra;
            break;
            }

        case 'S':
            {
            moja_tablica.przelicz_sume();
            unsigned int pozycja;
            cin >> pozycja;

            cout << moja_tablica.suma[n-pozycja] << endl;
            break;
            }
        
        default:
            cout << "\tZle polecenie! : " << polecenie << endl;
            break;
        }
    }

    return 0;
}