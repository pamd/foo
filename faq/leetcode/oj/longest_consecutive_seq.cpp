/* Given an unsorted array of integers, find the length of the longest 
 * consecutive elements sequence. 
 * For example, given [100, 4, 200, 1, 3, 2], the longest consecutive 
 * elements sequence is [1, 2, 3, 4]. Return its length: 4.
 * Your algorithm should run in O(n) complexity.
 */

#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

// 72ms for large dataset
class Solution {
public:
  int longestConsecutive(vector<int> &num) {
    unordered_map<int, bool> marker;
    for (size_t i = 0; i < num.size(); i++) 
      marker.insert(pair<int, bool>(num[i], false));

    unordered_map<int, bool>::iterator it = marker.begin();
    int max_len = 0;
    for (; it != marker.end(); ++it) {
      int tmp = it->first;
      if (it->second)
	continue;
      it->second = true;
      int len = 1;
      int i = 1;
      bool go_left = true;
      bool go_right = true;
      while (go_left || go_right) {
	if (go_left) {
	  if (marker.find(tmp - i) != marker.end()) {
	    marker[tmp - i] = true;
	    len++;
	  }
	  else 
	    go_left = false;
	}
	if (go_right) {
	  if (marker.find(tmp + i) != marker.end()) {
	    marker[tmp + i] = true;
	    len++;
	  }
	  else 
	    go_right = false;
	}
	i++;
      }
      if (max_len < len)
	max_len = len;
    }
  
    return max_len;    
  }

};


class Solution_anson {
public:
  int longestConsecutive1(vector<int> &num) {
    if (num.empty()) 
      return 0;

    sort(num.begin(), num.end()); // dhu: sort input vector, not O(n) time any more!
    int res = 1;
    int count = 1;
    for (size_t i = 1; i < num.size(); ++i) {
      int diff = num[i] - num[i-1];
      if (diff == 0) {
	continue;
      }
      if (diff == 1) {
	count++;
	if (count > res) {
	  res = count;
	}
      }
      else 
	count = 1;
    }

    return res;
  }

  int longestConsecutive2(vector<int> &num) {
    if (num.empty()) 
      return 0;
   
    unordered_map<int, int> table;
    int res = 1;
    for (size_t i = 0; i < num.size(); i++) {
      if (table.find(num[i]) != table.end()) 
	continue;

      table[num[i]] = 1;
      if (table.find(num[i] - 1) != table.end()) {
	res = max(res, merge(table, num[i] - 1, num[i])); 
      }

      if (table.find(num[i] + 1) != table.end()) {
	res = max(res, merge(table, num[i], num[i] + 1));
      }
    }

    return res;
  }

  int merge(unordered_map<int, int> & table, int left, int right) {
    int lower = left - table[left] + 1;
    int upper = right + table[right] - 1;
    int len = upper - lower + 1;
    table[lower] = len;
    table[upper] = len;

    return len;
  }

};
