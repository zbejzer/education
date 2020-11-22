#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    // n - dlugosc wyswietlacza
    // z - liczba opracji do wykonania
    int n, z, int_d_wewnetrzny, int_d_zewnetrzny, int_d_calkowity;

    cin >> n >> z;
    cin >> int_d_wewnetrzny >> int_d_zewnetrzny;

    for(int i=0; i<z; i++)
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
    }

    return 0;
}