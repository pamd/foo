/* The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows 
 * like this: 
 *
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 *
 * And then read line by line: "PAHNAPLSIIGYIR"
 * Write the code that will take a string and make this conversion given a number of rows:
 *     string convert(string text, int nRows);
 * For example, convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 * And convert("PAYPALISHIRING", 4) should return "PINALSIGYAHRPI":
 *
 * P     I     N
 * A   L S   I G
 * Y A   H R 
 * P     I
 *
 */

#include <iostream>
#include <vector>

using namespace std;

// 100ms for large dataset
class Solution {
public:
  string convert(string s, int nRows) {
    if (nRows <= 1)
      return s;

    vector<string> table(nRows);
    size_t r = 0;
    bool move_up = false;
    for (size_t i = 0; i < s.size(); i++) {
      table[r].push_back(s[i]);
      if ((int) r == nRows - 1) { 
	r--;
	move_up = true;
      }
      else if (r == 0) {
	r++;
	move_up = false;
      }
      else if (move_up)
	r--;
      else
	r++;
    }

    string ret;
    for (size_t i = 0; i < table.size(); i++) 
      ret += table[i];
    
    return ret;
  }
};

/* Dropbox solution: 80ms for large dataset.
 * This solution is better than mine, because it does not require
 * extra storage. anson627 uses the same idea. */
string Convert(string s, int nRows) {
  if (nRows < 2)
    return s;

  int patternSize = (nRows - 1) * 2;
  int length = s.size();
  string r; // result;

  // First row
  for (int i = 0; i < length; i += patternSize)
    r.push_back(s[i]);

  // Each of the rows in the middle (from 2nd row to the second from last) 
  // contains two letters in one pattern
  for (int i = 1; i < nRows - 1; ++i) {
    for (int j = i; j < length; j += patternSize) {
      r.push_back(s[j]);
      int k = (j - i) + (patternSize - i);
      if (k < length)
	r.push_back(s[k]);
    }
  }

  // Last row
  for (int i = nRows - 1; i < length; i += patternSize)
    r.push_back(s[i]);
  
  return r;
}

int main() {
  Solution foo;
  string s("PAYPALISHIRING");
  string s2 = foo.convert(s, 3);
  cout << s2 << endl;
}


