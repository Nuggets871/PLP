#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "lexer.h"
#include "parseur.h"
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
}

void afficher_aide(void)
{
    printf("aide : affiche les commandes\n");
    printf("afficher : affiche du texte\n");
    printf("version : affiche la version\n");
    printf("date : affiche la date\n");
    printf("quitter : quitter\n");
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

int main(void)
{
    int continuer = 1;

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
        // sinon essayer de calculer
        else {
            Token tokens[8];
            int n = lexer_tokenize(commande, tokens, 8);

            if (n >= 0) {
                Expression expr;
                int parse_ok = parse_expression(tokens, &expr);
                if (parse_ok == 0) {
                    double res;
                    int eval_ok = eval_expression(&expr, &res);
                    if (eval_ok == 0) {
                        printf("%g\n", res);
                    }
                } else {
                    printf("commande non reconnue: %s\n", commande);
                }
            } else {
                printf("commande non reconnue: %s\n", commande);
            }
        }

        printf("\n");
    }

    return 0;
}


