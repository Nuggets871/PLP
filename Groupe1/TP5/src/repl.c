#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdlib.h>
#include "variables.h"
#include "lambda.h"
#include "evaluation.h"

// fonction pour comparer deux chaines sans tenir compte majuscule/minuscule
int comparer_commande(const char *a, const char *b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        char c1 = a[i];
        char c2 = b[i];
        if (c1 >= 'A' && c1 <= 'Z') {
            c1 = c1 + 32;
        }
        if (c2 >= 'A' && c2 <= 'Z') {
            c2 = c2 + 32;
        }
        if (c1 != c2) {
            return 0;
        }
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') {
        return 1;
    }
    return 0;
}

// fonction pour verifier si une commande commence par un mot
int commence_par(const char *commande, const char *mot)
{
    int i = 0;
    while (mot[i] != '\0') {
        if (commande[i] == '\0') {
            return 0;
        }
        char c1 = commande[i];
        char c2 = mot[i];
        if (c1 >= 'A' && c1 <= 'Z') {
            c1 = c1 + 32;
        }
        if (c2 >= 'A' && c2 <= 'Z') {
            c2 = c2 + 32;
        }
        if (c1 != c2) {
            return 0;
        }
        i++;
    }
    return 1;
}

void afficher_version(void)
{
    printf("version 1.0.0\n");
}

void afficher_help(void)
{
    printf("help : affiche les commandes\n");
    printf("echo : affiche du texte\n");
    printf("version : affiche la version\n");
    printf("date : affiche la date\n");
    printf("quit : quitter\n");
    printf("variable = valeur : definir une variable\n");
    printf("(lambda x.expr) val : expression lambda\n");
}

void afficher_aide(void)
{
    printf("aide : affiche les commandes\n");
    printf("afficher : affiche du texte\n");
    printf("version : affiche la version\n");
    printf("date : affiche la date\n");
    printf("quitter : quitter\n");
    printf("variable = valeur : definir une variable\n");
    printf("(lambda x.expr) val : expression lambda\n");
}

void afficher_echo(char commande[1024])
{
    int premier_espace = 1;
    int i = 0;
    while (commande[i] != '\0') {
        char c = commande[i];
        if (i == 0) {
            if (c >= 'a' && c <= 'z') {
                c = c - 32;
            }
        }
        if (c == ' ' && premier_espace == 1) {
            printf(": ");
            premier_espace = 0;
            i++;
            continue;
        }
        printf("%c", c);
        i++;
    }
    printf("\n");
}

void afficher_date(void)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("date: %d-%02d-%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

// verifier si c'est une affectation de variable
int est_affectation(const char *commande, char *nom, char *valeur)
{
    int i = 0;
    int j = 0;

    // lire le nom de variable
    while (commande[i] != '\0' && commande[i] != ' ' && commande[i] != '=') {
        nom[j] = commande[i];
        i++;
        j++;
    }
    nom[j] = '\0';

    // sauter espaces
    while (commande[i] == ' ') {
        i++;
    }

    // verifier le =
    if (commande[i] != '=') {
        return 0;
    }
    i++;

    // sauter espaces
    while (commande[i] == ' ') {
        i++;
    }

    // lire la valeur
    j = 0;
    while (commande[i] != '\0') {
        valeur[j] = commande[i];
        i++;
        j++;
    }
    valeur[j] = '\0';

    if (strlen(nom) == 0 || strlen(valeur) == 0) {
        return 0;
    }

    return 1;
}

// traiter une affectation de variable
void traiter_affectation(const char *nom, const char *valeur)
{
    // verifier si c'est une chaine (entre guillemets)
    if (valeur[0] == '"') {
        char val_str[256];
        int i = 1;
        int j = 0;
        while (valeur[i] != '\0' && valeur[i] != '"') {
            val_str[j] = valeur[i];
            i++;
            j++;
        }
        val_str[j] = '\0';
        ajouter_variable(nom, TYPE_CHAINE, 0, val_str);
        return;
    }

    // sinon c'est un nombre
    // verifier si c'est un entier ou reel
    int a_point = 0;
    int i = 0;
    while (valeur[i] != '\0') {
        if (valeur[i] == '.') {
            a_point = 1;
        }
        i++;
    }

    double val = atof(valeur);
    if (a_point == 1) {
        ajouter_variable(nom, TYPE_REEL, val, "");
    } else {
        ajouter_variable(nom, TYPE_ENTIER, val, "");
    }
}

// verifier si c'est juste un nom de variable
int est_nom_variable(const char *commande)
{
    int i = 0;
    while (commande[i] != '\0') {
        if (commande[i] == ' ' || commande[i] == '=' || commande[i] == '+' || 
            commande[i] == '-' || commande[i] == '*' || commande[i] == '/') {
            return 0;
        }
        i++;
    }
    return 1;
}

int main(void)
{
    int continuer = 1;
    init_variables();

    while (continuer == 1) {
        printf("> ");

        char commande[1024];
        if (fgets(commande, sizeof(commande), stdin) == NULL) {
            break;
        }

        // enlever le retour a la ligne
        int i = 0;
        while (commande[i] != '\0') {
            if (commande[i] == '\n') {
                commande[i] = '\0';
                break;
            }
            i++;
        }

        // verifier quit
        if (comparer_commande(commande, "quit") == 1 || comparer_commande(commande, "quitter") == 1) {
            printf("arret...\n");
            continuer = 0;
        }
        // verifier echo
        else if (commence_par(commande, "echo ") == 1 || commence_par(commande, "afficher ") == 1) {
            afficher_echo(commande);
        }
        // verifier date
        else if (comparer_commande(commande, "date") == 1) {
            afficher_date();
        }
        // verifier version
        else if (comparer_commande(commande, "version") == 1) {
            afficher_version();
        }
        // verifier help
        else if (comparer_commande(commande, "help") == 1) {
            afficher_help();
        }
        // verifier aide
        else if (comparer_commande(commande, "aide") == 1) {
            afficher_aide();
        }
        // verifier lambda
        else if (est_lambda(commande) == 1) {
            double resultat;
            int ok = evaluer_lambda(commande, &resultat);
            if (ok == 0) {
                printf("%g\n", resultat);
            }
        }
        // verifier affectation
        else {
            char nom[100];
            char valeur[256];
            if (est_affectation(commande, nom, valeur) == 1) {
                traiter_affectation(nom, valeur);
            }
            // verifier si c'est juste un nom de variable
            else if (est_nom_variable(commande) == 1) {
                afficher_variable(commande);
            }
            // sinon essayer d'evaluer comme expression
            else {
                double resultat;
                int ok = evaluer_expression(commande, &resultat);
                if (ok == 0) {
                    printf("%g\n", resultat);
                } else {
                    printf("commande non reconnue: %s\n", commande);
                }
            }
        }

        printf("\n");
    }

    return 0;
}
