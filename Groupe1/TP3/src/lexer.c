// lexer.c
#include "lexer.h"
#include <ctype.h>
#include <stdlib.h>

int lexer_tokenize(const char *input, Token *tokens, int max_tokens)
{
    int pos = 0;
    int count = 0;

    while (input[pos] != '\0' && count < max_tokens - 1) {
        while (input[pos] == ' ' || input[pos] == '\t')
            pos++;

        if (input[pos] == '\0')
            break;

        if (isdigit((unsigned char)input[pos]) || input[pos] == '.') {
            char *endptr;
            double val = strtod(&input[pos], &endptr);
            if (&input[pos] == endptr) {
                tokens[count].type = TOK_ERROR;
                return -1;
            }
            tokens[count].type = TOK_NUMBER;
            tokens[count].value = val;
            tokens[count].op = 0;

            count++;
            pos = (int)(endptr - input);
        }
        else if (input[pos] == '+' || input[pos] == '-' ||
                 input[pos] == '*' || input[pos] == '/') {
            tokens[count].type = TOK_OPERATOR;
            tokens[count].op = input[pos];
            tokens[count].value = 0.0;

            count++;
            pos++;
        }
        else {
            tokens[count].type = TOK_ERROR;
            return -1;
        }
    }

    if (count < max_tokens) {
        tokens[count].type = TOK_END;
        tokens[count].value = 0.0;
        tokens[count].op = 0;
        count++;
    }

    return count;
}
