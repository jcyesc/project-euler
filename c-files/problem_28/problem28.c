/*
 * Number spiral diagonals
 *
 * Problem 28
 *
 * Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is
 * formed as follows:
 *
 * 21 22 23 24 25
 * 20  7  8  9 10
 * 19  6  1  2 11
 * 18  5  4  3 12
 * 17 16 15 14 13
 *
 * It can be verified that the sum of the numbers on the diagonals is 101.
 *
 * What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
 *
 * problem28.c
 *
 *  Created on: Jan 14, 2014
 *      Author: jcyescas
 */

#include <stdint.h>
#include <stdio.h>

int main() {
  printf("\nNumber spiral diagonals\n");

  int32_t limit = 1001 * 1001;
  int64_t total = 0;
  int32_t i, j;
  int32_t step;

  for (j = 0, i = 1, step = 0; i <= limit; j++, i = i + step) {
    total += i;

    printf("%d ", i);
    if (j % 4 == 0) {
      step += 2;
    }
  }

  printf("\nThe sum of the numbers one the diagonals is %llu", total);
  return 0;
}
