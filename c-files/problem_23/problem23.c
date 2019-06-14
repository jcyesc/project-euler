/*
 * Non-abundant sums
 *
 *
 * Problem 23
 *
 * A perfect number is a number for which the sum of its proper divisors is exactly equal to the
 * number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which
 * means that 28 is a perfect number.
 *
 * A number n is called deficient if the sum of its proper divisors is less than n and it is called
 * abundant if this sum exceeds n.
 *
 * As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be
 * written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that
 * all integers greater than 28123 can be written as the sum of two abundant numbers. However, this
 * upper limit cannot be reduced any further by analysis even though it is known that the greatest
 * number that cannot be expressed as the sum of two abundant numbers is less than this limit.
 *
 * Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
 *
 * problem23.c
 *
 *  Created on: Jan 9, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/hash.h"
#include "../lib/list.h"
#include "../lib/util.h"

/* Removes the last element from the list and release the memory.
 *
 * @param list_ptr is a pointer to a list of struct long_number elements.
 */
void remove_last_element(struct list *list_ptr) {
  if (list_size(list_ptr) <= 0) {
    return;
  }

  struct list_elem *last_elem = list_pop_back(list_ptr);
  struct long_number *ln = list_entry(last_elem, struct long_number, elem);
  free(ln);
}

/* Gets the abundant number from 1 to limit.
 *
 * Note: The caller of this function has to free the memory assigned to list and the elements
 *     of the list.
 *
 * @param limit is the maximum number that will be evaluated to determine if it's abundant or not.
 * @param return the list of abundant numbers.
 */
struct list *get_abundant_numbers(int32_t limit) {
  struct list *list_abundant = malloc(sizeof (struct list));
  list_init(list_abundant);

  int32_t i;
  for (i = 1; i <= limit; i++) {
    struct list *list_numbers = get_distinct_multiples(i);
    // Remove the last element which is the given number.
    remove_last_element(list_numbers);
    uint32_t sum = list_add_elements(list_numbers);
    if (sum > i) {
      struct long_number *ln = malloc(sizeof (struct long_number));
      ln->number = i;
      list_push_back(list_abundant, &ln->elem);
    }

    free_memory_long_number_list(list_numbers);
    free(list_numbers);
  }

  return list_abundant;
}

/* Sets the abundant numbers from the list to the array. The array has to be as big as
 * the size of the list.
 *
 * @param list_abundant is the list of abundant numbers.
 * @param abundant_numbers is the array where the abundant numbers will be copied.
 */
void set_abundant_numbers (struct list *list_abundant, uint32_t abundant_numbers[]) {
  struct long_number *ln;
  struct list_elem *temp;
  uint32_t i = 0;
  for (temp = list_begin(list_abundant); temp != list_end(list_abundant); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    abundant_numbers[i] = ln->number;
    i++;
  }
}

/* Returns true if the given number can be written as the sum of two numbers that are found
 * in the array. This algorithm requires the array of elements and a hash table of the elements
 * in order to run in O(n).
 *
 * @param number that will be analized.
 * @param elements that will be used to see if the number can be written as the sum of two numbers.
 * @param size of the array
 * @param hash_long is the hash table that contains the same elements that the given array.
 */
bool can_be_sum_by_two_numbers(uint32_t number, uint32_t elements[], uint32_t size, struct hash *hash_long) {
  // This fragment determines if the number can be written as the sum of two numbers from the array.
  uint32_t j;
  bool added = false;
  for (j = 0; j <= size && number > elements[j]; j++) {
    uint64_t tmp = number - elements[j];
    struct long_number *ln = hash_long_number_lookup(hash_long, tmp);
    if (ln != NULL) {
      added = true;
      break;
    }
  }

  return added;
}

int main() {
  printf("\nNon-abundant sums");

  // Getting the abundant numbers.
  uint32_t limit = 28123;
  struct list *list_abundant = get_abundant_numbers(limit);

  uint32_t size = list_size(list_abundant);
  uint32_t abundant_numbers[size];

  // Setting the abundant numbers in the array.
  set_abundant_numbers(list_abundant, abundant_numbers);

  // Releasing resources from the list
  free_memory_long_number_list(list_abundant);
  free(list_abundant);

  // Creating the hash table.
  struct hash hash_abundant;
  hash_init(&hash_abundant, hash_long_number, compare_hash_long_number_asc, NULL);

  // Putting all the abundant numbers in the hash.
  uint32_t i;
  for (i = 0; i < size; i++) {
    struct long_number *ln = malloc(sizeof (struct long_number));
    ln->number = abundant_numbers[i];
    hash_insert(&hash_abundant, &ln->hash_elem);
  }

  // Adding the numbers that cannot be written as the sum of two abundant numbers.
  uint32_t total = 0;
  uint32_t number;
  for (number = 0; number <= limit; number++) {
    if(!can_be_sum_by_two_numbers(number, abundant_numbers, size, &hash_abundant)) {
      // This number cannot be written as the sum of two abundant numbers.
      total += number;
    }
  }

  // Release the resources from the hash table.
  hash_clear(&hash_abundant, free_memory_long_number_hash);

  printf("\nThe sum of all the positive integers which cannot be written as the sum of two "
      "abundant numbers is %u\n", total);
}


