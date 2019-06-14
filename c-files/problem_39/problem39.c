/* Integer right triangles
 *
 * Problem 39
 *
 * If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are
 * exactly three solutions for p = 120.
 *
 * {20,48,52}, {24,45,51}, {30,40,50}
 *
 * For which value of p ² 1000, is the number of solutions maximised?
 *
 * problem39.c
 *
 *  Created on: Jan 18, 2014
 *      Author: jcyescas
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/util.h"
#include "../lib/list.h"

/* Struct that defines the value of the three sides of a triangle.
 *
 */
struct triangle {
  int a;
  int b;
  int c;
  struct list_elem elem;
};

/* Returns true if the evaluation of sqrt(pow(a, 2) + pow(b,2)) returns an integer,
 * otherwise it returns false.
 *
 * @param a side of the triangle.
 * @param b side of the triangle.
 * @return true if the evaluation of sqrt(pow(a, 2) + pow(b,2)) returns an integer,
 *     otherwise it returns false.
 *
 */
bool is_diagonal_integer(int a, int b) {
  int diagonal = a * a + b * b;
  double c = sqrt(diagonal);

  if (pow((int) c, 2) == diagonal) {
    return true;
  }

  return false;
}

/* Calculates the value of the c side of a triangle given the sides a and b. It uses
 * this formula c = sqrt(a^2 + b^2).
 *
 */
int calculate_c(int a, int b) {
  int diagonal = a * a + b * b;
  double c = sqrt(diagonal);
  return c;
}

/* Checks if the given triangle is in the list, if yes, return true, otherwise false.
 *
 * @param list is a pointer to the struct list.
 * @param triangle is a pointer to the struct triangle.
 * @return true if the triangle was found, otherwise false.
 */
bool is_triangle_in_list(struct list *list, struct triangle *triangle) {
  struct triangle *ptr_triangle;
  struct list_elem *temp;
  for (temp = list_begin(list); temp != list_end(list); temp = list_next(temp)) {
    ptr_triangle = list_entry(temp, struct triangle, elem);
    if (ptr_triangle->a == triangle->a && ptr_triangle->b == triangle->b &&
        ptr_triangle->c == ptr_triangle->c) {
      return true;
    }
  }

  return false;
}

/* Inserts the given triangle in the list if the triangle is not there, otherwise it doesn't
 * insert it.
 *
 * @param ptr_list is an array of struct list. The triangle will be inserted in the list with
 *     index that is equals to the perimeter.
 * @param perimeter of the triangle.
 * @param a side of the triangle.
 * @param b side of the triangle.
 * @param c side of the triangle.
 */
void insert_in_list(struct list *ptr_list[], int perimeter, int a, int b, int c) {
  struct list *ptr = ptr_list[perimeter];

  // If the list is not created, create it and initialize it.
  if (ptr == NULL) {
    ptr = malloc(sizeof(struct list));
    list_init(ptr);
    ptr_list[perimeter] = ptr;
  }

  // Creating the triangle.
  struct triangle *triangle = malloc(sizeof(struct triangle));
  triangle->a = a;
  triangle->b = b;
  triangle->c = c;

  if (is_triangle_in_list(ptr, triangle)) {
    return;
  }

  // If the triangle is not in the list, insert it.
  list_push_front(ptr, &triangle->elem);
}

/* Iterates through the whole list and returns the index of the list that contains
 * the maximum number of elements.
 *
 * @param list_ptr is an array of struct list.
 * @param size of the array of lists.
 * @return the index of the list that contains the maximum number of elements.
 */
int get_index_max_size_list(struct list* list_ptr[], int size) {
  int maxIndex = -1;
  int maxSize = 0;
  int i;
  for (i = 0; i < size; i++) {
    if (list_ptr[i] != NULL) {
      int tmp_size = list_size(list_ptr[i]);
      if (tmp_size > maxSize) {
        maxSize = tmp_size;
        maxIndex = i;
      }
    }
  }

  return maxIndex;
}

/* Prints the triangle elements of the given list.
 *
 * @param list of triangles.
 */
void print_list_triangles(struct list *list) {
  struct triangle *ptr;
   struct list_elem *temp;
   printf("\n");
   for (temp = list_begin(list); temp != list_end(list); temp = list_next(temp)) {
     ptr = list_entry(temp, struct triangle, elem);
     int perimeter = ptr->a + ptr->b + ptr->c;
     printf("{%d, %d, %d} = %d\n", ptr->a, ptr->b, ptr->c, perimeter);
   }
}

/* Releases the memory that was allocated to create the struct triangle elements from the list.
 *
 * Running time: O(n)
 *
 * @param list that contains the elements allocated with malloc.
 */
void free_memory_triangle_lists(struct list *list) {
  if (list == NULL) {
      return;
  }

  struct list_elem *e;
  while (!list_empty (list)) {
    e = list_pop_front (list);
    struct triangle *triangle = list_entry(e, struct triangle, elem);
    // Releasing the memory from the triangle.
    free(triangle);
  }

  // Releasing the memory from the list.
  free(list);
}


int main() {
  printf("\nInteger right triangles");

  int size = 1001;
  struct list* list_ptr[size];
  int i;
  // Initializing the elements of the array to NULL.
  for (i = 0; i < size; i++) {
    list_ptr[i] = NULL;
  }

  int perimeter = 1000;
  int upper_limit = perimeter / 2;
  int a;
  for (a = 1; a < upper_limit; a++) {
    int b;
    for (b = a; b < upper_limit; b++) {
      if (is_diagonal_integer(a, b)) {
        int c = calculate_c(a, b);
        int tmp_perimeter = a + b + c;
        if (tmp_perimeter <= perimeter) {
          insert_in_list(list_ptr, tmp_perimeter, a, b, c);
        }
      }
    }
  }

  printf("\nFor which value of p ² 1000, is the number of solutions maximised?");

  int index = get_index_max_size_list(list_ptr, size);
  int maxSize = list_size(list_ptr[index]);

  printf("\nList size %d", maxSize);
  print_list_triangles(list_ptr[index]);

  // Releasing resources from the array of lists.
  for (i = 0; i < size; i++) {
    free_memory_triangle_lists(list_ptr[i]);
  }

  return 0;
}



