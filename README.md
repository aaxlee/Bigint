# Bigint

A C data structure that supports integers larger than unsigned long long

stores each digit of a long number in an array where the first digit of the number is at index 0 in the array

if you are using c11 you can use the following macro to typecast strings and integers to a bigint_t:

bigint_t(11) / bigint_t("11")

***************************************

Simple example program
```
#include "bigint.h"

int main()
{
        bigint_t n = bigint_create("3022222102039492");
        bigint_t k = bigint_create("-2221929394095939200");
        bigint_t res = bigint_multiply(n, k);
        bigint_print(res);
        bigint_printf("\n*****Formatted*****\n%,S\n*******************\n", res);

        bigint_t r = bigint_create("1E6");
        bigint_printf("exponent form: %E\nnormal: %N", r, r);

        return 0;
}
```
