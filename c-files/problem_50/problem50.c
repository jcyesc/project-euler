/*
 * Consecutive prime sum
 *
 * Problem 50
 *
 * The prime 41, can be written as the sum of six consecutive primes:
 *
 * 41 = 2 + 3 + 5 + 7 + 11 + 13
 *
 * This is the longest sum of consecutive primes that adds to a prime below one-hundred.
 *
 *
 * The longest sum of consecutive primes below one-thousand that adds to a prime,
 * contains 21 terms, and is equal to 953.
 *
 * Which prime, below one-million, can be written as the sum of the most consecutive primes?
 *
 * problem50.c
 *
 *  Created on: Jan 7, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/util.h"

/* Counts the number of primes.
 *
 * @param sieve[] is the Sieve of Eratosthenes.
 * @param size of the Sieve of Eratosthenes.
 */
uint32_t count_number_of_primes(bool sieve[], size_t size) {
  uint32_t counter = 0;
  size_t i;
  for (i = 1; i < size; i++) {
    if (sieve[i]) {
      counter++;
    }
  }

  return counter;
}

void set_primes(bool sieve[], size_t size, uint32_t primes[]) {
  size_t i, j;
  for (i = 1, j = 0; i < size; i++) {
    if (sieve[i]) {
      primes[j] = i;
      j++;
    }
  }
}

int main() {
  printf("Consecutive prime sum\n");

  size_t size = 1000000;
  //size_t size = 1000;
  bool sieve[size];

  sieve_eratosthenes_create(sieve, size);

  uint32_t number_primes = count_number_of_primes(sieve, size);
  uint32_t primes[number_primes];

  printf("Number of primes %u\n", number_primes);
  set_primes(sieve, size, primes);

  int32_t i;
  int32_t j;

  uint32_t longest_sequence = 0;
  // The loop start in 1 because we omit the first prime number.
  for (i = 1; i < number_primes; i++) {
    uint32_t sum = 0;
    uint32_t sequence = 0;
    for (j = i; sum < size && j < number_primes; j++) {
       sum += primes[j];
       sequence++;
       if (sum < size && sieve[sum] && sequence > longest_sequence) {
         longest_sequence = sequence;
         printf("\nPrime Number %u, sequence size %u", sum, longest_sequence);
       }
    }
  }
}

