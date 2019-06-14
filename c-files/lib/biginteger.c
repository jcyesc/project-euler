/* Provides a library for managing Big integer numbers.
 *
 * biginteger.c
 *
 *  Created on: Dec 29, 2013
 *      Author: jcyescas
 */

#include "biginteger.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
struct big_integer *big_integer_create_from_string(char *string) {
  struct big_integer *bi = malloc(sizeof (struct big_integer));
  uint32_t size = strlen(string);
  bi->number = malloc (sizeof (uint8_t) * size);
  bi->size = size;

  int32_t i, j;
  for (i = size - 1, j = 0; i >= 0; i--, j++) {
    bi->number[j] = string[i] - '0'; // Converting the ASCII Code to the appropriate number.
  }

  return bi;
}

/* Creates a big_integer of the given size.
 *
 * @param size of the big_integer to be created.
 */
struct big_integer *big_integer_create(uint32_t size) {
  struct big_integer *bi = calloc(1, sizeof(struct big_integer));
  bi->number = calloc(1, sizeof (uint8_t) * size);
  bi->size = size;

  return bi;
}

/* Clones a big_integer
 *
 * @param big_int to clone.
 */
struct big_integer *big_integer_clone(struct big_integer *big_int) {
  struct big_integer *bi = malloc(sizeof (struct big_integer));
  bi->number = malloc (sizeof (uint8_t) * big_int->size);
  bi->size = big_int->size;

  int32_t index;
  for (index = 0; index < big_int->size; index++) {
    bi->number[index] = big_int->number[index];
  }

  return bi;
}

/* Adds two big integers.
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */
struct big_integer *big_integer_add(struct big_integer *b1, struct big_integer *b2) {
  uint32_t size = b1->size > b2->size ? b1->size : b2->size;
  uint8_t numbers[size];
  uint8_t carry = 0;
  uint8_t digit = 0;
  uint8_t tmp = 0;

  int32_t i;
  // Adding the two big integers.
  for (i = 0; i < b1->size && i < b2->size; i++) {
    tmp = b1->number[i] + b2->number[i] + carry;
    digit = tmp % 10;
    carry = tmp / 10;
    numbers[i] = digit;
  }

  // If b1 is longer than b2, continue adding b1 with the carry.
  if (i < b1->size) {
    for (; i < b1->size; i++) {
      tmp = b1->number[i] + carry;
      digit = tmp % 10;
      carry = tmp / 10;
      numbers[i] = digit;
    }
  } else if (i < b2->size) {
    // If b2 is longer than b1, continue adding b2 with the carry.
    for (; i < b2->size; i++) {
      tmp = b2->number[i] + carry;
      digit = tmp % 10;
      carry = tmp / 10;
      numbers[i] = digit;
    }
  }

  // Creating the big_integer
  struct big_integer *result;
  if (carry > 0) {
    result = big_integer_create(size + 1);
    for (i = 0; i < size; i++) {
      result->number[i] = numbers[i];
    }
    result->number[i] = carry;
  } else {
    result = big_integer_create(size);
    for (i = 0; i < size; i++) {
      result->number[i] = numbers[i];
    }
  }

  return result;
}

/* Subtracts two big integers.
 *
 * Note:  First number has to be greater than second.
 *     A better implementation of this function would use "The method of complements".
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */
struct big_integer *big_integer_subtract(struct big_integer *b1, struct big_integer *b2) {
  uint32_t size = b1->size > b2->size ? b1->size : b2->size;
  uint8_t numbers[size];
  uint8_t carry = 0;
  uint8_t digit = 0;

  int32_t i;
  // Subtracting the two big integers.
  for (i = 0; i < b1->size && i < b2->size; i++) {
    uint8_t subtrahend = b2->number[i] + carry;
    if (b1->number[i] > subtrahend) {
      digit = b1->number[i] - subtrahend;
      carry = 0;
    } else if (b1->number[i] == subtrahend){
      digit = 0;
      carry = 0;
    } else {
      digit = (b1->number[i] + 10) - subtrahend;
      carry = 1;
    }

    numbers[i] = digit;
  }

  // If b1 is longer than b2, continue subtracting b1 with the carry.
  if (i < b1->size) {
    for (; i < b1->size; i++) {
      if (b1->number[i] > carry) {
        digit = b1->number[i] - carry;
        carry = 0;
      } else if (b1->number[i] == carry){
        digit = 0;
        carry = 0;
      } else {
        digit = (b1->number[i] + 10) - carry;
        carry = 1;
      }
      numbers[i] = digit;
    }
  }

  // Find the first not left zero.
  int32_t j;
  for (j = (int32_t) size - 1; j >= 0; j--) {
    if (numbers[j] != 0) {
      break;
    }
  }

  // Returns zero if all the digits are zero.
  if (j < 0) {
    return big_integer_create_from_string("0");
  }

  uint32_t size_new_big = j + 1;

  // Creating the big_integer
  struct big_integer *result = big_integer_create(size_new_big);

  for (; j >= 0; j--) {
    result->number[j] = numbers[j];
  }

  return result;
}

/* Multiplies two big integers.
 *
 * Note: The current implementation just adds the b1 big_number b2 times. This is a really bad
 * implementation.
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */

struct big_integer *big_integer_multiply_inefficient(struct big_integer *b1, struct big_integer *b2) {
  struct big_integer *one = big_integer_create_from_string("1");
  struct big_integer *result = big_integer_clone(b1);
  struct big_integer *tmp;
  struct big_integer *index = big_integer_create_from_string("1");

  while (!big_integer_equals(index, b2)) {
      // Increasing the counter
      tmp = index;
      index = big_integer_add(index, one);
      big_integer_destroy(tmp);

      // Adding first big integer.
      tmp = result;
      result = big_integer_add(result, b1);
      big_integer_destroy(tmp);
  }

  big_integer_destroy(index);
  big_integer_destroy(one);

  return result;
}

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
struct big_integer *big_integer_shift(struct big_integer *b1, int32_t positions) {
  uint32_t new_size = b1->size + positions;
  struct big_integer *result = big_integer_create(new_size);
  uint32_t i;
  for (i = 0; i < b1->size; i++) {
    result->number[i + positions] = b1->number[i];
  }

  return result;
}

/* Multiplies two big integers.
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
 * @param b1 first big_integer
 * @param b2 second big_integer
 */

struct big_integer *big_integer_multiply(struct big_integer *b1, struct big_integer *b2) {
  struct big_integer *result = big_integer_create_from_string("0");
  struct big_integer *tmp;

  uint32_t j;
  for (j = 0; j < b2->size; j++) {
    tmp = big_integer_create(b1->size);
    uint32_t i;
    int32_t carry = 0;
    for (i = 0; i < b1->size; i++) {
       int32_t intermediate = b1->number[i] * b2->number[j] + carry;
       tmp->number[i] = intermediate % 10;
       carry = intermediate / 10;
    }

    if (carry != 0) {
      // Resizing the big integer.
      struct big_integer *tmp_res = big_integer_create(tmp->size + 1); // Size + carry.
      int index;
      for (index = 0; index < tmp->size; index++) {
        tmp_res->number[index] = tmp->number[index];
      }
      tmp_res->number[index] = carry;
      big_integer_destroy(tmp);
      tmp = tmp_res;
    }

    // Shifting to the left
    struct big_integer *tmp2 = big_integer_shift(tmp, j);
    big_integer_destroy(tmp);

    // Adding to result.
    struct big_integer *tmp_result = big_integer_add(tmp2, result);
    big_integer_destroy(tmp2);
    big_integer_destroy(result);
    result = tmp_result;
  }

  return result;
}


/* Calculates the power of the b1 big_number to the b2 big_numbers.
 *
 * b1 ^ b2
 *
 * @param b1 first big_integer
 * @param power big_integer
 */
struct big_integer *big_integer_pow(struct big_integer *b1, struct big_integer *power) {
  struct big_integer *zero = big_integer_create_from_string("1");
  struct big_integer *one = big_integer_create_from_string("1");

  if (big_integer_equals(power, zero)) {
      big_integer_destroy(zero);
      return one;
  }

  big_integer_destroy(zero);
  if (big_integer_equals(power, one)) {
      big_integer_destroy(one);
      return big_integer_clone(b1);
  }

  struct big_integer *result = big_integer_clone(b1);
  struct big_integer *tmp;
  struct big_integer *index = big_integer_create_from_string("1");

  while (!big_integer_equals(index, power)) {
      // Increasing the counter
      tmp = index;
      index = big_integer_add(index, one);
      big_integer_destroy(tmp);

      // Adding first big integer.
      tmp = result;
      result = big_integer_multiply(result, b1);
      big_integer_destroy(tmp);
  }

  big_integer_destroy(index);
  big_integer_destroy(one);

  return result;
}

/* Returns true if the two big_integers are equal, otherwise false.
 *
 * @param b1 first big_integer
 * @param b2 second big_integer
 */
bool big_integer_equals(struct big_integer *b1, struct big_integer *b2) {
  if (b1->size != b2->size)
    return false;

  int32_t index;
  for (index = 0; index < b1->size; index++) {
      if (b1->number[index] != b2->number[index])
        return false;
  }

  return true;
}

/* Converts the big_integer number to a string.
 *
 * @param big_integer number to be converted to a string.
 * @param char * is the string that will hold the big_number as a string and it must have a
 *     length of big_integer.size + 1.
 */
void big_integer_to_string(struct big_integer *bi, char *str) {

  int32_t i, j;
  for (i = bi->size - 1, j = 0; i >= 0; i--, j++) {
    // Converting the number to char
    char dig = (char) ('0' + bi->number[i]);
    str[j] = dig;
  }

  str[bi->size] = '\0';
}

/* Destroys the big integer.
 *
 * @param big_inteter number to be destroy.
 */
void big_integer_destroy(struct big_integer *bi) {
  // Releases the memory for the array.
  free (bi->number);
  // Releases the memory for the big_integer.
  free(bi);
}

/* Calculates the factorial of the given number.
 *
 * The factorial of a number is defined as:
 *
 * n! means n x (n - 1) x ... x 3 x 2 x 1
 *
 * @param number that will be used to calculate the factorial.
 * @return the big_integer number that contains the result.
 */
struct big_integer* big_integer_factorial(struct big_integer* number) {
  struct big_integer *index = big_integer_clone(number);
  struct big_integer *result = big_integer_create_from_string("1");
  struct big_integer *one = big_integer_create_from_string("1");
  struct big_integer *tmp;

  while (!big_integer_equals(one, index)) {
    tmp = result;
    result = big_integer_multiply(result, index);
    big_integer_destroy(tmp);

    tmp = index;
    struct big_integer *next_val = big_integer_subtract(index, one);
    index = next_val;
    big_integer_destroy(tmp);
  }

  big_integer_destroy(index);
  big_integer_destroy(one);

  return result;
}

/* Returns the hash of a struct big_integer.
 *
 * @param ptr is a pointer to a struch hash_elem.
 */
uint32_t big_integer_hash(const struct hash_elem *ptr, void *aux) {
  const struct big_integer *ln = (struct big_integer *) hash_entry(ptr, struct big_integer, hash_elem);
  char number[ln->size + 1];
  big_integer_to_string(ln, number);
  return hash_string(number);
}

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
bool big_integer_compare_asc(const struct hash_elem *a, const struct hash_elem *b, void *aux) {
  struct big_integer *an =  (struct big_integer *) hash_entry(a, struct big_integer, hash_elem);
  struct big_integer *bn =  (struct big_integer *) hash_entry(b, struct big_integer, hash_elem);

  if (an->size < bn->size) {
    return true;
  } else if (an->size > bn->size) {
    return false;
  }

  // If we are here, that means that the size are equals.
  int32_t i;
  for (i = an->size - 1; i >= 0; i--) {
    if (an->number[i] < bn->number[i]) {
      return true;
    } else if (an->number[i] > bn->number[i]) {
      return false;
    }
  }

  return false;
}

/* Releases the memory that was allocated to create the struct big_integer element..
 *
 * Running time: O(1)
 *
 * @param e is the pointer to the struct hash_elem.
 */
void big_integer_free_memory_hash(struct hash_elem *e, void *aux) {
  if (e == NULL)
    return;

  struct big_integer *bi = hash_entry(e, struct big_integer, hash_elem);
  big_integer_destroy(bi);
}
