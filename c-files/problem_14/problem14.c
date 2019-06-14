/*
 * Longest Collatz sequence
 *
 * Problem 14
 *
 * The following iterative sequence is defined for the set of positive integers:
 *
 * n -> n/2 (n is even)
 * n -> 3n + 1 (n is odd)
 *
 *
 * Using the rule above and starting with 13, we generate the following sequence:
 *
 * 13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1
 *
 * It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms.
 * Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.
 *
 * Which starting number, under one million, produces the longest chain?
 *
 *
 * NOTE: Once the chain starts the terms are allowed to go above one million.
 *
 * problem14.c
 *
 *  Created on: Jan 3, 2014
 *      Author: jcyescas
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/util.h"
#include "../lib/list.h"

/* Returns the Collatz sequence of the given number.
 *
 * Note: The caller has to release the memory for each element in the list and also the memory
 *     from the list.
 *
 * @param number where the Collatz sequence will start.
 * @return a list with the Collatz sequence.
 */
struct list * get_collatz_sequence(uint64_t number) {
  struct list *sequence = malloc(sizeof(struct list));
  list_init(sequence);

  struct long_number *ln = malloc(sizeof(struct long_number));
  ln->number = number;
  list_push_back(sequence, &ln->elem);

  while (number != 1) {
   if (number % 2 == 0) {
       number = number / 2;
   } else {
       number = 3 * number + 1;
   }

   ln = malloc(sizeof(struct long_number));
   ln->number = number;

   list_push_back(sequence, &ln->elem);
  }

  return sequence;
}

/* Gets longest Collatz sequence, under the given.
 *
 * Note: The caller has to release the memory for each element in the list and also the memory
 *     from the list.
 *
 * @param value that will be decremented in order to get the longest Collatz sequence.
 * @return the longest Collatz sequence under the given value.
 */
struct list *get_longest_collatz_sequence(uint64_t value) {

  struct list *longest_sequence = NULL;
  struct list *tmp_sequence;
  uint32_t max_size = 0;
  for (;value >= 1; value--) {
      tmp_sequence = get_collatz_sequence(value);
      if (list_size(tmp_sequence) > max_size) {
          // Releasing the memory from the previous list.
          if (longest_sequence != NULL) {
              free_memory_long_number_list(longest_sequence);
              free(longest_sequence);
          }

          max_size = list_size(tmp_sequence);
          longest_sequence = tmp_sequence;
          continue;
      }

      free_memory_long_number_list(tmp_sequence);
      free(tmp_sequence);
  }

  return longest_sequence;
}

void print_long_number_list(struct list *list) {
  struct long_number *ln;
  struct list_elem *temp;
  for (temp = list_begin(list); temp != list_end(list); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    printf("%u ", ln->number);
  }
}

int main() {
  printf("Longest Collatz sequence\n");

  uint64_t number = 13;
  struct list *sequence = get_collatz_sequence(number);
  printf("Number %u, Size %d\n", number, list_size(sequence));
  print_long_number_list(sequence);

  free_memory_long_number_list(sequence);
  free(sequence);

  // Calculating the longest Collatz sequence with a number that is under one million.
  number = 1000000;
  sequence = get_longest_collatz_sequence(number);

  printf("\n\nNumber %u, Size %d\n", number, list_size(sequence));
  print_long_number_list(sequence);

  free_memory_long_number_list(sequence);
  free(sequence);
}


