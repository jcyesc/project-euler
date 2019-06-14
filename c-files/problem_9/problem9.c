/*
 * A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
 *
 * a^2 + b^2 = c^2
 *
 * For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
 *
 * There exists exactly one Pythagorean triplet for which a + b + c = 1000.
 *
 * Find the product a * b * c.
 *
 *
 * problem9.c
 *
 *  Created on: Dec 25, 2013
 *      Author: jcyescas
 */

#include <math.h>
#include <stdio.h>
#include <stdint.h>


int main() {
  printf("Special Pythagorean triplet\n");

  uint32_t a;
  uint32_t b;
  for (a = 0; a <= 1000; a++) {
    for (b = 0; b <= 1000; b++) {
      if (a > b)
        continue;

      uint32_t c = (uint32_t) sqrt(pow(a, 2) + pow(b, 2));
      uint32_t result = a + b + c;
      if (result == 1000 &&
          (pow(a, 2) + pow(b, 2)) == pow(c, 2) &&
          a < b && b <c) {
          printf("a = %u, b = %u, c = %u, (a * b * c) = %u\n", a, b, c, (a * b * c));
      }
    }
  }

  return 0;
}

