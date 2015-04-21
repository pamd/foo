/* Leetcode OJ: Determine whether an integer is a palindrome. 
 * Do this without extra space.
 */

// 272ms for large dataset 
class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0)
      return false;

    int reversed = 0;
    int prev = 0;
    int tmp = x;
    while (tmp) {
      prev = reversed;
      reversed = prev * 10 + tmp % 10;
      // Overflow!
      if ((reversed - tmp % 10) / 10 != prev)
	return false;

      tmp /= 10;
    }  
     
    return x == reversed;
  }
};

// anson627 solution: do not have to worry about int overflow
class Solution_anson {
public:
  bool isPalindrome(int x) {
    if (x < 0) 
      return false;

    int d = 1;
    while (x / d >= 10) 
      d *= 10;

    while (x != 0) {
      int l = x / d;
      int r = x % 10;
      if (l != r) 
	return false;

      x = (x % d) / 10;
      d /= 100;
    }

    return true;
  }
};

int main() {
  
}
