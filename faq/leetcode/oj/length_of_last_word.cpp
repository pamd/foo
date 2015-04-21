/* Leetcode online Judge: Given a string s consists of upper/lower-case alphabets 
 * and empty space characters ' ', return the length of last word in the string.
 * If the last word does not exist, return 0.
 * For example, given s = "Hello World", return 5.
 */

#include <iostream>

using namespace std;

class Solution {
public:
  // 16ms for large dataset
  int lengthOfLastWord(const char *s) {
    if (!s || !(*s))
      return 0;
    
    int last_len = 0;
    int curr_len = 0;
    while (*s) {
      char c = *s;
      if (c != ' ')
	curr_len++;
      else {
	if (curr_len)
	  last_len = curr_len;
	curr_len = 0;
      }   
      s++;
    }

    if (curr_len)
      last_len = curr_len;

    return last_len;
  }

};

int main() {
  const char* s = "a";
  Solution foo;
  cout << foo.lengthOfLastWord(s) << endl;
}
