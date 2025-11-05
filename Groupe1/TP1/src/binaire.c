#include <stdio.h>

int main() {
    int num;
    printf("Entrez un nombre entier : ");
    scanf("%d", &num);

    printf("Représentation binaire de %d : ", num);
    if (num == 0) {
        printf("0\n");
    } else {
        // utilisation d'un tableau pour stocker les bits
        int bits[32];
        int index = 0;
        int temp = num;
        while (temp > 0) {
            bits[index++] = temp % 2;
            temp /= 2;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("%d", bits[i]);
        }
        printf("\n");
    }

    // Tests avec les valeurs demandées
    int test_values[] = {0, 4096, 65536, 65535, 1024};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    for (int t = 0; t < num_tests; t++) {
        int val = test_values[t];
        printf("Représentation binaire de %d : ", val);
        if (val == 0) {
            printf("0\n");
        } else {
            int bits[32];
            int index = 0;
            int temp = val;
            while (temp > 0) {
                bits[index++] = temp % 2;
                temp /= 2;
            }
            for (int i = index - 1; i >= 0; i--) {
                printf("%d", bits[i]);
            }
            printf("\n");
        }
    }

    return 0;
}
