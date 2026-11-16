# Projekt 3

## Zadanie **AL3.5.** (maks. 5 punktów)

1. Zaimplementuj algorytm sortowania szybkiego omówiony na wykładzie. (3 pkt.)
2. Następnie zmodyfikuj ten algorytm zastępując warunek `p<r` warunkiem `p+c<r`, gdzie `c` to pewna stała większa lub równa `0`. Czyli dla tablic o rozmiarze takim, że `p+c<r` (czyli o rozmiarze większym od `c+1`) będzie normalnie wykonywana procedura Partition i wywołania rekurencyjne, a w przy rozmiarze takim, że `p+c>=r` niech będzie stosowane jakieś proste sortowanie, np. bąbelkowe czy przez wstawianie ale _tylko na podtablicy od `p` do `r`._ Przetestuj czy zmodyfikowany algorytm poprawnie sortuje.(1 pkt.)
3. Porównaj czasy działania algorytmu podstawowego oraz jego modyfikacji dla dwóch rodzajów danych: dane losowe oraz dane skrajnie niekorzystne (ciąg malejący). Podobnie jak w zadaniu AL3.3, dla tego samego rodzaju danych należy zestawić czasy działania dwóch wersji algorytmów. (1 pkt)

## Zadanie **AL3.3.** (maks. 4,5 punktu)

Zaimplementuj i przetestuj (3.5 pkt.) oraz porównaj czasy działania (1 pkt.) podstawowej wersji sortowania szybkiego i jednej ze zmodyfikowanych wersji, gdzie element wyznaczający podział jest:

1. skrajnie prawym elementem `A[r]` (pod)tablicy (wersja podstawowa);
2. wybranym pseudolosowo (RandomizedQuicksort);
3. medianą (czyli elementem środkowym co do wartości) z trzech następujących elementów tablicy: skrajnie lewego (`A[p]`), środkowego (`A[p + (r−p)/2]`), skrajnie prawego (`A[r]`).

Podobnie jak w zadaniu AL3.2, testy powinny być wykonane dla danych losowych i niekorzystnych, dla różnych wielkości tablicy (np. 10000, 50000, 100000 i 150000). Dla tego samego rodzaju danych należy zestawić czasy działania trzech wersji algorytmów. Sugerowany sposób prezentacji wyników testów:

### DANE LOSOWE

| rozmiar tablicy | czas - algorytm 1 | czas - algorytm 2 | czas - algorytm 3 |
|-----------------|-------------------|-------------------|-------------------|
| 10000           |                   |                   |                   |
| 50000           |                   |                   |                   |
| itd.            |                   |                   |                   |

### DANE NIEKORZYSTNE

| rozmiar tablicy | czas - algorytm 1 | czas - algorytm 2 | czas - algorytm 3 |
|-----------------|-------------------|-------------------|-------------------|
| 10000           |                   |                   |                   |
| 50000           |                   |                   |                   |
| itd.            |                   |                   |                   |
