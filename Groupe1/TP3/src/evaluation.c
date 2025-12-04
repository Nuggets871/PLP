// evaluation.c
#include "evaluation.h"
#include <stdio.h>

int eval_expression(const Expression *expr, double *result)
{
    switch (expr->op) {
    case '+':
        *result = expr->left + expr->right;
        return 0;

    case '-':
        *result = expr->left - expr->right;
        return 0;

    case '*':
        *result = expr->left * expr->right;
        return 0;

    case '/':
        if (expr->right == 0.0) {
            printf("Erreur: division par zéro.\n");
            return -1;
        }
        *result = expr->left / expr->right;
        return 0;

    default:
        printf("Erreur: opérateur inconnu '%c'.\n", expr->op);
        return -1;
    }
}
