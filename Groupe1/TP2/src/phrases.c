#include <stdio.h>
#include <string.h>

int main() {
    char nom_fichier[100];
    char phrase_recherche[200];
    char ligne[500];
    int nombre_occurrences = 0;
    FILE *fichier;
    char *position;

    printf("Entrez le nom du fichier: ");
    scanf("%s", nom_fichier);

    getchar();

    printf("Entrez la phrase à rechercher: ");
    fgets(phrase_recherche, 200, stdin);

    phrase_recherche[strcspn(phrase_recherche, "\n")] = 0;

    fichier = fopen(nom_fichier, "r");

    while (fgets(ligne, 500, fichier) != NULL) {
        position = ligne;
        while ((position = strstr(position, phrase_recherche)) != NULL) {
            nombre_occurrences++;
            position++;
        }
    }

    fclose(fichier);

    printf("\nLa phrase \"%s\" apparait %d fois dans le fichier.\n", phrase_recherche, nombre_occurrences);

    return 0;
}

