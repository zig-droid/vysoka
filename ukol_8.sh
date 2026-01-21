#!/bin/bash

# kontrola argumentu
if [ $# -le 1 ]
then
    echo "Neplatný vstup, zadej název adresáře"
    exit 1
fi

# první argument adresář,  další jsou přepínače pro příkaz find
DIR="$1"
args=("${@:2}")  # počet argumentů je víc jak 2
#size=$("^([+])([0-9]{?})+(\.[0-9])([kMGT])$")

# prepinace pro prikaz find
if [ $# -ge 2 ];then  
    case "$2" in
        -f) args=$(find -type f);;
        -d) args=$(find -type d);;
        #'^(+\[0-9])+(\.[0-9])([kMGT])$') args=$(find -size);;
    esac 
fi 

COPY=0

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
