# Bigint

stores each digit of a long number in an array where the first digit of the number is at index 0 in the array

if you are using c11 you can use the following macro to typecast strings and integers to a bigint_t:

bigint_t(11) / bigint_t("11")


example usage of some useful functions:

WARNING: there is little to no error handling, use at your own risk

bigint_t n = bigint_create("193201293005903902300923");

bigint_t k = bigint_create("-123900952023949");

bigint_t r = bigint_multiply(n, k);

bigint_print(r);

bigint_t f = bigint_factorial(100);

bigint_print(f);
