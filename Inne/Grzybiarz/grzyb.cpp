#include <iostream>
#include <vector>

// dla danego przedziału [a...b]  suma liczb w tym przedziale jest równa  sum_pref[b+1] - sum_pref[a]

// cmd /c "grzyb.exe < grzyb0.in"

using namespace std;

int main()
{
    int n_mushrooms, start_position, moves, max_left, max_right, maximal_sum;
    vector <int> mushrooms;
    vector <int> prefix_sum = {0};

    //cout << "Podaj liczbe grzybow: ";
    cin >> n_mushrooms;
    //cout << "Podaj pozycje grzybiarza: ";
    cin >> start_position;
    //cout << "Podaj ilosc ruchow grzybiarza: ";
    cin >> moves;

    // Wyznaczenie granic
    if( start_position - moves >= 0 )
        max_left = start_position - moves;
    else
        max_left = 0;

    if( start_position + moves < n_mushrooms )
        max_right = start_position + moves;
    else
        max_right = n_mushrooms - 1;


    for(int i=0; i<n_mushrooms; i++)
    {
        int amount;
        //cout << "Podaj ilosc grzybow na polu " << i << " :\t";
        cin >> amount;
        mushrooms.push_back(amount);
        prefix_sum.push_back( prefix_sum[i] + mushrooms[i] );
    }

    maximal_sum = mushrooms[start_position];

    for(int i=0; i<=n_mushrooms; i++) cout << i << '\t';
    cout << endl;
    for(int i=0; i<n_mushrooms; i++) cout << mushrooms[i] << '\t';
    cout << endl;
    for(int i=0; i<=n_mushrooms; i++) cout << prefix_sum[i] << '\t';
    cout << endl << endl;

    cout << "\tMax left: " << max_left << endl;
    cout << "\tMax right: " << max_right << endl;

    for(int i=max_left; i < start_position; i++)
    {
        int current_end = max( start_position, start_position + moves - (start_position-i)*2 );
        current_end = min( current_end, n_mushrooms-1);
        int new_sum = prefix_sum[current_end + 1] - prefix_sum[i];
        if(new_sum > maximal_sum) maximal_sum = new_sum;

        cout << "\tSumowanie od pozycji " << i << " do " << current_end << endl;
        cout << "\t\tSuma: " << new_sum << endl;
    }

    for(int i=max_right; i > start_position; i--)
    {
        int current_start = min( start_position, start_position - (moves - (i-start_position)*2) );
        current_start = max( current_start, 0);
        int new_sum = prefix_sum[i + 1] - prefix_sum[current_start];
        if(new_sum > maximal_sum) maximal_sum = new_sum;

        cout << "\tSumowanie od pozycji " << current_start << " do " << i << endl;
        cout << "\t\tSuma: " << new_sum << endl;
    }
    
    cout << maximal_sum << endl;

    return 0;

    // A MNIE KURWA BOLI NIE
    // I OLKA TEŻ KURWA BOLI
}