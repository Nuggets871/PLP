#include <stdio.h>
#include <stdlib.h>

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

int depiler(Pile *pile)
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

int main()
{

}