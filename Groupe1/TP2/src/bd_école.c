#include <stdio.h>
#include <string.h>

struct etudiant {
    char prenom[30];
    char nom[30];
    char rue[30];
    char ville[30];
    short notes;
};


int main() {
    struct etudiant dupont;

    strcpy(dupont.prenom, "Dupont");
    strcpy(dupont.nom, "Pierre");
    strcpy(dupont.rue, "Boulevard du 11 novembre 1918");
    strcpy(dupont.ville, "Villeurbanne");
    dupont.notes = 19;

    printf("Exemple initalisation Dupont : %s %s %s %s %d\n", dupont.prenom, dupont.nom, dupont.rue, dupont.ville, dupont.notes);

    struct etudiant etudiant_cpe[5];
    for (int i = 0; i < 5; i++) {
        char prenom[30];
        char nom[30];
        char rue[30];
        char ville[30];
        short notes;

        printf("Entrez le prénom de l'étudiant %d : ", i + 1);
        scanf("%29s", prenom);

        printf("Entrez le nom de l'étudiant %d : ", i + 1);
        scanf("%29s", nom);

        printf("Entrez la rue de l'étudiant %d : ", i + 1);
        scanf("%29s", rue);

        printf("Entrez la ville de l'étudiant %d : ", i + 1);
        scanf("%29s", ville);

        printf("Entrez la note de l'étudiant %d : ", i + 1);
        scanf("%hd", &notes);

        strcpy(etudiant_cpe[i].prenom, prenom);
        strcpy(etudiant_cpe[i].nom, nom);
        strcpy(etudiant_cpe[i].rue, rue);
        strcpy(etudiant_cpe[i].ville, ville);
        etudiant_cpe[i].notes = notes;
    }

    printf("Recapitulatif de tous les étudiants : \n");
    for (int i = 0; i < 5; i++) {
        printf("Etudiant %d : %s %s %s %s %hd\n",
             i + 1,
            etudiant_cpe[i].prenom,
            etudiant_cpe[i].nom,
            etudiant_cpe[i].rue,
            etudiant_cpe[i].ville,
            etudiant_cpe[i].notes
        );
    }

    return 0;
}