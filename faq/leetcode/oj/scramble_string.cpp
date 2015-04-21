/* leetcode OJ: Given a string s1, we may represent it as a binary tree 
 * by partitioning it to two non-empty substrings recursively.
 *
 * Below is one possible representation of s1 = "great":
 *
 *      great
 *     /     \
 *    gr    eat
 *   / \    /  \
 *  g   r  e   at
 *            /  \
 *           a    t
 *
 * To scramble the string, we may choose any non-leaf node and swap its two children.
 * For example, if we choose the node "gr" and swap its two children, it produces a 
 * scrambled string "rgeat".
 *
 *     rgeat
 *    /	   \
 *   rg    eat
 *  / \    /  \
 * r   g  e   at
 *           /  \
 *          a    t
 *
 * We say that "rgeat" is a scrambled string of "great".
 * 
 * Similarly, if we continue to swap the children of nodes "eat" and "at", 
 * it produces a scrambled string "rgtae".
 *
 *      rgtae
 *     /    \
 *    rg    tae
 *   / \    / \
 *  r   g  ta  e
 *        /  \
 *       t    a
 *
 * We say that "rgtae" is a scrambled string of "great".
 * Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1.
 */

/* dhu: This brute-force method can pass small dataset, 
 * but exceeded memory limit for large dataset. */
class Solution {
public:
  bool isScramble(string s1, string s2) {
    vector<string> scrambles = getScrambles(s1);
    for (size_t i = 0; i < scrambles.size(); i++) {
      if (s2 == scrambles[i])
	return true;
    }
    return false;
  }

  vector<string> getScrambles(const string& str) {
    vector<string> scrambles;
    if (str.size() == 0)
      return srambles;
    if (str.size() == 1) 
      scrambles.push_back(str);
    
    for (size_t i = 1; i < str.size(); i++) {
      vector<string> left = getScrambles(str.substr(0, i));
      vector<string> right = getScrambles(str.substr(i));
      for (size_t i = 0; i < left.size(); i++) {
	for (size_t j = 0; j < right.size(); j++) {
	  scrambles.push_back(left[i] + right[j]);
	  scrambles.push_back(right[j] + left[i]);
	}
      }
    }

    return scrambles;
  }
};

// anson627 solution: 20ms for large dataset
class Solution_anson {
public:
  /* Make sure s1[low1 ... up1) and s2[low2 ... up2) are composed of 
   * identical characters. Note that s1[up1] and s2[up2] are excluded! */
  bool isSameCharSet(string &s1, int low1, int up1, string &s2, int low2, int up2) {
    if (up1 - low1 != up2 - low2) 
      return false;

    int c[256] = { 0 };
    for (int i = low1; i < up1; i++) 
      c[s1[i]]++;

    for (int i = low2; i < up2; i++) 
      c[s2[i]]--;
     
    for (int i = 0; i < 256; i++) {
      if (c[i] != 0) 
	return false;
    }

    return true;
  }

  // Recursive helper function
  bool isScrambleHelper(string &s1, int low1, int up1, string &s2, int low2, int up2) {
    if(!isSameCharSet(s1, low1, up1, s2, low2, up2)) 
      return false;

    // dhu note: the following termination condition can also be written as:
    // if (up1 - low1 <= 2)
    //   return true;
    if (low1 + 1 == up1) 
      return true;
      
    for (int i = 1; i < up1 - low1; i++) {
      if ((isScrambleHelper(s1, low1, low1 + i, s2, low2, low2 + i) && 
	   isScrambleHelper(s1, low1 + i, up1, s2, low2 + i, up2)) || 
	  (isScrambleHelper(s1, low1, low1 + i, s2, up2 - i, up2) && 
	   isScrambleHelper(s1, low1 + i, up1, s2, low2, up2 - i)))
	return true;
    }

    return false;
  }

  bool isScramble(string s1, string s2) {
    return isScrambleHelper(s1, 0, s1.size(), s2, 0, s2.size());
  }

};
