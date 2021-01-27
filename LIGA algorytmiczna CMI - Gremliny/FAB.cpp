#include <iostream>

using namespace std;

bool isTriangle(int a, int b, int c)
{
    if(a+b>c && a+c>b && b+c>a)
        return true;
    else
        return false;
}

int main()
{
    unsigned long long int counter = 0;
    unsigned int begin, end;

    cin >> begin >> end;

    for(int a=begin; a<=end; a++)
        for(int b=a+1; b<=end; b++)
            for(int c=b+1; c<=end; c++)
                if(isTriangle(a, b, c))
                    counter++;

    cout << counter;

    return 0;
}
