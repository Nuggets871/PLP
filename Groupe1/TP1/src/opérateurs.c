#include <stdio.h>

int main()
{
    int a = 16;
    int b = 3;

    printf("Addition: %d + %d = %d\n", a, b, a + b);
    printf("Soustraction: %d - %d = %d\n", a, b, a - b);
    printf("Multiplication: %d * %d = %d\n", a, b, a * b);
    printf("Division: %d / %d = %d\n", a, b, a / b);
    printf("Modulo: %d %% %d = %d\n", a, b, a % b);

    printf("Egalité: %d == %d est %d\n", a, b, a == b);
    printf("Supérieur: %d > %d est %d\n", a, b, a > b);

    return 0;
}