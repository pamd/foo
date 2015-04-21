/* Leetcode OJ: Given a number represented as an array of digits, 
 * plus one to the number.
 */

// 16ms for large dataset
class Solution {
public:
  vector<int> plusOne(vector<int> &digits) {
    vector<int> result(digits);
    if (digits.size() == 0)
      return result;

    int carry = 1;
    int idx = result.size() - 1;
    while (carry && idx >= 0) {
      int tmp = result[idx] + carry;
      result[idx] = tmp % 10;
      carry = tmp / 10;
      idx--;
    }

    if (carry == 0)
      return result;

    result.insert(result.begin(), 1);
    return result;
  }

};
