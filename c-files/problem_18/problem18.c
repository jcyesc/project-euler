/*
 * Maximum path sum I
 *
 * Problem 18
 * By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.
 *
 * 3
 * 7 4
 * 2 4 6
 * 8 5 9 3
 *
 * That is, 3 + 7 + 4 + 9 = 23.
 *
 * Find the maximum total from top to bottom of the triangle below:
 *
 * 75
 * 95 64
 * 17 47 82
 * 18 35 87 10
 * 20 04 82 47 65
 * 19 01 23 75 03 34
 * 88 02 77 73 07 63 67
 * 99 65 04 28 06 16 70 92
 * 41 41 26 56 83 40 80 70 33
 * 41 48 72 33 47 32 37 16 94 29
 * 53 71 44 65 25 43 91 52 97 51 14
 * 70 11 33 28 77 73 17 78 39 68 17 57
 * 91 71 52 38 17 14 91 43 58 50 27 29 48
 * 63 66 04 68 89 53 67 30 73 16 69 87 40 31
 * 04 62 98 27 23 09 70 98 73 93 38 53 60 04 23
 *
 * NOTE: As there are only 16384 routes, it is possible to solve this problem by trying every route.
 * However, Problem 67, is the same challenge with a triangle containing one-hundred rows;
 * it cannot be solved by brute force, and requires a clever method! ;o)
 *
 * problem18.c
 *
 *  Created on: Jan 7, 2014
 *      Author: jcyescas
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/*
int32_t matrix[4][4] = {
    {3, 0, 0, 0},
    {7, 4, 0, 0},
    {2, 4, 6, 0},
    {8, 5, 9, 3}
};
*/

int32_t matrix[15][15] = {
  {75,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {95, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {17, 47, 82,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {18, 35, 87, 10,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {20,  4, 82, 47, 65,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {19,  1, 23, 75,  3, 34,  0,  0,  0,  0,  0,  0,  0,  0,  0},
  {88,  2, 77, 73,  7, 63, 67,  0,  0,  0,  0,  0,  0,  0,  0},
  {99, 65,  4, 28,  6, 16, 70, 92,  0,  0,  0,  0,  0,  0,  0},
  {41, 41, 26, 56, 83, 40, 80, 70, 33,  0,  0,  0,  0,  0,  0},
  {41, 48, 72, 33, 47, 32, 37, 16, 94, 29,  0,  0,  0,  0,  0},
  {53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,  0,  0,  0,  0},
  {70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,  0,  0,  0},
  {91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,  0,  0},
  {63, 66,  4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,  0},
  { 4, 62, 98, 27, 23,  9, 70, 98, 73, 93, 38, 53, 60,  4, 23},
};

/* Initializes all the elements of the matrix to zero.
 *
 * Note: A 2D array is flatten to a 1D array by the compiler. If we don't want to receive a 2D
 *  array as a 1D array, we need to pass the columns in the array declaration like this:
 *  array[][NCOLUMNS].
 *
 * @param ptr_matrix is a pointer to the matrix that will be initialized.
 * @param size of the matrix
 */
void matrix_initialize(int32_t *ptr_matrix[], int32_t size) {
  int32_t *p = (int32_t *) ptr_matrix;

  int32_t i;
  int32_t j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      p[j] = 0;
    }
    p = p + size;
  }
}

/* Prints the elements of the matrix.
 *
 * Note: A 2D array is flatten to a 1D array by the compiler. If we don't want to receive a 2D
 *    array as a 1D array, we need to pass the columns in the array declaration like this:
 *    array[][NCOLUMNS].
 *
 * @param ptr_matrix is the pointer to the matrix.
 * @param size of the matrix.
 */
void matrix_print(int32_t *ptr_matrix[], int32_t size) {
  int32_t *p = (int32_t *) ptr_matrix;

  int32_t i;
  int32_t j;
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      printf("%4d ", p[j]);
    }

    printf("\n");
    p = p + size;
  }
}

/*
3
7 4
2 4 6
8 5 9 3
*/

int main() {
  printf("Maximum path sum I\n");

  int32_t size = 15;

  matrix_print(matrix, size);

  int32_t result[size][size];

  matrix_initialize(result, size);


  int32_t row;
  int32_t column;
  // Start in second row.
  for (row = 1; row < size; row++) {
    for (column = 0; column < size; column++) {
      if (column == 0) {
        matrix[row][column] = matrix[row][column] + matrix[row - 1][column];
      } else {
        int32_t tmp_left = matrix[row - 1][column - 1];
        int32_t tmp_right = matrix[row - 1][column];
        if (tmp_left > tmp_right) {
          matrix[row][column] = matrix[row][column] + tmp_left;
        } else {
          matrix[row][column] = matrix[row][column] + tmp_right;
        }
      }
    }
  }

  printf("\nResult\n");
  matrix_print(matrix, size);

  int32_t maximum = 0;
  int32_t i;
  for (i = 0; i < size; i++) {
    if (matrix[size - 1][i] > maximum) {
      maximum = matrix[size -1][i];
    }
  }

  printf("\nThe maximum total from top to bottom of the triangle below: %d\n", maximum);
}

