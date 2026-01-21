#include <stdio.h>

void vykresleni_podle_n(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            if (j > 1) {
                printf(" ");
            }
            else {
                for (int k = 0; k < n - i; k++) {
                    printf(" ");
                }
            }
            printf("*");
        }
        printf("\n");
    }
}

void sachovnice(int m){
    for (int i = 1; i<=m; i++) {
        for (int j =1; j <= m; j++) {
            if ((i + j) % 2 == 1) {
                printf(" * ");
            }
            else {
                printf(" . ");
            }
        }
        printf("\n");
    }
}

int main() {
    int n;
    printf("Zadejte cislo n: ");
    scanf("%d", &n);
    vykresleni_podle_n(n);
    printf("\n");
    int m = 4;
    sachovnice(m);
    return 0;
}