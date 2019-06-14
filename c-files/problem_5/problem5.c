/*
 * Smallest multiple
 *
 * Problem 5
 * 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
 *
 * What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
 *
 * problem5.c
 *
 * Created on: Dec 18, 2013
 * Author: jcyescas
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../lib/util.h"
#include "../lib/list.h"


void merge_multiple_list(struct list *multiples, struct list *sub_multiples);
uint64_t multiply_elements_list(struct list *list_ptr);
uint64_t get_smallest_number_divisible (uint64_t number);


/* Gets the smallest positive number that is evently divisible by all the numbers from 1 to NUMBER.
 *
 * @param number that will be used to calculate the smallest positive number that is evenly
 *     divisible by all the numbers from 1 to NUMBER.
 */
uint64_t get_smallest_number_divisible (uint64_t number) {
  uint64_t i;
  uint64_t smallest_number;
  struct list multiples;
  list_init(&multiples);

  struct list *tmp_list;
  for (i = 2; i <= number; i++) {
    tmp_list = get_multiples(i);

    // Merge the multiples of the current number in the list so all the multiples for all the
    // numbers appear in the list.
    merge_multiple_list(&multiples, tmp_list);

    free_memory_long_number_list(tmp_list);
    free(tmp_list);
  }

  smallest_number = multiply_elements_list(&multiples);
  free_memory_long_number_list(&multiples);

  return smallest_number;
}

/* Merges the two list. It makes sure that all the elements in the sub_multiples list are in the
 * multiples list.
 *
 * Example:
 *   multiples [2 2 3 4 5], sub_multiples [4 4 7]
 *   merge [2 2 3 4 4 5 7]
 */
void merge_multiple_list(struct list *multiples, struct list *sub_multiples) {
  struct long_number *ln;
  struct list_elem *temp;

  for (temp = list_begin(sub_multiples); temp != list_end(sub_multiples); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);

    if (contains_long_number(multiples, ln->number)) {
      uint32_t occurr_mul = get_ocurrences_long_number(multiples, ln->number);
      uint32_t occurr_sub_mul = get_ocurrences_long_number(sub_multiples, ln->number);
      if (occurr_sub_mul > occurr_mul) {
        uint32_t add_occur = occurr_sub_mul - occurr_mul;
        uint32_t i;
        for (i = 0; i < add_occur; i++) {
          struct long_number *num = (struct long_number *) malloc(sizeof(struct long_number));
          num->number = ln->number;
          list_insert_ordered(multiples, &num->elem, compare_long_number_asc, NULL);
        }
      }
    } else {
      // Add the number to the list.
      struct long_number *num = (struct long_number *) malloc(sizeof(struct long_number));
      num->number = ln->number;
      list_insert_ordered(multiples, &num->elem, compare_long_number_asc, NULL);
    }
  }
}

/* Multiplies all the elements in the list and returns the result.
 */
uint64_t multiply_elements_list(struct list *list_ptr) {
  struct list_elem *temp;
  struct long_number *ln;
  uint64_t result = 1;

  for (temp = list_begin(list_ptr); temp != list_end(list_ptr); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    result *= ln->number;
  }

  return result;
}

int main() {
  uint64_t number = 10;
  uint64_t smallest_number = get_smallest_number_divisible(number);
  printf("The smallest number that is evenly divisible by all of the numbers from 1 to %llu is %llu\n",
      number, smallest_number);

  number = 20;
  smallest_number = get_smallest_number_divisible(number);
  printf("\nThe smallest number that is evenly divisible by all of the numbers from 1 to %llu is %llu\n",
      number, smallest_number);

  return 0;
}
