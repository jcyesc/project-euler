
#include "util.h"
#include "hash.h"
#include "list.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


/* Compares two string objects A and B. Returns true if A is less than B,
 * or false if A is greater than or equal to B.
 *
 * @param a is a struct list_elem that is wrapped in a struct string_obj
 * @param b is a struct list_elem that is wrapped in a struct string_number.
 * @param aux is an extra data.
 */
bool compare_string_obj_asc(const struct list_elem *a, const struct list_elem *b, void *aux) {
  struct string_obj *an =  (struct string_obj *) list_entry(a, struct string_obj, elem);
  struct string_obj *bn =  (struct string_obj *) list_entry(b, struct string_obj, elem);

  int result = strcmp(an->string, bn->string);
  if (result == 0 || result > 0) {
      return false;
  }

  return true;
}

/* Compares two long numbers A and B. Returns true if A is less than B,
 * or false if A is greater than or equal to B.
 *
 * @param a is a struct list_elem that is wrapped in a struct long_number.
 * @param b is a struct list_elem that is wrapped in a struct long_number.
 * @param aux is an extra data.
 */
bool compare_long_number_asc(const struct list_elem *a, const struct list_elem *b, void *aux) {
  struct long_number *an =  (struct long_number *) list_entry(a, struct long_number, elem);
  struct long_number *bn =  (struct long_number *) list_entry(b, struct long_number, elem);

  return an->number < bn->number;
}



/* Adds all the elements of the list.
 *
 * @param list_ptr is a pointer to a list of struct long_number elements.
 */
uint64_t list_add_elements(struct list *list_ptr) {
  uint64_t total = 0;
  struct long_number *ln;
  struct list_elem *temp;
  for (temp = list_begin(list_ptr); temp != list_end(list_ptr); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    total += ln->number;
  }

  return total;
}

/* Returns the hash of a struct long_number.
 *
 * @param ptr is a pointer to a struch hash_elem.
 */
uint32_t hash_long_number(const struct hash_elem *ptr, void *aux) {
  const struct long_number *ln = (struct long_number *) hash_entry(ptr, struct long_number, hash_elem);
  return hash_int(ln->number);
}

/* Finds and return a struct long_number based on the number.
 *
 * @param hash_table where the number will be searched.
 * @param number To be found.
 * @return a pointer  to a struct long_number if found, otherwise NULL.
 */
struct long_number *hash_long_number_lookup(struct hash *ht, const uint64_t number) {
  struct long_number ln_tmp;
  struct hash_elem *he;

  ln_tmp.number = number;
  he = hash_find(ht, &ln_tmp.hash_elem);
  return he != NULL ? hash_entry(he, struct long_number, hash_elem) : NULL;
}

/* Compares two long numbers A and B. Returns true if A is less than B,
 * or false if A is greater than or equal to B.
 *
 * @param a is a struct hash_elem that is wrapped in a struct long_number.
 * @param b is a struct hash_elem that is wrapped in a struct long_number.
 * @param aux is an extra data.
 */
bool compare_hash_long_number_asc(const struct hash_elem *a, const struct hash_elem *b, void *aux) {
  struct long_number *an =  (struct long_number *) hash_entry(a, struct long_number, hash_elem);
  struct long_number *bn =  (struct long_number *) hash_entry(b, struct long_number, hash_elem);

  return an->number < bn->number;
}

/* Finds the first multiple of the given number.
 * It only works with positive numbers.
 *
 * Running time O(n)
 *
 * @param number that will be broken down.
 */
uint64_t find_first_multiple (uint64_t number) {
  uint64_t i;
  for (i = 2; i < number; i++) {
      if (number % i == 0)
        return i;
  }

  return number;
}

/* Gets the list of multiples of the given number. It creates the space for the list and
 * all the list_elems that are required. The caller of this function has to release the memory
 * for the list and all the elements.
 *
 * Example: get_multiples(150) = 2, 3, 5, 5
 *
 * Running time: O(n ^2)
 *
 * Note: This function doesn't return the 1 or the {@code number}.
 *
 * @param number that will be broken down in factors.
 */
struct list *get_multiples(uint64_t number) {
  struct list *list_multiples = (struct list*) malloc(sizeof(struct list));
  list_init(list_multiples);

  uint64_t tmp = number;
  uint64_t multiple = find_first_multiple(number);
  struct long_number *ln;

  while (true) {
    ln = (struct long_number *) malloc(sizeof(struct long_number));
    ln->number = multiple;
    list_insert_ordered(list_multiples, &ln->elem, compare_long_number_asc, NULL);

    if (tmp == multiple)
      break;

    tmp = tmp / multiple;
    multiple = find_first_multiple(tmp);
  }

  return list_multiples;
}

/* Gets the list of multiples of the given number. It creates the space for the list and
 * all the list_elems that are required. The caller of this function has to release the memory
 * for the list and all the elements.
 *
 * Example:
 *          get_multiples(150) = 2, 3, 25
 *
 *          get_distinct_multiples(28) = 1, 2, 4, 7, 14, 28
 *
 * Running time: O(n)
 *
 * Note: This function is really inefficient because if iterates more than half of the numbers below
 *     the given number.
 *
 *    There are several improvements that can be done like creating a Sieve of Erathostenes and
 *    before iterating from 1 to the given number, we might check if it's prime.
 *
 * @param number that will be broken down in factors.
 */
struct list *get_distinct_multiples(uint64_t number) {

  struct list *list_multiples = (struct list*) malloc(sizeof(struct list));
  list_init(list_multiples);

  if (number == 0) {
    return list_multiples;
  }
  struct long_number *ln;

  // Insert the first multiple (1)
  ln = (struct long_number *) malloc(sizeof(struct long_number));
  ln->number = 1;
  list_insert_ordered(list_multiples, &ln->elem, compare_long_number_asc, NULL);

  if (number == 1) {
      return list_multiples;
  }

  // Insert the number itself
  ln = (struct long_number *) malloc(sizeof(struct long_number));
  ln->number = number;
  list_insert_ordered(list_multiples, &ln->elem, compare_long_number_asc, NULL);

  uint64_t i;
  for (i = 2; i <= number / 2; i++) {
    if (number % i == 0) {
      ln = (struct long_number *) malloc(sizeof(struct long_number));
      ln->number = i;
      list_insert_ordered(list_multiples, &ln->elem, compare_long_number_asc, NULL);
    }
  }

  return list_multiples;
}

/* Returns true if the list of long_numbers contains the given number, otherwise false.
 *
 * Running time: O(n)
 *
 * @param list_ptr is a pointer to the list of long_numbers.
 * @param number is the number that will be looked for in the list.
 * @return true if the number is in the list, otherwise false.
 */
bool contains_long_number (struct list *list_ptr, uint64_t number) {
  struct long_number *ln;
  struct list_elem *temp;

  for (temp = list_begin(list_ptr); temp != list_end(list_ptr); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    if (ln->number == number) {
      return true;
    }
  }

  return false;
}

/* Gets the number of occurrences of the given number in the list.
 *
 * Running time: O(n)
 *
 * @param list_prt is a pointer to the list of long_numbers.
 * @param number To calculate the number of occurrences of it in the list.
 * @return the number of occurrences of the given number.
 */
uint32_t get_ocurrences_long_number (struct list *list_ptr, uint64_t number) {
  uint32_t occurrences = 0;
  struct long_number *ln;
  struct list_elem *temp;

  for (temp = list_begin(list_ptr); temp != list_end(list_ptr); temp = list_next(temp)) {
    ln = list_entry(temp, struct long_number, elem);
    if (ln->number == number) {
      occurrences++;
    }
  }

  return occurrences;
}

/* Releases the memory that was allocated to create the struct long_number elements from the list.
 *
 * Running time: O(n)
 *
 * @param list that contains the elements allocated with malloc.
 */
void free_memory_long_number_list(struct list *ptr_list) {
  if (ptr_list == NULL)
    return;

  struct list_elem *e;

  while (!list_empty (ptr_list)) {
    e = list_pop_front (ptr_list);
    struct long_number *ptr_long_number = list_entry(e, struct long_number, elem);
    free(ptr_long_number);
  }
}

/* Releases the memory that was allocated to create the struct string_obj elements from the list.
 *
 * Running time: O(n)
 *
 * @param list that contains the elements allocated with malloc.
 */
void free_memory_string_obj_list(struct list *ptr_list) {
  if (ptr_list == NULL)
    return;

  struct list_elem *e;

  while (!list_empty (ptr_list)) {
    e = list_pop_front (ptr_list);
    struct string_obj *ptr_string_obj = list_entry(e, struct string_obj, elem);
    free(ptr_string_obj->string);
    free(ptr_string_obj);
  }
}


/* Releases the memory that was allocated to create the struct long_number element..
 *
 * Running time: O(1)
 *
 * @param e is the pointer to the struct hash_elem.
 */
void free_memory_long_number_hash(struct hash_elem *e, void *aux) {
  if (e == NULL)
    return;

  struct long_number *ln = hash_entry(e, struct long_number, hash_elem);
  free(ln);
}

/* Return true if the given number is a prime number, otherwise false.
 * It only works with positive numbers.
 *
 * Running time: O(n)
 *
 * @param number to be tested if it's a prime or not.
 */
bool is_prime(uint64_t number) {
  if (number == 0) {
    return false;
  }

  uint64_t result = find_first_multiple(number);
  if (number == result) {
    return true;
  }

  return false;
}

/* Returns true if the string is a palindromic, otherwise false.
 *
 * Running time: O(n)
 */
bool is_palindromic_string(char *str) {
  size_t size = strlen(str);

  int i;
  int j;
  for (i = 0, j = size -1; i < j; i++, j--) {
    if (str[i] != str[j]) {
      return false;
    }
  }

  return true;
}

/* Creates the Sieve of Eratosthenes. First it initializes the sieve and then start
 * executing the algorithm. The prime numbers start with 1, 2, 3, 5, 7 ......
 *
 * Running time: O(n ^ 2)
 *
 * @param sieve[] that contains the prime numbers.
 * @param size of the Sieve of Eratosthenes.
 */
void sieve_eratosthenes_create(bool sieve[], size_t size) {

  sieve[0] = false;
  sieve[1] = false;
  size_t index;
  for (index = 2; index < size; index++) {
    sieve[index] = true;
  }

  for (index = 2; index < size; index++) {
    if (sieve[index]) {
      size_t mark;
      for (mark = index + index; mark < size; mark += index) {
          sieve[mark] = false;
      }
    }

  }
}

/* Prints the prime numbers that are found in the Sieve of Eratosthenes.
 *
 * Running time: O(n)
 *
 * @param sieve[] that contains the prime numbers.
 * @param size of the Sieve of Eratosthenes.
 * @param numbers_per_line is the number of prime numbers to be printed per line.
 */
void sieve_eratosthenes_print_primes(bool array[], size_t size, int numbers_per_line) {
  size_t i;
  size_t number_primes = 0;
  for (i = 1; i < size; i++) {
    if (array[i]) {
      printf("%llu\t", i);
      number_primes++;
      if (number_primes > 0 && number_primes % numbers_per_line == 0) {
            printf("\n");
      }
    }
  }
}

/* Gets the n prime number from the Sieve of Eratosthenes.
 *
 *  Running time: O(n)
 *
 * @param sieve[] that contains the prime numbers.
 * @param size of the Sieve of Eratosthenes.
 * @param n prime number that will be return.
 * @return n primen number.
 */
size_t sieve_eratosthenes_get_prime(bool array[], size_t size, size_t n) {
  size_t i;
  size_t number_primes = 0;
  for (i = 1; i < size; i++) {
    if (array[i]) {
      number_primes++;
      if (number_primes == n) {
          return i;
      }
    }
  }

  return 0;
}

/* Rotate the string from the position = size - newSize to size.
 *
 * @param string to be rotate.
 * @param newSize is the size of the string that will be rotated.
 */
static void rotate(char string[], int32_t newSize) {
  int32_t size = strlen(string);
  int32_t position = size - newSize;
  char first_char = string[position];
  int32_t i;
  for (i = position + 1; i < size; i++) {
    string[i - 1] = string[i];
  }

  string[i - 1] = first_char;
}

/* Rotate the given string.
 * Example:
 *    rotate("abcde") = "bcdea"
 *
 * @param string to be rotate.
 */
void rotate_string(char string[]) {
  rotate(string, strlen(string));
}

/*
 * How would you write a program to anagram a word? Hereâ it is one approach. Assume
 * the word has n letters.
 *
 *   1. Anagram the rightmost n-1 letters.
 *   2. Rotate all n letters.
 *   3. Repeat these steps n times.
 *
 * To rotate the word means to shift all the letters one position left, except for the
 * leftmost letter, which "rotates back to the right.
 *
 * @param newSize
 * @param arrChar
 * @param permutations is the list of different permutations.
 */
static void permutate(char string[], int32_t size, struct list *permutations) {
  if (size == 1) // too small
    return;

  int32_t i;
  for (i = 0; i < size; i++) {
    permutate(string, size -1, permutations);
    if (size == 2) {
      // Adding the element to the list.
      char *copy = malloc(sizeof(strlen(string) + 1));
      sprintf(copy, "%s", string);
      struct string_obj *str = malloc(sizeof(struct string_obj));
      str->string = copy;
      list_push_back(permutations, &str->elem);
    }
    rotate(string, size);
  }
}

/* Permutates the given string and returns a list with all the possible permutations.
 *
 * Note: The list, the elements of the list and the memory for holding the string was created
 *     dynamically, so the list, the elements of the list and the string has to be released.
 *
 * @param string to be permuted.
 * @return a list that contains all the possible permutations.
 */
struct list* permutate_string(char string[]) {
  struct list *permutations = malloc(sizeof(struct list));
  list_init(permutations);

  permutate(string, strlen(string), permutations);

  return permutations;
}

/* Converts a decimal number to binary. It does that by shifting a one from the last
 * position of the integer to the very beginning, after this, it applies the AND operation to
 * see if there is a One or a Zero.
 *
 * Note: The string that is returned it has to be released after used..
 *
 * Running time: O(n) where n is the number of bits in the decimal number.
 *
 * @param decimal number
 * @return a string that represents the binary number.
 */
char *convert_from_decimal_to_binary(int decimal) {
  char *binary = malloc(sizeof(int));
  int index = 0;

  int i;
  bool first_one = false;
  for (i = 31; i >= 0; i--) {
    int tmp = 1;
    tmp = tmp << i;
    if (tmp & decimal) {
      binary[index] = '1';
      index++;
      first_one = true;
    } else {
      if (first_one) {
        binary[index] = '0';
        index++;
      }
    }
  }

  return binary;
}

/* Returns true if the given value is pandigital, this means that it uses all the digits 1 to n
 * exactly once. Otherwise returns false.
 *
 * @param value to be checked.
 * @return true if the value is pandigital, otherwise false.
 */
bool is_pandigital(char *value) {
  int value_size = strlen(value);

  int size = 10;
  int digits[size];
  int i;
  for (i = 0; i < size; i++){
    digits[i] = 0;
  }

  for (i = 0; i < value_size; i++) {
    int c = value[i] - '0';
    // Zero doesn't count in the pandigital number
    if (c == 0 || c > value_size) {
      return false;
    }

    if (digits[c] == 1) {
      return false;
    }

    digits[c] = 1;
  }

  return true;
}


