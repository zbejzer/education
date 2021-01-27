#include <iostream>
#include <vector>

using namespace std;

class komnata
{
    public:
    int n, liczonyObwod;
    vector <vector<char>> plan;
    vector <vector<bool>> sprawdzone;

    void wczytaj()
    {
        cin >> n;
        
        for(int i=0; i<n; i++)
        {
            vector <char> tvector;
            vector <bool> tvbool;

            for(int j=0; j<n; j++)
            {
                char tchar;
                cin >> tchar;
                tvector.push_back(tchar);
                tvbool.push_back(false);
            }

            plan.push_back(tvector);
            sprawdzone.push_back(tvbool);
        }

        for(int i=0; i<n; i++)
        {
            int x, y;
            cin >> x >> y;
            cout << obwod(x-1, y-1) << endl;
        }
    }

    void wypisz()
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
    }

    int wartoscKropki(int x, int y)
    {
        int obwodKropki;
        if(plan[x][y+1] == '#') obwodKropki++;
        if(plan[x][y-1] == '#') obwodKropki++;
        if(plan[x+1][y] == '#') obwodKropki++;
        if(plan[x-1][y] == '#') obwodKropki++;
        return obwodKropki;
    }

    void sprawdzaj(int x, int y)
    {
        cout << "   SPRAWDZANIE NA POZYCJI " << x+1 << " " << y+1 << endl;
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

    int obwod(int x, int y)
    {
        cout << "   NOWY TEST" << endl;
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
    komnata MojaKomnata;

    MojaKomnata.wczytaj();

    MojaKomnata.wypisz();

    return 0;
}