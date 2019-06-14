/*
 * Largest palindrome product
 *
 * Problem 4
 *
 * A palindromic number reads the same both ways. The largest palindrome made from the
 * product of two 2-digit numbers is 9009 = 91 x 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
 *
 * problem4.c
 *
 *  Created on: Dec 19, 2013
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../lib/util.h"

/* Iterate from 999 * 999 to 100 * 100 and check if the result is palindromic number or not. If it's
 * a palindromic number, get the multiples of the number. This is the ugly part, find the numbers
 * manually. In this case the brute force algorithm works better. The reason that this decesion
 * was taken was to try to find a pattern in the multiples.
 */
int main() {
  uint32_t lower_limit = 100 * 100;
  uint32_t upper_limit = 999 * 999;

  char str[10];

  uint32_t i;
  for(i = upper_limit; i >= lower_limit; i--) {
    sprintf(str, "%u", i);
    if (is_palindromic_string(str)) {
      struct list *multiples = get_multiples((uint64_t) atoi(str));
      struct long_number *ln;
      struct list_elem *temp;

      printf ("\nMultiples of %s: ", str);
      for (temp = list_begin(multiples); temp != list_end(multiples); temp = list_next(temp)) {
        ln = list_entry(temp, struct long_number, elem);
        printf ("%llu ", ln->number);
      }
      printf("\n");

      free_memory_long_number_list(multiples);
      free(multiples);
    }
  }

  return 0;
}

