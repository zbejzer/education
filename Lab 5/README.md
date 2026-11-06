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

5. Zbadaj empiryczny rozkład wariancji empirycznej $S_n^2$ w eksperymencie Monte Carlo.

    a) Wygeneruj $N = 1000$ prób o liczności $n = 10$ z rozkładu $N(0, 1)$. Dla każdej z prób oblicz wariancję empiryczną.

    b) Narysuj histogram średnich i porównaj go z gęstością teoretyczną rozkładu wariancji empirycznej: $\Gamma \left(\frac{n-1}{2}, \frac{2}{n-1}\right)$.

    c) Powtórz dla próby o liczności $n = 50$ i porównaj histogramy.

    d) Powtórz kroki a) i c) dla estymatora wybranego kwantyla i wartości dystrybuanty w punkcie zero $F(0)$.

6. Wygeneruj próbę o liczności $n = 10$ z rozkładu wykładniczego z parametrem $\lambda = 1$.

    a) Zapisz teoretyczne wzory wartości oczekiwanej i mediany, dla zmiennej $X \sim \text{Exp}(\lambda)$. Oblicz wartość oczekiwaną i medianę dla $\lambda = 1$.

    b) Oblicz średnią empiryczną i medianę empiryczną (funkcja `quantile` z domyślnym ustawieniem) z wygenerowanej próby. Porównaj je z wartościami rzeczywistymi.

    c) Powtórz eksperyment $N = 1000$ razy i narysuj histogramy estymatorów. Który z estymatorów ma mniejsze obciążenie (tutaj, różnicę między średnią z wyestymowanych wartości, a średnią rzeczywistą)? Który z nich jest bardziej odporny na zmienność (ma mniejsze odchylenia wokół średniego wyniku, oblicz wariancje z wyników)?

    d) Zrób podobną analizę dla zmiennej o rozkładzie log-normalnym $X \sim \text{LN}(0, 1)$.
