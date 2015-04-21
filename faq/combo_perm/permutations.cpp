/* Permutation generations, copied from:
 * http://www.mitbbs.com/article_t/JobHunting/32305759.html
 */

#include <string>
#include <iostream>

using namespace std;

// Helper function
void swap(string& perm, size_t level, size_t i) {
  char c = perm[level];
  perm[level] = perm[i];
  perm[i] = c;
}

// All Permutations, invoked by: permute(str, 0);
// This is a compact and neat implementation.
// The only disadvantage of this implementation
// is that the output permutations are not sorted by indexes.
// For eample, suppose input string is "abc", the output is:
//     abc
//     acb
//     bac
//     bca
//     cba
//     cab
// Note that if they are sorted alphabetically, then "cba"
// should be after "cab". 
void permute_all(string& perm, size_t level) {
  if (level == perm.size()) {
    cout << perm << endl;
    return;
  }

  for (size_t i = level; i < perm.size(); i++) {
    // if (level != i) // optional, because swap(perm, i, i) does is valid too
    swap(perm, level, i);

    permute_all(perm, level + 1);

    // if (level != i) // optional, because swap(perm, i, i) does is valid too
    swap(perm, level, i);
  }

}

/* Permutation without duplications: NOT right. 
 * Suppose input string is "aabc", when 'c' is swapped with 'a', 
 * the string becomes "caba", which is in unsorted order. 
 * Then the permutation algorithm is totally messed up.
 */
void permute_no_dup(string& perm, size_t level) {
  if (level == perm.size()) {
    cout << perm << endl;
    return;
  }

  for (size_t i = level; i < perm.size(); i++) {
    if (i > level && perm[i] == perm[i - 1])
      continue;

    swap(perm, level, i);
    permute_no_dup(perm, level + 1);
    swap(perm, level, i);
  }

}

// Test harness 
int main() {
  string str("fummy");
  permute_no_dup(str, 0);

}

/* aabbc:
1:	aabbc
2:	aabcb
3:	aacbb
4:	ababc
5:	abacb
6:	abbac
7:	abbca
8:	abcba
9:	abcab
10:	acbba
11:	acbab
12:	acabb

13:	baabc
14:	baacb
15:	babac
16:	babca
17:	bacba
18:	bacab

19:	bbaac
20:	bbaca
21:	bbcaa

22:	bcaba
23:	bcaab
24:	bcbaa

25:	bcaba (dup)
26:	bcaab (dup)

27:	cabba
28:	cabab
29:	caabb
30:	cbaba
31:	cbaab
32:	cbbaa
33:	cbaba
34:	cbaab
35:	cabba
36:	cabab
37:	caabb
*/

/* aabc:

1:	aabc
2:	aacb

3:	abac
4:	abca

5:	acba
6:	acab

7:	baac
8:	baca
9:	bcaa

10:	caba
11:	caab
12:	cbaa

13:	caba (dup)
14:	caab (dup)

*/
