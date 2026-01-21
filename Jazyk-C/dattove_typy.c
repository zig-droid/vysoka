#include <stdio.h>

typedef int cele_cislo;

int main() {
    cele_cislo a = 0;
    cele_cislo b = 10;
    a = b++;
    printf("hodnota a je %d a hodnota b je %d\n", a, b);
    a = ++b;
    printf("hodnota a je %d a hodnota b je %d\n", a, b);
    cele_cislo cislo = 3;
    printf("%i\n", cislo);
    
    /*vypis načteneho znaku*/
    cele_cislo znak;
    znak = getchar();
    putchar(znak);
    return 0;
}
