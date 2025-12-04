// parseur.c
#include "parseur.h"

int parse_expression(const Token *tokens, Expression *out_expr)
{

    if (tokens[0].type != TOK_NUMBER) {
        return -1;
    }

    if (tokens[1].type != TOK_OPERATOR) {
        return -1;
    }

    if (tokens[2].type != TOK_NUMBER) {
        return -1;
    }

    if (tokens[3].type != TOK_END) {
        return -1;
    }

    out_expr->left  = tokens[0].value;
    out_expr->right = tokens[2].value;
    out_expr->op    = tokens[1].op;

    return 0;
}
