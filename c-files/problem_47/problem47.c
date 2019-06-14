/* Distinct primes factors
 *
 * Problem 47
 *
 * The first two consecutive numbers to have two distinct prime factors are:
 *
 *  14 = 2 x 7
 *  15 = 3 x 5
 *
 *  The first three consecutive numbers to have three distinct prime factors are:
 *
 *  644 = 2 ^ 2 x 7 x 23
 *  645 = 3 x 5 x 43
 *  646 = 2 x 17 x 19.
 *
 *  Find the first four consecutive integers to have four distinct prime factors.
 *  What is the first of these numbers?
 *
 * problem47.c
 *
 *  Created on: Jan 12, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/util.h"
#include "../lib/list.h"

/* Returns a list of struct long_number elements without duplicate elements. It eliminates the
 * duplicates by multiplying elements that are equal.
 *
 * Example:
 *       Original list: 2, 2, 5, 7
 *       Result list:   4, 5, 7
 *
 * @param ptr_list is the list of struct long_number elements that might contain duplicates.
 * @return the list of struct long_number without duplicates.
 */
struct list * eliminate_duplicates_by_multiplying(struct list *ptr_list) {
  struct list *no_duplicates = malloc(sizeof(struct list));
  list_init(no_duplicates);

  if (list_size(ptr_list) == 0) {
    return no_duplicates;
  }

  struct long_number *ln;
  struct list_elem *temp;

  uint32_t previous = 0;
  uint32_t current;
  uint32_t acumulate = 1;

  temp = list_begin(ptr_list);
  ln = list_entry(temp, struct long_number, elem);
  previous = ln->number;
  current = ln->number;

  for (temp = list_next(temp); temp != list_end(ptr_list); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    current = ln->number;
    if (current != previous) {
      ln = (struct long_number *) malloc(sizeof(struct long_number));
      if (acumulate != 1) {
        ln->number = acumulate * previous;
      } else {
        ln->number = previous;
      }
      list_insert_ordered(no_duplicates, &ln->elem, compare_long_number_asc, NULL);
      acumulate = 1;
    } else {
        acumulate *= current;
    }

    previous = current;
  }

  // Add the last element
  ln = (struct long_number *) malloc(sizeof(struct long_number));
  ln->number = acumulate * current;
  list_insert_ordered(no_duplicates, &ln->elem, compare_long_number_asc, NULL);

  return no_duplicates;
}

/* Prints the list of struct long_numbers.
 *
 * @param ptr_list is the list of long_numbers to be printed.
 */
void print_list(struct list *ptr_list) {
  struct long_number *ln;
  struct list_elem *temp;

  for (temp = list_begin(ptr_list); temp != list_end(ptr_list); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    printf("%llu ", ln->number);
  }

  printf("\n");
}

/* Returns true if the four lists contain different elements, otherwise it returns false.
 *
 * @param list_ptr1 is the first list of struct long_number elements.
 * @param list_ptr2 is the second list of struct long_number elements.
 * @param list_ptr3 is the third list of struct long_number elements.
 * @param list_ptr4 is the fourth list of struct long_number elements.
 * @return true if the four lists contain different elements, otherwise false.
 */
bool are_sequences_different(struct list *list_ptr1, struct list *list_ptr2,
    struct list *list_ptr3, struct list *list_ptr4) {
  struct hash hash_numbers;
  hash_init(&hash_numbers, hash_long_number, compare_hash_long_number_asc, NULL);

  struct long_number *ln;
  struct list_elem *temp;

  for (temp = list_begin(list_ptr1); temp != list_end(list_ptr1); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    if (hash_insert(&hash_numbers, &ln->hash_elem) != NULL) {
      return false;
    }
  }

  for (temp = list_begin(list_ptr2); temp != list_end(list_ptr2); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    if (hash_insert(&hash_numbers, &ln->hash_elem) != NULL) {
      return false;
    }
  }

  for (temp = list_begin(list_ptr3); temp != list_end(list_ptr3); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    if (hash_insert(&hash_numbers, &ln->hash_elem) != NULL) {
      return false;
    }
  }

  for (temp = list_begin(list_ptr4); temp != list_end(list_ptr4); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    if (hash_insert(&hash_numbers, &ln->hash_elem) != NULL) {
      return false;
    }
  }

  return true;
}

int main() {
  printf("\nDistinct primes factors");

  bool sequence_found = false;
  uint32_t i;
  for(i = 1; true ; i++) {
    struct list *mul = get_multiples(i);
    struct list *no_duplicates = eliminate_duplicates_by_multiplying(mul);

    if (list_size(no_duplicates) == 4) {
      struct list *second = get_multiples(i + 1);
      struct list *second_no_dup = eliminate_duplicates_by_multiplying(second);
      struct list *third = get_multiples(i + 2);
      struct list *third_no_dup = eliminate_duplicates_by_multiplying(third);
      struct list *four = get_multiples(i + 3);
      struct list *four_no_dup = eliminate_duplicates_by_multiplying(four);

      if (list_size(second_no_dup) == 4 && list_size(third_no_dup) == 4 &&
          list_size(four_no_dup) == 4 &&
          are_sequences_different(no_duplicates, second_no_dup, third_no_dup, four_no_dup)) {
        printf("\nFirst number of the sequence: %u\n", i);
        print_list(no_duplicates);
        print_list(second_no_dup);
        print_list(third_no_dup);
        print_list(four_no_dup);
        printf("\n");
        sequence_found = true;
      }

      // Releasing resources from the list
      free_memory_long_number_list(second);
      free(second);
      free_memory_long_number_list(second_no_dup);
      free(second_no_dup);
      free_memory_long_number_list(third);
      free(third);
      free_memory_long_number_list(third_no_dup);
      free(third_no_dup);
      free_memory_long_number_list(four_no_dup);
      free(four_no_dup);
    }

    free_memory_long_number_list(mul);
    free(mul);
    free_memory_long_number_list(no_duplicates);
    free(no_duplicates);

    if (sequence_found) {
        break;
    }
  }

  return 0;
}

