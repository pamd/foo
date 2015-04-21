/* Given an array S of n integers, are there elements a, b, c, and d in S 
 * such that a + b + c + d = target? Find all unique quadruplets in the 
 * array which gives the sum of target.
 *
 * Note:
 * Elements in a quadruplet (a,b,c,d) must be in non-descending order. 
 * (ie, a <= b <= c <= d)
 * The solution set must not contain duplicate quadruplets.
 * For example, given array S = {1, 0, -1, 0, -2, 2}, and target = 0.
 *
 * A solution set is:
 *   (-1,  0, 0, 1)
 *   (-2, -1, 1, 2)
 *   (-2,  0, 0, 2)
 *
 * Accepted by OJ: 1,040 ms when testing large dataset.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Data structure that specifies a pair of elements in original array
struct PairInfo {
  PairInfo(size_t i1, int v1_in, size_t i2, int v2_in) {
    idx1 = i1;
    v1 = v1_in;
    idx2 = i2;
    v2 = v2_in;
  }

  int v1, v2;
  size_t idx1, idx2;
};

// Does two pairs share any array elements?
bool overlap(const PairInfo& p1, const PairInfo& p2) {
  if (p1.idx1 == p2.idx1 || p1.idx1 == p2.idx2 
      || p1.idx2 == p2.idx1 || p1.idx2 == p2.idx2)
    return true;

  return false;
}

// Is the input vector already an element in result?
bool isDuplicate(const vector<int>& foo, const vector<vector<int> >& result)
{
  for (size_t i = 0; i < result.size(); i++) {
    if (foo == result[i])
      return true;
  }

  return false;
}

// dhu solution #1 that is based on 2sum. (anson627 uses the same idea.)
// time complexity: O(n^2 * logn).
class Solution_dhu1 {
public:
  // Use multimap to solve two sum problem
  vector<vector<int> > twoSum(const vector<PairInfo>& pairs, int target) {
    vector<vector<int> > result;
    multimap<int, PairInfo> theMap;
    multimap<int, PairInfo>::iterator it;
    pair<multimap<int, PairInfo>::iterator, multimap<int, PairInfo>::iterator> matches;
    for (size_t i = 0; i < pairs.size(); i++) {
      int tmp = pairs[i].v1 + pairs[i].v2;
      matches = theMap.equal_range(target - tmp);
      for (it = matches.first; it != matches.second; ++it) {
	if (overlap(it->second, pairs[i]))
	  continue;
	vector<int> foo(4);
	foo[0] = it->second.v1;
	foo[1] = it->second.v2;
	foo[2] = pairs[i].v1;
	foo[3] = pairs[i].v2;
	sort(foo.begin(), foo.end());
	if (isDuplicate(foo, result))
	  continue;
	result.push_back(foo);
      }
      theMap.insert(pair<int, PairInfo>(tmp, pairs[i]));
    }
    
    return result;
  }

  // Wrapper that calls twoSum()
  vector<vector<int> > fourSum(vector<int> &num, int target) {
    vector<PairInfo> pairs;
    for (size_t i = 0; i < num.size(); i++) {
      for (size_t j = i + 1; j < num.size(); j++) 
	pairs.push_back(PairInfo(i, num[i], j, num[j]));
    }
    return twoSum(pairs, target);    
  }
};

// dhu solution #2 that uses unordered_multimap, 
// time complexity: O(n^2)
class Solution_dhu2 {
public:
  bool overlap(const pair<int, int>& int_pair, int i, int j) {
    if (int_pair.first == i || int_pair.second == i)
      return true;
    if (int_pair.first == j || int_pair.second == j)
      return true;

    return false;
  }

  vector<vector<int> > fourSum(vector<int> &num, int target) {
    vector<vector<int> > ret;
    if (num.size() < 4)
      return ret;

    unordered_multimap<int, pair<int, int> > sum2_pairs;
    for (size_t i = 0; i < num.size() - 1; i++) {
      for (size_t j = i + 1; j < num.size(); j++) {
	int sum2 = num[i] + num[j];
	unordered_multimap<int, pair<int, int> >::iterator it = sum2_pairs.find(target - sum2);
	for (; it != sum2_pairs.end() && it->first == target - sum2; it++) {
	  if (!overlap(it->second, i, j)) {
	    vector<int> tmp(4);
	    tmp[0] = num[i];
	    tmp[1] = num[j];
	    tmp[2] = num[it->second.first];
	    tmp[3] = num[it->second.second];
	    sort(tmp.begin(), tmp.end());
	    if (find(ret.begin(), ret.end(), tmp) == ret.end())
	      ret.push_back(tmp);
	  }
	}
	sum2_pairs.insert(pair<int, pair<int, int> >(sum2, pair<int, int>(i, j)));
      }
    }

    return ret;
  }

};

// Test harness
int main()
{
  int arr[] = { 1, 0, -1, 0, -2, 2 };
  int target = 0;

  int n = sizeof(arr) / sizeof(int);
  vector<int> v(arr, arr + n);
  Solution foo;
  vector<vector<int> > ret = foo.fourSum(v, target);
  
  for (size_t i = 0; i < ret.size(); i++) {
    for (size_t j = 0; j < ret[i].size(); j++)
      cout << ret[i][j] << " ";
    cout << endl;
  }
  
}

