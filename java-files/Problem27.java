package org.algorithms.euler;

/**
 * Quadratic primes
 *
 * Problem 27
 *
 * Euler discovered the remarkable quadratic formula:
 *
 * n^2 + n + 41
 *
 * It turns out that the formula will produce 40 primes for the consecutive
 * values n = 0 to 39. However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is
 * divisible by 41, and certainly when n = 41, 41^2 + 41 + 41 is clearly
 * divisible by 41.
 *
 * The incredible formula  n^2 - 79n + 1601 was discovered, which produces
 * 80 primes for the consecutive values n = 0 to 79. The product of the
 * coefficients, -79 and 1601, is -126479.
 *
 * Considering quadratics of the form:
 *
 * n^2 + an + b, where |a| < 1000 and |b| < 1000
 *
 * where |n| is the modulus/absolute value of n
 *
 * e.g. |11| = 11 and |-4| = 4
 *
 * Find the product of the coefficients, a and b, for the quadratic
 * expression that produces the maximum number of primes for consecutive
 * values of n, starting with n = 0.
 *
 * How to solve it
 *
 * First: Create a sieve of Eratosthenes that contains about 1 million of elements.
 * Second: Have two nested loops, one for a, and one b.
 * Third: Evaluate the quadratic formula and check how many prime numbers produce
 *     and selects the one that produce the maximum number of primes
 * Fourth: Select the
 *
 * Result:
 * a = -61, b = 971, #71 (a * b = -59231)
 * The max number of primes the quadratic formula produces is 71
 *
 */
public class Problem27 {


  public static boolean sieve[] = SieveOfEratosthenes.create(1000000);

  public static int getNumberOfPrimesProduce(int a, int b) {
    int numberPrimes = 0;

    for (int n = 0; n < sieve.length; n++) {
      int result = (n * n) + (a * n) + b;
      if (result > 0 && sieve[result]) {
        numberPrimes++;
        continue;
      }

      break;
    }

    return numberPrimes;
  }

  public static void main(String[] args) {

    int maxNumberPrimes = 0;

    for (int a = -999; a < 1000; a++) {
      for (int b = -999; b < 1000; b++) {
        int result = getNumberOfPrimesProduce(a, b);
        if (result > maxNumberPrimes) {
          maxNumberPrimes = result;
          System.out.println(String.format("a = %d, b = %d, #%d, (a * b = %d)",
              a, b, maxNumberPrimes, a * b));
        }
      }
    }

    System.out.println("The max number of primes the quadratic formula produces is " + maxNumberPrimes);
  }
}
