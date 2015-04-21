/* Leetcode OJ: Given two numbers represented as strings, 
 * return multiplication of the numbers as a string.
 * Note: The numbers can be arbitrarily large and are non-negative.
 */

#include <string>
#include <iostream>

using namespace std;

// 44ms for large dataset
class Solution {
public:
  string multiply(string num1, string num2) {
    if (num1 == "0" || num2 == "0")
      return string("0");

    int len1 = num1.size();
    int len2 = num2.size();
    string result(len1 + len2, '0');
    for (int i = len1 - 1; i >= 0; i--) {
      int x = num1[i] - '0';
      for (int j = len2 - 1; j >= 0; j--) {
	int y = num2[j] - '0';
	size_t digit = (len1 - 1 - i) + (len2 - 1 - j); 
	size_t idx = len1 + len2 - 1 - digit;
        int foo = x * y;
	int curr_digit = result[idx] - '0' + foo;
	result[idx] = curr_digit % 10 + '0';
	result[idx - 1] += curr_digit / 10;
      }
    }

    size_t p = 0;
    for (; p < result.size(); p++) {
      if (result[p] != '0')
	break;
    }

    return result.substr(p);
  }
};

int main() {
  Solution foo;
  string num1("23");
  string num2("45");
  cout << foo.multiply(num1, num2) << endl;

}
