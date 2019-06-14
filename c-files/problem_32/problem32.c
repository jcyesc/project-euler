/*
 *
 * Pandigital products
 *
 * Problem 32
 *
 * We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n
 * exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.
 *
 * The product 7254 is unusual, as the identity, 39 x 186 = 7254, containing multiplicand,
 * multiplier, and product is 1 through 9 pandigital.
 *
 * Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1
 * through 9 pandigital.
 *
 * HINT: Some products can be obtained in more than one way so be sure to only include it once in
 * your sum.
 *
 * problem32.c
 *
 *  Created on: Jan 22, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/hash.h"
#include "../lib/util.h"


int main() {
  printf("\nPandigital products");

  struct hash numbers;
  hash_init(&numbers, hash_long_number, compare_hash_long_number_asc, NULL);

  int total = 0;
  int i;
  for (i = 1; i <= 999; i++) {
    int j;
    for (j = i + 1; j <= 9999; j++) {
      int result = i * j;
      char value[25];
      sprintf(value, "%d%d%d", i, j, result);
      if (hash_long_number_lookup(&numbers, result) == NULL && strlen(value) == 9 && is_pandigital(value)) {
        total+= result;
        printf("\n%d x %d = %d", i, j, result);
        struct long_number *ln = malloc(sizeof(struct long_number));
        ln->number = result;
        hash_insert(&numbers, &ln->hash_elem);
      }
    }
  }

  printf("\nThe sum of all products whose multiplicand/multiplier/product identiy"
      "can be written as a 1 through 9 panditial is %d", total);

  // Releasing the resources from the hash_table.
  hash_clear(&numbers, free_memory_long_number_hash);
  return 0;
}
