/* Leetcode OJ: Given an array of strings, return all groups of strings 
 * that are anagrams.
 * Note: All inputs will be in lower-case.
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

bool my_func(const string& s1, const string& s2) {
  string s11(s1);
  sort(s11.begin(), s11.end());
  
  string s22(s2);
  sort(s22.begin(), s22.end());
  
  return s11 < s22;
}

class Solution {
public:
  vector<string> anagrams(vector<string> &strs) {
    map<string, vector<string> > theMap;
    for (size_t i = 0; i < strs.size(); i++) {
      string sorted(strs[i]);
      sort(sorted.begin(), sorted.end());
      theMap[sorted].push_back(strs[i]);
    }
    vector<string> ret;
    map<string, vector<string> >::iterator it;
    for (it = theMap.begin(); it != theMap.end(); ++it) {
      if (it->second.size() == 1) 
	continue;
      for (size_t i = 0; i < it->second.size(); i++)
	ret.push_back(it->second[i]);
    }

    //for (size_t i = 0; i < ret.size(); i++)
    //  cout << ret[i] << endl;

    return ret;
  }

};

/*
int main() {
  vector<string> v;
  v.push_back("asdf");
  v.push_back("asdet");
  v.push_back("ntyr");
  //v.push_back("dfas");
  //sort(v.begin(), v.end(), my_func);
  Solution foo;
  foo.anagrams(v);
}
*/

// Online solution
/*
**  The idea of this solution is to sort each string with alphabet order.
**  Then each anagrams would has the same result.
**  Group the result and record the indics in orignial array, if the 
**  count is larger than 2, we find anagram.
**
**  Since the strings only contains lowercase, we could sort it with 
**  bucket sort, the time complexity if O(m), where m is length of string.
**
**  I use map for grouping, so it takes O(n log n) time, where n is size
**  of array. If we use hashtable, it could be reduced to O(n).
**  
**  Hence the total time complexity of this idea would be O(mn).
*/
string BucketSort(string s) {
  vector<int> b(26, 0);
  for (size_t i = 0; i < s.size(); ++i)
    ++b[s[i]-'a'];
    
  s.clear();
  for (size_t i = 0; i < b.size(); ++i)
    for (size_t j = 0; j < b[i]; ++j)
      s.push_back('a' + i);
  
  return s;
}

vector<string> Anagrams(vector<string> &strs) {
  map<string, vector<size_t> > mapper;
  
  for (size_t i = 0; i < strs.size(); ++i)
    mapper[BucketSort(strs[i])].push_back(i);
  
  map<string, vector<size_t> >::iterator beg = mapper.begin();
  map<string, vector<size_t> >::iterator end = mapper.end();
  vector<string> result;
  while(beg != end) {
    vector<size_t>& indics = (*beg).second;
    if (indics.size() > 1)
      for (size_t i = 0; i < indics.size(); ++i)
	result.push_back(strs[indics[i]]);
    ++beg;
  }

  return result;
}

void PrintV(vector<string> &strs) {
  for (int i = 0; i < strs.size(); ++i)
    cout << strs[i] << ", ";
  
  cout << endl;
}

// Test harness
int main(int argc, char** argv) {
  char a[][20] = {
    "amp",
    "map",
    "tea",
    "eat",
    "hello"
  };

  vector<string> strs;
  strs.assign(a, a+5);
  
  PrintV(strs);
  
  vector<string> result = Anagrams(strs);
  PrintV(result);
  
  return 0;
}
