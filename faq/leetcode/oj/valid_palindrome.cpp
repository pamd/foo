/* Given a string, determine if it is a palindrome, considering only alphanumeric 
 * characters and ignoring cases.
 * For example, "A man, a plan, a canal: Panama" is a palindrome.
 * "race a car" is not a palindrome.
 * Note:
 * Have you consider that the string might be empty? This is a good question to ask 
 * during an interview.
 * For the purpose of this problem, we define empty string as valid palindrome.
 */

#include <iostream>
#include <string>

using namespace std;

// 56ms for large dataset
class Solution {
public:
  bool isPalindrome(string s) {
    int head = 0;
    int tail = s.size() - 1;
    while (head < tail) {
      char c1 = s[head];
      char c2 = s[tail];
      if (!isalpha(c1) && !isdigit(c1)) {
	head++;
	continue;
      }

      if (!isalpha(c2) && !isdigit(c2)) {
	tail--;
	continue;
      }

      if (islower(c1))
	c1 = toupper(c1);

      if (islower(c2))
	c2 = toupper(c2);

      if (c1 != c2)
	return false;

      head++;
      tail--;
    }

    return true;
  }

};

int main() {
  Solution foo;
  if (foo.isPalindrome("1ab2"))
    cout << "yes" << endl;
  else 
    cout << "no" << endl;

  return 0;
}
