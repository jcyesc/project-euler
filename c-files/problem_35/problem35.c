/* Circular primes
 *
 * Problem 35
 * The number, 197, is called a circular prime because all rotations of the digits:
 * 197, 971, and 719, are themselves prime.
 *
 * There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
 *
 * How many circular primes are there below one million?
 *
 *
 * problem35.c
 *
 * Created on: Jan 15, 2014
 * Author: jcyescas
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/hash.h"
#include "../lib/list.h"
#include "../lib/util.h"


int main() {
  printf("\nCircular primes");

  int32_t limit = 1000000;
  bool sieve[limit];

  // Creating the Sieve of Erathostenes.
  sieve_eratosthenes_create(sieve, limit);
  // Creating the hash table.
  struct hash circular_primes;
  hash_init(&circular_primes, hash_long_number, compare_hash_long_number_asc, NULL);

  int32_t i;
  for (i = 2; i < limit; i++) {
    // Checking if it's a prime number and that is not in the list.
    if (sieve[i] && hash_long_number_lookup(&circular_primes, (uint64_t) i) == NULL) {
      char prime[10];
      sprintf(prime, "%d", i);
      int32_t size = strlen(prime);
      int32_t j;
      bool all_prime = true;;
      // Rotating the prime number and checks that the result of the rotation is a prime number.
      for (j = 0; j < size - 1; j++) {
        rotate_string(prime);
        int32_t tmp = atoi(prime);
        if (!sieve[tmp]) {
          all_prime = false;
          break;
        }
      }

      // If all the previous rotations were prime, add the numbers to the hash table.
      if (all_prime) {
        for (j = 0; j < size; j++) {
          rotate_string(prime);
          // Put all the numbers in the hash table.
          struct long_number *ln = malloc(sizeof(struct long_number));
          ln->number = atoi(prime);
          hash_insert(&circular_primes, &ln->hash_elem);
        }
      }
    }
  }

  int32_t number_circular = hash_size(&circular_primes);
  printf("\nThe number of circular primes below one million is %d", number_circular);

  // Release the resources from the hash table.
   hash_clear(&circular_primes, free_memory_long_number_hash);

   return 0;
}

