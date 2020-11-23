/*https://p...content-available-to-author-only...j.com/problems/TFIBRE/
Hashmap -> kluczem jest adres w formacie uint, wartosc to vector/lista do jakich adresow (przed hashem) jest polaczony ten wierzcholek grafu.
*/
#include <iostream>     //std::cin & std::cout
#include <vector>
#include <queue>
#include <unordered_map>

using HashMap = std::unordered_map<uint_fast32_t, std::vector<uint_fast32_t> >;
bool test{0};

void Add(HashMap& Connections, uint_fast32_t add1, uint_fast32_t add2)
{
    if (add1==add2)
    {
        Connections[add1];
    }
    else
    {
        Connections[add1].push_back(add2);
        Connections[add2].push_back(add1);
    }
}
bool Check(HashMap& Connections, uint_fast32_t add1, uint_fast32_t add2)
{
    // Ten sam komputer ma polaczenie sam ze soba
    if (add1==add2)
        return 1;

    // Jesli nie znamy adresu to nie mozemy miec do niego polaczenia
    if ((Connections.find(add1)==Connections.end()) || (Connections.find(add2)==Connections.end()))
        return 0;

    std::queue<unsigned int> NodesQueue;
    std::unordered_map<uint_fast32_t, bool> NodesVisited;
    NodesQueue.push(add1);
    NodesVisited[add1] = 1;

    while (!NodesQueue.empty())
    {
        add1=NodesQueue.front();
        NodesQueue.pop();

        for (uint_fast32_t i{0}; i<Connections[add1].size(); ++i)
        {
            if (test) std::cout << "Connections[add1][i]==" << Connections[add1][i] << '\n';
            if (Connections[add1][i]==add2)
                return 1;
            if (!NodesVisited[Connections[add1][i]])
            {
                NodesVisited[Connections[add1][i]]=1;
                NodesQueue.push(Connections[add1][i]);
            }
        }
    } //while
    return 0;
}

uint_fast32_t GetIPAddress()
{
    uint_fast32_t a{0}, b{0}, c{0}, d{0};
    char garbage{0};
    std::cin >> a >> garbage >> b >> garbage >> c >> garbage >> d;
    return ((a<<24)+(b<<16)+(c<<8)+d);
}

void Print (HashMap& Connections)
{
    for (auto& element : Connections)
    {
        std::cout << element.first << '\t';
        for (auto& element2 : element.second)
            std::cout << element2 << ' ';
        std::cout << '\n';
    }
}

int main()
{
    char request{0};
    uint_fast32_t address1{0}, address2{0};
    HashMap Connections;

    while (std::cin >> request)
    {
        address1=GetIPAddress();
        address2=GetIPAddress();
        if (request=='B')
        {
            Add(Connections,address1,address2);
        }
        if (request=='T')
        {
            if(Check(Connections,address1,address2))
                std::cout << "T\n";
            else
                std::cout << "N\n";
        }
    }//while
    if (test) Print(Connections);
    return 0;
}//main
