/* Discussion #399, from:
 * http://www.mitbbs.com/article_t/JobHunting/32127411.html
 */

#include <iostream>
#include <vector>

using namespace std;

// longway2008
int BinaryTreeDepth(const string& str)
{
  int maxDepth = -1; 
  int depth = -1; 
  string stack;  // stack that keeps track of current node
  for (size_t i = 0; i < str.size(); ++i) {
    // When current char is '(' or '0', push it into the stack 
    if (str[i] == '(') {
      stack.push_back(str[i]);
      maxDepth = max(maxDepth, ++depth);
    } 
    else if (str[i] == '0') {
      stack.push_back('0');
    } 
    // When currnet char is '0', the top three elements in stack must be "(00".
    // If not, the input string is not a valid binary tree.
    else if (str[i] == ')') {
      int n = stack.size();
      if (n < 3 || stack[n - 1] != '0' || stack[n - 2] != '0' || stack[n - 3] != '(') 
	return -1;

      // Change subtree that is rooted at current node into a single leef node
      stack[n - 3] = '0';
      stack.resize(n - 2); // delete two top elements in stack
      --depth;  // decrement depth
    } 
    else 
      return -1;
  }

  return v[0] == '0' && v.size() == 1 ? maxDepth : -1;     
}

// Test harness
int main() {
  string str("((00)(00))");
  cout << BinaryTreeDepth(str) << endl;

}
