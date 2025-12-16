#include "lambda.h"
#include "variables.h"
#include "evaluation.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int est_lambda(const char *input)
{
    // verifier si ca commence par (lambda
    if (input[0] != '(') {
        return 0;
    }
    int i = 1;
    while (input[i] == ' ') {
        i++;
    }
    if (input[i] == 'l' && input[i+1] == 'a' && input[i+2] == 'm' && 
        input[i+3] == 'b' && input[i+4] == 'd' && input[i+5] == 'a') {
        return 1;
    }
    return 0;
}

int evaluer_lambda(const char *input, double *result)
{
    // parser (lambda x.expression) valeur
    int i = 1;
    while (input[i] == ' ') {
        i++;
    }
    
    // sauter "lambda"
    i += 6;
    while (input[i] == ' ') {
        i++;
    }

    // lire le nom de la variable (x)
    char var_name[50];
    int j = 0;
    while (input[i] != '.' && input[i] != ' ' && input[i] != '\0') {
        var_name[j] = input[i];
        i++;
        j++;
    }
    var_name[j] = '\0';

    // sauter le point
    while (input[i] == ' ') {
        i++;
    }
    if (input[i] == '.') {
        i++;
    }
    while (input[i] == ' ') {
        i++;
    }

    // lire l'expression jusqu'a la parenthese fermante
    char expression[256];
    j = 0;
    int parentheses = 0;
    while (input[i] != '\0') {
        if (input[i] == ')' && parentheses == 0) {
            break;
        }
        if (input[i] == '(') {
            parentheses++;
        }
        if (input[i] == ')') {
            parentheses--;
        }
        expression[j] = input[i];
        i++;
        j++;
    }
    expression[j] = '\0';

    // sauter la parenthese fermante
    if (input[i] == ')') {
        i++;
    }
    while (input[i] == ' ') {
        i++;
    }

    // lire la valeur a appliquer
    char valeur_str[100];
    j = 0;
    while (input[i] != '\0') {
        valeur_str[j] = input[i];
        i++;
        j++;
    }
    valeur_str[j] = '\0';

    // determiner la valeur a substituer
    double valeur;
    if (isdigit(valeur_str[0]) || valeur_str[0] == '.' || valeur_str[0] == '-') {
        valeur = atof(valeur_str);
    } else {
        // c'est une variable
        Variable *v = chercher_variable(valeur_str);
        if (v == NULL) {
            printf("erreur: la variable %s n'est pas definie\n", valeur_str);
            return -1;
        }
        if (v->type != TYPE_ENTIER && v->type != TYPE_REEL) {
            printf("erreur: la variable doit etre numerique\n");
            return -1;
        }
        valeur = v->valeur_num;
    }

    // remplacer toutes les occurrences de var_name par la valeur dans expression
    char expr_finale[512];
    i = 0;
    j = 0;
    int var_len = strlen(var_name);
    while (expression[i] != '\0') {
        // verifier si on a le nom de variable
        int match = 1;
        int k = 0;
        while (k < var_len) {
            if (expression[i + k] != var_name[k]) {
                match = 0;
                break;
            }
            k++;
        }
        
        // verifier que c'est bien un mot complet
        if (match == 1) {
            char avant = (i > 0) ? expression[i - 1] : ' ';
            char apres = expression[i + var_len];
            if ((isalnum(avant) || avant == '_') || (isalnum(apres) || apres == '_')) {
                match = 0;
            }
        }

        if (match == 1) {
            // remplacer par la valeur
            char val_buf[50];
            sprintf(val_buf, "%g", valeur);
            int m = 0;
            while (val_buf[m] != '\0') {
                expr_finale[j] = val_buf[m];
                j++;
                m++;
            }
            i += var_len;
        } else {
            expr_finale[j] = expression[i];
            i++;
            j++;
        }
    }
    expr_finale[j] = '\0';

    // evaluer l'expression finale
    return evaluer_expression(expr_finale, result);
}
