// evaluation.h
#ifndef EVALUATION_H
#define EVALUATION_H

#include "parseur.h"

/**
 * Évalue une expression A op B.
 * - expr  : expression interne (left, op, right)
 * - result: pointeur où stocker le résultat
 *
 * Retourne 0 si OK, -1 en cas d'erreur (ex: division par zéro ou opérateur inconnu).
 * En cas d'erreur, la fonction affiche un message adapté.
 */
int eval_expression(const Expression *expr, double *result);

#endif