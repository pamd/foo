/* Leetcode OJ: Implement next permutation, which rearranges numbers into 
 * the lexicographically next greater permutation of numbers.
 * If such arrangement is not possible, it must rearrange itself as the 
 * lowest possible order (ie, sorted in ascending order).
 *
 * The replacement must be in-place, do not allocate extra memory.
 * Here are some examples. Inputs are in the left-hand column and its corresponding 
 * outputs are in the right-hand column.
 * 1,2,3 => 1,3,2
 * 3,2,1 => 1,2,3
 * 1,1,5 => 1,5,1
 */

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// 64ms for large dataset
class Solution {
public:
  void nextPermutation(vector<int> &num) {
    if (num.size() == 0)
      return;

    size_t idx = 0;
    for (idx = num.size() - 1; idx >= 1; idx--) {
      if (num[idx - 1] < num[idx])
	break;
    }

    if (idx) { 
      size_t j;
      for (j = num.size() - 1; j >= idx; j--)
	if (num[j] > num[idx - 1])
	  break;
      swap(num[idx - 1], num[j]);
    }

    size_t end = num.size() - 1;
    while (idx < end) 
      swap(num[idx++], num[end--]);
  }
};

int main() {
  vector<int> num;
  num.push_back(1);
  num.push_back(3);
  num.push_back(2);
  
  Solution foo;
  foo.nextPermutation(num);
  for (size_t i = 0; i < num.size(); i++)
    cout << num[i] << endl;

}
