/*
 * Power digit sum
 *
 * Problem 16
 *
 * 2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.
 *
 * What is the sum of the digits of the number 2^1000?
 *
 * problem16.c
 *
 *  Created on: Dec 29, 2013
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/biginteger.h"

int main() {
  printf("Power digit sum\n");

  struct big_integer *b1 = big_integer_create_from_string("2");
  struct big_integer *b2 = big_integer_create_from_string("1000");

  struct big_integer *result = big_integer_pow(b1, b2);


  char number[result->size + 1];
  big_integer_to_string(result, number);

  printf("The result of 2 ^ 1000 is:  %s\n", number);

  int32_t i;
  uint64_t sum = 0;
  for (i = strlen(number) - 1; i >= 0; i--)
    sum += number[i] - '0';

  printf("The sum of the digits of the number 2 ^ 1000 is: %u\n\n", sum);

  big_integer_destroy(b1);
  big_integer_destroy(b2);
  big_integer_destroy(result);

}
