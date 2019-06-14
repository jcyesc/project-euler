package org.algorithms.euler;

/**
 * Champernowne's constant
 *
 * Problem 40
 * An irrational decimal fraction is created by concatenating the positive integers:
 *
 * 0.123456789101112131415161718192021...
 *
 * It can be seen that the 12th digit of the fractional part is 1.
 *
 * If dn represents the nth digit of the fractional part, find the value of the following expression.
 *
 * d1 x d10 x d100 x d1000 x d10000 x d100000 x d1000000
 *
 */
public class Problem40 {

  public static void main(String[] args) {
    StringBuffer sb = new StringBuffer();
    int limit = 1000000;
    for (int i = 1; i <= limit; i++) {
      sb.append(i);
    }

    int total = 1;
    for (int i = 1; i <= limit; i*= 10) {
      System.out.println(sb.charAt(i - 1));
      total *= Integer.parseInt(sb.charAt(i - 1) + "");
    }

    System.out.println("Total: " + total);
  }

  public static void main1(String[] args) {
    String sb = new String();
    int limit = 1000000;
    for (int i = 1; i <= limit; i++) {
      sb += "" + i;
    }

    int total = 1;
    for (int i = 1; i <= limit; i*= 10) {
      System.out.println(sb.charAt(i - 1));
      total *= Integer.parseInt(sb.charAt(i - 1) + "");
    }

    System.out.println("Total: " + total);
  }
}
