#ifndef __LIG__BIG_INTEGER_H
#define __LIG__BIG_INTEGER_H

/* Provides a library for managing Big integer numbers.
 *
 * biginteger.h
 *
 *  Created on: Dec 29, 2013
 *      Author: jcyescas
 */


#include <stdbool.h>
#include <stdint.h>
#include "hash.h"

/* Struct for the big_integer.
 */
struct big_integer {
  uint32_t size;      /* size of the big integer. */
  uint8_t *number;   /* Pointer to the array that will contain the numbers of the big_integer. */
  bool positive;      /* NOT IN USE Sign of the big_integer. true is positive, false is negative. */
  struct hash_elem hash_elem;  /* Hash element that will be used to reference the element inside the hash table. */
};

/* Creates a big_integer using a string. This is the only way to create a big integer.
 *
 * Example:
 *   Given the string "123456",
 *   it creates the array:
 *
 *   a[0] = 6
 *   a[1] = 5
 *   a[2] = 4
 *   a[3] = 3
 *   a[4] = 2
 *   a[5] = 1
 *
 * @param string that will be used to create the big_integer.
 */
struct big_integer *big_integer_create_from_string(char *string);

/* Creates a big_integer of the given size.
 *
 * @param size of the big_integer to be created.
 */
struct big_integer *big_integer_create(uint32_t size);

/* Clones a big_integer
 *
 * @param big_int to clone.
 */
struct big_integer *big_integer_clone(struct big_integer *big_int);

/* Adds two big integers.
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */
struct big_integer *big_integer_add(struct big_integer *b1, struct big_integer *b2);

/* Subtracts two big integers.
 *
 * Note:  First number has to be greater than second.
 *     A better implementation of this function would use "The method of complements".
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */
struct big_integer *big_integer_subtract(struct big_integer *b1, struct big_integer *b2);

/* Multiplies two big integers.
 *
 * Note: The current implementation just adds the b1 big_number b2 times. This is a really bad
 * implementation and it is extremely inefficient.
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */

struct big_integer *big_integer_multiply_inefficient(struct big_integer *b1, struct big_integer *b2);

/* Multiplies two big integers.
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */
struct big_integer *big_integer_multiply(struct big_integer *b1, struct big_integer *b2);

/* Shifts the big_integer number n positions to the left and insert Zeros instead.
 *
 * Example:
 *        big_integer_shift(3234234, 2) will return 323423400
 *
 * Note: Given the string "123456", the big_integer representation is:
 *
 *   a[0] = 6
 *   a[1] = 5
 *   a[2] = 4
 *   a[3] = 3
 *   a[4] = 2
 *   a[5] = 1
 *
 * @param b1 big_integer
 * @param positions is the number of positions that the big_integer will be shifted.
 */

struct big_integer *big_integer_shift(struct big_integer *b1, int32_t positions);

/* Calculates the power of the b1 big_number to the b2 big_numbers.
 *
 * b1 ^ b2
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */
struct big_integer *big_integer_pow(struct big_integer *b1, struct big_integer *b2);

/* Returns true if the two big_integers are equal, otherwise false.
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */
bool big_integer_equals(struct big_integer *b1, struct big_integer *b2);

/* Converts the big_integer number to a string.
 *
 * @param big_integer number to be converted to a string.
 * @param char * is the string that will hold the big_number as a string and it must have a
 *     length of big_integer.size + 1.
 */
void big_integer_to_string(struct big_integer *bi, char *str);

/* Destroys the big integer.
 *
 * @param big_inteter number to be destroy.
 */
void big_integer_destroy(struct big_integer *bi);

/* Calculates the factorial of the given number.
 *
 * The factorial of a number is defined as:
 *
 * n! means n x (n - 1) x ... x 3 x 2 x 1
 *
 * @param number that will be used to calculate the factorial.
 * @return the big_integer number that contains the result.
 */
struct big_integer* big_integer_factorial(struct big_integer* number);

/* Returns the hash of a struct big_integer.
 *
 * @param ptr is a pointer to a struch hash_elem.
 */
uint32_t big_integer_hash(const struct hash_elem *ptr, void *aux);

/* Compares two big_integers  A and B. Returns true if A is less than B,
 * or false if A is greater than or equal to B.
 *
 *
 * Note: Given the string "123456", the big_integer representation is:
 *
 *   a[0] = 6
 *   a[1] = 5
 *   a[2] = 4
 *   a[3] = 3
 *   a[4] = 2
 *   a[5] = 1
 *
 * @param a is a struct hash_elem that is wrapped in a struct big_integer.
 * @param b is a struct hash_elem that is wrapped in a struct big_integer.
 * @param aux is an extra data.
 * @return true if A is less than B, or false if A is greater than or equal to B.
 */
bool big_integer_compare_asc(const struct hash_elem *a, const struct hash_elem *b, void *aux);

/* Releases the memory that was allocated to create the struct big_integer element..
 *
 * Running time: O(1)
 *
 * @param e is the pointer to the struct hash_elem.
 */
void big_integer_free_memory_hash(struct hash_elem *e, void *aux);

#endif /* lib/biginteger.h */
