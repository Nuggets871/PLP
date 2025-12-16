#ifndef VARIABLES_H
#define VARIABLES_H

typedef enum {
    TYPE_ENTIER,
    TYPE_REEL,
    TYPE_CHAINE
} TypeVariable;

typedef struct {
    char nom[100];
    TypeVariable type;
    double valeur_num;
    char valeur_str[256];
} Variable;

void init_variables(void);

int ajouter_variable(const char *nom, TypeVariable type, double val_num, const char *val_str);

Variable* chercher_variable(const char *nom);

void afficher_variable(const char *nom);

#endif
