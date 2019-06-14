package org.cs.algorithms.dp.permutations;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * Permutations of a string
 *
 * Design an algorithm to print all permutations of a string.
 *
 * Consider a test string abcdefg
 * 		Case "a"  --> {a}
 * 		Case "ab" --> {ab, ba}
 * 		Case "abc" --> {abc, bac, bca, acb, cab, cba}
 *
 * This is the first "interesting case" If we had the answer to P("ab"), how could we generate
 * P("abc")? Well, the additional letter is "c", so we can just stick c in at every possible point.
 *
 * We can see that when we add a new letter, we insert that letter into all locations of all
 * strings.
 *
 * Recursion Example
 * 	               P(abc) - combine and return list of permutations
 *                 /    \
 * 	              a     P(bc) - combine and return list of permutations.
 *                     /    \
 *                     b    P(c) - return list of permutations
 *
 * ALGORITHM
 *
 * PERMUTATE(s)
 *   if s.length == 0
 *   	return []
 *
 *   if s.length == 1
 *   	return [s]
 *
 *   s1 = get first character of s
 *   s2 = get the remaining of s
 *
 *   list = PERMUTATE(s2)
 *
 *   Insert s1 into  all locations of all strings in the list and add all this new
 *   permutations to the result.
 *
 * The running time of the algorithm is:
 *
 *  T(n) = T(n-1) + n ^ 2
 *  T(n) = n ^ 4
 *
 * Where T(n -) is the recursive call to PERMUTATE
 *
 * @author jcyescas
 *
 */
public class PermutateWord {

	public static List<String> permutate(String word) {
		if (word.length() == 0) {
			return new ArrayList<String>();
		}

		if (word.length() == 1) {
			List<String> list = new ArrayList<String>();
			list.add(word);
			return list;
		}

		String p1 = word.substring(0, 1);
		String p2 = word.substring(1);

		List<String> tmpList = permutate(p2);

		List<String> result = new ArrayList<String>();

		for (String s : tmpList) {
			result.addAll(combine(p1, s));
		}

		return result;
	}

	public static List<String> combine(String p1, String p2) {
		List<String> result = new ArrayList<String>();

		result.add(p1 + p2);
		for (int i = 1 ; i < p2.length(); i++) {
			String n = p2.substring(0, i) + p1 + p2.substring(i);
			result.add(n);
		}
		result.add(p2 + p1);
		return result;
	}

	public static void main(String[] args) {
		// System.out.println(combine("d", "abc"));
		System.out.println(permutate("abc"));
		System.out.println(permutate("abcd"));

		// In order to run this part is necessary to increase the HEAP SIZE with these parameters:
		// -Xms1024m -Xmx2g
		List<String> result = permutate("0123456789");
		Collections.sort(result);
		System.out.println("Size " + result.size() + ", Element: " + result.get(999999));

	}
}
