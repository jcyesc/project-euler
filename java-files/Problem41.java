package org.algorithms.euler;

/**
 * Pandigital prime
 * 
 * Problem 41
 * We shall say that an n-digit number is pandigital if it makes use of all the
 * digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is
 * also prime.
 * 
 * What is the largest n-digit pandigital prime that exists?
 * 
 * Solution
 * 
 * Start from the largest number that is posible for this case 999,999,999
 * 
 * Pandigital that is prime: 7652413
 * 
 */
public class Problem41 {
  
  public static boolean isPandigital(String s) {
    if (s.length() == 0) {
      return false;
    }
    
    for (int i = 0; i < s.length(); i++) {
      if (!s.contains(String.valueOf(i + 1))) {
        return false;
      }
    }
    return true;
  }
  
  
  public static void main(String[] args) {
    int size = 1000000000;
    boolean sieve[] = SieveOfEratosthenes.create(size);
    System.out.println("Sieve is ready!");
    //SieveOfEratosthenes.print(sieve);
    
    for (int i = size -1; i >= 0; i--) {
      if (sieve[i]) {
        if (isPandigital(String.valueOf(i))) {
          System.out.println("Pandigital that is prime: " + i);
          return;
        }
      }
    }
    
  }
}
