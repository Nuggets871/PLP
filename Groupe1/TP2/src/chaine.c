#include <stdio.h>
#include <string.h>

int main() {
    char chaine1[20], chaine2[20];

    printf("Entrez une chaine de caractères : ");
    scanf("%s", chaine1);

    printf("Entrez une deuxième chaine de caractères : ");
    scanf("%s", chaine2);

    printf("Chaine 1 : %s\n", chaine1);
    printf("Chaine 2 : %s\n", chaine2);

    printf("Longueur de la chaîne 1 : %lu\n", strlen(chaine1));

    printf("Chaine 2 copiée dans Chaine 1 : %s\n", strcpy(chaine1, chaine2));

    printf("Concatenation de chaine 1 et chaine 2 : %s\n", strcat(chaine1, chaine2));

    return 0;
}
