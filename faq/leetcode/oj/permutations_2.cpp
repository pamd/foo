/* Leetcode OJ: Given a collection of numbers that might contain duplicates, 
 * return all possible unique permutations. 
 * For example, [1,1,2] have the following unique permutations:
 * [1,1,2], [1,2,1], and [2,1,1].
 */

#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

// 220 ms for large dataset
class Solution {
public:
  vector<vector<int> > permuteUnique(vector<int> &num) {
    vector<vector<int> > result;
    if (num.size() == 0)
      return result;

    if (num.size() == 1) {
      result.push_back(num);
      return result;
    }

    sort(num.begin(), num.end());
    for (size_t i = 0; i < num.size(); i++) {
      if (i > 0 && num[i] == num[i - 1])
	continue;

      vector<int> v(num);
      v.erase(v.begin() + i);
      vector<vector<int> > tmp = permuteUnique(v);
      for (size_t j = 0; j < tmp.size(); j++) {
	/* // Insert num[i] at the very beginning
	vector<int> v2;
	v2.push_back(num[i]);
	for (size_t k = 0; k < tmp[j].size(); k++) 
	  v2.push_back(tmp[j][k]);
	result.push_back(v2);
	*/

	/* Code will be more compact if we add num[i] 
	 * at the end of previous permutations. */
	tmp[j].push_back(num[i]);
	result.push_back(tmp[j]);
      }
    }

    return result;
  }

  /* Another approach that is similar to the one which has 
   * no duplicate elements, 192ms for large dataset. */
  vector<vector<int> > permuteUnique2(vector<int> &num) {
    // Sort input numbers first
    sort(num.begin(), num.end());

    vector<vector<int> > result;
    vector<bool> used(num.size(), false);
    vector<int> tmp(num.size());
    helper2(num, result, used, tmp, 0);
    return result;
  }

  // Heper function for permuteUnique2
  void helper2(const vector<int>& num, vector<vector<int> >& result, 
	       vector<bool>& used, vector<int>& tmp, size_t level) {
    if (level == num.size()) {
      result.push_back(tmp);
      return;
    }

    for (size_t i = 0; i < num.size(); i++) {
      if (used[i])
	continue;
      if (i > 0 && num[i] == num[i - 1] && used[i - 1]) 
	continue;
      
      used[i] = true;
      tmp[level] = num[i];
      helper2(num, result, used, tmp, level + 1);
      used[i] = false;
    }
  }

};

/* Code by anson627: 146ms for large dataset.
 * This approach is more effcient. It keeps calling nextPermutation(). 
 * So input vector does NOT have to be sorted.
 */
class Solution_anson {
public:
  void reverse(vector<int> &num, int i, int j) {
    while (i < j) 
      swap(num[i++], num[j--]);
  }
  
  void nextPermutation(vector<int> &num) {
    int N = num.size();
    if (N < 2) 
      return;

    int i = N - 2;
    while (i >= 0 && num[i] >= num[i+1]) 
      i--;

    if (i == -1) {
      reverse(num, 0, N - 1);
      return;
    }

    int j = N - 1;
    while (j > i && num[j] <= num[i]) 
      j--;

    assert(j > i);
    swap(num[i], num[j]);
    reverse(num, i + 1, N - 1);
  };
  
  vector<vector<int> > permuteUnique(vector<int> &num) {
    vector<vector<int> > result;
    do {
      result.push_back(num);
      nextPermutation(num);
    } while (!equal(result[0].begin(), result[0].end(), num.begin()));

    return result;
  }
};


int main() {
  vector<int> v;
  v.push_back(1);
  v.push_back(1);
  v.push_back(2);
  //v.push_back(3);
  Solution foo;
  vector<vector<int> > ret = foo.permuteUnique2(v);
  for (size_t i = 0; i < ret.size(); i++) {
    for (size_t j = 0; j < ret[i].size(); j++)
      cout << ret[i][j] << " ";
    cout << endl;
  }
  

  
  //string str("aabb");
  //permute_uniq(str);
}
