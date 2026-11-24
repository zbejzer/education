#!/usr/bin/env bash

CLIENT_PIPE="klient_pipe"
SERVER_PIPE="serwer_pipe"

mkfifo "$CLIENT_PIPE"

read -p "Podaj liczbę naturalną: " liczba

FULL_CLIENT_PATH="$(pwd)/$CLIENT_PIPE"

echo "$liczba $FULL_CLIENT_PATH" > "$SERVER_PIPE" &

echo "[Oczekiwanie na wynik od serwera..."

wynik=$(cat "$CLIENT_PIPE")

echo "$wynik"