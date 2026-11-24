# Lab 5

## Zad 1

```
find . -perm /g+r
```

## Zad 2

```
mkdir /tmp/sborodziuk
mkdir /tmp/sborodziuk/folderA
mkdir /tmp/sborodziuk/folderA/folderB
chmod 000 .
chmod 700 folderB
chmod 000 .
```

## Zad 5

```
umask 022
mkdir folderA
touch plikA
umask 666
mkdir folderB
touch plikB
```

## Zad 6

```
stat -c "%a %n" /usr/bin/passwd
```

## Zad 7

```
touch file1
touch file2
mkdir dir1
chmod u+s file1
chmod g+s file2
touch file3
chmod u+s,g+s file3
chmod o+t dir1
ls -la
```

## Zad 9

```
chmod 755 zad9.out
chmod 644 plik.txt
chmod u=rws zad9.out
```
