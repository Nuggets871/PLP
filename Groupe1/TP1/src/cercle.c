#include <stdio.h>

int main()
{
    float rayon, aire, perimetre, pi = 3.14159265358979323846;
    printf("Donnez le rayon du cercle : ");
    scanf("%f", &rayon);

    aire = pi * rayon * rayon;
    printf("L'aire du cercle est de %.2f\n", aire);

    perimetre = 2 * pi * rayon;
    printf("Le perimetre du cercle est de %.2f\n", perimetre);

    return 0;
}
