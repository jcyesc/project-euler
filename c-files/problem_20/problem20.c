/* Factorial digit sum
 *
 * n! means n x (n - 1) x ... x 3 x 2 x 1
 *
 * For example, 10! = 10 x 9 x ... x 3 x 2 x 1 = 3628800, and the sum of the digits
 * in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.
 *
 * Find the sum of the digits in the number 100!
 *
 * problem20.c
 *
 *  Created on: Jan 1, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/biginteger.h"



int main() {
  printf("Factorial digit sum\n");

  char *value = "100";
  struct big_integer *number = big_integer_create_from_string(value);

  struct big_integer *result = big_integer_factorial(number);

  char factorial[result->size + 1];
  big_integer_to_string(result, factorial);

  printf("The factorial of %s is %s\n", value, factorial);

  int32_t i;
  uint64_t sum = 0;
  for (i = strlen(factorial) - 1; i >= 0; i--)
    sum += factorial[i] - '0';

   printf("Tsum of the digits in the number %s!: %u\n\n", value, sum);

  big_integer_destroy(number);
  big_integer_destroy(result);
}









