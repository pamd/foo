/* OJ problem: Given a digit string, return all possible letter combinations 
 * that the number could represent.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 8ms for large dataset
class Solution {
public:
  vector<string> letterCombinations(string digits) {
    vector<string> ret;
    string curr(digits.size());
    recur_helper(ret, curr, digits, 0);

    return ret;
  }

  // Recursive helper
  void recur_helper(vector<string>& ret, string& curr, const string& digits, size_t level) {
    static string dict[10] = { "", "", "abc", "def", "ghi", "jkl", 
			       "mno", "pqrs", "tuv", "wxyz" }; 

    if (level == digits.size()) {
      ret.push_back(curr);
      return;
    }

    char c = dict[level];
    if (c == '0' || c == '1') {
      curr[level] = c;
      recur_helper(ret, curr, digits, level + 1);
      return;
    }
    
    string str = digits[c - '0'];
    for (size_t i = 0; i < str.size(); i++) {
      curr[level] = str[i];
      recur_helper(ret, curr, digits, level + 1);
    }
  }

};

int main() {
  Solution foo;
  string digits("7");
  vector<string> results = foo.letterCombinations(digits);
  for (size_t i = 0; i < results.size(); i++)
    cout << results[i] << endl;

}
