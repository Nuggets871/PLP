#include <stdio.h>

int main()
{
    char my_char_var = 'a';
    printf("%c\n", my_char_var);

    unsigned char my_uchar_var = 234;
    printf("%u\n", my_uchar_var);

    short my_short_var = -12;
    printf("%d\n", my_short_var);

    unsigned short my_ushort_var = 65535;
    printf("%u\n", my_ushort_var);

    int my_int_var = 12;
    printf("%d\n", my_int_var);

    unsigned int my_uint_var = 3456;
    printf("%u\n", my_uint_var);

    long my_long_var = -1234553L;
    printf("%ld\n", my_long_var);

    unsigned long my_ulong_var = 234556UL;
    printf("%lu\n", my_ulong_var);

    long long my_llong_var = 1123345LL;
    printf("%lld\n", my_llong_var);

    unsigned long long my_ullong_var = 1234567ULL;
    printf("%llu\n", my_ullong_var);

    float my_float_var = 3.14;
    printf("%f\n", my_float_var);

    double my_double_var = 3.14E-12;
    printf("%f\n", my_double_var);

    long double my_long_double_var = 3.14E-22;
    printf("%Lf\n", my_long_double_var);

    return 0;
}