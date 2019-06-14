/*
 *
 * Pandigital multiples
 *
 * Problem 38
 *
 * Take the number 192 and multiply it by each of 1, 2, and 3:
 *
 * 192 x 1 = 192
 * 192 x 2 = 384
 * 192 x 3 = 576
 *
 * By concatenating each product we get the 1 to 9 pandigital, 192384576.
 * We will call 192384576 the concatenated product of 192 and (1,2,3)
 *
 * The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4, and 5, giving the
 * pandigital, 918273645, which is the concatenated product of 9 and (1,2,3,4,5).
 *
 * What is the largest 1 to 9 pandigital 9-digit number that can be formed as the concatenated
 * product of an integer with (1,2, ... , n) where n > 1?
 *
 * problem38.c
 *
 *  Created on: Jan 23, 2014
 *      Author: jcyescas
 */


#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "../lib/util.h"

int main() {
  printf("\nPandigital multiples");


  int64_t greatest_pandigital = 0;
  int i;
  for (i = 9000; i <= 9999; i++) {
    char pandigital[50];
    pandigital[0] = '\0';
    int j;
    for (j = 1; j < 10; j++) {
      int result = i * j;
      char partial[20];
      sprintf(partial, "%d", result);
      strcat(pandigital, partial);
      int size = strlen(pandigital);

      if (size > 9) {
        break;
      }

      if (is_pandigital(pandigital)) {
        printf("\n%s", pandigital);
        if (greatest_pandigital < atoll(pandigital)) {
          greatest_pandigital = atoll(pandigital);
        }

      }
    }
  }

  printf("\n\nThe greatest pandigital number is %llu", greatest_pandigital);


  return 0;
}
