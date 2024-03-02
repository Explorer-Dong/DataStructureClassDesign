#include <stdio.h>

int main()
{
    int auto_var = 0;
    float const_var = 3.14;
    double double_var = 2.71828;
    enum
    {
        ENUM_VAL1,
        ENUM_VAL2
    } enum_var = ENUM_VAL1;
    extern int extern_var;
    static int static_var;
    register int register_var;

    char char_var = 'A';
    signed char signed_char_var = -127;
    unsigned char unsigned_char_var = 255;
    short short_var = 32767;
    unsigned short unsigned_short_var = 65535;
    int int_var = 2147483647;
    unsigned int unsigned_int_var = 4294967295;
    long long_var = 2147483647L;
    unsigned long unsigned_long_var = 4294967295UL;
    long long long_long_var = 9223372036854775807LL;
    unsigned long long unsigned_long_long_var = 18446744073709551615ULL;
    float float_var = 3.14f;
    double double_var = 2.71828;
    long double long_double_var = 3.1415926535L;

    if (auto_var == 0)
    {
        printf("auto\n");
    }
    else
    {
        printf("break\n");
    }

    switch (enum_var)
    {
    case ENUM_VAL1:
        printf("case\n");
        break;
    case ENUM_VAL2:
        printf("char\n");
        break;
    default:
        printf("const\n");
    }

    for (int i = 0; i < 10; ++i)
    {
        printf("continue\n");
    }

    while (static_var < 10)
    {
        printf("default\n");
        static_var++;
    }

    do
    {
        printf("double\n");
    } while (register_var < 10);

    return 0;
}
