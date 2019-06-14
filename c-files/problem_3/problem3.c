/*
 * Largest prime factor
 *
 * Problem 3
 * The prime factors of 13195 are 5, 7, 13 and 29.
 *
 * What is the largest prime factor of the number 600851475143?
 *
 * problem3.c
 *
 *  Created on: Dec 16, 2013
 *  Author: jcyescas
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../lib/util.h"

int main() {
  //9223372036854775807LL
  uint64_t number = 600851475143;
  //uint64_t number = 120;
  //uint64_t number = 997799;

  printf("Largest prime factor %llu\n", number);

  uint64_t tmp = number;
  uint64_t multiple = find_first_multiple(number);
  while (true) {

      printf("%llu ", multiple);
      if (tmp == multiple)
        break;

      tmp = tmp / multiple;
      multiple = find_first_multiple(tmp);
  }

  return 0;
}






