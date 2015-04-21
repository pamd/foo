/* Leetcode OJ: Reverse digits of an integer.
 * Example1: x = 123, return 321;
 * Example2: x = -123, return -321.
 */

// 16ms for large dataset
class Solution {
public:
  int reverse(int x) {
    unsigned y;
    bool isNeg = false;
  
    if (x < 0) {
      y = -x;
      isNeg = true;
    }
    else 
      y = x;

    int result = 0;
    while (y) {
      result = 10 * result + y % 10;
      y /= 10;
    }

    if (isNeg)
      return -result;

    return result;
  }
};
