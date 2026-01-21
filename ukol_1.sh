#!/bin/bash

echo "Zadej adresář"
read dir
#dir=~/Plocha  zkušbní adresář

# ověření že adresář existuje
if [ ! -d $dir ]; then
    echo "Chyba: adresář '$dir' nenexistuje"
    exit 1
fi

seznam=$(echo "$dir"/.* "$dir"/*)  # skryté soubory

#Projde všechny položky v adresáři
if [ -d $dir ]; then  # při zadani adresare vypise jeho polozky
    for soubor in $seznam
        do
            #určí typ
            if [ -d "$soubor" ]; then
                typ="adresář"
            elif [ -L "$soubor" ]; then
                typ="symbolický odkaz"
            else
                typ="soubor"
            fi

            # určí práva
            prava=""
            [ -r "$soubor" ] && prava="${prava}r" || prava="${prava}-"
            [ -w "$soubor" ] && prava="${prava}w" || prava="${prava}-"
            [ -x "$soubor" ] && prava="${prava}x" || prava="${prava}-"
            echo "$(basename "$soubor") $typ $prava"
        done
fi
