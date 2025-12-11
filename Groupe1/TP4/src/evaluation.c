#include "evaluation.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// pile simple pour operateurs
char pile_op[100];
int sommet_op = -1;

void empiler_op(char c)
{
    sommet_op++;
    pile_op[sommet_op] = c;
}

char depiler_op(void)
{
    if (sommet_op < 0) {
        return '\0';
    }
    char c = pile_op[sommet_op];
    sommet_op--;
    return c;
}

char voir_sommet_op(void)
{
    if (sommet_op < 0) {
        return '\0';
    }
    return pile_op[sommet_op];
}

// fonction pour avoir la priorite d'un operateur
int priorite(char op)
{
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

int convertir_en_postfixe(const char *input, char *output, int max_len)
{
    sommet_op = -1;
    int out_pos = 0;
    int len = strlen(input);
    int i = 0;

    while (i < len && out_pos < max_len - 1) {
        // sauter espaces
        if (input[i] == ' ' || input[i] == '\n') {
            i++;
            continue;
        }

        // si c'est un chiffre
        if (isdigit(input[i]) || input[i] == '.') {
            while (i < len && (isdigit(input[i]) || input[i] == '.')) {
                output[out_pos] = input[i];
                out_pos++;
                i++;
            }
            output[out_pos] = ' ';
            out_pos++;
        }
        // si c'est une parenthese ouvrante
        else if (input[i] == '(') {
            empiler_op(input[i]);
            i++;
        }
        // si c'est une parenthese fermante
        else if (input[i] == ')') {
            while (sommet_op >= 0 && voir_sommet_op() != '(') {
                char op = depiler_op();
                output[out_pos] = op;
                out_pos++;
                output[out_pos] = ' ';
                out_pos++;
            }
            if (sommet_op >= 0 && voir_sommet_op() == '(') {
                depiler_op();
            }
            i++;
        }
        // si c'est un operateur
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            while (sommet_op >= 0 && priorite(input[i]) <= priorite(voir_sommet_op())) {
                char op = depiler_op();
                output[out_pos] = op;
                out_pos++;
                output[out_pos] = ' ';
                out_pos++;
            }
            empiler_op(input[i]);
            i++;
        }
        else {
            return -1;
        }
    }

    // vider la pile
    while (sommet_op >= 0) {
        char op = depiler_op();
        output[out_pos] = op;
        out_pos++;
        output[out_pos] = ' ';
        out_pos++;
    }

    output[out_pos] = '\0';
    return 0;
}

int evaluer_postfixe(const char *expression, double *result)
{
    double pile[100];
    int sommet = -1;
    int len = strlen(expression);
    int i = 0;

    while (i < len) {
        // sauter espaces
        if (expression[i] == ' ') {
            i++;
            continue;
        }

        // si c'est un chiffre
        if (isdigit(expression[i]) || expression[i] == '.') {
            char nombre[50];
            int j = 0;
            while (i < len && (isdigit(expression[i]) || expression[i] == '.')) {
                nombre[j] = expression[i];
                j++;
                i++;
            }
            nombre[j] = '\0';
            double valeur = atof(nombre);
            sommet++;
            pile[sommet] = valeur;
        }
        // si c'est un operateur
        else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            if (sommet < 1) {
                return -1;
            }
            double b = pile[sommet];
            sommet--;
            double a = pile[sommet];
            sommet--;

            double resultat;
            if (expression[i] == '+') {
                resultat = a + b;
            }
            else if (expression[i] == '-') {
                resultat = a - b;
            }
            else if (expression[i] == '*') {
                resultat = a * b;
            }
            else if (expression[i] == '/') {
                if (b == 0.0) {
                    printf("erreur: division par zero\n");
                    return -1;
                }
                resultat = a / b;
            }
            sommet++;
            pile[sommet] = resultat;
            i++;
        }
        else {
            i++;
        }
    }

    if (sommet != 0) {
        return -1;
    }

    *result = pile[sommet];
    return 0;
}

int evaluer_expression(const char *input, double *result)
{
    char postfixe[256];

    if (convertir_en_postfixe(input, postfixe, sizeof(postfixe)) != 0) {
        return -1;
    }

    if (evaluer_postfixe(postfixe, result) != 0) {
        return -1;
    }

    return 0;
}
