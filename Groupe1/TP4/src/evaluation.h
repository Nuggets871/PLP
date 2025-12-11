#ifndef EVALUATION_H
#define EVALUATION_H

int convertir_en_postfixe(const char *input, char *output, int max_len);

int evaluer_postfixe(const char *expression, double *result);

int evaluer_expression(const char *input, double *result);

#endif
