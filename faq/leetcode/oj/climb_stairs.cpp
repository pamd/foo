/* Leetcode OJ: You are climbing a stair case. It takes n steps to 
 * reach to the top. Each time you can either climb 1 or 2 steps. 
 * In how many distinct ways can you climb to the top?
 */

#include <iostream>

using namespace std;

// Variant of Fibnacci numbers
class Solution {
public:
    int climbStairs(int n) {
      if (n <= 1)
	return 1;
      int f1 = 1;
      int f2 = 1;
      for (int i = 2; i <= n; i++) {
	int f = f1 + f2;
	f2 = f1;
	f1 = f;
      }
      return f1;
    }
};

int main() {
  Solution foo;
  for (int i = 0; i < 10; i++)
    cout << foo.climbStairs(i) << endl;

}
