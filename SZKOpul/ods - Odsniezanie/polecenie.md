**Odśnieżanie**

**Limit pamięci: 64 MB**

Biednemu zawsze wiatr w oczy. Niedźwiedź (główny bohater zadania
*Niedźwiedź*) bardzo ucieszył się, że nadeszła wczesna zima i już nie
będzie musiał przemykać po lesie, cały czas brodząc po kolana w błocie i
bacząc na czyhające na niego owady. Niestety, zima postanowiła
uprzykrzyć życie Niedźwiedzia i śniegu nasypało tyle, że nasz bohater
ledwo może się przemieszczać po lesie.

Niedźwiedź postanowił nie poddawać się i odśnieżyć las, a przynajmniej
ścieżki prowadzące do trzech polan, koło których zazwyczaj łapie on ryby
na kolację. Las składa się z <img src="media\image1.png" />polan
połączonych
<img src="media\image2.png" style="width:0.14583in" />(dwukierunkowymi)
ścieżkami. Polany są ponumerowane liczbami od
<img src="media\image3.png" style="height:0.11458in" />do
<img src="media\image1.png" />. Wygląda na to, że niektóre ścieżki mogą
biec tunelami lub estakadami, co nieco zdziwiło Niedźwiedzia, ale ma on
teraz poważniejsze problemy na głowie. Dla każdej ścieżki Niedźwiedź
wie, ile czasu będzie potrzebować na jej odśnieżenie.

Ile czasu będzie on musiał spędzić na odśnieżenie tylu ścieżek, by mógł
poruszać się między swoją norą (położoną obok polany numer
<img src="media\image3.png" style="height:0.11458in" />), a polanami,
koło których łapie ryby, chodząc jedynie po odśnieżonych ścieżkach?

**Wejście**

W pierwszym wierszu wejścia znajdują się dwie liczby całkowite
<img src="media\image1.png" />i
<img src="media\image2.png" style="width:0.14583in" />(<img src="media\image4.png" style="width:1.09375in;height:0.13542in" />,
<img src="media\image5.png" style="width:1.23958in;height:0.13542in" />).
Oznaczają one kolejno liczbę polan w lesie oraz liczbę łączących je
ścieżek. Drugi wiersz zawiera trzy różne od siebie liczby całkowite
<img src="media\image6.png" style="width:0.61458in;height:0.10417in" />(<img src="media\image7.png" style="width:0.77083in;height:0.14583in" />)
– są to numery polan, przy których Niedźwiedź łapie ryby. Każdy z
kolejnych <img src="media\image2.png" style="width:0.14583in" />wierszy
opisuje jedną ścieżkę. W
<img src="media\image8.png" style="height:0.11458in" />-tym z tych
wierszy znajdują się trzy liczby całkowite
<img src="media\image9.png" style="width:0.53125in;height:0.14583in" />(<img src="media\image10.png" style="width:0.97917in;height:0.14583in" />,
<img src="media\image11.png" style="width:0.45833in;height:0.15625in" />,
<img src="media\image12.png" style="width:1.34375in;height:0.14583in" />).
Oznaczają one, że polany o numerach
<img src="media\image13.png" style="width:0.11458in;height:0.10417in" />i
<img src="media\image14.png" style="width:0.10417in;height:0.14583in" />są
połączone dwukierunkową ścieżką, której odśnieżenie zajmie
<img src="media\image15.png" style="width:0.11458in;height:0.14583in" />sekund.
Każda para polan może być połączona co najwyżej jedną ścieżką. Pomiędzy
każdą parą polan ze zbioru
<img src="media\image16.png" style="width:0.91667in;height:0.1875in" />można
przejść, idąc po ścieżkach.

**Wyjście**

Na wyjściu należy wypisać minimalną liczbę sekund potrzebną do
odśnieżenia ścieżek, które umożliwią poruszanie się między polanami
numer <img src="media\image3.png" style="height:0.11458in" />,
<img src="media\image17.png" style="width:0.14583in;height:0.10417in" />,
<img src="media\image18.png" style="width:0.15625in;height:0.10417in" />i
<img src="media\image19.png" style="width:0.14583in;height:0.10417in" />.

**Przykład**

Dla danych wejściowych:

7 8

3 6 7

1 2 2

1 4 3

2 3 4

3 5 3

3 7 5

4 5 3

4 6 5

5 7 4

poprawną odpowiedzią jest:

18

**Ograniczenia**

W testach wartych co najmniej
<img src="media\image20.png" style="width:0.29167in;height:0.14583in" />punktów
zachodzi
<img src="media\image21.png" style="width:0.90625in;height:0.13542in" />oraz
<img src="media\image22.png" style="width:1.03125in;height:0.13542in" />.

*Autor zadania: Marcin Mucha.*
