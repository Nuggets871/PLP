#include "evaluation.h"
#include <stdio.h>

int eval_expression(const Expression *expr, double *result)
{
    // addition
    if (expr->op == '+') {
        *result = expr->left + expr->right;
        return 0;
    }

    // soustraction
    if (expr->op == '-') {
        *result = expr->left - expr->right;
        return 0;
    }

    // multiplication
    if (expr->op == '*') {
        *result = expr->left * expr->right;
        return 0;
    }

    // division
    if (expr->op == '/') {
        if (expr->right == 0.0) {
            printf("erreur: division par zero\n");
            return -1;
        }
        *result = expr->left / expr->right;
        return 0;
    }

    // operateur inconnu
    printf("erreur: operateur inconnu\n");
    return -1;
}
