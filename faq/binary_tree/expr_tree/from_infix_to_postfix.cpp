/* Convert infix notation into postfix. */

#include <stack>
#include <string>
#include <iostream>

using namespace std;

/* Convert an infix notation that has proper "()" to postfix.
 * See "Algorithms in C++", by Robert Sedgewick, page 152.
 * The idea is to use one stack to store the operators.
 * If current char is a number, append it into the final result string;
 * if current char is '(', skip it;
 * if current char is an operator, push it into the stack; 
 * if current char is ')', pop the top element in stack and append it
 * into the final result string.
 */
string convert_proper(const string& infix) {
  stack<char> operators;
  string result;
  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    if (c >= '0' && c <= '9')
      result.push_back(c);
    else if (c == '+' || c == '-' || c == '*' || c == '/')
      operators.push(c);
    else if (c == ')') {
      result.push_back(operators.top());
      operators.pop();
    }
  }

  return result;
}

/* Convert an infix string that does NOT have all "()" to postfix.
 * When infix string is not enclosed by "()", there may be multiple
 * expression trees (see construct_from_infix.cpp), so there may be
 * multiple postfix notations. For example, infix string "1+2+3" can
 * be converted to postfix "123++" or "12+3+". 
 * The following solution converts an infix string into postfix whose 
 * correpsonding expression tree is rooted at the last lowest priority 
 * operator. 
 * Also refer to:
 * http://baike.baidu.com/view/552648.htm
 * http://www.mitbbs.com/article_t/JobHunting/32030585.html
 * The algorithm is similar to constructing expression tree from infix.
 */
string convert_wild(const string& infix) {
  stack<char> operators;
  string result;
  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    if (c >= '0' && c <= '9')
      result.push_back(c);
    else if (c == '(')
      operators.push(c);
    else if (c == '+' || c == '-') {
      while (!operators.empty()) {
	if (operators.top() == '(') 
	  break;

	result.push_back(operators.top());
	operators.pop();
      }
      operators.push(c);
    }
    else if (c == '*' || c == '/') {
      if (!operators.empty() && (operators.top() == '*' || operators.top() == '/')) {
	result.push_back(operators.top());
	operators.pop();
      }
      operators.push(c);
    }
    else if (c == ')') {
      while (operators.top() != '(') {
	result.push_back(operators.top());
	operators.pop();
      }
      operators.pop();
    }
  }

  while (!operators.empty()) {
    result.push_back(operators.top());
    operators.pop();
  }

  return result;
}

// Test harness
int main() {
  //string infix("((1-2)+(3*(4/5)))");
  //string postfix = convert_proper(infix);

  //string infix("1*(2+3)");
  string infix("1-2+3*4/5");
  string postfix = convert_wild(infix);
  cout << postfix << endl;

}
