package org.algorithms.euler;

import java.util.ArrayList;
import java.util.List;

/**

Longest Collatz sequence

Problem 14

The following iterative sequence is defined for the set of positive integers:

n -> n/2 (n is even)
n -> 3n + 1 (n is odd)

Using the rule above and starting with 13, we generate the following sequence:

13 -> 40 -> 20 -> 10 -> 5 -> 16 -> 8 -> 4 -> 2 -> 1

It can be seen that this sequence (starting at 13 and finishing at 1)
contains 10 terms. Although it has not been proved yet (Collatz Problem),
it is thought that all starting numbers finish at 1.

Which starting number, under one million, produces the longest chain?

NOTE: Once the chain starts the terms are allowed to go above one million.
 */
public class Problem14 {

  /**
   * Gets the Collatz sequence.
   *
   * @param number
   * @return the Collatz sequence for the given number.
   */
  public static List<Long> getCollatzSequence(long number) {
    List<Long> list = new ArrayList<Long>();

    list.add(number);

    while (number != 1) {
      if (number % 2 == 0) {
        number = number / 2;
      } else {
        number = 3 * number + 1;
      }

      list.add(number);
    }

    return list;
  }

  public static void main(String[] args) {
    System.out.println("Collatz sequence");

    int number = 1000000;

    long longestSequence = 0;
    for (int i = number; i >= 1; i--) {
      List<Long> sequence = getCollatzSequence(i);
      if (sequence.size() > longestSequence) {
        longestSequence = sequence.size();
        System.out.println(sequence + ", size " + sequence.size());

      }
    }

    System.out.println("The longest sequence has " + longestSequence + " elements.");
  }

}
