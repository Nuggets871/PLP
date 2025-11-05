#include <stdio.h>

int main()
{
    const char* all_types[12] = {
        "char", "signed char", "unsigned char", "short", "unsigned short", "int", "unsigned int", "long",
        "unsigned long", "float", "double", "long double"
    };

    size_t sizes[12] = {
        sizeof(char), sizeof(signed char), sizeof(unsigned char), sizeof(short), sizeof(unsigned short),
        sizeof(int), sizeof(unsigned int), sizeof(long), sizeof(unsigned long), sizeof(float), sizeof(double), sizeof(long double)
    };

    for (int i = 0; i < 12; i++) {
        printf("%s: %zu\n", all_types[i], sizes[i]);
    }

    return 0;
}
