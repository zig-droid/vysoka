#include <stdio.h>

int obvod_ctverce () {
    int a;
    scanf("%i", &a);
    return 4*a;
}

int obsah_ctverce() {
    int a;
    scanf("%i", &a);
    return a*a;
}

int main() {
    printf("zadej stranu čtverce a: ");
    printf("obvod čtverce je %i\n a obsah je %i\n", obvod_ctverce(), obsah_ctverce());
    return 0;
}
