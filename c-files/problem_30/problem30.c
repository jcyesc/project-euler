/* Digit fifth powers
 *
 * Problem 30
 *
 * Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
 *
 * 1634 = 1^4 + 6^4 + 3^4 + 4^4
 * 8208 = 8^4 + 2^4 + 0^4 + 8^4
 * 9474 = 9^4 + 4^4 + 7^4 + 4^4
 *
 * As 1 = 1^4 is not a sum it is not included.
 *
 * The sum of these numbers is 1634 + 8208 + 9474 = 19316.
 *
 * Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
 *
 * problem30.c
 *
 *  Created on: Jan 15, 2014
 *      Author: jcyescas
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


int32_t char_to_number(char c) {
  return c - '0';
}

int64_t find_sum_fifth_powers() {
  int32_t powers[10];
  int32_t i;
  for (i = 0; i < 10; i++) {
    powers[i] = pow(i, 5);
  }

  int64_t total = 0;
  int32_t limit = 5 * pow(9, 5); // Limit of the Narcissistic Number is 5 * (9 ^ 5);
  for (i = 2; i <= limit; i++) {
    char str[7];
    sprintf(str, "%d", i);
    int32_t tmp = 0;
    int32_t size = strlen(str);

    int32_t j;
    for (j = 0; j < size; j++) {
      tmp += powers[char_to_number(str[j])];
    }

    if (tmp == i) {
      printf("\n%i", i);
      total += i;
    }
  }

  return total;
}


int main() {
  printf("\nDigit fifth powers");

  int64_t total = find_sum_fifth_powers();
  printf("\nThe sum of all the numbers that can be written as the sum of "
      "fifth powers of their digits is: %llu", total);

  return 0;
}

