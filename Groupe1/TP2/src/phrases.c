#include <stdio.h>
#include <string.h>

int main() {
    char nom_fichier[100];
    printf("Entrez le nom du fichier dans lequel chercher la phrase : ");
    scanf("%99s", nom_fichier);

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) { }

    char chaine[100];
    printf("Entrez une chaîne de caractères à rechercher : ");
    if (fgets(chaine, sizeof(chaine), stdin) == NULL) chaine[0] = '\0';
    size_t len = strlen(chaine);
    if (len > 0 && chaine[len - 1] == '\n') chaine[len - 1] = '\0';

    FILE * fichier = fopen(nom_fichier, "r");

    char ligne[256];
    int count = 0;
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (strstr(ligne, chaine) != NULL) {
            printf("Phrase trouvée : %s", ligne);
            count++;
        }
    }

    if (count == 0) {
        printf("La phrase '%s' n'a pas été trouvée dans le fichier %s.\n", chaine, nom_fichier);
    } else {
        printf("La phrase a été trouvée %d fois\n", count);
    }

    fclose(fichier);
    return 0;
}
