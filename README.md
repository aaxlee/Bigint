# Bigint
big integer implementation in c









example usage:

WARNING: there is NO error handling / checks if the input string is a "valid" number in the bigint_create() function



bigint_t n = bigint_create("193201293005903902300923");

bigint_t k = bigint_create("-123900952023949");

bigint_t r = bigint_multiply(n, k);

bigint_print(r);

bigint_t f = bigint_factorial(100);

bigint_print(f);
