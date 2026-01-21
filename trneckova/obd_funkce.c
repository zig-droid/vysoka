/*
* obd_funkce.c  verze 1.0
*
* Funkce pro vypocet obvodu a obsahu
*===================================
*
* Jaroslav Zikmund leden 2026
*
*/

/* sytemove hlavickove soubory - zadne nejsou*/

/* vlastni hlavickove soubory*/
#include <obd_funkce.h> /* hlavickovy soubor vlastniho modulu*/

/* hlavickove soubory ostanich modulu - zadne nejsou*/

/* def. globalnich promennych - zadne nejsou*/

/*lokalni def. symbolickych konstant a maker - zadne nejsou*/

/* uplne funkcni prototypy lokalnich funkci - zadne nejsou*/

/* funkce main v tomto modulu neni*/

/* def. lokalnich funkci - zadne nejsou*/

/* definice globalnich funkci*/
double obvod( double a, double b) {
    return 2 * ( a+ b);
}

double obsah( double a, double b) {
    return a * b
}