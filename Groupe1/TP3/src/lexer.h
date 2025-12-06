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
    double value;
    char op;
} Token;

int lexer_tokenize(const char *input, Token *tokens, int max_tokens);

#endif
