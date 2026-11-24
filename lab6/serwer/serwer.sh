#!/usr/bin/env bash

SERVER_PIPE="serwer_pipe"

mkfifo "$SERVER_PIPE"

while true; do
    if read -r liczba client_pipe < "$SERVER_PIPE"; then
            echo "[SERWER] Otrzymano liczbę: $liczba od klienta: $client_pipe"
            
            # Obliczenie prostej funkcji arytmetycznej: f(x) = x * 2 + 10
            wynik=$(( liczba * 2 + 10 ))
            
            # Wysłanie wyniku do łącza klienta (w tle, aby uniknąć zakleszczenia)
            if [ -p "$client_pipe" ]; then
                echo "$wynik" > "$client_pipe" &
                echo "[SERWER] Wysłano wynik: $wynik"
            else
                echo "[SERWER] Błąd: Łącze klienta nie istnieje lub zostało zamknięte."
            fi
    fi
done
