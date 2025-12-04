// lexer.h
#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOK_NUMBER,
    TOK_OPERATOR,
    TOK_END,
    TOK_ERROR
} TokenType;

typedef struct {
    TokenType type;
    double    value;
    char      op;   
} Token;

/**
 * Tokenise une chaîne d'expression simple "A op B".
 * Retourne le nombre de tokens remplis dans tokens,
 * ou -1 en cas d'erreur de lexing.
 */
int lexer_tokenize(const char *input, Token *tokens, int max_tokens);

#endif
