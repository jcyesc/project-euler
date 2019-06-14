/*
 *
 * Champernowne's constant
 *
 * Problem 40
 *
 * An irrational decimal fraction is created by concatenating the positive integers:
 *
 * 0.123456789101112131415161718192021...
 *
 * It can be seen that the 12th digit of the fractional part is 1.
 *
 * If dn represents the nth digit of the fractional part, find the value of the following expression.
 *
 * d1 x d10 x d100 x d1000 x d10000 x d100000 x d1000000
 *
 * problem40.c
 *
 *  Created on: Jan 23, 2014
 *      Author: jcyescas
 */

#include <stdio.h>
#include <string.h>

int main() {
  printf("Champernowne's constant");

  int size = 1000000;
  char fraction[size + 1]; //
  fraction[0] = '\0';

  int i;
  for (i = 1; i <= size; i++) {
    char number[8];
    sprintf(number, "%d", i);
    if ((strlen(number) + strlen(fraction)) > size) {
      break;
    }

    strcat(fraction, number);
  }

  //printf("\n%s", fraction);
  int total = 1;
  for (i = 1; i < size; i*= 10) {
    printf("\n%c", fraction[i - 1]);
    total *= fraction[i - 1] - '0';
  }

  printf("\nThe value of the expression is %d", total);

  return 0;
}
