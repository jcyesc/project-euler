/*
 * Sum square difference
 *
 * The sum of the squares of the first ten natural numbers is,
 *
 * 1^2 + 2^2 + ... + 10^2 = 385
 *
 * The square of the sum of the first ten natural numbers is,
 *
 * (1 + 2 + ... + 10)^2 = 552 = 3025
 *
 * Hence the difference between the sum of the squares of the first ten natural numbers and
 * the square of the sum is 3025 - 385 = 2640.
 *
 * Find the difference between the sum of the squares of the first one hundred natural numbers
 * and the square of the sum.
 *
 *
 * Note: This problem can be solved in one loop, but for readability, it was done in two functions.
 *
 *
 * problem6.c
 *
 *  Created on: Dec 23, 2013
 *      Author: jcyescas
 */

#include <stdio.h>
#include <stdint.h>

/* Calculates the sum of squares of the n natural numbers:
 *
 * 1^2 + 2^2 + 3^2 + ..... + n^2
 *
 * @param n natural numbers
 */
uint64_t calculate_sum_squares(uint32_t n) {
  uint64_t sum = 0;
  uint32_t i;
  for (i = 1; i <= n; i++) {
      sum += (i * i);
  }

  return sum;
}

/* Calculates the square of the sum of the n natural numbers.
 *
 * (1 + 2 + ... + n)^2
 *
 * @param n natural numbers
 */
uint64_t calculate_square_sum(uint32_t n) {
  uint64_t result = 0;
  uint32_t i;
  for (i = 1; i <= n; i++) {
    result += i;
  }

  return result * result;
}

int main() {
  printf("Sum square differences\n");

  uint32_t n = 100;
  uint64_t sum_squares = calculate_sum_squares(n);
  uint64_t square_sum = calculate_square_sum(n);
  uint64_t result = square_sum -  sum_squares;


  printf("\nSum of squares of the %u natural numbers is: %llu", n, sum_squares);
  printf("\nSquare of the sum of the %u natural numbers is: %llu", n, square_sum);
  printf("\nDifference between the sum of the squares of the %u natural numbers\nand the square of the sum = %llu",
      n, result);

  return 0;
}

