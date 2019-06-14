/*
 * Summation of primes
 *
 * Problem 10
 *
 * The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
 *
 * Find the sum of all the primes below two million.
 *
 * problem10.c
 *
 *  Created on: Dec 23, 2013
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include "../lib/util.h"

/* Adds the prime numbers that appears in the array. The Sieve of Eratosthenes has to be
 * created previously.
 *
 * @param sieve[] that contains the prime numbers.
 * @param size of the Sieve of Eratosthenes.
 * @return the sum of the prime numbers that apper in the sieve.
 */
uint64_t sieve_erotosthenes_sum_primes(bool array[], size_t size) {
  size_t i;
  uint64_t sum_primes = 0;
  for (i = 1; i < size; i++) {
    if (array[i]) {
      sum_primes += i;
    }
  }

  return sum_primes;
}


int main() {

  printf("\nSieve of Eratosthenes - Summation of primes\n");

  size_t size = 2000000;
  bool sieve[size];

  sieve_eratosthenes_create(sieve, size);

  //sieve_eratosthenes_print_primes(sieve, size, 100);

  uint64_t sum_primes = sieve_erotosthenes_sum_primes(sieve, size);

  printf("\n\nThe sum of all the primes below two million: %llu\n", sum_primes);

  return 0;
}
