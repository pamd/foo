/* Leetcode OJ: Given a string containing just the characters '(' and ')', 
 *  find the length of the longest valid (well-formed) parentheses substring.
 *
 * For example, in "(()", the longest valid parentheses substring is "()", 
 * whose length = 2.
 * Another example is ")()())", in which the longest valid parentheses substring 
 * is "()()", whose length = 4.
 */

#include <iostream>
#include <string>

using namespace std;

/* This solution is INCORRECT, because for "()(()",
 * it returns an answer of 4, but it should be 2. */
class Solution {
public:
  int longestValidParentheses(string s) {
    int left = 0;
    int right = 0;
    int maxLen = 0;
    for (size_t i = 0; i < s.size(); i++) {
      if (s[i] == '(')
	left++;
      else
	right++;

      if (right <= left && maxLen < right * 2)
	maxLen = right * 2;
      if (right > left) {
	left = 0;
	right = 0;
      }
    }
    return maxLen;
  }
};

/* O(n) solution based on solution on mitbbs. It scans the 
 * input string twice, one moves forward, the other moves backward.
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32066231.html
 * 32ms for large dataset.
 */
int longestValidParentheses(string s) {
  int counter = 0;
  int ret = 0;
  int curr_max = 0;
  // Forward traversal
  for (size_t i = 0 ; i < s.length() ; i++) {
    if (s[i] == '(') {
      counter++;
      curr_max++;
      continue;
    }
    // if current char is ')'
    counter--;
    curr_max++;
    if (counter == 0)
      ret = (ret >= curr_max) ? ret : curr_max;    
    else if (counter < 0) {
      curr_max = 0;
      counter = 0;
    }
  }

  // Backward traversal
  counter = 0;
  curr_max = 0;
  for (int i = s.length() -1; i >=0; i--) {
    if (s[i] == ')') {
      counter++;
      curr_max++;
      continue;
    }
    // If current char is '('
    counter--;
    curr_max++;
    if (counter == 0)
      ret = (ret >= curr_max) ? ret : curr_max;
    else if (counter < 0) {
      curr_max = 0;
      counter = 0;
    }
  }

  return ret;        
}

// Helper function that counts number of valid () pairs from a starting index
int count(string s, size_t start) {
  int counter = 0;
  int max = 0;
  int tmp = 0;
  for (size_t i = start; i < s.size(); i++) {
    if (s[i] == '(')
      counter++;
    else {
      counter--;
      tmp++;
    }

    if (counter < 0)
      return max;

    if (counter == 0) {
      if (tmp > max)
	max = tmp;
    }
  }

  return max;
}

/* Dropbox solution: somewhat confusing.
 * This question need to pay attention to at leat three valid parentheses situations:
 * valid parentheses inside of other valid parentheses: ((()))
 * valid parentheses next to other other valid parentheses: ()()()
 * and combination of above two: ()(())
 */

#include <string>
#include <stack>

using namespace std;

int LongestValidParentheses(string& s) {
  int longest = 0;
  int length = s.size();
  stack<size_t> iStack; // stack for index of left parenthesis in string
  stack<size_t> eStack; // stack for the end index of valid parentheses
  stack<size_t> lStack; // stack for length of valid parentheses associated in eStack
  int offset;
  
  for (int i = 0; i < length; ++i) {
    // Push left parenthesis
    if (s[i] == '(') {
      iStack.push(i);
    }   
    else if (!iStack.empty()) { // meet a matched right parenthesis
      size_t iLeft = iStack.top();
      // Offset of these matched parentheses
      offset = i - iLeft + 1;
      
      /* Pop out all saved valid parentheses that are 
       * just inside of current found valid parentheses. */
      while(!eStack.empty() && iLeft < eStack.top()) {
	eStack.pop();
	lStack.pop();
      }

      // Former valid parentheses is just next to current one,
      // join them together now.
      if(!eStack.empty() && eStack.top() == iLeft-1) {
	offset += lStack.top();
	eStack.top() = i;
	lStack.top() = offset;
      }
      // eStack is empty or the former valid parentheses 
      // is not next to current one
      else {
	eStack.push(i);
	lStack.push(offset);
      }
      
      if (offset > longest) 
	longest = offset;
      
      iStack.pop();
    }
    //else invalid right parenthesis ')' as it matches nothing
  }
  return longest;
}

/* // Dropbox solution main function 
#include <iostream>
#include <list>
#include <utility>
using namespace std;

int main(int argc, char** argv)
{
	string parentheses1 = "()(()(())";
	string parentheses2 = ")()())";
	
	cout << LongestValidParentheses(parentheses1) << '\n';
	cout << LongestValidParentheses(parentheses2) << '\n';
	return 0;
}
*/

/* O(n^2) brute force method to count the valid lenght of () pairs.
 * This function is not acceptable in OJ because it exceeded time limit.
 */
int brute(string s) {
  int max = 0;
  for (size_t i = 0; i < s.size(); i++) {
    int tmp = count(s, i);
    if (max < tmp)
      max = tmp;
  }

  return 2 * max;
}

/* Scan once, use an explicit stack
 * http://www.mitbbs.com/article_t/JobHunting/32300463.html
 * 44ms for large dataset. */
int longestValidParentheses(string s) {
  int m = 0;
  stack<int> stk;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(' || stk.empty() || s[stk.top()] == ')') 
      stk.push(i);
    else {
      stk.pop();
      int prev = stk.empty() ? -1 : stk.top();
      m = max(m, i - prev);
    }
  }
  return m;
}

// Test harness
int main()
{
  string s("()(()");
  cout << longestValidParentheses(s) << endl;
  cout << brute(s) << endl;

  return 0;
}
