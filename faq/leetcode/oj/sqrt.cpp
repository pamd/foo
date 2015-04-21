/* Leetcode OJ: Implement int sqrt(int x) to compute square root of x. */

// 40ms for large dataset
class Solution {
public:
  int sqrt(int x) {
    if (x < 0)
      return -1;

    if (x == 0)
      return 0;

    unsigned x2 = x;
    unsigned left = 0;
    unsigned right = x2;
    unsigned r2 = 1 << ((sizeof(x) * 8) / 2);
    if (right > r2)
      right = r2;

    while (left + 1 < right) {
      unsigned mid = left + (right - left) / 2;
      if (mid * mid > x2) 
	right = mid - 1;
      else if (mid * mid < x2)
	left = mid;
      else
	return mid;
    }

    if (right * right <= x2)
      return right;

    return left;
  }
};


/* Dropbox solution:
 * The idea of the solution is to calculate each bit in the result, from high to low.
 * First set the bit on. If the square value exceeds the parameter, set bit off.
 */
int Sqrt(int x) {
  // Convert to unsigned type to avoid overflow
  unsigned int k = x; 

  // Max bit would be in max square result
  unsigned int add = (1 << ((sizeof(x) * 8 - 1) / 2));  
	
  int result = 0;
  // Decide each bit
  while (add) {
    result |= add;
    if (k < result * result)
      // Remove the bit from result
      result -= add;
    
    add >>= 1;
  }
	
  return result;
}

// anson627: binary search
class Solution {
public:
  int sqrt(int x) {
    if(x < 2) 
      return x;

    long long left = 0;
    long long right = 1 + (x / 2);
    while(left + 1 < right) {
      long long mid = left + (right - left) / 2;
      long long tmp = mid * mid;
      if (tmp > x)
	/* dhu note: use "right = mid - 1" here will break 
	 * the guarantee that "left" will be the final answer. */
	right = mid;
      else if (tmp < x)
	left = mid;
      else
	return mid;
    }
    return (int)l;
  }
};
