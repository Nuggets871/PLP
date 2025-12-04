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
    if (pile == NULL || pile->premier == NULL)
    {
        exit(EXIT_FAILURE);
    }

    char caractereDepile;
    Element *elementDepile = pile->premier;

    caractereDepile = elementDepile->caractere;
    pile->premier = elementDepile->suivant;
    free(elementDepile);

    return caractereDepile;
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
    case '(':
        return 0;
    default:
        return 0;
    }
}


int evaluerPostfixe(char *expression)
{
    int pile[100];
    int sommet = -1;

    for (int i = 0; i < strlen(expression); i++)
    {
        if (expression[i] == ' ')
        {
            continue;
        }

        if (isdigit(expression[i]))
        {
            int valeur = expression[i] - '0';
            sommet++;
            pile[sommet] = valeur;
        }
        else
        {
            int b = pile[sommet];
            sommet--;
            int a = pile[sommet];
            sommet--;

            int resultat;

            if (expression[i] == '+')
                resultat = a + b;
            else if (expression[i] == '-')
                resultat = a - b;
            else if (expression[i] == '*')
                resultat = a * b;
            else if (expression[i] == '/')
                resultat = a / b;

            sommet++;
            pile[sommet] = resultat;
        }
    }

    return pile[sommet];
}


int main()
{
    Pile pile;
    pile.premier = NULL;

    char calculEntree[100];
    char calculSortie[100] = "";

    printf("Entrez un calcul avec parenthèses : ");
    fgets(calculEntree, 100, stdin);

    for (int ii = 0; ii < strlen(calculEntree); ii++)
    {
        if (calculEntree[ii] == ' ' || calculEntree[ii] == '\n')
        {
            continue;
        }
        else if (isdigit(calculEntree[ii]))
        {
            strncat(calculSortie, &calculEntree[ii], 1);
        }
        else if (calculEntree[ii] == '(')
        {
            empiler(&pile, calculEntree[ii]);
        }
        else if (calculEntree[ii] == ')')
        {
            while (pile.premier != NULL && pile.premier->caractere != '(')
            {
                char operateur = depiler(&pile);
                strncat(calculSortie, &operateur, 1);
            }
            if (pile.premier != NULL && pile.premier->caractere == '(')
            {
                depiler(&pile);
            }
        }
        else
        {
            while (pile.premier != NULL &&
                   getPriorite(calculEntree[ii]) <= getPriorite(pile.premier->caractere))
            {
                char operateur = depiler(&pile);
                strncat(calculSortie, &operateur, 1);
            }
            empiler(&pile, calculEntree[ii]);
        }
    }

    while (pile.premier != NULL)
    {
        char operateur = depiler(&pile);
        strncat(calculSortie, &operateur, 1);
    }

    printf("Notation polonaise inversée : %s\n", calculSortie);

    int resultat = evaluerPostfixe(calculSortie);

    printf("Resultat du calcul : %d\n", resultat);

    return 0;
}
