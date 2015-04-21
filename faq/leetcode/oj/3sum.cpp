/* Given an array S of n integers, are there elements a, b, c 
 * in S such that a + b + c = 0? 
 * Find all unique triplets in the array which gives the sum of zero.
 * Note:
 * Elements in a triplet (a,b,c) must be in non-descending order. (ie, a <= b <= c)
 * The solution set must not contain duplicate triplets.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Defined for dhu solution #1
struct Sum2 { 
  Sum2(int i, int j) { v1 = i; v2 = j; }
  int v1, v2; 
};
    
// dhu Solution #1
class Solution_dhu1 {
public:
  vector<Sum2> twoSum(const vector<int>& num, int target, size_t idx) {
    vector<Sum2> ret;
    size_t head = idx;
    size_t tail = num.size() - 1;
    while (head < tail) {
      if (num[head] + num[tail] == target) {
	ret.push_back(Sum2(num[head], num[tail]));
	head++;
	tail--;
      }
      else if (num[head] + num[tail] < target) 
	head++;
      else
	tail--;
    }
    return ret;
  }

  vector<vector<int> > threeSum(vector<int> &num) {
    vector<vector<int> > result;
    sort(num.begin(), num.end());
    for (size_t i = 0; i < num.size(); i++) {
      if (i > 0 && num[i] == num[i-1])
	continue;

      int target = -num[i];
      vector<Sum2> pair2 = twoSum(num, target, i + 1);
      for (size_t j = 0; j < pair2.size(); j++) {
	vector<int> tmp(3);
	tmp[0] = num[i];
	tmp[1] = pair2[j].v1;
	tmp[2] = pair2[j].v2;
	// To avoid duplicate triplets in result, when the last triplet in the
	// result is identical to current triplet, ignore current triplet. 
	if (!result.size() || result.back() != tmp)
	  result.push_back(tmp);
      }
    }

    return result;    
  }
};

// dhu solution #2
class Solution_dhu2 {
public:
  vector<vector<int> > threeSum(vector<int> &num) {
    vector<vector<int> > ret;
    sort(num.begin(), num.end());
    if (num.size() < 3)
      return ret;

    for (size_t i = 0; i < num.size() - 2; i++) {
      if (i > 0 && num[i] == num[i - 1]) // Avoid duplicate triplets
	continue;

      int n1 = num[i];
      int left = i + 1;
      int right = num.size() - 1;
      while (left < right) {
	if (num[left] + num[right] + n1 == 0) {
	  // Avoid duplicate triplets
	  if (left > i + 1 && num[left] == num[left - 1]) {
	    left++;
	    continue;
	  }

	  ret.push_back(vector<int>(3));
	  ret.back()[0] = n1;
	  ret.back()[1] = num[left];
	  ret.back()[2] = num[right];
	  left++;
	  right--;
	}
	else if (num[left] + num[right] + n1 > 0)
	  right--;
	else 
	  left++;
      }
    }

    return ret;
  }

};

// Another way to avoid duplicates in the result is 
// calling std::find(), anson627 used this method.

int main() {

  return 0;
}

