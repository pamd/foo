/* Leetcode OJ: The set [1,2,3,…,n] contains a total of n! unique permutations.
 * By listing and labeling all of the permutations in order, we get the following 
 * sequence (ie, for n = 3):
 * 
 * "123"
 * "132"
 * "213"
 * "231"
 * "312"
 * "321"
 * 
 * Given n and k, return the kth permutation sequence.
 * Note: Given n will be between 1 and 9 inclusive.
 */

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// 8ms for large dataset
class Solution {
public:
  string getPermutation(int n, int k) {
    string result(n, '0');

    vector<int> helper(n + 1);
    for (size_t i = 0; i < helper.size(); i++) 
      helper[i] = i;
        
    vector<int> perm(n, 1);
    for (int i = 1; i < n; i++)
      perm[i] = perm[i - 1] * i;

    k--;
    for (int i = 0; i < n; i++) {
      int foo = k / perm[n - 1 - i];
      result[i] = '1' + helper[foo];
      helper.erase(helper.begin() + foo);
      k = k % perm[n - 1 - i];
    }

    return result;
  }
};

int main() {
  Solution foo;
  int n = 3;
  for (int k = 1; k <= 6; k++)
    cout << foo.getPermutation(n, k) << endl;
}
