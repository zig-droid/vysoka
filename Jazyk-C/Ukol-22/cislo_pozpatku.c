#include <stdio.h>

int cislo_pozpatku(int cislo) {
    int pozpatku = 0;  // Promenna pro ulozeni cisla pozpatku
    while (cislo != 0) {
        pozpatku = pozpatku * 10 + (cislo % 10); // Pridani posledni cifry cisla na konec pozpatku
        cislo /= 10; // Odstraneni posledni cifry z puvodniho cisla
    }
    return pozpatku;
}

int main() {
    int cislo;
    printf("Zadejte cele cislo: ");
    scanf("%d", &cislo);
    
    int vysledek = cislo_pozpatku(cislo);
    printf("Cislo pozpatku je: %d\n", vysledek);
    
    return 0;
}