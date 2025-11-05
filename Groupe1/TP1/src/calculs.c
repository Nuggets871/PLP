#include <stdio.h>

int main()
{
    int num1, num2;
    char op;

    printf("Entrez le premier nombre entier : ");
    scanf("%d", &num1);

    printf("Entrez le deuxième nombre entier : ");
    scanf("%d", &num2);

    printf("Entrez l'opérateur (+, -, *, /, %%, &, |, ~) : ");
    // attention!!! mettre un espace avant %c pour ignorer les espaces blancs à cause du précédent scanf
    scanf(" %c", &op);

    switch (op)
    {
    case '+':
        printf("Résultat : %d + %d = %d\n", num1, num2, num1 + num2);
        break;
    case '-':
        printf("Résultat : %d - %d = %d\n", num1, num2, num1 - num2);
        break;
    case '*':
        printf("Résultat : %d * %d = %d\n", num1, num2, num1 * num2);
        break;
    case '/':
        if (num2 == 0)
        {
            printf("Erreur : Division par zéro.\n");
        }
        else
        {
            printf("Résultat : %d / %d = %d\n", num1, num2, num1 / num2);
        }
        break;
    case '%':
        if (num2 == 0)
        {
            printf("Erreur : Modulo par zéro.\n");
        }
        else
        {
            printf("Résultat : %d %% %d = %d\n", num1, num2, num1 % num2);
        }
        break;
    case '&':
        printf("Résultat : %d & %d = %d\n", num1, num2, num1 & num2);
        break;
    case '|':
        printf("Résultat : %d | %d = %d\n", num1, num2, num1 | num2);
        break;
    case '~':
        printf("Résultat : ~%d = %d\n", num1, ~num1);
        break;
    default:
        printf("Opérateur invalide.\n");
        break;
    }

    return 0;
}
