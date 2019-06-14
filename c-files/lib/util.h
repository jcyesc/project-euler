#ifndef __LIB__UTIL_H
#define __LIB__UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "list.h"
#include "hash.h"

/* UTIL LIBRARY
 *
 *
 * Defines a util library of functions that are used to solve the problems.
 */

/* Defines a struct that will contain unsigned long number and it could be
 * a member of a list.
 */
struct long_number {
  uint64_t number;
  struct list_elem elem;
  struct hash_elem hash_elem;
};

/* Defines a struct that will contain a string and it could be a member of a list.
 */
struct string_obj {
  char *string;
  struct list_elem elem;
};

/* Compares two string objects A and B. Returns true if A is less than B,
 * or false if A is greater than or equal to B.
 *
 * @param a is a struct list_elem that is wrapped in a struct string_obj
 * @param b is a struct list_elem that is wrapped in a struct string_number.
 * @param aux is an extra data.
 */
bool compare_string_obj_asc(const struct list_elem *a, const struct list_elem *b, void *aux);

/* Compares two long numbers A and B. Returns true if A is less than B,
 * or false if A is greater than or equal to B.
 */
bool compare_long_number_asc(const struct list_elem *a, const struct list_elem *b, void *aux);

/* Adds all the elements of the list.
 *
 * @param list_ptr is a pointer to a list of struct long_number elements.
 */
uint64_t list_add_elements(struct list *list_ptr);

/* Returns the hash of a struct long_number.
 *
 * @param ptr is a pointer to a struch hash_elem.
 */
uint32_t hash_long_number(const  struct hash_elem *ptr, void *aux);

/* Compares two long numbers A and B. Returns true if A is less than B,
 * or false if A is greater than or equal to B.
 *
 * @param a is a struct hash_elem that is wrapped in a struct long_number.
 * @param b is a struct hash_elem that is wrapped in a struct long_number.
 * @param aux is an extra data.
 */
bool compare_hash_long_number_asc(const struct hash_elem *a, const struct hash_elem *b, void *aux);

/* Finds and return a struct long_number based on the number.
 *
 * @param hash_table where the number will be searched.
 * @param number To be found.
 * @return a pointer  to a struct long_number if found, otherwise NULL.
 */
struct long_number *hash_long_number_lookup(struct hash *ht, const uint64_t number);

/* Finds the first multiple of the given number.
 *
 * @param number that will be broken down.
 */
uint64_t find_first_multiple (uint64_t number);

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
struct list * get_multiples(uint64_t number);

/* Gets the list of multiples of the given number. It creates the space for the list and
 * all the list_elems that are required. The caller of this function has to release the memory
 * for the list and all the elements.
 *
 * Example:
 *          get_multiples(150) = 2, 3, 5, 5
 *
 *          get_distinct_multiples(28) = 1, 2, 4, 7, 14, 28
 *
 * Running time: O(n)
 *
 * Note: This function is really inefficient because if iterates more than half of the numbers below
 *     the given number.
 *
 * @param number that will be broken down in factors.
 */
struct list *get_distinct_multiples(uint64_t number);

/* Returns true if the list of long_numbers contains the given number, otherwise false.
 *
 * @param list_ptr is a pointer to the list of long_numbers.
 * @param number is the number that will be looked for in the list.
 * @return true if the number is in the list, otherwise false.
 */
bool contains_long_number (struct list *list_ptr, uint64_t number);

/* Gets the number of occurrences of the given number in the list.
 *
 * @param list_prt is a pointer to the list of long_numbers.
 * @param number To calculate the number of occurrences of it in the list.
 * @return the number of occurrences of the given number.
 */
uint32_t get_ocurrences_long_number (struct list *list_ptr, uint64_t number);

/* Releases the memory that was allocated to create the struct long_number elements from the list.
 *
 * @param list that contains the elements allocated with malloc.
 */
void free_memory_long_number_list(struct list *list);

/* Releases the memory that was allocated to create the struct string_obj elements from the list.
 *
 * Running time: O(n)
 *
 * @param list that contains the elements allocated with malloc.
 */
void free_memory_string_obj_list(struct list *ptr_list);

/* Releases the memory that was allocated to create the struct long_number element..
 *
 * Running time: O(1)
 *
 * @param e is the pointer to the struct hash_elem.
 */
void free_memory_long_number_hash(struct hash_elem *e, void *aux);

/* Return true if the given number is a prime number, otherwise false.
 *
 * @param number to be tested if it's a prime or not.
 */
bool is_prime(uint64_t number);

/* Returns true if the string is a palindromic, otherwise false.
 *
 * Running time: O(n)
 */
bool is_palindromic_string(char *str);

/* Creates the Sieve of Eratosthenes. First it initializes the sieve and then start
 * executing the algorithm. The prime numbers start with 1, 2, 3, 5, 7 ......
 *
 * @param sieve[] that contains the prime numbers.
 * @param size of the Sieve of Eratosthenes.
 */
void sieve_eratosthenes_create(bool sieve[], size_t size);

/* Prints the prime numbers that are found in the Sieve of Eratosthenes.
 *
 * @param sieve[] that contains the prime numbers.
 * @param size of the Sieve of Eratosthenes.
 * @param numbers_per_line is the number of prime numbers to be printed per line.
 */
void sieve_eratosthenes_print_primes(bool array[], size_t size, int numbers_per_line);

/* Gets the n prime number from the Sieve of Eratosthenes.
 *
 * @param sieve[] that contains the prime numbers.
 * @param size of the Sieve of Eratosthenes.
 * @param n prime number that will be return.
 * @return n primen number.
 */
size_t sieve_eratosthenes_get_prime(bool array[], size_t size, size_t n);

/* Rotate the given string.
 * Example:
 *    rotate("abcde") = "bcdea"
 *
 * @param string to be rotate.
 */
void rotate_string(char string[]);

/* Permutates the given string and returns a list with all the possible permutations.
 *
 * Note: The list, the elements of the list and the memory for holding the string was created
 *     dynamically, so the list, the elements of the list and the string has to be released.
 *
 * @param string to be permuted.
 * @return a list that contains all the possible permutations.
 */
struct list* permutate_string(char string[]);

/* Converts a decimal number to binary. It does that by shifting a one from the last
 * position of the integer to the very beginning, after this, it applies the AND operation to
 * see if there is a One or a Zero.
 *
 * Note: The string that is returned it has to be released after used..
 *
 * @param decimal number
 * @return a string that represents the binary number.
 */
char *convert_from_decimal_to_binary(int decimal);

/* Returns true if the given value is pandigital, this means that it uses all the digits 1 to n
 * exactly once. Otherwise returns false
 *
 * @param value to be checked.
 * @return true if the value is pandigital, otherwise false.
 */
bool is_pandigital(char *value);

#endif /* lib/util.h */
