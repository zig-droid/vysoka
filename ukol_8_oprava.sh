#!/bin/bash

# kontrola argumentu
if [ -n "${1}" ];then
# prvni argument je adresar
    DIR="${1}"
else
    echo "Neplatný vstup, zadej název cílového adresáře"
    exit 1
fi

find_args=("${@:2}")  # počet argumentů je víc jak 2
COPY=0

# Vytvoření cílového adresáře pokud neexistuje
mkdir -p "$DIR"

# prepinace pro prikaz find
args=$(find . "${find_args[@]}" -type f)
    

for f in ${args[@]}  # cyklus na procházení souborů uložených v poli. [@] je index souboru v poli
    do
        file "$(basename ${f})"
        echo "Má se soubor zkopírovat do zadaného adresáře? [ano/ne/stop]"
        read ODPOVED
        case "$ODPOVED" in
            ano) cp -r ${f} "$DIR"
            COPY=$[${COPY} + 1]
            echo "Soubor byl zkopírován";;
            ne) echo "soubor nebyl zkopírován";;
            stop) continue;;
        esac
    done

echo "Bylo zkopírováno celkem "$COPY" souborů"