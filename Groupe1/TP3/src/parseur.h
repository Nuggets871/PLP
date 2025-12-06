#ifndef PARSEUR_H
#define PARSEUR_H

#include "lexer.h"

typedef struct {
    double left;
    double right;
    char op;
} Expression;

int parse_expression(const Token *tokens, Expression *out_expr);

#endif
