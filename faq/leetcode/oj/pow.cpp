/* Leetcode OJ: Implement pow(x, n). */

// 20ms for alrge dataset
class Solution {
public:
  double pow(double x, int n) {
    bool isNeg = false;
    // Avoid overflow issues
    unsigned y = n;
    if (n < 0) {
      y = -n;
      isNeg = true;
    }

    double result = 1;
    double power = x;
    while (y) {
      if (y & 1)
	result *= power;
      power = power * power;
      y >>= 1;
    }
     
    if (isNeg)
      result = 1.0 / result;

    return result;
  }

};

/*
 * Dropbox solution: A typical divide-conquer problem
 */
double pow(double x, int n) {
  if(n == 0) 
    return 1;

  if(n == 1) 
    return x;

  bool negative = false;
  if(n < 0) {
    negative = true;
    n = -n;
  }

  // Apply divide-conquer algorithm
  double r = pow(x, n/2);
  r = r*r;
  if ( n%2 != 0) 
    r *= x;
  
  if (negative) 
    r = 1/r;

  return r;
}
