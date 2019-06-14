package org.algorithms.euler;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Using names.txt (right click and 'Save Link/Target As...'), a 46K text file
 * containing over five-thousand first names, begin by sorting it into
 * alphabetical order. Then working out the alphabetical value for each name,
 * multiply this value by its alphabetical position in the list to obtain a
 * name score.
 *
 * For example, when the list is sorted into alphabetical order,
 * COLIN, which is worth 3 + 15 + 12 + 9 + 14 = 53, is the 938th name in the
 * list. So, COLIN would obtain a score of 938 x 53 = 49714.
 *
 * What is the total of all the name scores in the file?
 */
public class Problem22 {

  public static void main(String[] args) throws IOException {
    FileInputStream fi = new FileInputStream("/Users/jcyescas/development/computing/workspaces/javaAlgorithms/project-euler/src/org/algorithms/euler/names.txt");

    BufferedReader br = new BufferedReader(new InputStreamReader(fi));

    String names = br.readLine();

    names = names.replaceAll("\"", "");
    names = names.replaceAll(",", " ");
    System.out.println(names);
    String arr[] = names.split(" ");
    List<String> list = new ArrayList<String>();

    for (String name : arr) {
      list.add(name);
    }

    Collections.sort(list);

    System.out.println(list);

    long total = 0;
    for (int j = 0; j < list.size(); j++) {
      String s = list.get(j);

      int subtotal = 0;
      for (int i = 0; i < s.length(); i++) {
        subtotal += (s.charAt(i) - 'A') + 1;
      }

      total += (subtotal * (j + 1));
    }

    br.close();
    System.out.println(total);
  }
}
