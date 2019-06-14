/*
 * Double-base palindromes
 *
 * Problem 36
 *
 * The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.
 *
 * Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
 *
 * (Please note that the palindromic number, in either base, may not include leading zeros.)
 *
 * problem36.c
 *
 *  Created on: Jan 20, 2014
 *      Author: jcyescas
 */


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/list.h"
#include "../lib/util.h"


int main() {
  printf("\nDouble-base palindromes\n");

  char number[8];
  int limit = 1000000;
  uint64_t total = 0;
  int i;
  for (i = 1; i <= limit; i++) {
    sprintf(number, "%d", i);
    if (is_palindromic_string(number)) {
      char *binary = convert_from_decimal_to_binary(i);
      if (is_palindromic_string(binary)) {
        printf("\n%s", number);
        total += i;
      }

      free(binary);
    }
  }

  printf("\nSum of all numbers that are palindromic in base 10 and 2: %llu", total);

  return 0;
}
