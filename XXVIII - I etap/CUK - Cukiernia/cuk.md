

Zadanie: CUK

Cukiernia

XXVIII OI, etap I. Plik źródłowy cuk.\* Dostępna pamięć: 128 MB.

19.10 – 23.11.2020

Cukiernia „Bajtuś” specjalizuje się w wypieku drożdżówek, pączków i rogalików. W cukierni jest n gablot

z wypiekami. Na każdej z nich powinien się znajdować tylko jeden rodzaj wypieków. Powinien. . . jednak pew-

nego poranka do cukierni zakradł się Bajtuś – syn Bajtazara, właściciela cukierni – i pod nieobecność taty

poprzestawiał wypieki między gablotami.

Za moment cukiernia powinna się otworzyć! Bajtazar chce poprzestawiać wypieki tak, aby znów w każ-

dej gablocie był tylko jeden rodzaj wypieków. Pomóż mu i napisz program, który obliczy minimalną liczbę

przestawień wypieków, która do tego doprowadzi.

Wejście

W pierwszym wierszu wejścia znajduje się jedna liczba całkowita n, oznaczająca liczbę gablot.

Kolejne n wierszy opisuje gabloty: i-ty z nich, dla i = 1, . . . , n, zawiera trzy liczby całkowite d , p i r

i

i

i

(0 ≤ d , p , r ≤ 109) oznaczające odpowiednio liczbę drożdżówek, pączków i rogalików, które znajdują się

i

i

i

obecnie w i-tej gablocie. Możesz założyć, że w cukierni znajduje się co najmniej jeden wypiek.

Wyjście

W pierwszym i jedynym wierszu wyjścia powinna się znaleźć jedna liczba całkowita, oznaczająca minimalną

liczbę przestawień wypieków między gablotami, niezbędnych do tego, aby w każdej gablocie znalazł się dokład-

nie jeden rodzaj wypieków. Jeśli w jakiejś gablocie ostatecznie nie będzie żadnych wypieków, to ten warunek

również będzie spełniony.

Przykład

Dla danych wejściowych:

poprawnym wynikiem jest:

5

9

5 1 1

0 3 4

1 4 3

4 0 0

0 0 0

Wyjaśnienie przykładu: Optymalny sposób przestawiania wypieków może wyglądać następująco:

\1. Przestaw pączka z gabloty 1 do gabloty 3 i rogalika z gabloty 1 do gabloty 2.

\2. Przestaw trzy pączki z gabloty 2 do gabloty 3.

\3. Przestaw drożdżówkę z gabloty 3 do gabloty 1 i trzy rogaliki z gabloty 3 do gabloty 2.

W ten sposób wykonanych zostanie 9 przestawień, po których zawartość gablot będzie następująca: gablota 1:

drożdżówki, gablota 2: rogaliki, gablota 3: pączki, gablota 4: drożdżówki, a gablota 5 będzie pusta.

Testy „ocen”:

1ocen: trzy gabloty – pierwsza: 1, 1, 2, druga: 2, 1, 1 oraz trzecia: 1, 1, 2;

2ocen: pięć gablot, 5 sztuk każdego wypieku w każdej gablocie;

3ocen: 1000 gablot, w każdej albo 10 drożdżówek, albo 10 pączków; wynikiem jest 0;

4ocen: 300 000 gablot, w każdej 3 drożdżówki, 2 pączki oraz 1 rogalik.

Olimpiada Informatyczna (oi.edu.pl)

1/2

Cukiernia (v. 1.2)

Olimpiada Informatyczna ﬁnansowana jest ze środków Ministerstwa Edukacji Narodowej w ramach zadania publicznego

„Organizacja i przeprowadzenie olimpiad i turniejów w latach szkolnych 2019/2020, 2020/2021, 2021/2022”.





Ocenianie

Zestaw testów dzieli się na następujące podzadania. Testy do każdego podzadania składają się z jednej lub więk-

szej liczby osobnych grup testów.

Podzadanie Warunki

Liczba punktów

1

2

3

3 ≤ n ≤ 10

3 ≤ n ≤ 5000

3 ≤ n ≤ 300 000

15

35

50

Olimpiada Informatyczna (oi.edu.pl)

2/2

Cukiernia (v. 1.2)

Olimpiada Informatyczna ﬁnansowana jest ze środków Ministerstwa Edukacji Narodowej w ramach zadania publicznego

„Organizacja i przeprowadzenie olimpiad i turniejów w latach szkolnych 2019/2020, 2020/2021, 2021/2022”.

