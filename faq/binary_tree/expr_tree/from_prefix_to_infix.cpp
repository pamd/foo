/* Convert an input prefix string into infix notation. */

#include <string>
#include <iostream>
#include <stack>

using namespace std;

// Iterative solution using a stack, scan from right to left
string iteration(const string& prefix) {
  stack<string> stk;
  for (int i = prefix.size() - 1; i >= 0; i--) {
    char c = prefix[i];
    if (c >= '0' && c <= '9') 
      stk.push(string(1, c));
    else {
      string tmp("(");
      tmp += stk.top();
      stk.pop();
      tmp.push_back(c);

      tmp += stk.top();
      stk.pop();

      tmp.push_back(')');
      stk.push(tmp);
    }
  }

  return stk.top();
}

// Recursive solution: scan from left to right
string recursion(const string& prefix, size_t& idx) {
  char c = prefix[idx];
  if (c >= '0' && c <= '9')
    return string(1, c);

  string result("(");
  result += recursion(prefix, ++idx);
  result.push_back(c);
  result += recursion(prefix, ++idx);
  result.push_back(')');
  return result;
}

// Test harness
int main() {
  string prefix("+-12*3/45");
  //string prefix("+-12*45");

  size_t idx = 0;
  string infix = recursion(prefix, idx);
  cout << infix << endl;

}
