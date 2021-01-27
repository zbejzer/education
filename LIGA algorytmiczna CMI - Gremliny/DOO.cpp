#include <iostream>
#include <vector>

using namespace std;

class Komnata
{
    public:
    int n, liczonyObwod;
    vector <vector<char>> plan;
    vector <vector<bool>> sprawdzone;

    void wczytaj()
    {
        cin >> n;
        
        // Wczytanie planszy i fill wektora
        for(int i=0; i<n; i++)
        {
            // Tymczasowe wektory
            vector <char> tChVector;
            vector <bool> tBVector;
            
            for(int j=0; j<n; j++)
            {
                char tChar;
                cin >> tChar;
                tChVector.push_back(tChar);
                tBVector.push_back(false);
            }

            plan.push_back(tChVector);
            sprawdzone.push_back(tBVector);
        }

        // Wczytywanie punktow do sprawdzania
        for(int i=0; i<n; i++)
        {
            int x, y;
            cin >> x >> y;
            cout << obwod(x-1, y-1) << endl;
        }
    }

    /*void wypisz()
    {
        for(int i=0; i<n+1; i++)
            cout << i;

        cout << endl;    
        for(int i=0; i<n; i++)
        {
            cout << i+1;
            for(int j=0; j<n; j++)
                cout << plan[i][j];
            cout << endl;
        }
        cout << endl;
    }*/

    // sprawdzenie sasiadujacych scian
    int wartoscKropki(int x, int y)
    {
        int obwodKropki;
        if(plan[x][y+1] == '#') obwodKropki++;
        if(plan[x][y-1] == '#') obwodKropki++;
        if(plan[x+1][y] == '#') obwodKropki++;
        if(plan[x-1][y] == '#') obwodKropki++;
        return obwodKropki;
    }

    // Rekurencyjne sprawdzanie per kropka
    void sprawdzaj(int x, int y)
    {
        if(!sprawdzone[x][y])
        {
            sprawdzone[x][y] = true;
            liczonyObwod +=  wartoscKropki(x, y);
            if(plan[x][y+1] == '.') sprawdzaj(x, y+1);
            if(plan[x][y-1] == '.') sprawdzaj(x, y-1);
            if(plan[x+1][y] == '.') sprawdzaj(x+1, y);
            if(plan[x-1][y] == '.') sprawdzaj(x-1, y);
        }
    }

    // Wlasciwe liczenie obwodu
    int obwod(int x, int y)
    {
        liczonyObwod = 0;

        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                sprawdzone[i][j] = false;

        sprawdzaj(x, y);

        return liczonyObwod;
    }
};

int main()
{
    Komnata MojaKomnata;
    MojaKomnata.wczytaj();

    return 0;
}