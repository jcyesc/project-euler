/* Digit factorials
 *
 * Problem 34
 *
 * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
 *
 * Find the sum of all numbers which are equal to the sum of the factorial of their digits.
 *
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
 *
 *  Created on: Feb 20, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_DIGITS 10

void initialize_digit_factorials(int digit_factorials[]) {
  int i;
  digit_factorials[0] = 1;
  for (i = 1; i < NUMBER_DIGITS; i++) {
    digit_factorials[i] = digit_factorials[i - 1] * i;
  }
}

bool is_curious_number(int number, int digit_factorials[]) {
  // Note: as 1! = 1 and 2! = 2 are not sums they are not included.
  if (number == 1 || number == 2) {
    return false;
  }

  char value[10];
  sprintf(value, "%d", number);

  int size = strlen(value);
  int result = 0;
  int i;
  for (i = 0; i < size; i++) {
    int digit = value[i] - '0';
    result += digit_factorials[digit];
  }

  return result == number;
}

int main() {

  printf("\nDigit factorials\n");

  int digit_factorials[NUMBER_DIGITS];

  initialize_digit_factorials(digit_factorials);

  int i;
  for (i = 0; i < NUMBER_DIGITS; i++) {
    printf("\nFactorial %d! = %d", i, digit_factorials[i]);
  }

  printf("\nIs 145 a curious number? %s", is_curious_number(145, digit_factorials) ? "YES" : "NO");

  int limit =   4000000;
  int sum = 0;
  for (i = 1; i < limit ; i++) {
    if (is_curious_number(i, digit_factorials)) {
      sum += i;
      printf("\nCurious Number = %d", i);
    }
  }

  printf("\nThe sum of all numbers which are equal to the sum of the factorial"
      "of their digits is %d", sum);

  return 0;
}

