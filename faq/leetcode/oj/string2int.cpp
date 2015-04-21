/* Leetcode OJ: Implement atoi to convert a string to an integer.
 * Hint: Carefully consider all possible input cases. 
 * Requirements for atoi:
 * The function first discards as many whitespace characters as necessary 
 * until the first non-whitespace character is found. Then, starting from 
 * this character, takes an optional initial plus or minus sign followed by 
 * as many numerical digits as possible, and interprets them as a numerical value.
 * The string can contain additional characters after those that form the integral 
 * number, which are ignored and have no effect on the behavior of this function.
 * If the first sequence of non-whitespace characters in str is not a valid integral 
 * number, or if no such sequence exists because either str is empty or it contains 
 * only whitespace characters, no conversion is performed. If no valid conversion 
 * could be performed, zero is returned. If the correct value is out of the range of 
 * representable values, INT_MAX (2147483647) or INT_MIN (-2147483648) is returned.
 */

#include <iostream>
#include <climits>

using namespace std;

// 40ms for large dataset
class Solution {
public:
  int atoi(const char *str) {
    if (!str || !*str)
      return 0;

    bool isNeg = false;
    char c = 0;
    // Skip the leading space and tab characters
    while (*str) {
      c = *str;
      if (c == ' ' || c == '\t')
	str++;
      else
	break;
    }

    // No any valid digits are found in str
    if (!*str)
      return 0;
    
    if (c != '+' && c != '-' && (c < '0' || c > '9'))
      return 0;

    if (c == '+' || c == '-') {
      if (c == '-')
	isNeg = true;

      str++;
      if (*str < '0' || *str > '9')
	return 0;
    }

    long long tmp = 0;
    while (*str >= '0' && *str <= '9') {
      tmp *= 10;
      tmp += *str - '0';
      str++;
    }

    if (isNeg)
      tmp = -tmp;

    if (tmp > INT_MAX)
      return INT_MAX;

    if (tmp < INT_MIN)
      return INT_MIN;

    return tmp;

  }

};

// anson627 solution
class Solution_anson627 {
public:
  int atoi(const char *str) {
    int sign = 1;
    while(*str == ' ') 
      str++;

    if (*str == '+') 
      str++;
    else if (*str == '-') 
      str++, sign = -1;

    long long val = 0;
    int digit;
    while (*str != '\0') {
      if (*str < '0' || *str > '9') 
	break;

      digit = (*str - '0');
      val = val * 10 + digit;
      str++;
    }

    if (sign == -1) 
      val = -val;

    if (val < INT_MIN) 
      val = INT_MIN;

    if (val > INT_MAX) 
      val = INT_MAX;

    return val;
  }
};

int main() {
  Solution foo;
  const char* str = "\t123";
  cout << foo.atoi(str) << endl;
  cout << "std: " << atoi(str) << endl; 
}
