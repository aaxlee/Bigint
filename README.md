# Big_Integer
A big integer struct in c to support numbers larger than 2^64\n









example usage:

WARNING: there is NO error handling in this function, if the minus sign is anywhere other than index 0, it will not be accounted for
bigint_t n = bigint_create("193201293005903902300923");
bigint_t k = bigint_create("-123900952023949");

bigint_t r = bigint_multiply(n, k);
bigint_print(r)

bigint_t f = bigint_factorial(100);
bigint_print(f);
