/* Given a string containing just the characters '(', ')', '{', '}', '[' and ']', 
 * determine if the input string is valid.
 * The brackets must close in the correct order, fro example, "()" and "()[]{}" are all valid, 
 * but "(]" and "([)]" are not.
 */

// 4ms for large dataset
class Solution {
public:
  bool isValid(string s) {
    vector<char> stk;
    for (size_t i = 0; i < s.size(); i++) {
      char c = s[i];
      if (c == '(' || c == '[' || c == '{')
	stk.push_back(c);
      else if (c == ')') {
	if (!stk.size() || stk.back() != '(')
	  return false;
	stk.pop_back();
      }
      else if (c == ']') {
	if (!stk.size() || stk.back() != '[')
	  return false;
	stk.pop_back();
      }
      else if (c == '}') {
	if (!stk.size() || stk.back() != '{')
	  return false;
	stk.pop_back();
      }
      else
	return false;
    }

    return stk.size() == 0;
  }
};
