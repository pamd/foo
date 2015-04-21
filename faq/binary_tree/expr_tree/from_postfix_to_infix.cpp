/* Convert an input postfix string into infix notation. */

#include <string>
#include <iostream>
#include <stack>

using namespace std;

// Iterative solution using a stack, scan from left to right
string iteration(const string& postfix) {
  stack<string> stk;
  for (size_t i = 0; i < postfix.size(); i++) {
    char c = postfix[i];
    if (c >= '0' && c <= '9') 
      stk.push(string(1, c));
    else {
      string tmp("(");
      string right = stk.top(); 
      stk.pop();
      string left = stk.top();
      stk.pop();

      tmp += left;
      tmp.push_back(c);
      tmp += right;
      tmp.push_back(')');
      stk.push(tmp);
    }
  }

  return stk.top();
}

// Recursive solution: scan from right to left
string recursion(const string& postfix, size_t& idx) {
  char c = postfix[idx];
  if (c >= '0' && c <= '9')
    return string(1, c);

  string result("(");
  string right = recursion(postfix, --idx);
  string left  = recursion(postfix, --idx);

  result += left;
  result.push_back(c);
  result += right;
  result.push_back(')');
  return result;
}

// Test harness
int main() {
  string postfix("12-345/*+");

  size_t idx = postfix.size() - 1;
  string infix = recursion(postfix, idx);
  cout << infix << endl;

}
