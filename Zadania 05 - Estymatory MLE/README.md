# Zadania 5 (estymator największej wiarygodności (maximum likelihood estimation – MLE))

## Praca z danymi wygenerowanymi z rozkładów

1. Zapoznaj się z opisem funkcji `fitdist` z biblioteki `fitdistrplus`. Zwróć uwagę na metody estymacji.

2. Wygeneruj próbę liczności $n = 100$ z rozkładu normalnego standardowego $F \sim N(0,1)$, a następnie wykonaj poniższe analizy.

   a) Korzystając z estymatora największej wiarygodności (MLE), wyestymuj parametry rozkładu normalnego oraz rozkładu t-Studenta.

   b) Oceń dobroć dopasowania obu rozkładów, wykorzystując cztery klasyczne wykresy diagnostyczne:
      * histogram z nałożoną wyestymowaną gęstością,
      * wykres kwantyl-kwantyl (Q-Q plot),
      * wykres dystrybuanty empirycznej i teoretycznej,
      * wykres prawdopodobieństwo-prawdopodobieństwo (P-P plot).

      Na podstawie wykresów zdecyduj wstępnie, który z rozkładów lepiej dopasowuje się do danych.

      > **Uwaga.** Funkcje `qqcomp` i `ppcomp` w bibliotece `fitdistrplus` do kwantyli empirycznych dodają szum. Czasem jest on zbyt duży, użyj wtedy funkcji z poniższym ustawieniem:
>
      > ```r
      > qqcomp(..., ynoise = FALSE); ppcomp(..., ynoise = FALSE)
      > ```
>
   c) Zweryfikuj swój wybór, porównując wartości statystyk KS, CM i AD oraz kryteriów informacyjnych AIC i BIC.

1. Porównaj wybór na innych próbach. Która ze statystyk lub które z kryteriów częściej dokonuje poprawnego wyboru?

2. Wykonaj eksperyment odwrotny. Wygeneruj próbę liczności $n = 100$ z rozkładu t-Studenta o $\nu = 4$ stopniach swobody i powtórz analizy z Punktu 2 (a)–(c). Następnie porównaj wybory statystyk i kryteriów na innych próbach wygenerowanych z tego rozkładu.

---

## Praca z danymi rzeczywistymi z pakietów R

1. **(Analiza drogi hamowania samochodu)** Załaduj zbiór danych `cars` zawierający drogę hamowania samochodu `dist` w zależności od prędkości. Zbiór ten jest częścią pakietu `datasets`, który jest automatycznie ładowany przy starcie R. Zbadaj rozkład zmiennej `dist` z danych `cars`. Wykonaj poniższe analizy.

   a) Oszacuj parametry rozkładu normalnego, wykładniczego i log-normalnego metodą największej wiarygodności.

   b) Oceń dobroć dopasowania, wykorzystując wykresy diagnostyczne. Na podstawie wykresów zdecyduj wstępnie, który z rozkładów lepiej dopasowuje się do danych.

   c) Zweryfikuj swój wybór, porównując wartości statystyk KS, CM i AD oraz kryteriów informacyjnych AIC i BIC.

2. **(Analiza poziomu bilirubiny)** Wczytaj dane `pbc` z biblioteki `survival` i rozważ zmienną `bili`. Wykonaj poniższe analizy.

   a) Oszacuj parametry rozkładów normalnego, gamma i log-normalnego metodą MLE.

   b) Oceń dobroć dopasowania, wykorzystując wykresy diagnostyczne. Na podstawie wykresów zdecyduj wstępnie, który z rozkładów lepiej dopasowuje się do danych.

   c) Zweryfikuj swój wybór, porównując wartości statystyk KS, CM i AD oraz kryteriów informacyjnych AIC i BIC.

3. **(Analiza wynagrodzeń)** Wczytaj dane `Wage` z biblioteki `ISLR` i zbadaj rozkład zmiennej `wage`.

   a) Oszacuj parametry rozkładu normalnego, gamma i Weibulla metodą największej wiarygodności.

   b) Oceń dobroć dopasowania, wykorzystując wykresy diagnostyczne. Na podstawie wykresów zdecyduj wstępnie, który z rozkładów lepiej dopasowuje się do danych.

   c) Zweryfikuj swój wybór, porównując wartości statystyk KS, CM i AD oraz kryteriów informacyjnych AIC i BIC.

4. Wczytaj dane `EuStockMarkets` zawierający dzienne kursy zamknięcia czterech głównych europejskich indeksów giełdowych z lat 1991–1998. Zbiór ten jest częścią pakietu `datasets`, który jest automatycznie ładowany przy starcie R.

   Jeśli $s_0, s_1, \dots, s_n$ są kursami zamknięcia z kolejnych dni, to dzienne log-zwroty definiujemy jako:
   $$r_1 = \ln \frac{s_1}{s_0}, \quad r_2 = \ln \frac{s_2}{s_1}, \quad \dots, \quad r_n = \ln \frac{s_n}{s_{n-1}}.$$

   Dla indeksu `DAX` wyznacz dzienne log-zwroty. W R można to zrobić w prosty sposób:

   ```r
   close.prices <- as.numeric(EuStockMarkets[, 'DAX'])
   log.returns <- diff(log(close.prices)) # sprawdź co robi funkcja diff
