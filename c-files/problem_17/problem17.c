/*
 * Number letter counts
 *
 *
 * Problem 17
 *
 * If the numbers 1 to 5 are written out in words: one, two, three, four, five,
 * then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
 *
 * If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words,
 * how many letters would be used?
 *
 * NOTE:
 * Do not count spaces or hyphens. For example, 342 (three hundred and forty-two) contains 23
 * letters and 115 (one hundred and fifteen) contains 20 letters. The use of "and" when writing
 * out numbers is in compliance with British usage.
 *
 * Examples:
 *
 * One hundred
 * One hundred and one
 * One thousand
 *
 * problem17.c
 *
 *  Created on: Jan 3, 2014
 *      Author: jcyescas
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


/* Counts the number of letters in the string. It doesn't count the spaces.
 *
 * @param str is the pointer to the string.
 */
uint32_t count_number_letters(char *str) {
  size_t size = strlen(str);
  uint32_t counter = 0;
  int32_t i;
  for (i = 0; i < size; i++) {
    if (str[i] != ' ') {
      counter++;
    }
  }

  return counter;
}

/* Converts the one digit number to string representation.
 *
 * @param number to be converted to string.
 * @param string that will store the string representation of the number.
 */
void convert_digit_to_string(uint8_t number, char string[]) {
  switch (number) {
    case 0:
      sprintf(string, "%s", "zero");
      break;
    case 1:
      sprintf(string, "%s", "one");
      break;
    case 2:
      sprintf(string, "%s", "two");
      break;
    case 3:
      sprintf(string, "%s", "three");
      break;
    case 4:
      sprintf(string, "%s", "four");
      break;
    case 5:
      sprintf(string, "%s", "five");
      break;
    case 6:
      sprintf(string, "%s", "six");
      break;
    case 7:
      sprintf(string, "%s", "seven");
      break;
    case 8:
      sprintf(string, "%s", "eight");
      break;
    case 9:
      sprintf(string, "%s", "nine");
      break;
  }
}

/* Converts the two digit number to string representation. The digits to covert are in the range:
 *   10 to 19
 *   20, 30, 40, 50, 60, 70, 80, 90
 *
 * @param number to be converted to string.
 * @param string that will store the string representation of the number.
 */
void convert_two_digit_to_string(uint8_t number, char string[]) {
  switch (number) {
    case 10:
      sprintf(string, "%s", "ten");
      break;
    case 11:
      sprintf(string, "%s", "eleven");
      break;
    case 12:
      sprintf(string, "%s", "twelve");
      break;
    case 13:
      sprintf(string, "%s", "thirteen");
      break;
    case 14:
      sprintf(string, "%s", "fourteen");
      break;
    case 15:
      sprintf(string, "%s", "fifteen");
      break;
    case 16:
      sprintf(string, "%s", "sixteen");
      break;
    case 17:
      sprintf(string, "%s", "seventeen");
      break;
    case 18:
      sprintf(string, "%s", "eighteen");
      break;
    case 19:
      sprintf(string, "%s", "nineteen");
      break;
    case 20:
      sprintf(string, "%s", "twenty");
      break;
    case 30:
      sprintf(string, "%s", "thirty");
      break;
    case 40:
      sprintf(string, "%s", "forty");
      break;
    case 50:
      sprintf(string, "%s", "fifty");
      break;
    case 60:
      sprintf(string, "%s", "sixty");
      break;
    case 70:
      sprintf(string, "%s", "seventy");
      break;
    case 80:
      sprintf(string, "%s", "eighty");
      break;
    case 90:
      sprintf(string, "%s", "ninety");
      break;
  }
}

/* Converts the two digit number to string representation. The digits to covert are in the range:
 *   100, 200, 300, 400, 500, 600, 700, 800, 900
 *
 * @param number to be converted to string.
 * @param string that will store the string representation of the number.
 */
void convert_three_digit_to_string(uint32_t number, char string[]) {
  switch (number) {
    case 100:
      sprintf(string, "%s", "one hundred");
      break;
    case 200:
      sprintf(string, "%s", "two hundred");
      break;
    case 300:
      sprintf(string, "%s", "three hundred");
      break;
    case 400:
      sprintf(string, "%s", "four hundred");
      break;
    case 500:
      sprintf(string, "%s", "five hundred");
      break;
    case 600:
      sprintf(string, "%s", "six hundred");
      break;
    case 700:
      sprintf(string, "%s", "seven hundred");
      break;
    case 800:
      sprintf(string, "%s", "eight hundred");
      break;
    case 900:
      sprintf(string, "%s", "nine hundred");
      break;
  }
}

/* Converts the two digit number to string representation. The digits to covert are in the range:
 *   10 to 99.
 *
 * @param number to be converted to string.
 * @param string that will store the string representation of the number.
 */
void convert_two_digit_number_to_string(uint8_t number, char string[]) {
  uint8_t digit = number % 10;
  uint8_t tens = number / 10;

  // Numbers greater or equal to 20.
  if (tens > 1) {
    char tmp_digit[30];
    char tmp_tens[30];

    if (digit == 0) {
      convert_two_digit_to_string(tens * 10, tmp_tens);
      sprintf(string, tmp_tens, tens * 10);
      return;
    } else {
      convert_digit_to_string(digit, tmp_digit);
      convert_two_digit_to_string(tens * 10, tmp_tens);
      sprintf(string, "%s %s", tmp_tens, tmp_digit);
      return;
    }
  } else {
    // Numbers lest than or equal to 19 and greater than 9.
    convert_two_digit_to_string(number, string);
    return;
  }
}

/* Converts the two digit number to string representation. The digits to covert are in the range:
 *   100 to 999.
 *
 * @param number to be converted to string.
 * @param string that will store the string representation of the number.
 */
void convert_three_digit_number_to_string(uint32_t number, char string[]) {
  uint32_t two_digits = number % 100;
  uint32_t hundreds = number / 100;

  if (two_digits == 0) {
    convert_three_digit_to_string(number, string);
    return;
  }

  char tmp_digits[30];
  char tmp_hundreds[30];
  convert_three_digit_to_string(hundreds * 100, tmp_hundreds);

  if (two_digits < 10) {
    convert_digit_to_string(two_digits, tmp_digits);
  } else {
    convert_two_digit_number_to_string(two_digits, tmp_digits);
  }

  sprintf(string, "%s and %s", tmp_hundreds, tmp_digits);
}

/* Converts the given number to string. The range of numbers supported is from 0 to 1000.
 *
 * @param number To convert to string.
 * @param string To store the number with letters.
 */
void convert_number_to_string(uint32_t number, char string[]) {
  // Four digits numbers
  if (number == 1000) {
    sprintf(string, "%s", "One thousand");
    return;
  }

  // Three digits numbers
  if (number / 100 != 0) {
    convert_three_digit_number_to_string(number, string);
    return;
  }

  // Two digits numbers
  if (number / 10 != 0) {
    convert_two_digit_number_to_string(number, string);
    return;
  }

  // One digit number
  if (number / 10 == 0) {
    convert_digit_to_string(number, string);
    return;
  }

}

int main() {
  printf("Number letter counts\n");

  char number[100];
  uint32_t counter = 0;

  uint32_t i;
  for (i = 1; i <= 1000; i++) {
   convert_number_to_string(i,number);
   counter += count_number_letters(number);
   printf("\n%u - %s", i, number);
  }

  printf("\nNumber of letters %u", counter);
}
