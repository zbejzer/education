#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Tablica
{
    public:
    vector <unsigned short> dlug_wew;
    vector <unsigned short> dlug_zew;

    void set_lenght(unsigned int nowy_rozmiar)
    {
        dlug_wew.reserve(nowy_rozmiar);
        dlug_wew.resize(nowy_rozmiar, 0);
        dlug_zew.reserve(nowy_rozmiar);
        dlug_zew.resize(nowy_rozmiar, 0);
    }

    void wypisz_pozycje(int n)
    {
        
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
        moja_tablica.dlug_wew[n-i-1] = s_d_wewnetrzny[i] - '0';
        moja_tablica.dlug_zew[n-i-1] = s_d_zewnetrzny[i] - '0';
    }

    for(int i=0; i<moja_tablica.dlug_wew.size(); i++)
        cout << moja_tablica.dlug_wew[i];

    /*for(int i=0; i<z; i++)
    {
        char polecenie;
        int_d_calkowity = int_d_wewnetrzny + int_d_zewnetrzny;
        cin >> polecenie;

        switch (polecenie)
        {
        case 'W':
            {
            int pozycja, cyfra;
            string s_d_wewnetrzny = to_string(int_d_wewnetrzny);
            cin >> pozycja >> cyfra;

            s_d_wewnetrzny[s_d_wewnetrzny.size() - pozycja] = to_string(cyfra)[0];
            int_d_wewnetrzny = stoi(s_d_wewnetrzny);
            break;
            }

        case 'Z':
            {
            int pozycja, cyfra;
            string s_d_zewnetrzny = to_string(int_d_zewnetrzny);
            cin >> pozycja >> cyfra;

            s_d_zewnetrzny[s_d_zewnetrzny.size() - pozycja] = to_string(cyfra)[0];
            int_d_zewnetrzny = stoi(s_d_zewnetrzny);
            break;
            }

        case 'S':
            {
            string s_d_calkowity = to_string(int_d_calkowity);
            int pozycja;
            cin >> pozycja;

            cout << s_d_calkowity[s_d_calkowity.size() - pozycja] << endl;
            break;
            }
        
        default:
            cout << "\tZle polecenie! : " << polecenie << endl;
            break;
        }
    }*/

    return 0;
}