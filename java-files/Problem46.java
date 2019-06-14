package org.algorithms.euler;

/**
 * Goldbach's other conjecture
 *
 * Problem 46
 *
 * It was proposed by Christian Goldbach that every odd composite number
 * can be written as the sum of a prime and twice a square.
 *
 * 9 = 7 + 2x1^2
 * 15 = 7 + 2x2^2
 * 21 = 3 + 2x3^2
 * 25 = 7 + 2x3^2
 * 27 = 19 + 2x2^2
 * 33 = 31 + 2x1^2
 *
 * It turns out that the conjecture was false.
 *
 * What is the smallest odd composite that cannot be written as the sum of a
 * prime and twice a square?
 *
 * Note: A composite number is a positive integer that has at least one positive
 * divisor other than one or the number itself. In other words, a composite
 * number is any positive integer greater than one that is not a prime number.
 *
 * How to solve it
 *
 * Composite = Prime + 2 * n ^ 2
 *
 * First create a Sieve of Eratosthenes of about 1 million (increase if the
 * composite number is not found among this range).
 * Get the first odd composite number using the Sieve of Eratosthenes.
 * Given the formula:
 *   Composite - 2 * n ^ 2 = Prime
 *
 * Try to solve this equation, if a prime number can not be found, that means
 * that we are done.
 *
 */
public class Problem46 {

  public static void main(String[] args) {
    int size = 1000000;
    //int size = 100;
    boolean sieve[] = SieveOfEratosthenes.create(size);

    for (int composite = 2; composite < sieve.length; composite++) {
      if (!sieve[composite] && composite % 2 != 0) {
        boolean found = false;
        for (int n = 1; n < composite / 2; n++) {
          int prime = composite - 2 * (n * n);
          if (prime > 0 && sieve[prime]) {
            found = true;
            break;
          }
        }

        if (!found) {
          System.out.println("The odd composite number is " + composite);
          break;
        }
      }
    }
  }
}
