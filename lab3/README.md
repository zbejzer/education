# Lab 3

## Zad 1

a) `set`
b) `printenv`

## Zad 3

a) `declare test="Ala ma kota"`
b) `echo $test`
c) `declare test="Kot ma Ale" && echo $test`
d) 
```
declare -p test
export test
```
e)
```
export -n test
declare -p test
```
f) 
```
export test
unset test
declare -p test
```
g)
```
readonly test="Kot ma Ale"
readonly test="Ala ma Kota"
declare test="Ala ma kota"
unset test
```

## Zad 4

a) 
```
declare napis1="Ala ma kota"
declare napis2="Kot ma ale"
declare napisy=$napis1$napis2
echo $napisy
```
b) `echo ${#napisy}`
c) `echo ${napisy:3}`
d) `echo ${napisy:3:5}`
e)
```
declare -i liczba1=3
declare -i liczba2=7
```
f)
```
declare -i suma=$liczba1+$liczba2
declare -i roznica=$liczba1-$liczba2
declare -i iloczyn=$liczba1*$liczba2
declare -i iloraz=$liczba1/$liczba2
```
g) `declare -i tablica=(3 5 7 11)`
h) `echo ${tablica[2]}`
i) `echo ${#tablica[*]}`
j)
```
declare -i hexliczba=16#17
declare -i octliczba=8#11
echo $(($hexliczba*$octliczba))
```

## Zad 5

```
export zmiennaSrodowiskowa=36
```

## Zad 6

```
alias search='grep -rn'
```

## Zad 7

```
export PATH=$PATH:~/example
```

## Zad 8

```
declare -i liczbaPlikow=$(find -maxdepth 1 -type d | wc -l)
declare -i liczbaFolderow=$(find -maxdepth 1 -type f | wc -l)
declare -i suma=$liczbaPlikow+$liczbaFolderow
```

## Zad 9

```
declare -a katalogi=($(ls))
echo ${katalogi[0]}
```

## Zad 10

```
declare rok=$(date +%Y)
cal $rok
```

