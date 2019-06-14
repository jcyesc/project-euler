package org.algorithms.euler;

import java.util.HashMap;
import java.util.Map;

/**
 * Pandigital products
Problem 32
We shall say that an n-digit number is pandigital if it makes use of all the
digits 1 to n exactly once; for example, the 5-digit number, 15234,
is 1 through 5 pandigital.

The product 7254 is unusual, as the identity, 39 x 186 = 7254, containing
multiplicand, multiplier, and product is 1 through 9 pandigital.

Find the sum of all products whose multiplicand/multiplier/product identity
can be written as a 1 through 9 pandigital.

HINT: Some products can be obtained in more than one way so be sure to only
include it once in your sum
 */
public class Problem32 {

  public static boolean isPandigital(String s) {

    Map<String, Integer> map = new HashMap<String, Integer>();
    for (int i = 0; i < s.length(); i++) {
      if (s.charAt(i) == '0') {
        return false;
      }

      if (map.put(s.charAt(i) + "", 1) != null) {
        return false;
      }
    }

    return true;
  }

  public static void main(String[] args) {
    Map<Integer, String> map = new HashMap<Integer, String>();
    int total = 0;
    for (int i = 1; i <= 9999; i++) {
      for (int j = i + 1; j <= 9999; j++) {
        int result = i * j;
        StringBuffer st = new StringBuffer();
        if (st.append(i).append(j).append(result).length() == 9) {
          if (isPandigital(st.toString()) && map.get(result) == null) {
            System.out.println(i + " x " + j + " = " + result);
            map.put(result, st.toString());
            total += result;
          }
        }
          // 475687
      }
    }

    System.out.println("The result is " + total);
  }
}
