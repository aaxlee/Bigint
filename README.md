# Bigint

C library that can handle integers larger than unsigned long long

Features
- No heap allocations
- Supports large integers up to 1024 digits (Modifyable via _BIG_INT_MAX_LENGTH)
- ***Moderate*** error handling
- Operations: Multiplication, Permutations, Combinations, Comparisons
- Utility: Formatted printing (Exponential notation, Digit separation)

***************************************

Simple example program
```C
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

Solution to problem 20 on projecteuler.net with Bigint
```C
#include <stdio.h>

#include "bigint.h"

/* Factorial Digit Sum
 * Problem 20
 * n! means n x (n-1) x ... x 3 x 2 x 1.
 * For example, 10! = 10 x 9 x ... x 3 x 2 x 1 = 3628800,
 * and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
 * Find the sum of the digits in the number 100!. */

int main()
{
        bigint_t n = bigint_factorial(100);

        int sum = 0;
        for (int i = 0; i < n.length; i++) {
                sum += n.data[i];
        }

        printf("The digit sum of 100! is %d.\n", sum);
        // output: 648

        return 0;
}
```
