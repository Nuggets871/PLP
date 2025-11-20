#include <stdio.h>

char liste_phrase[10][100] = {
    "Bonjour, comment ça va ?\n",
    "Le temps est magnifique aujourd'hui.\n",
    "C'est une belle journée.\n",
    "La programmation en C est amusante.\n",
    "Les tableaux en C sont puissants.\n",
    "Les pointeurs en C peuvent être déroutants.\n",
    "Il fait beau dehors.\n",
    "La recherche dans un tableau est intéressante.\n",
    "Les structures de données sont importantes.\n",
    "Programmer en C, c'est génial.\n",
}; // j'ai ajoute \n a la fin pour bien faire la comparaison avec la phrase recherchée parce que fgets rajoute un \n à la fin


int main() {
    char phrase_recherchee[100];

    printf("Entrez une phrase à rechercher : \n");
    fgets(phrase_recherchee, 100, stdin);


    int phrase_dans_liste = 0;
    for (int ii = 0; ii < 10; ii++) {
        // on doit comparer caractere par carcactere comme on ne peut pas utiliser strcmp
        int jj = 0;
        int identique = 1;
        while (liste_phrase[ii][jj] != '\0' || phrase_recherchee[jj] != '\0') {
            if (liste_phrase[ii][jj] != phrase_recherchee[jj]) {
                identique = 0;
                break;
            }
            jj++;
        }

        if (identique) {
            phrase_dans_liste = 1;
            break;
        }
    }

    if (phrase_dans_liste) {
        printf("Phrase trouvée");
    } else {
        printf("Phrase non trouvée");
    }

    return 0;
}