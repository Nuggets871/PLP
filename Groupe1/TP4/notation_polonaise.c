#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// implémentation d'une logique de pile
typedef struct Element Element;
struct Element
{
    char caractere;
    Element *suivant;
};

typedef struct Pile Pile;
struct Pile
{
    Element *premier;
};

void empiler(Pile *pile, char nouveauCaractere)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (pile == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }

    nouveau->caractere = nouveauCaractere;
    nouveau->suivant = pile->premier;
    pile->premier = nouveau;
}

char depiler(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int caractereDepile;
    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier)
    {
        caractereDepile = elementDepile->caractere;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }
    return caractereDepile;
}

void afficherPile(Pile *pile)
{
    if (pile == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;

    while (actuel != NULL)
    {
        printf("%c\n", actuel->caractere);
        actuel = actuel->suivant;
    }
    printf("\n");
}

// fonction permettant d'avoir la priorité d'un opérateur
int getPriorite(char operateur)
{
    switch (operateur)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}

int main()
{
    Pile pile;
    pile.premier = NULL;

    char calculEntree[100];
    char calculSortie[100] = "";
    printf("Entrez un calcul sans parenthèses : ");
    fgets(calculEntree, 100, stdin);

    for (int ii = 0; ii < strlen(calculEntree); ii++)
    {
        if (calculEntree[ii] == ' ') {
            continue;
        }
        else if (isdigit(calculEntree[ii]))
        {
            strncat(calculSortie, &calculEntree[ii], 1);
        }
        else
        {
            if (pile.premier == NULL ||
                getPriorite(calculEntree[ii]) > getPriorite(pile.premier->caractere))
            {
                // on va empiler si la pile est vide ou que la priorité de l'operateur actuel est plus haute que l'operateur de la pile
                empiler(&pile, calculEntree[ii]);
            }
            else
            {
                // sinon on va depiler et ajouter a la reponse
                while (pile.premier != NULL &&
                       getPriorite(calculEntree[ii]) <= getPriorite(pile.premier->caractere))
                {
                    char operateur = depiler(&pile);
                    strncat(calculSortie, &operateur, 1);
                }
                empiler(&pile, calculEntree[ii]);
            }
        }
    }
    while (pile.premier != NULL)
    {
        char operateur = depiler(&pile);
        strncat(calculSortie, &operateur, 1);
    }

    printf("Notation polonaise inversée : %s\n", calculSortie);

    return 0;
}