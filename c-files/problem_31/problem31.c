/*
 * Coin sums
 *
 * Problem 31
 *
 * In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:
 *
 * 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
 *
 * It is possible to make £2 in the following way:
 *
 * 1x£1 + 1x50p + 2x20p + 1x5p + 1x2p + 3x1p
 *
 * How many different ways can £2 be made using any number of coins?
 *
 * problem31.c
 *
 *  Created on: Jan 16, 2014
 *      Author: jcyescas
 */


#include <stdio.h>

#define NUMBER_COINS 8

int english_coins[NUMBER_COINS] = {1, 2, 5, 10, 20, 50, 100, 200};

/* Calculates how many different ways can £2 be made using any number of coins.
 *
 * @param value How many different ways can this value be made using any number of coins.
 * @param index of the current coin being processed.
 * @return the number of different ways the given value can be made using any number of coins.
 */
int get_number_coins_combinations(int value, int index) {
  // Base case
  if (value == 0)
    return 1;
  // Base case
  if (value < 0) {
    return 0;
  }

  int combinations = 0;
  int i = 0;
  // Recursive case
  for (i = index; i < NUMBER_COINS; i++) {
    combinations += get_number_coins_combinations(value - english_coins[i], i);
  }

  return combinations;
}

/* Calculates how many different ways can £2 be made using any number of coins.
 *
 * @param value How many different ways can this value be made using any number of coins.
 * @return the number of different ways the given value can be made using any number of coins.
 */
int get_coins_combinations(int value) {
  return get_number_coins_combinations(value, 0);
}

int main() {
  printf("\nCoin sums");

  int combinations = get_coins_combinations(200);
  printf("\nThe different ways can £2 be made using any number of coins are %d\n", combinations);

  return 0;
}
