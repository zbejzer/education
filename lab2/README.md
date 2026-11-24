# Lab 2

## Zad 4

```
cat | sort | tee >(head -n 5) >(tail -n 3)
```

## Zad 5

```
cat | tee zad5.1.out >zad5.2.out
```

## Zad 6

```
gcc zad6.c 2> zad6.err.out
```

## Zad 7

*Błąd w poleceniu, brakuje `<stdio.h>` po `#include`*

```
gcc zad7.c -o zad7
```

## Zad 8

```
echo -n abcdefghijklmn > zad8
cat zad8
exec 3<> zad8
read -n 5 <&3
echo -n ABC >&3
exec 3>&-
cat zad8
```

## Zad 9

```
nano dane.txt
touch wynik.txt
exec 3<> wynik.txt
echo "Witaj Linux" >&3
exec 4< dane.txt
read <&4
touch log.txt
exec 5>&1
exec 1> log.txt
echo "Witaj Linux" >&5
exec 3>&-
echo "Witaj Linux" >&3
exec 4>&- && exec 5>&-
```
