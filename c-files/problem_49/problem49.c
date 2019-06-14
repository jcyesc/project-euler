/*
 * Prime permutations
 *
 * Problem 49
 *
 * The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330,
 * is unusual in two ways: (i) each of the three terms are prime, and, (ii) each of the 4-digit
 * numbers are permutations of one another.
 *
 * There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes,
 * exhibiting this property, but there is one other 4-digit increasing sequence.
 *
 * What 12-digit number do you form by concatenating the three terms in this sequence?
 *
 * ==========
 * Algorithm
 * ==========
 *
 * Create the sieve of erathostenes from 1 to 10000.
 * Get all the prime numbers from 1000 to 9999.
 * For each prime number, permutate that prime and check that at least two of then are primes.
 *   - If this is true, the number was found, otherwise, continue iterating.
 *
 * problem49.c
 *
 *  Created on: Jan 11, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/util.h"
#include "../lib/list.h"

/* Count the number of prime numbers that are in the list.
 *
 * @param permutations is the list of permutations.
 * @param sieve is the Sieve of Eratoshenes.
 * @return the number of primes numbers that were found in the list.
 */
int32_t count_prime_numbers(struct list *permutations, bool sieve[]) {
  struct string_obj *str;
  struct list_elem *temp;

  int32_t primes = 0;
  for (temp = list_begin(permutations); temp != list_end(permutations); temp = list_next(temp)) {
    str = list_entry(temp, struct string_obj, elem);
    int32_t number = atoi(str->string);
    if (sieve[number]) {
        primes++;
    }
  }

  return primes;
}

/* Prints the prime numbers that are in the list and that are greater than the given prime number.
 *
 * @param list_numbers contains the list of struct string_obj.
 * @param sieve is the Sieve of Eratosthenes.
 */
void print_prime_numbers_sequence(int32_t prime, int32_t sequence_difference) {
  printf("%d %d %d", prime, prime + sequence_difference, prime + (2 * sequence_difference));
}

/* Returns the difference if the sequence of three consecutive primes is found, otherwise, it
 * returns 0.
 *
 * @param prime number that will be analized to see if there is a sequence.
 * @param ptr_list is the list of permutations of the given prime number.
 * @param sieve is the Sieve of Eratosthenes.
 */
int32_t get_arithmetic_sequence_difference(int32_t prime, struct list *ptr_list, bool sieve[]) {
  int32_t sequence_difference = 0;
  struct hash hash_numbers;
  hash_init(&hash_numbers, hash_long_number, compare_hash_long_number_asc, NULL);

  // Putting all the prime numbers in the hash so they can be search fast.
  struct string_obj *str;
  struct list_elem *temp;
  for (temp = list_begin(ptr_list); temp != list_end(ptr_list); temp = list_next(temp)) {
    str = list_entry(temp, struct string_obj, elem);
    int32_t number = atoi(str->string);
    if (sieve[number] && number > prime) {
      struct long_number *ln = malloc(sizeof (struct long_number));
      ln->number = (uint64_t) number;
      hash_insert(&hash_numbers, &ln->hash_elem);
    }
  }

  // Search for the sequence, iterate through the permutations list.
  uint64_t difference = 0;
  for (temp = list_begin(ptr_list); temp != list_end(ptr_list); temp = list_next(temp)) {
     str = list_entry(temp, struct string_obj, elem);
     int32_t number = atoi(str->string);
     if (sieve[number]) {
       difference = (uint64_t) (number - prime);
       int32_t next_number = number + difference;
       // Search for the next element in the sequence.
       struct long_number *ln = hash_long_number_lookup(&hash_numbers, next_number);
       if (ln != NULL) {
          // The sequence was found.
          sequence_difference = difference;
          break;
       }
     }
   }

  // Release the resources from the hash table.
  hash_clear(&hash_numbers, free_memory_long_number_hash);

  return sequence_difference;
}

int main() {
  printf("\nPrime permutations");

  int32_t size = 10000;
  bool sieve[size];
  char prime[7];

  // Creating Sieve of Eratosthenes.
  sieve_eratosthenes_create(sieve, size);

  int32_t i;
  for (i = 1000; i < size; i++) {
    if (sieve[i]) {
      sprintf(prime, "%d", i);
      // Getting the permutations for the given prime number.
      struct list *permutations = permutate_string(prime);
      // Counting the number of prime numbers.
      int32_t primes = count_prime_numbers(permutations, sieve);
      if (primes > 1) {
        // Getting the arithmetic difference.
        int32_t sequence_difference = get_arithmetic_sequence_difference(i, permutations, sieve);
        if (sequence_difference != 0) {
          printf("\nPrime: %d :", i);
          // Printing sequence.
          print_prime_numbers_sequence(i, sequence_difference);
        }
      }
      free_memory_string_obj_list(permutations);
      free(permutations);
    }
  }
}

