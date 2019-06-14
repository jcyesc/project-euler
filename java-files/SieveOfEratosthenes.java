package org.algorithms.euler;


public class SieveOfEratosthenes {

  public static boolean[] create(int size) {
    boolean sieve[] = new boolean[size];
    sieve[0] = false;
    sieve[1] = false;
    
    for (int i = 2; i < size; i++) {
      sieve[i] = true;
    }
    
    for (int i = 2; i < size; i++) {
      for (int j = i + i; j < size; j = j + i) {
        sieve[j] = false;
      }
    }
    
    return sieve;
  }
  
  public static void print(boolean[] sieve) {
    int count = 0;
    for (int i = 0; i < sieve.length; i++) {
      if (sieve[i]) {
        System.out.print(i + "\t");
        count++;
        if (count % 20 == 0 && count > 0) {
          System.out.println();
        }
      }
    }
  }
  
  public static void main(String[] args) {
    boolean sieve[] = create(1000);
    print(sieve);
  }
  
}

