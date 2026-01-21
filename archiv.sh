#!/bin/bash

#exec 6<&3
exec 3<~/S.txt

while read line; do
    case "$line" in
        *.txt)
            zip -r "txt-$(date +%Y%m%d-%H%M).zip" *.txt
            ;;
        *.png)
            zip -r png-$(date +%Y%m%d-%H%M).zip *.png
            ;;
        *.json)
            zip -r json.zip *.json
            ;;
        *.jpeg)
            zip -r jpeg.zip *.jpeg
            ;;
    esac
done <<< ~/S.txt

exec 0<&3