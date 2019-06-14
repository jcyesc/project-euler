/*
 * Amicable numbers
 *
 * Problem 21
 *
 * Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly
 * into n).
 *
 * If d(a) = b and d(b) = a, where a ­ b, then a and b are an amicable pair and each of a and b are
 * called amicable numbers.
 *
 *
 * For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110;
 * therefore d(220) = 284. The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
 *
 *
 * Evaluate the sum of all the amicable numbers under 10000.
 *
 * ==========
 * Algorithm
 * ==========
 *
 * 1. Create a Sieve of Eratosthenes of size 10000.
 * 2. Iterate from 1 to 10000
 *      - If the number is prime, continue
 *      - If not prime, then get the proper divisors for that number and add them, then, get the proper
 *      divisors of the result of the sum and add them. If the number that is currently being processed
 *      is equal to the second sum, then is an amicable number and should be added to the great total.
 *
 * problem21.c
 *
 *  Created on: Jan 7, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/list.h"
#include "../lib/util.h"

/* Removes the last element from the list and release the memory.
 *
 * @param list_ptr is a pointer to a list of struct long_number elements.
 */
void remove_last_element(struct list *list_ptr) {
  struct list_elem *last_elem = list_pop_back(list_ptr);
  struct long_number *ln = list_entry(last_elem, struct long_number, elem);
  free(ln);
}


/* Returns true if it's an amicable number, otherwise it returns false.
 *
 * @param
 */
bool is_amicable(uint64_t number) {

  struct list *list_mult;
  uint64_t sum1;

  list_mult= get_distinct_multiples(number);
  // Remove the last element which is the given number.
  remove_last_element(list_mult);
  sum1 = list_add_elements(list_mult);

  // Releasing resources.
  free_memory_long_number_list(list_mult);
  free(list_mult);

  if (number != sum1) {
    list_mult = get_distinct_multiples(sum1);

    // Remove the last element which is the given number.
    remove_last_element(list_mult);
    uint64_t sum2 = list_add_elements(list_mult);

    // Releasing resources.
    free_memory_long_number_list(list_mult);
    free(list_mult);

    if (number == sum2) {
       return true;
     }
  }

  return false;
}


int main() {
  printf("Amicable numbers\n");

  int32_t size = 10000;
  bool sieve[size];
  int64_t total = 0;

  sieve_eratosthenes_create(sieve, size);
  //sieve_eratosthenes_print_primes(sieve, size, 100);

  int32_t i;
  for (i = 1; i <= size; i++) {
    // If it's not prime, check if it's amicable.
    if (!sieve[i] && is_amicable(i)) {
      printf("\nAmicable: %d", i);
      total += i;
    }
  }

  printf("\nThe sum of all the amicable numbers under %d is : %llu.", size, total);
}


