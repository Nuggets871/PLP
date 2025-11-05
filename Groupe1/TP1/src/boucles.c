#include <stdio.h>

int main() {
    int size;
    printf("Entrez une taille (< 10) : ");
    scanf("%d", &size);
    if (size >= 10 || size <= 0) {
        printf("Taille invalide.\n");
        return 1;
    }

    // Version avec boucles for
    printf("Version avec for :\n");
    for (int i = 1; i <= size; i++) {
        for (int j = 1; j <= i; j++) {
            // Si on est sur une bordure, on affiche * sinon #
            if (i == j || j == 1 || j == size || i == size) {
                printf("*");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }

    // Version avec boucles while
    printf("Version avec while :\n");
    int i = 1;
    while (i <= size) {
        int j = 1;
        while (j <= i) {
            // Si on est sur une bordure, on affiche * sinon #
            if (i == j || j == 1 || j == size || i == size) {
                printf("*");
            } else {
                printf("#");
            }
            j++;
        }
        printf("\n");
        i++;
    }

    return 0;
}
