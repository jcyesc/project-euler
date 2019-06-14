/*
 * problem11.c
 *
 * Largest product in a grid
 *
 * In the 20 x 20 grid below, four numbers along a diagonal line have been marked in red.
 *
 * 08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08
 * 49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00
 * 81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65
 * 52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91
 * 22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80
 * 24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50
 * 32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70
 * 67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21
 * 24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72
 * 21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95
 * 78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92
 * 16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57
 * 86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58
 * 19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40
 * 04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66
 * 88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69
 * 04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36
 * 20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16
 * 20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54
 * 01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48
 *
 *
 * The product of these numbers is 26 x 63 x 78 x 14 = 1788696.
 *
 * What is the greatest product of four adjacent numbers in the same direction
 * (up, down, left, right, or diagonally) in the 20 x 20 grid?
 *
 *  Created on: Dec 26, 2013
 *      Author: jcyescas
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char numbers_grid[] =
    "08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08 "
    "49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00 "
    "81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65 "
    "52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91 "
    "22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80 "
    "24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50 "
    "32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70 "
    "67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21 "
    "24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72 "
    "21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95 "
    "78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92 "
    "16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57 "
    "86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58 "
    "19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40 "
    "04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66 "
    "88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69 "
    "04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36 "
    "20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16 "
    "20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54 "
    "01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48 ";

/* Converts a string of digits to an array of n digits.
 *
 * @param s string that contains the numbers.
 * @param matriz that will store the numbers
 * @param size of the matriz.
 *
 * Note:
 *
 *  We can't modify string literals (char *s). It's undefined behavior. To fix that
 *  we can make the string a local array: char s[].
 */
void convert_string_to_numbers_matriz(char s[], uint32_t matriz[][20], uint32_t size) {
  /* Add const is redundant because a string defined as char * is already a constant. */
  const char *delimeter = " ";

  uint32_t numbers = 0;
  uint32_t row = 0;
  uint32_t column = 0;
  char *number = strtok(s, delimeter);

  while(number != NULL) {

    if (numbers % 20 == 0 && numbers > 0) {
      // Increase row
      row++;
    }
    column = numbers % size;
    matriz[row][column] = (uint32_t) atoi(number);

    numbers++;
    number = strtok(NULL, delimeter);
  }
}

/* Prints a square matriz that is 20 x 20.
 *
 * @param matriz to be printed (20 x 20)
 * @param size of matriz
 */
void print_matriz(uint32_t matriz[][20], uint32_t size) {
  uint32_t i = 0;

  for (i = 0; i < size; i++) {
    uint32_t j = 0;
    for (j = 0; j < size; j++) {
      printf("%2u ", matriz[i][j]);
    }

    printf("\n");
  }
}

/**
 * Find the greatest product of four adjacent numbers in the same direction
 * (up, down, left, right, or diagonally) in the 20 x 20 grid
 */
uint32_t find_greatest_product_adjacent_numbers(uint32_t matriz[][20], uint32_t size) {
  uint32_t greates_product = 0;

  int32_t i;
  uint32_t tmp;

  // Finding the greatest product from left to right.
  for (i = 0; i < size; i++) {
    uint32_t j;
    for (j = 0; j <= (size - 4); j++) {
      tmp = matriz[i][j] * matriz[i][j + 1] * matriz[i][j + 2] * matriz[i][j + 3];

      if (tmp > greates_product) {
          greates_product = tmp;
      }
    }
  }

  // Finding the greatest product from up to down.
  for (i = 0; i < size; i++) {
    uint32_t j;
    for (j = 0; j <= (size - 4); j++) {
      tmp = matriz[j][i] * matriz[j + 1][i] * matriz[j + 2][i] * matriz[j + 3][i];

      if (tmp > greates_product) {
          greates_product = tmp;
      }
    }
  }

  // Finding the greatest product diagonally (right to left).
  for (i = 0; i < size; i++) {
    uint32_t j;
    int32_t column = i;
    for (j = 0; (column - 3) >= 0 && j <= size ; j++, column--) {
      //printf("[%u, %u] ", j, column);
      //printf("%u ", matriz[j][column]);
      tmp = matriz[j][column] * matriz[j + 1][column - 1] * matriz[j + 2][column - 2] * matriz[j + 3][column - 3];

      if (tmp > greates_product) {
        greates_product = tmp;
      }
    }

    //printf("\n");
  }

  // Finding the greatest product diagonally (left to right).
  for (i = size - 1; i >= 0; i--) {
    int32_t j;
    int32_t column = i;
    for (j = size - 1; (column + 3) < size && j >= 0 ; j--, column++) {
      //printf("[%u, %u] ", j, column);
      //printf("%u ", matriz[j][column]);
      tmp = matriz[j][column] * matriz[j - 1][column + 1] * matriz[j - 2][column + 2] * matriz[j - 3][column + 3];

      if (tmp > greates_product) {
        greates_product = tmp;
      }
    }

    //printf("\n");
  }

  return greates_product;
}

int main() {
  printf ("Largest product in a grid\n\n");

  uint32_t size = 20;
  uint32_t matriz[size][size];

  convert_string_to_numbers_matriz(numbers_grid, matriz, size);

  print_matriz(matriz, size);

  uint32_t result = find_greatest_product_adjacent_numbers(matriz, size);

  printf("\nGreatest product of four adjacent numbers is: %u ", result);

  return 0;
}
