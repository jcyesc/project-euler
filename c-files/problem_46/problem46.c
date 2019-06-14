
/*
 * Goldbach's other conjecture
 *
 * Problem 46
 *
 * It was proposed by Christian Goldbach that every odd composite number
 * can be written as the sum of a prime and twice a square.
 *
 * 9 = 7 + 2 x 1^2
 * 15 = 7 + 2 x 2^2
 * 21 = 3 + 2 x 3^2
 * 25 = 7 + 2 x 3^2
 * 27 = 19 + 2 x 2^2
 * 33 = 31 + 2 x 1^2
 *
 * It turns out that the conjecture was false.
 *
 * What is the smallest odd composite that cannot be written as the sum of a
 * prime and twice a square?
 *
 * Note: A composite number is a positive integer that has at least one positive
 * divisor other than one or the number itself. In other words, a composite
 * number is any positive integer greater than one that is not a prime number.
 *
 * How to solve it
 *
 * Composite = Prime + 2 * n ^ 2
 *
 * First create a Sieve of Eratosthenes of about 1 million (increase if the
 * composite number is not found among this range).
 * Get the first odd composite number using the Sieve of Eratosthenes.
 * Given the formula:
 *   Composite - 2 * n ^ 2 = Prime
 *
 * Try to solve this equation, if a prime number can not be found, that means
 * that we are done.
 *
 */

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/util.h"
#include "../lib/list.h"


int get_counterexample_goldbach_conjeture() {
  size_t size = 1000000;
  bool *sieve = (bool *) malloc(sizeof(bool) * size);
  sieve_eratosthenes_create(sieve, size);

  int composite;
  for (composite = 2; composite < size; composite++) {
    if (!sieve[composite] && composite % 2 != 0) {
      bool found = false;
      int n;
      for (n = 1; n < composite / 2; n++) {
        int prime = composite - 2 * (n * n);
        if (prime > 0 && sieve[prime]) {
          found = true;
          break;
        }
      }

      if (!found) {
        return composite;
      }
    }
  }


  return -1;
}


int main() {
  int composite_number = get_counterexample_goldbach_conjeture();

  printf("\nFirst composite number that is a counter example of Goldbach conjecture %d",
      composite_number);
  return 0;
}



































