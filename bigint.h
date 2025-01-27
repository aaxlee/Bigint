#ifndef BIGINT_H
#define BIGINT_H

#include <math.h>
#include <ctype.h> // for isdigit() todo: write my own

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>

#define _BIG_INT_MAX_LENGTH 512

typedef struct bigint_t {
        int data[_BIG_INT_MAX_LENGTH];
        int sign;
        int length;
} bigint_t;

// C11-specific macro for bigint_t initialization
#ifdef __STDC_VERSION__
        #if __STDC_VERSION__ >= 201112L
                #define bigint_t(value) _Generic((value), \
                        char *: bigint_create, \
                        int: bigint_int_to_bigint)(value)
        #endif
#endif

/* INITIALIZATION FUNCTIONS */
bigint_t bigint_create(char *num);
bigint_t bigint_int_to_bigint(int num);
/****************************/

/* Operations */
bigint_t bigint_multiply(bigint_t num1, bigint_t num2);
bigint_t bigint_factorial(int num);
bigint_t bigint_permutations(int n, int r);
bigint_t bigint_combinations(int n, int r);

bigint_t bigint_divide_simple(bigint_t num1, int num2);
/**************/

/* UTILITY */
// cleans up zeroes. example => 000123 becomes 123
bigint_t bigint_adjust(bigint_t num);
/************************/

/* PRINTING FUNCTIONS */
void bigint_print(bigint_t num);
void bigint_print_exponent(bigint_t num);
void bigint_print_separate(bigint_t num, char separator);

// bigint_printf() works like printf()
// NOTE: the arguments must be bigint_t
// %E => exponent form                  ex. 5.3E4
// %N => standard notation              ex. 5300
// %S => separated form
//      %S => 5,300, %.S => 5.300, %_S => 5_300 ... etc
void bigint_printf(char *format, ...);
/**********************/

/*______________________________________________________*/

bigint_t bigint_create(char *num)
{
        bigint_t n = { {0}, 1, 0 };

        if (*num == '-') {
                n.sign = -1;
                num++;
        }

        while (*num != '\0') {

                if (isdigit(*num)) {
                        n.data[n.length] = *num - '0';
                        num++;
                        n.length++;
                }

                else if (*num == 'E' || *num == 'e') {

                        int digits = 0;
                        char *ptr = num;
                        ptr++;
                        while (*ptr != '\0') {
                                digits++;
                                ptr++;
                        }
                        digits--;

                        int zeroes = 0;
                        ptr = num;
                        ptr++;
                        while (*ptr != '\0') {
                                zeroes += (*ptr - '0') * (int)pow(10, digits);
                                digits--;
                                ptr++;
                        }

                        for (int j = 0; j < zeroes; j++) {
                                n.data[n.length] = 0;
                                n.length++;

                                assert(n.length <= _BIG_INT_MAX_LENGTH && "The resulting number is too large.\n");
                        }

                        break;

                }

        }

        return n;
}

bigint_t bigint_int_to_bigint(int num)
{
        bigint_t result = { {0}, (num > 0) ? 1 : -1, 0 };
        if (num < 0) {
                num *= -1;
        }
        
        int num_len = 0;
        int n = num;
        while (n != 0) {
                n /= 10;
                num_len++;
        }

        result.length = num_len;

        for (int i = num_len - 1; i >= 0; i--) {
                int digit = num % 10;
                result.data[i] = digit;
                num /= 10;
        }

        return result;
}

bigint_t bigint_adjust(bigint_t num)
{
        int zeroes = 0;
        int i = 0;
        while (i < num.length) {
                if (num.data[i] == 0) {
                        zeroes++;
                } else {
                        break;
                }
                i++;
        }

        bigint_t result = { {0}, num.sign, num.length - zeroes };

        for (int i = zeroes; i < num.length; i++) {
                result.data[i - zeroes] = num.data[i];
        }

        return result;
}

void bigint_print(bigint_t num)
{
        if (num.sign == -1) {
                printf("-");
        }
        for (int i = 0; i < num.length; i++) {
                printf("%d", num.data[i]);
        }
        printf("\n");
}

void bigint_print_exponent(bigint_t num)
{

        if (num.sign == -1) {
                printf("-");
        }

        int last_nonzero_index = -1;
        for (int i = num.length - 1; i >= 0; i--) {
                if (num.data[i] == 0 && i - 1 >= 0) {
                        if (num.data[i - 1] != 0) {
                                last_nonzero_index = i;
                                break;
                        }
                }
        }

        printf("%d", num.data[0]);
        if (last_nonzero_index > 1) {
                printf(",");
        }

        int exponent = num.length - 1;
        for (int i = 1; i < num.length; i++) {
                if (i == last_nonzero_index) {
                        break;
                }
                printf("%d", num.data[i]);
        }
        printf("E%d", exponent);

}

void bigint_print_separate(bigint_t num, char separator)
{
        if (num.sign == -1) {
                printf("-");
        }

        int counter = 1;
        int offset;
        if ( (num.length - 1) % 3 == 0) {
                offset = 0;
        }
        if ( (num.length - 1) % 3 > 0) {
                offset = (num.length - 1) % 3;
        }
        if (num.length - 1 < 3) {
                offset = num.length;
                counter = 4;
        }
        for (int i = 0; i < num.length; i++) {
                printf("%d", num.data[i]);
                if (i == offset) {
                        printf("%c", separator);
                        counter = 0;
                        offset = 0;
                }
                if (counter == 3 && offset == 0 && i + 3 < num.length) {
                        printf("%c", separator);
                        counter = 0;
                }
                counter++;
        }
}

void bigint_printf(char *format, ...)
{
        va_list args;
        char *f_ptr = format;
        va_start(args, format);

        while (*f_ptr != '\0') {

                if (*f_ptr == '%' && *(f_ptr + 1) == 'E') {
                        f_ptr += 2;
                        bigint_t n = va_arg(args, bigint_t);
                        bigint_print_exponent(n);
                        continue;
                } else if (*f_ptr == '%' && *(f_ptr + 1) == 'N') {
                        f_ptr += 2;
                        bigint_t n = va_arg(args, bigint_t);
                        bigint_print(n);
                        continue;
                } else if (*f_ptr == '%' && *(f_ptr + 1) == 'S' ||
                                *f_ptr == '%' && *(f_ptr + 1) != ' '
                                && *(f_ptr + 2) == 'S') {
                        bigint_t n = va_arg(args, bigint_t);
                        char separator;

                        // separator becomes the character before 'S',
                        // if the character before 'S' is '%' separator becomes ','
                        int incrament;
                        if (*(f_ptr + 1) == 'S') {
                                separator = ',';
                                incrament = 2;
                        } else {
                                separator = *(f_ptr + 1);
                                incrament = 3;
                        }

                        bigint_print_separate(n, separator);
                        f_ptr += incrament;
                        continue;
                }

                printf("%c", *f_ptr);

                f_ptr++;
        }

        va_end(args);
}

// multiply two bigint_t numbers using long multiplication
bigint_t bigint_multiply(bigint_t num1, bigint_t num2)
{
        bigint_t result = { {0}, 1, 0 };
        result.length = num1.length + num2.length;
        result.sign = num1.sign * num2.sign;

        assert(result.length <= _BIG_INT_MAX_LENGTH && "The resulting number is too large.\n");

        int start = result.length - 1;
        int num1_iterations = 0;
        int offset = 0;

        for (int i = num2.length - 1; i >= 0; i--) {

                int n2 = num2.data[i];
                int carry = 0;

                for (int j = num1.length - 1; j >= 0; j--) {

                        int n1 = num1.data[j];
                        int prod = n1 * n2;
                        int sum = result.data[start - offset] + prod + carry;

                        result.data[start - offset] = sum % 10;

                        carry = sum / 10;

                        offset++;

                }
                num1_iterations++;

                offset = num1_iterations;

                if (carry > 0) {
                        result.data[i] += carry;
                }

        }

        if (result.data[0] == 0) {
                result = bigint_adjust(result);
        }

        return result;
}

bigint_t bigint_divide_simple(bigint_t num1, int num2)
{
        bigint_t result = { {0}, 1, 0 };
        result.length = num1.length;
        result.sign = num1.sign * ( (num2 > 0) ? 1 : -1 );

        int remainder = 0;
        for (int i = 0; i < num1.length; i++) {
                int n1 = num1.data[i];
                int sum = remainder * 10 + n1;
                int m = sum / num2;
                result.data[i] = m;
                remainder = sum - (m * num2);
        }

        if (result.data[0] == 0) {
                result = bigint_adjust(result);
        }

        return result;
}

bigint_t bigint_factorial(int num)
{
        bigint_t result = bigint_int_to_bigint(num);

        for (int i = num - 1; i >= 2; i--) {
                bigint_t n = bigint_int_to_bigint(i);
                result = bigint_multiply(result, n);
        }

        return result;
}

bigint_t bigint_permutations(int n, int r)
{
        bigint_t result = bigint_int_to_bigint(n);

        for (int i = n - 1; i > n - r; i--) {
                bigint_t coeff = bigint_int_to_bigint(i);
                result = bigint_multiply(result, coeff);
        }

        return result;
}

bigint_t bigint_combinations(int n, int r)
{
        bigint_t result = bigint_create("1");

        int i2 = 1;
        for (int i = n; i > n - r; i--) {
                bigint_t prod = bigint_multiply(result, bigint_int_to_bigint(i));
                result = bigint_divide_simple(prod, i2);
                i2++;
        }

        return result;
}

#endif /* BIGINT_H */
