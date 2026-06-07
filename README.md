# Projekt bazy danych dla farmy drukarek 3D

Baza danych umożliwia śledzenie aktualnych zleceń i użycia drukarek 3D. Przeznaczona jest dla małych i średnich farm drukarek 3D.

## Założenia

- Zlecenie ma określony wymagany rozmiar pola roboczego drukarki oraz materiał z którego detal ma zostać wydrukowany.
- Pojedyncze zlecenie obejmuje tylko jeden wydruk. Kazdy wydruk tego samego modelu to osobne zlecenie.
- Model drukarki posiada ograniczenia w typie filamentu którym jest w stanie drukować oraz wymiarach pola roboczego,.
- Masa szpuli filamentu jest określana przy wprowadzaniu do systemu a następnie modyfikowana wraz ze zrealizowanymi nią wydrukami przez odrębne zapytania.
- Dany kolor filamentu może występować w wielu materiałach
- Kolory o takiej samej nazwie od różnych producentów nie muszą być identyczne
- Ustawienia są przeznaczone dla połączenia modelu drukarki i filamentu.

## Przykładowe użycie

- Wypisanie listy wszystkich posiadanych kolorów filamentów
- Wypisanie listy szpul filamentu, których pozostała masa jest poniżej określonego progu
- Wypisanie najczęściej używanego koloru i materiału filamentu
- Kiedy drukarka spełniające określone wymagania będzie najwcześniej dostępna
- Jak długo drukarka pracowała w danym okresie
