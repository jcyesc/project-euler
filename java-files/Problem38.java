package org.algorithms.euler;

import java.util.HashMap;
import java.util.Map;

/**
 * Take the number 192 and multiply it by each of 1, 2, and 3:
 *
 * 192 x 1 = 192
 * 192 x 2 = 384
 * 192 x 3 = 576
 *
 * By concatenating each product we get the 1 to 9 pandigital, 192384576.
 * We will call 192384576 the concatenated product of 192 and (1,2,3)
 *
 * The same can be achieved by starting with 9 and multiplying by 1, 2, 3, 4,
 * and 5, giving the pandigital, 918273645, which is the concatenated product of
 * 9 and (1,2,3,4,5).
 *
 * What is the largest 1 to 9 pandigital 9-digit number that can be formed as
 * the concatenated product of an integer with (1,2, ... , n) where n > 1?
 *
 */
public class Problem38 {

  public static boolean isPandigital(String s) {

    if (s.length() != 9) {
      return false;
    }

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
    System.out.println("Executing");
    for (int i = 9000; i <= 9999; i++) {
      String value = "";
      for (int j = 1; j <= 999; j++) {
        value += (i * j);

        if (value.length() == 9 && isPandigital(value)) {
          System.out.println(value);
        }

        if (value.length() > 9) {
          break;
        }
      }
    }
  }
}
