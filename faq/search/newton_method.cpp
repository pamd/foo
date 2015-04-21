/* Newton's method: a method for finding successively better approximations 
 * to the roots (or zeroes) of a real-valued function.
 * x1 = x0 - f(x0) / f'(x0)
 * For example, suppose we want to calculate sqrt(n), we define: f(x) = x^2 - n,
 * then: f'(x) = 2 * x, so: 
 * x1 = x0 - (x0 * x0 - n) / (2 * x0)
 *  
 * Refer to:
 * http://en.wikipedia.org/wiki/Newton_method
 */

#include <iostream>
using namespace std;

/* Calculates cubic root, based on java code by yishan on:
 * http://www.mitbbs.com/article_t/JobHunting/32091353.html
 */
double CubicRoot(double n, double epsilon)
{
  double root = n;
  double diff = root * root * root - n;
  while (diff > epsilon) {
    root -= diff / (3 * root * root);
    diff = root * root * root - n;
  }

  return root;
} 

int main() {
  double epsilon = 1e-3;
  int n = 512;
  double ret = CubicRoot(n, epsilon);
  cout << ret << endl;
  cout << "confirm: " << ret * ret * ret << endl;
}
