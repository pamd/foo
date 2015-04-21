/* Convert prefix notation to postfix notation. 
 * The idea is similar to construction of expression tree based on prefix.
 */

#include <string>
#include <vector>
#include <iostream>
#include <stack>

using namespace std;

// Use an explicit stack, scan prefix string from right to left
string iteration_dhu(const string& prefix) {
  if (prefix.size() == 0) 
    return string();

  stack<string> stk;
  for (int i = prefix.size() - 1; i >= 0; i--) {
    char c = prefix[i];
    if (c >= '0' && c <= '9') 
      stk.push(string(1, c));
    else {
      string left = stk.top();
      stk.pop();
      string right = stk.top();
      stk.pop();
      stk.push(left + right + c);
    }
  }

  return stk.top();
}

/* Use an explicit stack, scan prefix string from left to right.
 * Based on code by xieyi@mitbbs. 
 * This approach is similar to prefix evaluation from left to right. */
string iteration_xieyi(const string& prefix) {
  if (prefix.size() == 0)
    return string();
  
  stack<string> stk;
  for (size_t i = 0; i < prefix.size(); i++) {
    string tmp = prefix.substr(i, 1);
    // If current char is an operator, push it into the stack
    if (tmp == "-" || tmp == "+" || tmp == "*" || tmp == "/")     
      stk.push(tmp);
    
    // If current char is a number
    else {
      /* If the stack is not empty and its top element is NOT an operator,
       * merge the current number with the top two elements in the stack.*/
      while (!stk.empty()) {
	string top = stk.top();
	if (top == "+" || top == "-" || top == "*" || top == "/")
	  break;
	
	stk.pop();
	top.append(tmp);
	top.append(stk.top());
	stk.pop();
	tmp = top;
      }  // end of inner while loop
      stk.push(tmp);
    } // end of else
    
  }

  /* At the end, the stack will have only one element, 
   * which is the postfix string. */
  return stk.top();
}

// Code by darksteel, comments added by dhu
void recursion_darksteel() {
  char c;
  // Read input until the next operand or operator
  while ((c = cin.get()) == ' ');
  
  /* If an operator is found, recursively read left and right subtrees; 
   * If operand is found, do nothing. */
  if(c < '0' || c > '9') {
    recursion_darksteel(); 
    recursion_darksteel();
  }

  // Print out the operand or operator
  cout << c;
}

/* dhu recursive function, based on pre2post() by darksteel. */
// ------------------------------------------------------------

// Recursive helper function, which will be called by recursion_wrapper() 
string recursion(const string& prefix, size_t& level) {
  string result;
  if (level == prefix.size())
    return result;

  char c = prefix[level];
  if (c == '+' || c == '-' || c == '*' || c == '/') {
    result += recursion(prefix, ++level);
    result += recursion(prefix, ++level);
  }

  result.push_back(c);

  return result;
}

// dhu wrapper function for recursion
string recursion_wrapper(const string& prefix) {
  size_t level = 0;
  return recursion_helper(prefix, level);
}

// Test harness
int main() {
  string prefix("+-12*3/45");
  //string prefix("+-12*45");

  string postfix = recursion_dhu(prefix);
  cout << postfix << endl;

}
