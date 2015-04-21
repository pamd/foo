/* Leetcode OJ: Given a string containing only digits, restore it by returning 
 * all possible valid IP address combinations. For example, given "25525511135",
 * return ["255.255.11.135", "255.255.111.35"] (Order does not matter).
 */

// 16ms for large dataset
class Solution {
public:
  vector<string> restoreIpAddresses(string s) {
    vector<string> result;
    string tmp;    
    helper(s, 4, tmp, result);
    return result;
  }

  void helper(string s, int num, string tmp, vector<string>& result) {
    if (num == 0 && s.size() == 0) {
      result.push_back(tmp);
      return;
    }

    if (num == 0 || s.size() == 0)
      return;

    if (s[0] == '0') {
      if (!tmp.size()) 
	tmp = "0";
      else 
	tmp += ".0";
      helper(s.substr(1), num - 1, tmp, result);
      return;
    }

    int foo = 0;
    for (size_t i = 0; i < 3 && i < s.size(); i++) {
      foo = 10 * foo + s[i] - '0';
      if (foo > 255)
	return;

      string tmp2;
      if (tmp.size() == 0)
	tmp2 = s.substr(0, i + 1);
      else 
	tmp2 = tmp + string(".") + s.substr(0, i + 1);

      helper(s.substr(i + 1), num - 1, tmp2, result);
    }
  }

};
