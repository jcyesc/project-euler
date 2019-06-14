package org.algorithms.euler;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

/**
 * Integer right triangles
 * Problem 39
 *
 * Published on Friday, 14th March 2003, 06:00 pm; Solved by 34357
 * If p is the perimeter of a right angle triangle with integral length sides,
 * {a,b,c}, there are exactly three solutions for p = 120.
 *
 * {20,48,52}, {24,45,51}, {30,40,50}
 *
 * For which value of p ≤ 1000, is the number of solutions maximized?
 */
public class Problem39 {

  public static Map<Integer, Set<Triangle>> getTrianglesMap(int maxPerimeter) {
    Map<Integer, Set<Triangle>>  trianglesMap =
          new HashMap<Integer, Set<Triangle>>();

    int limit = maxPerimeter / 2;
    for (int a = 1; a < limit; a++) {
      for (int b = a; b < limit; b++) {
        for (int c = b; c < limit; c++) {
          int p = a + b + c;
          if ((p <= maxPerimeter) && Triangle.isRightTriangle(a, b, c)) {
            Set<Triangle> triangles = trianglesMap.get(p);
            if (triangles == null) {
              triangles = new HashSet<Triangle>();
              trianglesMap.put(p, triangles);
            }
            triangles.add(new Triangle(a, b, c));
          }
        }
      }
    }

    return trianglesMap;
  }

  public static void main(String[] args) {
    System.out.println("Triangles");
    Map<Integer, Set<Triangle>> maps = getTrianglesMap(1000);

    int keyMax = 0;
    int max = 0;
    for (Integer key: maps.keySet()) {
      if (maps.get(key).size() > max) {
        max = maps.get(key).size();
        keyMax = key;
      }
    }

    System.out.println("Key: " + keyMax + " #Elements: " + max);
    System.out.println(maps.get(keyMax));
  }
}

class Triangle {
  private int a;
  private int b;
  private int c;

  public Triangle() {
  }

  public Triangle(int a, int b, int c) {
    this.a = a;
    this.b = b;
    this.c = c;
  }

  public static  boolean isRightTriangle(int a, int b, int c) {
    if (Math.pow(c, 2) == (Math.pow(a, 2) + Math.pow(b, 2))) {
      return true;
    }

    return false;
  }

  @Override
  public String toString() {
    return "{" + a + ", " + b + ", " + c + "}";
  }

  @Override
  public int hashCode() {
    return a * 7 + b * 7 + c * 7;
  }
  @Override
  public boolean equals(Object obj) {
    if (obj instanceof Triangle) {
      Triangle rt = (Triangle) obj;
      Set<Integer> set = new HashSet<Integer>();
      set.add(a);
      set.add(b);
      set.add(c);
      set.add(rt.a);
      set.add(rt.b);
      set.add(rt.c);
      return set.size() == 3;
    }

    return false;
  }
}