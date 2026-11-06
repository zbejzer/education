# Zadania 4 (estymatory: wartości oczekiwanej, wariancji, dystrybuanty, kwantyli, rozkład estymatora metodą Monte-Carlo)

1. Wygeneruj próbę liczności $n=10$ z rozkładu normalnego standardowego $F \sim N(0, 1)$.

    a) Oblicz $\overline{X}_n$, $S_n^2$, $\tilde{S}_n^2$ oraz $\hat{F}_n(0)$. Porównaj wyniki z wartościami rzeczywistymi (do ich obliczenia użyj odpowiednich funkcji w R).

    b) Powtórz obliczenia dla próby liczności $n = 100$. Jakie zauważasz różnice?

    c) Zaplanuj i wykonaj eksperymenty z próbkami, z innych rozkładów.

2. Wygeneruj próbę liczności $n=10$ z rozkładu normalnego standardowego $F \sim N(0, 1)$.

    a) Korzystając z klasycznego estymatora kwantyli (funkcja `quantile` w R, z domyślnym ustawieniem), wyestymuj kwantyle rzędu $\alpha = 5\%, 50\%$ i $95\%$. Oblicz rzeczywiste wartości kwantyli (funkcja `qnorm`) i porównaj wyniki.

    b) Powtórz obliczenia dla próby liczności $n = 100$. Jakie zauważasz różnice?

    c) Zaplanuj i wykonaj eksperyment z próbkami, z innych rozkładów.

3. Wygeneruj próbę liczności $n=10$ z rozkładu normalnego standardowego $F \sim N(0, 1)$.

    a) Narysuj na jednym wykresie dystrybuantę teoretyczną i empiryczną.

    b) Powtórz eksperyment dla próby liczności $n = 100$. Jakie zauważasz różnice?

    c) Zaplanuj i wykonaj eksperyment z próbkami, z innych rozkładów.

4. Zbadaj empiryczny rozkład średniej empirycznej $\overline{X}_n$ w eksperymentcie Monte Carlo.

    a) Wygeneruj $N = 1000$ prób o liczności $n = 10$ z rozkładu $N(0, 1)$. Dla każdej z prób oblicz średnią empiryczną.

    b) Narysuj histogram średnich i porównaj go z gęstością teoretyczną rozkładu średniej empirycznej: $N(0, \frac{1}{n})$.

    c) Powtórz dla próby o liczności $n = 50$ i porównaj histogramy. Oblicz wariancję empiryczną dla uzyskanych wyników. Porównaj z wariancją dla wyników z punktu a).

    d) Powtórz kroki a) i c) z próbkami z innych rozkładów.
