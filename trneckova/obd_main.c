/*
* obd_main.c    verze 1.0
*
* Program pro praci s obdelniky
*================================
*
* Jaroslav zikmund leden 2026
*
*/

/* systemove hlavickove soubory */
#include <stdio.h>

/* vlastni hlavickove soubory*/
/* hlavickovy soubor vlastniho modulu - neni*/
/* hlavickovy soubor ostatnich modulu*/
#include <obd_funkce.h>

/* definice globalnich promennych - zadne nejsou*/

/* lokalni definice symbolickych konstant a maker*/
#define CHYBA -1.0
#define kontrola(delka) { (delka) >= 0.0 ? (delka) : CHYBA}

/* lokalni definice novych typu - zadne nejsou*/

/* definice statickych globalnich promennych*/
static double a;
static double b;

/* uplne funkcni prototypy lokalnich funkci*/
static double nacti();
static void vypis(double a, double b);

/* funkce main*/
int main(){
    double o, s;
    a = nacti();
    b = nacti();

    if ( a == CHYBA || b == CHYBA) {
        /* vypis chbove hlasky*/
        return 1;
    }

    o = obvod(a, b);
    s = obsah(a, b);

    vypis(o, s);
    return 0;
}

/* definicwe lokalnich funkci*/
static double nacti() {
    double vstup;
    /* nacteni strany od uzivatele*/
    scanf("%lf", &vstup);
    return kontrola(vstup);
}

static void vypis(double o, double s) {
    printf("obvod = %f, obsah = %f", o, s);
}

/* dfinice globalnich funkci - zadne nejsou*/