#include <stdio.h>

int posloupnost(int n) {
    switch (n)
    {
    case 1 | 3 | 5 | 7 | 9:
        for (; n >= 1; n--) {
            printf("%i", n);
        };
    case 2 | 4 | 6 | 8 | 10:
        for (int i = n; i >= n; i++) {
            printf("%d", i);
        };
        break;
    
    default:
        break;
    }
}

int main() {
    int n;
    printf("Zadejte cislo: ");
    scanf("%i", &n);
    posloupnost(n);
    return 0;
}