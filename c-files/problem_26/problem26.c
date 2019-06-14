/*
 * Reciprocal cycles
 *
 * Problem 26
 *
 * A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions
 * with denominators 2 to 10 are given:
 *
 * 1/2     =       0.5
 * 1/3     =       0.(3)
 * 1/4     =       0.25
 * 1/5     =       0.2
 * 1/6     =       0.1(6)
 * 1/7     =       0.(142857)
 * 1/8     =       0.125
 * 1/9     =       0.(1)
 * 1/10    =       0.1
 *
 * Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has
 * a 6-digit recurring cycle.
 *
 * Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal
 * fraction part.
 *
 * Algorithm
 *
 * 1. Iterate from 2 to 1000.
 *   - Create a hash table
 *   - Divide the current element by 10.
 *   - If the result is greater than zero
 *         check if the result is in the hash table, if it's there,
 *         we are done processing this element and the size of the hash table must be check.
 *         If it's not, added.
 *   - Otherwise, multiply by 10 the divisor till the result is greater than zero.
 *  2. Once all the elements have been processed, check which one has the longest reciprocal cycle.
 *
 *
 * problem26.c
 *
 *  Created on: Jan 9, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../lib/hash.h"
#include "../lib/list.h"
#include "../lib/util.h"


int main() {
  printf("\nReciprocal cycles\n\n");

  int32_t limit = 1000;

  int32_t i;
  for (i = 2; i < limit; i++) {
    printf("1 / %d = ", i);

    uint32_t dividend = 10;
    while (dividend / i == 0) {
      dividend *= 10;
      printf ("0 ");
    }

    struct hash hash_decimal;
    hash_init(&hash_decimal, hash_long_number, compare_hash_long_number_asc, NULL);

    uint32_t result = dividend / i;
    uint32_t residuo = dividend % i;
    while (hash_long_number_lookup(&hash_decimal, result) == NULL) {
      printf("%u ", result);
      struct long_number *ln = malloc(sizeof (struct long_number));
      ln->number = result;
      hash_insert(&hash_decimal, &ln->hash_elem);
      result = (dividend * residuo) / i;
      residuo = (dividend * residuo) % i;
    }

    // Release the resources from the hash table.
    hash_clear(&hash_decimal, free_memory_long_number_hash);

    printf("\n");
  }

  return 0;
}

