/* Leetcode OJ: Given an array S of n integers, find three integers in S 
 * such that the sum is closest to a given number, target. 
 * Return the sum of the three integers. You may assume that each input 
 * would have exactly one solution.
 * For example, given array S = { -1, 2, 1, -4 }, and target = 1,
 * the sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 */

#include <iostream>
#include <vector>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

// dhu solution
class Solution {
public:
  int threeSumClosest(vector<int> &num, int target) {
    if (num.size() < 3) 
      return INT_MIN;

    sort(num.begin(), num.end());
    int ret = num[0] + num[1] + num[2];
    int diff = 0;
    if (ret >= target)
      diff = ret - target;
    else
      diff = target - ret;

    for (size_t i = 0; i < num.size() - 2; i++) {
      int n1 = num[i];
      int left = i + 1;
      int right = num.size() - 1;
      while (left < right) {
	int sum3 = n1 + num[left] + num[right];
	if (sum3 > target) {
	  if (diff > sum3 - target) {
	    diff = sum3 - target;
	    ret = sum3;
	  }
	  right--;
	}
	else if (sum3 < target) {
	  if (diff > target - sum3) {
	    diff = target - sum3;
	    ret = sum3;
	  }
	  left++;
	}
	else
	  return target;
      }
    }
    
    return ret;
  }

};

// anson627: same idea as dhu solution
class Solution {
public:
  int threeSumClosest(vector<int> &num, int target) {
    int N = num.size();
    sort(num.begin(), num.end());
    int res = num[0] + num[1] + num[2];
    for (int k = 0; k < N-2; k++) {
      int i = k+1;
      int j = N-1;
      while (i < j) {
	int sum = num[i] + num[j] + num[k];
	if (sum == target) 
	  return sum;

	if (abs(sum - target) < abs(res - target)) 
	  res = sum;

	if (sum > target) 
	  j--;
	else 
	  i++;
      }
    }
    return res;
  }
};

// Test harness
int main() {
  int arr[] = { 1, 1, -1};
  int target = 0;

  int n = sizeof(arr) / sizeof(int);
  vector<int> num(arr, arr + n);
  Solution foo;
  cout << foo.threeSumClosest(num, target) << endl;
 
}
