#include <stdio.h>

int main() {
    // le nombre est divisible par 4 mais pas par 6
    printf("Nombres divisibles par 4 mais pas par 6:\n");
    for (int i = 1; i <= 1000; i++) {
        if (i % 4 == 0 && i % 6 != 0) {
            printf("%d ", i);
        }
    }
    printf("\n\n");

    // le nombre est pair et divisible par 8
    printf("Nombres pairs et divisibles par 8:\n");
    int i = 1;
    while (i <= 1000) {
        if (i % 2 == 0 && i % 8 == 0) {
            printf("%d ", i);
        }
        i++;
    }
    printf("\n\n");

    // Le nombre est divisible par 5 ou 7 mais pas par 10
    printf("Nombres divisibles par 5 ou 7 mais pas par 10:\n");
    i = 1;
    do {
        if ((i % 5 == 0 || i % 7 == 0) && i % 10 != 0) {
            printf("%d ", i);
        }
        i++;
    } while (i <= 1000);
    printf("\n");

    return 0;
}
