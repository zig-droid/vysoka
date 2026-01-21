#!/bin/bash

# kontrola argumentu
if [ $# -ne 1 ]
then
    echo "Použití: $0 <adresář>"
    exit 1
fi

DIR="$1"

# ověření že argument je adresář
if [ ! -d "$DIR" ]
then
    echo "Chyba: '$DIR' není adresář"
    exit 2
fi

for file in "$DIR"/*.txt
do
    # přeskočí pokud neexistuje
    [ -e "$file" ] || continue
    
    # načte obsah prvního řádku
    first_line=$(head -n 1 "$file")
    
    # rozdělí datum
    IFS='/' read -r DD MM YYYY <<< "$first_line"

    # ověření že datum je ve správném formátu
    if [[ -z "$DD" || -z "$MM" || -z "$YYYY" ]]
    then
        echo "upozornění: soubor '$file' nemá platný formát datumu ('$first_line')"
        continue
    fi
    # cílová cesta
    target_dir="$DIR/$YYYY/$MM/$DD"

    # vytvoření podadresáře
    mkdir -p "$target_dir"

    # přesunutí souborů
    mv "$file" "$target_dir"/
done
