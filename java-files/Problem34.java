package org.algorithms.euler;

/**
 * Digit factorials
 * 
 * Problem 34
 * 
 * 145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.
 * 
 * Find the sum of all numbers which are equal to the sum of the factorial of their digits.
 * 
 * Note: as 1! = 1 and 2! = 2 are not sums they are not included.
 * 
 * The huge number need to be at the end.
 * 
 */
public class Problem34 {

  public static int[] factorialDigits = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
  
  public static boolean isCuriousNumber(long number) {
    String value = String.valueOf(number);
    
    int sum = 0;
    for (int i = 0; i < value.length(); i++) {
      sum += factorialDigits[value.charAt(i) - '0'];
    }
    
    return sum == number;
  }
  
  
  public static int sumAllCuriousNumber () {
    int sum = 0;
    double limit = 1000000000;
    
    for (int i = 3; i < limit; i++ ) {
      if (isCuriousNumber(i)) {
        sum += i;
        System.out.println("Curious " + i);
      }
    }
    
    return sum;
  }
  
  public static void main(String[] args) {
    System.out.println(isCuriousNumber(145));

    int result = sumAllCuriousNumber();
    System.out.println("Sum all curious number: " + result);
    
  }
  
}
