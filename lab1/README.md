# Lab 1

## Zad 1

`ssh sborodziuk@sigma.ug.edu.pl`

## Zad 2

```
mkdir -p ~/systemy2026/laboratorium1/
cd ~/systemy2026/laboratorium1/
mkdir zadania && mkdir pliki && mkdir wykład
```

`rm -R systemy2026/`

`mkdir -p ~/systemy2026/laboratorium1/{zadania,pliki,wykład}`

## Zad 3

cd ~/

1. `find -type f -name *.c`
2. `find -type f -size 0`
3. `find -type f -mtime -30`
4. `find -size +1M -size -5M -mindepth 2`
5. `find -maxdepth 1 -size +0 -ok cp "{}" ~/systemy2026/laboratorium1/wykład \;`
6. `find -mmin -5 -ok rm "{}" \;`

## Zad 4

```
wget https://inf.ug.edu.pl/~rziemann/pan_tadeusz_zadanie.c
grep -v '^//' pan_tadeusz_zadanie.c > temp.txt && mv temp.txt pan_tadeusz_zadanie.c
cat --number pan_tadeusz_zadanie.c
sed -i "s/<<<//g" pan_tadeusz_zadanie.c
gcc pan_tadeusz_zadanie.c -o pan_tadeusz_zadanie.out &&chmod +x pan_tadeusz_zadanie.out && ./pan_tadeusz_zadanie.out 
```

## Zad 5

```
wget https://inf.ug.edu.pl/~rziemann/projekt.zip

```
