#ifndef BIGINT_H
#define BIGINT_H

#define _BIG_INT_MAX_LENGTH 500

typedef struct bigint_t {
        int number[_BIG_INT_MAX_LENGTH];
        int sign;
        int length;
} bigint_t;

bigint_t bigint_create(char *num);
// TODO: uh rename
bigint_t bigint_itbi(int num);
void bigint_print(bigint_t num);
void bigint_format_print(bigint_t num);
bigint_t bigint_multiply(bigint_t num1, bigint_t num2);
// TODO: redo this
bigint_t bigint_factorial(int num);

// modulo implementation: https://www.youtube.com/watch?v=2kUP9HcJwD4

// creates a bigint_t using a string
bigint_t bigint_create(char *num)
{
        bigint_t n = { {0}, 1, 0 };

        if (*num == '-') {
                n.sign = -1;
                num++;
        }

        int index = 0;
        while (*num != '\0') {
                n.number[index] = *num - '0';
                num++;
                index++;
        }
        n.length = index;

        return n;
}

// converts an int to a bigint_t, (itbi = int to bigint)
bigint_t bigint_itbi(int num)
{
        bigint_t result = { {0}, 1, 0 };
        
        int num_len = 0;
        int n = num;
        while (n > 0) {
                n /= 10;
                num_len++;
        }

        result.length = num_len;

        for (int i = num_len - 1; i >= 0; i--) {
                int digit = num % 10;
                result.number[i] = digit;
                num /= 10;
        }

        return result;
}

void bigint_print(bigint_t num)
{
        if (num.sign == -1) {
                printf("-");
        }
        for (int i = 0; i < num.length; i++) {
                printf("%d", num.number[i]);
        }
        printf("\n");
}


void bigint_format_print(bigint_t num)
{

}

// multiply two bigint_t numbers using long multiplication
bigint_t bigint_multiply(bigint_t num1, bigint_t num2)
{
        bigint_t result = { {0}, 1, 0 };
        result.length = num1.length + num2.length;
        result.sign = num1.sign * num2.sign;

        int start = result.length - 1;
        int num1_iterations = 0;
        int offset = 0;

        for (int i = num2.length - 1; i >= 0; i--) {

                int n2 = num2.number[i];
                int carry = 0;

                for (int j = num1.length - 1; j >= 0; j--) {

                        int n1 = num1.number[j];
                        int prod = n1 * n2;
                        int sum = result.number[start - offset] + prod + carry;

                        result.number[start - offset] = sum % 10;

                        carry = sum / 10;

                        offset++;

                }
                num1_iterations++;

                offset = num1_iterations;

                if (carry > 0) {
                        result.number[i] += carry;
                }

        }

        if (result.number[0] == 0) {
                bigint_t adjusted_result = { {0}, result.sign, result.length - 1 };
                for (int i = 1; i < result.length; i++) {
                        adjusted_result.number[i - 1] = result.number[i];
                }
                return adjusted_result;
        }

        return result;
}

bigint_t bigint_factorial(int num)
{
        bigint_t result = bigint_itbi(num);

        for (int i = num - 1; i >= 2; i--) {
                bigint_t n = bigint_itbi(i);
                result = bigint_multiply(result, n);
        }

        return result;
}

#endif /* BIGINT_H */ 
