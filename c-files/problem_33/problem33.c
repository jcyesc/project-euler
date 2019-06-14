/*
 * Digit canceling fractions
 *
 * Problem 33
 *
 * The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to
 * simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling
 * the 9s.
 *
 * We shall consider fractions like, 30/50 = 3/5, to be trivial examples.
 *
 * There are exactly four non-trivial examples of this type of fraction, less than one in value,
 * and containing two digits in the numerator and denominator.
 *
 * If the product of these four fractions is given in its lowest common terms, find the value of
 * the denominator.
 *
 * problem33.c
 *
 *  Created on: Jan 22, 2014
 *      Author: jcyescas
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main() {
  printf("\nDigit canceling fractions");

  int i;
  for (i = 10; i <= 99; i++) {
    int j;
    for (j = i + 1; j <= 99; j++) {
      char value1[3];
      char value2[3];
      sprintf(value1, "%d", i);
      sprintf(value2, "%d", j);
      int digit1 = value1[0] - '0';
      int digit2 = value2[1] - '0';

      if (value1[1] == value2[0] && ((double) i/j == (double) digit1/digit2 )) {
        printf("\n%d/%d = %d/%d", i, j, digit1, digit2);
      }
    }
  }
}

