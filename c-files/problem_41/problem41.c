/*
 * Pandigital prime
 *
 * Problem 41
 *
 * We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n
 * exactly once. For example, 2143 is a 4-digit pandigital and is also prime.
 *
 * What is the largest n-digit pandigital prime that exists?
 *
 *  Created on: Feb 20, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/util.h"

int main() {
  printf("\nPandigital Prime\n");

  size_t size = 987654322;
  bool *sieve = malloc(sizeof(bool) * size);
  sieve_eratosthenes_create(sieve, size);

  char value[10];
  int i;
  for (i = size - 1; i >=0; i--) {
    if (sieve[i]) {
      sprintf(value, "%d", i);
      if(is_pandigital(value)) {
        printf("\nThe largest n-digit pandigital prime that exists is %d", i);
        break;
      }
    }
  }

  free(sieve);
  return 0;
}

