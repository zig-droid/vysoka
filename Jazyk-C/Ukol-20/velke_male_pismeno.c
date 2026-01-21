#include <stdio.h>
#include <ctype.h>

int main() {
    char znak;
    printf("Zadejte znak: ");
    scanf("%c", &znak);
    if (isupper(znak)) {
        printf("Zadany znak je velke pismeno.\n");
    } else if (islower(znak)) {
        printf("Zadany znak je male pismeno.\n");
}}