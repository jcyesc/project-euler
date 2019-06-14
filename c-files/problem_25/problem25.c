/*
 * 1000-digit Fibonacci number
 *
 * Problem 25
 *
 * The Fibonacci sequence is defined by the recurrence relation:
 *
 * Fn = Fn-1 + Fn-2, where F1 = 1 and F2 = 1.
 *
 * Hence the first 12 terms will be:
 *
 * F1 = 1
 * F2 = 1
 * F3 = 2
 * F4 = 3
 * F5 = 5
 * F6 = 8
 * F7 = 13
 * F8 = 21
 * F9 = 34
 * F10 = 55
 * F11 = 89
 * F12 = 144
 * The 12th term, F12, is the first term to contain three digits.
 *
 * What is the first term in the Fibonacci sequence to contain 1000 digits?
 *
 * problem25.c
 *
 *  Created on: Jan 3, 2014
 *      Author: jcyescas
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/biginteger.h"

/* Gets the first Fibonnaci term that contains num_digits.
 *
 * @param num_digits that the Fibonnaci term will have.
 * @return the first Fibonnaci term that contains num_digits.
 */
uint32_t get_fibonnaci_term(uint32_t num_digits) {
  struct big_integer *first = big_integer_create_from_string("1");
  struct big_integer *second = big_integer_create_from_string("1");
  struct big_integer *tmp;

  uint32_t term = 1;
  while (first->size < num_digits) {
      term++;
      tmp = second;
      second = big_integer_add(first, second);
      big_integer_destroy(first);
      first = tmp;
  }

  char number[first->size + 1];
  big_integer_to_string(first, number);

  printf("Term %u, Fibonnaci number: %s", term, number);
  big_integer_destroy(first);
  big_integer_destroy(second);

  return term;
}



int main() {
  printf("1000-digit Fibonacci number\n");

  uint32_t num_digits = 3;
  uint32_t term = get_fibonnaci_term(num_digits);
  printf("\nThe first Fibonnaci term that contains %u digits is %u\n\n", num_digits, term);

  num_digits = 1000;
  term = get_fibonnaci_term(num_digits);
  printf("\nThe first Fibonnaci term that contains %u digits is %u\n", num_digits, term);

}

