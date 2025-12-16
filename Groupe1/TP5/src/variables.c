#include "variables.h"
#include <stdio.h>
#include <string.h>

Variable variables[100];
int nb_variables = 0;

void init_variables(void)
{
    nb_variables = 0;
}

int ajouter_variable(const char *nom, TypeVariable type, double val_num, const char *val_str)
{
    // chercher si la variable existe deja
    int i = 0;
    while (i < nb_variables) {
        if (strcmp(variables[i].nom, nom) == 0) {
            // variable existe, verifier le type
            if (variables[i].type != type) {
                printf("erreur: changement de type non autorise pour la variable %s\n", nom);
                return -1;
            }
            // mettre a jour la valeur
            if (type == TYPE_ENTIER || type == TYPE_REEL) {
                variables[i].valeur_num = val_num;
            } else {
                strcpy(variables[i].valeur_str, val_str);
            }
            printf("variable %s mise a jour\n", nom);
            return 0;
        }
        i++;
    }

    // variable n'existe pas, l'ajouter
    if (nb_variables >= 100) {
        printf("erreur: trop de variables\n");
        return -1;
    }

    strcpy(variables[nb_variables].nom, nom);
    variables[nb_variables].type = type;
    if (type == TYPE_ENTIER || type == TYPE_REEL) {
        variables[nb_variables].valeur_num = val_num;
    } else {
        strcpy(variables[nb_variables].valeur_str, val_str);
    }

    const char *type_str = "entier";
    if (type == TYPE_REEL) {
        type_str = "reel";
    } else if (type == TYPE_CHAINE) {
        type_str = "chaine";
    }

    if (type == TYPE_ENTIER) {
        printf("variable %s definie avec la valeur %d (%s)\n", nom, (int)val_num, type_str);
    } else if (type == TYPE_REEL) {
        printf("variable %s definie avec la valeur %g (%s)\n", nom, val_num, type_str);
    } else {
        printf("variable %s definie avec la valeur \"%s\" (%s)\n", nom, val_str, type_str);
    }

    nb_variables++;
    return 0;
}

Variable* chercher_variable(const char *nom)
{
    int i = 0;
    while (i < nb_variables) {
        if (strcmp(variables[i].nom, nom) == 0) {
            return &variables[i];
        }
        i++;
    }
    return NULL;
}

void afficher_variable(const char *nom)
{
    Variable *v = chercher_variable(nom);
    if (v == NULL) {
        printf("erreur: la variable %s n'est pas definie\n", nom);
        return;
    }

    if (v->type == TYPE_ENTIER) {
        printf("%d\n", (int)v->valeur_num);
    } else if (v->type == TYPE_REEL) {
        printf("%g\n", v->valeur_num);
    } else {
        printf("\"%s\"\n", v->valeur_str);
    }
}
