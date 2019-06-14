package org.algorithms.euler;

/**
 * Truncatable primes
 * Problem 37
 *
 * The number 3797 has an interesting property. Being prime itself, it is
 * possible to continuously remove digits from left to right, and remain prime
 * at each stage: 3797, 797, 97, and 7. Similarly we can work from right to
 * left: 3797, 379, 37, and 3.
 * 
 * Find the sum of the only eleven primes that are both truncatable from
 * left to right and right to left.
 *
 * NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.
 */
public class Problem37 {

  public static boolean isTruncatablePrime(int number, boolean sieve[]) {
    String prime = String.valueOf(number);
    
    for (int i = 0; i < prime.length(); i++) {
      String sub = prime.substring(i);
      if (!sieve[Integer.parseInt(sub)]) {
        return false;
      }
    }

    for (int i = 1; i <= prime.length(); i++) {
      String sub = prime.substring(0, i);
      if (!sieve[Integer.parseInt(sub)]) {
        return false;
      }
    }
    
    return true;
  }
  
  public static void main(String[] args) {

    boolean sieve[] = SieveOfEratosthenes.create(1000000);
 
    int truncableNumbers = 0;
    int total = 0;
    for (int i = 10; i < sieve.length && truncableNumbers < 12; i++) {
      
      if (sieve[i] && isTruncatablePrime(i, sieve)) {
        truncableNumbers++;
        total += i;
        System.out.println(i);
      }
    }
    System.out.println("Sum of the only eleven primes that are both truncatable: " + total);
  }
}
