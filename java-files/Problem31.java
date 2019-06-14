package org.algorithms.euler;

/**
 * Given the coins 1c, 5c, 10c and 25c, describe all the possible combinations that can be done
 * to get 1 dollar.
 *
 * @author jcyescas
 */
public class Problem31 {

  private static int coins[] = {1, 5, 10, 25};
  //private static int coins[] = {1, 2};
  public static int count(int value, int index) {

    if (value == 0) {
      return 1;
    }

    if (value < 0) {
      return 0;
    }

    int count = 0;

    for (int i = index; i < coins.length; i++) {
      count += count (value - coins[i], i);
    }

    return count;
  }

  public static void main(String[] args) {
    System.out.println("Count combinations");


    System.out.println("# " + count(100, 0));
  }
}
