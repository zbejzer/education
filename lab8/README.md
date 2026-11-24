# Lab 8

## Zad 1

- `ps -eO euser`
- `ps -NT`
- `ps -t -

## Zad 2

- `./zad2.sh &`
- `ps`
- `tty`
  `ps -t pts/12`
- `jobs`
  `fg $1` - nie można
- `kill -9 1787266`

## Zad 3

- `nohup ./zad2.sh &`

## Zad 4

```bash
nice -n 3 ./zad2.sh &
nice -n 6 ./zad2.sh &
nice -n 9 ./zad2.sh &
```

`top -u "$UID"`
