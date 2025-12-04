// parseur.h
#ifndef PARSEUR_H
#define PARSEUR_H

#include "lexer.h"

typedef struct {
    double left;   
    double right;  
    char   op;   
} Expression;

/**
 * Parse une liste de tokens de la forme:
 *   NUMBER OPERATOR NUMBER END
 *
 * Retourne 0 si OK, -1 si erreur de syntaxe.
 */
int parse_expression(const Token *tokens, Expression *out_expr);

#endif
