/* Problem 1
 *
 * If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9.
 * The sum of these multiples is 23.
 *
 * Find the sum of all the multiples of 3 or 5 below 1000.
 *
 * Result: 233168
 *
 * main.c
 *
 *  Created on: Dec 16, 2013
 *      Author: jcyescas
 */

#include <stdio.h>
#include <stdint.h>


/**
 * Adds the multiples of 3 or 5 below ranges.
 *
 * @param range is the limit till the multiples of 3 or 5 will be added.
 */
uint32_t sum_multiples(uint32_t range) {

  uint32_t sum = 0;
  uint32_t index;
  for (index = 1; index < range; index++) {
      if (index % 3 == 0 || index % 5 == 0) {
          sum += index;
      }
  }
  return sum;
}


int main() {
  printf("Problem 1: Find the sum of all the multiples of 3 or 5 below 1000.\n");

  uint32_t sum = sum_multiples(1000);
  printf("Result: %u\n", sum);
}









