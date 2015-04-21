/* Leetcode OJ: You are given a string S, and a list of words L of same length. 
 * Find all starting indices of substring(s) in S that is a concatenation of 
 * each word in L exactly once and without any intervening characters.
 * For example, given:
 * S: "barfoothefoobarman"
 * L: ["foo", "bar"]
 * You should return the indices: [0,9] (order does not matter).
 * dhu note: L may have duplicate elements.
 */

#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

// dhu solution: Time limit exceeded for large dataset
class Solution {
public:
  vector<int> findSubstring(string S, vector<string>& L) {
    vector<int> result;
    if (S.size() == 0)
      return result;

    size_t word_cnt = L.size();
    size_t word_len = L[0].size();
    map<string, int> word_map;
    for (size_t i = 0; i < word_cnt; i++) {
      word_map[L[i]]++;
    }

    size_t curr_cnt = 0;
    size_t curr_start = 0;
    map<string, int> left_over = word_map;
    size_t i = 0;
    while (i < S.size()) {
      string curr_word = S.substr(i, word_len);
      map<string, int>::iterator it = left_over.find(curr_word);
      // Current substring is not a word on the list
      if (it == left_over.end()) {
	curr_start++;
	i = curr_start;
	curr_cnt = 0;
	left_over = word_map;
      }
      // Current substring is a word on the list, and it was NOT found before 
      else {
	curr_cnt++;
	if (it->second == 1)
	  left_over.erase(curr_word);
	else
	  left_over[curr_word]--;

	/* If all words on the list have been found, add curr_start 
	 * into result, then start a new session. */ 
	if (curr_cnt == word_cnt) {
	  result.push_back(curr_start);
	  left_over = word_map;
	  curr_cnt = 0;
	  curr_start++;
	  i = curr_start;
	}	
	else 
	  i += word_len;
      }

    }

    return result;
  }

};

/* anson627 solution: 1969ms for large dataset.
 * The idea in this algorithm is close to mine, 
 * but the implementation is more intuitive and easier to follow.  
 * Runtime complexity is O(N*M), in which N is the length of S,
 * M is the length of one word on the list. 
 */
class Solution_anson {
public:
  vector<int> findSubstring(string S, vector<string> &L) {
    map<string, int> toFind;
    map<string, int> hasFound;
    for (size_t i = 0; i < L.size(); i++) 
      toFind[L[i]]++;
    int N = L.size();
    int M = L[0].size();
    vector<int> res;
    for (int i = 0; i <= (int)S.size() - N * M; i++) {
      hasFound.clear();
      int j;
      for (j = 0; j < N; j++) {
	int k = i + j * M;
	string sub = S.substr(k, M);
	// Current substring is not a word on the list
	if (toFind.find(sub) == toFind.end()) 
	  break;

	hasFound[sub]++;
	// Current substring is a word on the list, but it is an extra one
	if (hasFound[sub] > toFind[sub]) 
	  break;
      }
      if (j == N) 
	res.push_back(i);
    }

    return res;
  }
};

int main() {
  string S("lingmindraboofooowingdingbarrwingmonkeypoundcake");
  vector<string> L;
  L.push_back("fooo");
  L.push_back("barr");
  L.push_back("wing");
  L.push_back("ding");
  L.push_back("wing");

  Solution foo;
  vector<int> ret = foo.findSubstring(S, L);
  for (size_t i = 0; i < ret.size(); i++)
    cout << ret[i] << endl;
}
