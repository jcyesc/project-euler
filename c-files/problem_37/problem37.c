/*
 * Truncatable primes
 *
 * Problem 37
 *
 * The number 3797 has an interesting property. Being prime itself, it is possible to continuously
 * remove digits from left to right, and remain prime at each stage: 3797, 797, 97, and 7. Similarly
 * we can work from right to left: 3797, 379, 37, and 3.
 *
 *
 * Find the sum of the only eleven primes that are both truncatable from left to right and right
 * to left.
 *
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
 *
 * problem37.c
 *
 *  Created on: Jan 18, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/util.h"


/* Returns true if the value is truncatable from left to right, and remain prime at each stage.
 *
 * Example: 3797, 797, 97, and 7
 *
 * @param num to be tested.
 * @param sieve of Eratosthenes.
 * @return true if truncatable from left to right, otherwise false.
 */
bool is_truncatable_from_left_to_right(int num, bool sieve[]) {
  char number[10];
  sprintf(number, "%d", num);

  char tmp_number[10];
  int i;
  int size = strlen(number);
  for (i = 0; i < size; i++) {
    sprintf(tmp_number, "%s", number + i);
    // printf("\n%s", tmp_number);
    if (!sieve[atoi(tmp_number)]) {
      return false;
    }
  }

  return true;
}

/* Returns true if the value is truncatable from right to left, and remain prime at each stage.
 *
 * Example: 3797, 379, 37, and 3.
 *
 * @param num to be tested.
 * @param sieve of Eratosthenes.
 * @return true if truncatable from left to right, otherwise false.
 */
bool is_truncatable_from_right_to_left(int num, bool sieve[]) {
  char number[10];
  sprintf(number, "%d", num);

  int i;
  int size = strlen(number);
  for (i = size - 1; i >= 0; i--) {
    // printf("\n%s", number);
    if (!sieve[atoi(number)]) {
      return false;
    }

    number[i] = '\0';
  }

  return true;
}

/* Returns true if the prime number is truncatable from left to right and right to left.
 *
 * @param number is the prime number that would be analized.
 * @param sieve of Eratosthenes.
 */
bool is_prime_truncatable(int number, bool sieve[]) {
  return is_truncatable_from_left_to_right(number, sieve) &&
      is_truncatable_from_right_to_left(number, sieve);
}

int main() {
  printf("\nTruncatable primes");
  int size_sieve = 1000000;
  bool sieve[size_sieve];
  sieve_eratosthenes_create(sieve, size_sieve);

  int i;
  int counter = 0;
  int sum = 0;
  for (i = 10; i < size_sieve && counter < 12; i++) {
    if (sieve[i] && is_prime_truncatable(i, sieve)) {
      counter++;
      sum += i;
      printf("\nTruncatable prime: %d", i);
    }
  }

  printf("\nThe sum of the only element primes that are both"
            "truncatable from left to right and right to left is: %d", sum);

  return 0;
}



