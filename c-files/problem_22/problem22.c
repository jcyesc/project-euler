/*
 * Names scores
 *
 * Problem 22
 *
 * Using names.txt (right click and 'Save Link/Target As...'), a 46K text file containing over
 * five-thousand first names, begin by sorting it into alphabetical order. Then working out
 * the alphabetical value for each name, multiply this value by its alphabetical position
 * in the list to obtain a name score.
 *
 * For example, when the list is sorted into alphabetical order, COLIN, which
 * is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the list. So, COLIN would obtain a
 * score of 938 x 53 = 49714.
 *
 * What is the total of all the name scores in the file?
 *
 * problem22.c
 *
 *  Created on: Jan 16, 2014
 *      Author: jcyescas
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/util.h"
#include "../lib/list.h"


struct list *get_sorted_list_names(char *file_name) {
  // Opening the file.
  FILE *file = fopen("names.txt", "r");
  if (file  == NULL) {
    printf("\nFile couldn't be opened!!!");
    exit(0);
  }

  struct list *names = malloc(sizeof(struct list));
  list_init(names);

  char name[20];
  // Reading the names from the file.
  while (fscanf(file, "%s ", name) != EOF) {
    //printf("\n%s", name);

    char *tmp_name = malloc(sizeof(strlen(name) + 1));
    sprintf(tmp_name, "%s", name);

    struct string_obj *str = malloc(sizeof(struct string_obj));
    str->string = tmp_name;

    // Inserting the elements in the sorted list.
    list_insert_ordered(names, &str->elem ,compare_string_obj_asc, NULL);
  }

  fclose(file);

  return names;
}


int main() {
  printf("\nNames scores");

  char *file_name = "names.txt";
  struct list *names = get_sorted_list_names(file_name);

  struct string_obj *str;
  struct list_elem *temp;
  int position = 0;
  int total = 0;
  for (temp = list_begin(names); temp != list_end(names); temp = list_next(temp)) {
    position++;
    str = list_entry(temp, struct string_obj, elem);
    printf("\n%s", str->string);
    int size = strlen(str->string);
    int i;
    int subtotal = 0;
    for (i = 0; i < size; i++) {
      subtotal += (str->string[i] - 'A') + 1;
    }
    total += position * subtotal;
  }

  printf("\nThe total of all the name scores in the file is %d", total);

  free_memory_string_obj_list(names);
  free(names);

  return 0;
}
