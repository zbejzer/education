#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

string joinCords(int x, int y)
{
    return to_string(x) + " " + to_string(y);
}

class komnata
{
private:
    unordered_map < string, bool > plan;
    unordered_map < string, bool > sprawdzonyPlan;
    int bok, licznikObwodu, n;    

public:
    void wczytajPlan();
    void obwod(int, int);
};

void komnata::wczytajPlan()
{
    cin >> n;

    // wczytywanie planu
    for(int y=1; y<=n; y++)
        for(int x=1; x<=n; x++)
        {
            char tempChar;
            cin >> tempChar;

            if(tempChar == '.')
                plan[ joinCords(x, y) ] = 1;
            else
                plan[ joinCords(x, y) ] = 0;

            sprawdzonyPlan[ joinCords(x, y) ] = 0;
        }

    // wczytanie punktow do sprawdzenia 
    for(int i=0; i<n; i++)
    {
        int x, y;
        licznikObwodu = 0;      // Resetowanie licznika
        for(int i=1; i<=n; i++)     // resetowanie sprawdzonych pol
            for(int j=1; j<=n; j++)
                sprawdzonyPlan[ joinCords(j, i) ] = false;
        
        cin >> y >> x;
        obwod(x, y);
        cout << licznikObwodu << endl;
    }
};

// Liczenie obwodu
void komnata::obwod(int x, int y)
{
    //cout << "[DEBUG] Sprawdzanie pozycji: " << joinCords(x, y) << endl;

    if( !sprawdzonyPlan[ joinCords(x, y) ] )
    {
        //cout << "[DEBUG] Pozycja nie sprawdzana\n" ;
        sprawdzonyPlan[ joinCords(x, y) ] = true;

        if(!plan[ joinCords(x, y+1) ])  licznikObwodu++;    else    obwod(x, y+1);
        if(!plan[ joinCords(x, y-1) ])  licznikObwodu++;    else    obwod(x, y-1);
        if(!plan[ joinCords(x+1, y) ])  licznikObwodu++;    else    obwod(x+1, y);
        if(!plan[ joinCords(x-1, y) ])  licznikObwodu++;    else    obwod(x-1, y);
    }
};

int main()
{
    komnata nowaKomnata;
    nowaKomnata.wczytajPlan();

    return 0;
}