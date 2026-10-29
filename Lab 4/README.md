# Część 2 – zadania eksperymentalne w R

1. Wygeneruj próbę 1000-elementową: $x_1, \dots, x_{1000}$ z rozkładu normalnego $X \sim N(0, 2^2)$. Dla każdej z wygenerowanych wartości oblicz: $y_i = \exp(x_i)$, $i = 1, \dots, 1000$. Narysuj na jednym rysunku histogram danych $y_1, \dots, y_{1000}$ oraz wykres gęstości rozkładu log-normalnego $LN(0, 2^2)$. Poeksperymentuj z innymi parametrami i długościami prób.

2. Wygeneruj 1000 prób 100-elementowych: $x_1, \dots, x_{20}$ z rozkładu $X \sim N(0, 1)$. Oblicz dla każdej z nich sumę kwadratów $y = x_1^2 + \dots + x_{20}^2$. Narysuj na jednym rysunku histogram danych $y_1, \dots, y_{1000}$ oraz wykres gęstości rozkładu chi-kwadrat $\chi^2(20)$. Poeksperymentuj z innymi parametrami i długościami prób. *(Uwaga: w poleceniu tekstowo podano 100-elementowych, natomiast zapis wskazuje na próbki 20-elementowe)*.

3. Na jednym rysunku narysuj wykresy gęstości rozkładów $N(0,1)$ i $t(n)$, dla $n = 5, 10, 15, 20, 30$. Jak zmienia się rozkład $t$-Studenta w stosunku do rozkładu $N(0,1)$ wraz ze wzrostem liczby stopni swobody $n$? Oblicz wariancję dla rozkładu $t$-Studenta i porównaj z wariancją rozkładu $N(0,1)$.

4. Wykorzystaj do modelowania długości życia rozkład wykładniczy. Średnia długość życia na podstawie tablic życia z roku 2018 wynosi dla mężczyzn 73 lata, dla kobiet 81 lat.
a) Narysuj na jednym rysunku gęstości rozkładów wykładniczych $\text{Exp}(\frac{1}{73})$ i $\text{Exp}(\frac{1}{81})$ oraz na drugim funkcje przeżycia tych rozkładów.
b) Oblicz wartości oczekiwane i odchylenia standardowe.
c) Oblicz prawdopodobieństwo, że losowo wybrana osoba z każdej populacji przeżyje 70 lat.
d) Sprawdź w Tablicach Życia na rok 2024 średnią długość zycia kobiet i mężczyzn i zrób podobne analizy.
