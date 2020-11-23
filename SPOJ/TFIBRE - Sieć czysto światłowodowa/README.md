|                                        |
|----------------------------------------|
| **TFIBRE - Sieć czysto światłowodowa** |

Przypuśćmy, że budujemy nowoczesną światłowodową sieć szkieletową. Jeśli
przesył odbywa się tylko poprzez tą sieć, to opóźnienia komunikacyjne są
pomijalne. Te zalety powodują, że sieć rozwija się bardzo dynamicznie.
Twoje zadanie polega na napisaniu oprogramowania, które odpowie czy dane
dwa adresy IP łączy sieć czysto światłowodowa.

**Wejście**

Wejście składa się z wierszy, z których każdy zawiera informację o
budowie nowego połączenia lub zapytanie o istnienie połączenia.

Informacja o budowie nowego łącza ma postać

 

B IP1 IP2,

gdzie IP1 i IP2 to adresy IP (w formacie czterech liczb z zakresu 1..255
oddzielonych kropkami), pomiędzy którymi powstaje łącze. Na początku
działania programu sieć nie zawiera żadnych łączy.

Zapytanie o istnienie połączenia światłowodowego ma natomiast postać

 

T IP1 IP2.

Wejście kończy się wraz z końcem pliku.

**Wyjście**

Na każde zapytanie należy wypisać w osobnym wierszu T lub N w
zależności, czy dane dwa adresy IP łączy sieć światłowodowa, czy też
nie.

**Przykład**

**Wejście:**

B 100.100.100.1 100.100.100.2

B 100.100.100.1 100.100.100.3

B 100.100.100.10 100.100.100.11

T 100.100.100.1 100.100.100.3

T 100.100.100.10 100.100.100.2

T 100.100.100.10 100.100.100.11

B 100.100.100.11 100.100.100.2

T 100.100.100.10 100.100.100.3

T 100.100.100.100 100.100.100.103

**Wyjście:**

T

N

T

T

N
