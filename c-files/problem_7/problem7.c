/*
 * 10001st prime
 *
 * Problem 7
 *
 * By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13,
 * we can see that the 6th prime is 13.
 *
 * What is the 10 001st prime number?
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "../lib/util.h"

int main() {

  printf("\nSieve of Eratosthenes\n");

  size_t number_prime = 10002;
  size_t size = 2000000;
  bool sieve[size];

  sieve_eratosthenes_create(sieve, size);
  sieve_eratosthenes_print_primes(sieve, size, 100);

  size_t prime = sieve_eratosthenes_get_prime(sieve, size, number_prime);
  printf("\n\nThe prime number %llu is: %llu", number_prime, prime);

  return 0;
}
