/* Self powers
 *
 * Problem 48
 *
 * The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
 *
 * Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.
 *
 * problem48.c
 *
 *  Created on: Jan 12, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/biginteger.h"
#include "../lib/list.h"
#include "../lib/util.h"

int main() {
  printf("\nSelf powers");

  struct big_integer *result = big_integer_create_from_string("0");

  int32_t i;
  for (i = 1000; i >= 1; i--) {
    //printf("\nProcessing %d ^ %d", i, i);
    char number[6];
    sprintf(number, "%d", i);
    struct big_integer *tmp = big_integer_create_from_string(number);
    struct big_integer *subtotal = big_integer_pow(tmp, tmp);
    struct big_integer *total = big_integer_add(result, subtotal);

    // Releasing resources
    big_integer_destroy(tmp);
    big_integer_destroy(subtotal);
    big_integer_destroy(result);

    result = total;
  }

  char sum[result->size + 1];
  big_integer_to_string(result, sum);
  printf("\nThe result is:\n%s\n\n", sum);

  // Releasing resources.
  big_integer_destroy(result);

  return 0;
}
