/* Given a positive int that is at most 10^6, does integer b exist 
 * so that the product of a and b only has digit '1'? 
 * If b exists, return the number of '1' in a*b;
 * If b does not exist, return -1. 
 *
 * Ref:
 * http://www.itint5.com/oj/#18
 *
 * dhu: It turns out that "b" exists for any integer "a" that is odd 
 * and is NOT multiple of 5. We can prove it mathematically:
 * Assume that a is an odd integer and is NOT multiple of 5, 
 * aka. the last digit of a is 1, 3, 7 or 9, and we CAN NOT find b so that
 * a*b is an integer that includes only '1'. Then when we do the division
 * of 1/a, 11/a, 111/a, ..., etc, there must exist two all-1 numbers that
 * form a loop. Denote them as m and n, and m < n. We can m and n as:
 *     m = m' * a + r     (1)
 *     n = n' * a + r     (2)
 * in which m' < n', r is the remainder. So: 
 *     n - m = (n' - m') * a   (3)
 * Because m and n are composed of only '1's, so:
 *     n - m = x * (10^y)    (4)
 * in which x is also an integer that includes only '1's and x < n. 
 * According to Equation (3), x * (10^y) is a multiple of a, but because
 * a doesn't include factors of 2 and 5, x must be a multiple of a.
 * But if x is a multiple of a, we will never reach n when doing the division.
 * This is a contradiction, so for any odd integer that is not multiple of 5,
 * there must exist an integer b so that a*b includes only '1's.
 * 
 * Alternatively, we can use the same method to prove that for any a/b, 
 * in which 0 < a < b, and b includes only factors of 2 and/or 5, 
 * a/b will never form a repeated pattern. 
 * Proof: Assume a/b forms a repeated pattern, then there must exist two 
 * integers m and n (m < n) so that:
 *      m = m' * b + r
 *      n = n' * b + r
 * in which m' < n', and r is the non-zero remainder.
 * So:  n - m = (n' - m') * b    
 * Because of the fashion of division, we know that:
 *      m = a * (10^x)  
 *      n = a * (10^y)
 * So:  n - m = a * (10^y - 10 * x) = a * (10^x) * 9...9 = m * 9...9 
 * Since (n - m) is a multiple of b, and 9...9 doesn't include any factors 
 * of 2 or 5, m must be a multiple of b; but on the other hand, if m is a 
 * multiple of b, the division calculation will be over when we reach m. 
 * Contradiction found, so a/b will never have repeated pattern.
 * (Of course this conclusion can be drawn easily from division fashion, 
 * because we keep multiple a by 10 during division. Since 10 = 2*5, and 
 * b = (2^x) * (5*y), in which x>=0 and y>=0, no matter how large x or y 
 * is, eventually they will be consumed completely by 10.
 */

#include <iostream>

using namespace std;

// Solution copied from inint5.com
int findMinAllOne(int a) {
  // Equavalent to: 
  //    if (a < 0 || a % 2 == 0 || a % 5 == 0) 
  //        return -1;
  static const int M[] = { -1, 1, -1, 1, -1, -1, -1, 1, -1, 1 };
  if (a < 0 || M[a % 10] == -1) 
    return -1;
  
  int ans = 1;
  for (int p = 1; p != 0; p %= a) {
    p = 10 * p + 1;
    ++ans;
  }

  return (a == 1) ? (ans - 1) : ans;
}

// dhu revised version from findMinAllOne(), 
// easier to understand than findMinAllOne().
int dhu(int a) {
  if (a < 0 || a % 2 == 0 || a % 5 == 0) 
    return -1;

  int ans = 1;
  int p = 1;
  while (p % a) {
    p = (p % a) * 10 + 1; 
    ++ans;
  }

  return ans;
}


// Test harness
int main() {
  //int a = 43;
  for (int a = 1; a < 100; a++) {
    int ret = findMinAllOne(a);
    if (ret != dhu(a)) {
      cout << a << ": " << ret << endl;
    }
  }

  return 0;
}
