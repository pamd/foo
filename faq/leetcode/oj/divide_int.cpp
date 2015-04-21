/* leetcode: Divide two integers without using multiplication, division and mod operator. 
 * http://www.mitbbs.com/article_t/JobHunting/32099545.html
 * Based on Java code by peking2.
 */

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <exception>
#include <cassert>

using namespace std;

// OJ version
class Solution {
public:
  /* dhu version: time limit exceeded for when doing "2147483647 / 1",
   * aka "(2^31 - 1) / 1". Change intermediate type to "long long" will 
   * solve the problem. */
  int divide_dhu(int dividend, int divisor) {
    assert(divisor != 0);

    if (dividend == 0)
      return 0;

    bool isNegative = false;
    if (dividend < 0) {
      isNegative = !isNegative;
      dividend = -dividend;
    }
    if (divisor < 0) {
      isNegative = !isNegative;
      divisor = -divisor;
    }
    
    if (dividend < divisor)
      return 0;

    int tmp = divisor;
    int multiple = 1;
    while ((tmp << 1) <= dividend) {
      tmp <<= 1;
      multiple <<= 1;
    }

    dividend -= tmp;
    int result = multiple;
    while (dividend >= divisor) {
      tmp >>= 1;
      multiple >>= 1;
      if (dividend >= tmp) {
	result += multiple;
	dividend -= tmp;
      }
    }

    if (isNegative)
      result = -result;
    
    return result;
  }

  // Leetcode: 36ms for large dataset; refer to:
  // http://www.mitbbs.com/article_t/JobHunting/32047747.html
  typedef unsigned int uint;
  uint leetcode_divide_helper(uint dividend, uint divisor) {
    uint x = 0, ret = 0;
    int numBits = sizeof(uint) * 8;
    for (int i = numBits - 1; i >= 0; i--) {
      x |= ((dividend >> i) & 1);
      if (x >= divisor) {
	ret |= 1;
	x -= divisor;
      }
      if (i > 0)
	ret <<= 1;
      x <<= 1;   
    }

    return ret;
  }

  // Leetcode wrapper function
  int leetcode_divide(int dividend, int divisor) {
    assert(divisor != 0);
    int sign = 1;
    if ((dividend > 0 && divisor < 0) ||
	(dividend < 0 && divisor > 0)) {
      sign = -1;
    }
    uint x = abs(dividend);
    uint y = abs(divisor);
    uint ret = leetcode_divide_helper(x, y);
    return (int) ret * sign;
  }

};

/* Solution by anson627 */
class Solution_anson {
public:
  int divide(int dividend, int divisor) {
    int sign = 1;
    unsigned int unsigned_dividend, unsigned_divisor;
    if (dividend < 0) {
      unsigned_dividend = -dividend;
      sign = -sign;
    }
    else 
      unsigned_dividend = dividend;

    if (divisor < 0) {
      unsigned_divisor = -divisor;
      sign = -sign;
    }
    else 
      unsigned_divisor = divisor;

    unsigned int result = unsigned_divide(unsigned_dividend, unsigned_divisor);
    return (sign < 0) ? -result : result;
  }
  
  unsigned int unsigned_divide(unsigned int dividend, unsigned int divisor) {
    unsigned int quotient = 0;
    while (dividend >= divisor) {
      unsigned int tmp = divisor;
      unsigned int shift = 0;
      while (((unsigned long long)tmp << 1) <= dividend) {
	tmp <<= 1;
	shift++;
      }

      dividend -= tmp;
      quotient |= (1 << shift);
    }
    return quotient;
  }
};

// Dropbox solution: Time Limit Exceeded
/*
 * The idea is to calculate each bit of quotient from high to low.
 * Using addition to move up bit
 */

// After test, there is bug for value -2147483648 (the minimum of int type);
// as for int -(-2147483648) is still -2147483648, not 2147483648.
// So we need a larger type which could contains value 2147483648
typedef long long_int; 

// If the sizeof(long) is equal to sizeof(int) in your system,
// you will have to typedef long long instead:
// typedef long long long_int; 

int Divide(int dend, int dsor) {	
  long_int dividend = dend;
  long_int divisor = dsor;
  int quotient = 0;
  bool negative = false; //indicate if the final result is negative
  
  if (dividend < 0) {
    negative = true;
    dividend = -dividend;
  }
  
  if (divisor < 0) {
    negative = !negative; //negative based on dividend else
    divisor = -divisor;
  }

  while (dividend >= divisor) {
    long_int addition = divisor;
    int cur_quotient = 1;
    while (dividend >= (addition + addition)) {
      // move up bit
      addition += addition;
      cur_quotient <<= 1; // /*equal to*/ cur_quotient += cur_quotient;
    }

    quotient += cur_quotient;
    //prepare for next bit
    dividend -= addition;
  }
  
  if (negative) 
    quotient = -quotient;
  
  return quotient;
}

// Test harness
int main() {
  int a = 29;
  int b = 3;
  Solution foo;
  cout << foo.divide(a, b) << endl;

  return 0;
}
