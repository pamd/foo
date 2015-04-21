/* Convert infix notation into prefix. */

#include <stack>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/* Convert an infix notation that has proper "()" into prefix.
 * Similar to converting infix to postfix, but we scan the input infix
 * string from right to left. At the end we reverse the result.
 * Here is why it works: the order of infix is "LVR" ("L" is left,
 * "V" is visted, "R" is right), when it is scanned from right to left, 
 * the order is "RVL", then it is converted to postfix, so the order 
 * becomes "RLV"; finally it is reversed, the order becomes "VLR", 
 * which is the order of regular prefix.
 *
 * The idea is to use one stack to store the operators.
 * If current char is a number, append it into the final result string;
 * if current char is ')', skip it;
 * if current char is an operator, push it into the stack; 
 * if current char is '(', pop the top element in stack and append it
 * into the final result string.
 * At the end reverse result string.
 */
string convert_proper_from_right(const string& infix) {
  stack<char> operators;
  string prefix;
  for (int i = infix.size() - 1; i >= 0; i--) {
    char c = infix[i];
    if (c >= '0' && c <= '9')
      prefix.push_back(c);
    else if (c == '+' || c == '-' || c == '*' || c == '/')
      operators.push(c);
    else if (c == '(') {
      prefix.push_back(operators.top());
      operators.pop();
    }
  }

  reverse(prefix.begin(), prefix.end());
  return prefix;
}

/* Helper function which is called by convert_proper_from_left() 
 * and convert_wild(). It pops two top elements in numbers stack, 
 * then pop the top element from operators stack, do calculation 
 * based on input operator, then push result into numbers stack.
 */
void pop_push(stack<string>& numbers, stack<char>& operators) {
  string tmp;
  tmp.push_back(operators.top());
  operators.pop();
  
  string right = numbers.top();
  numbers.pop();
  string left = numbers.top();
  numbers.pop();
  tmp += left + right;

  numbers.push(tmp);
}

/* Alternatively, we can scan from left to right by using two stacks.
 * The idea is similar to infix evaluation. 
 */
string convert_proper_from_left(const string& infix) {
  if (infix.size() == 0)
    return string();

  stack<char> operators;
  stack<string> numbers;
  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    if (c >= '0' && c <= '9')
      numbers.push(string(1, c));
    else if (c == '+' || c == '-' || c == '*' || c == '/')
      operators.push(c);
    else if (c == ')') {
      pop_push(numbers, operators);
    }
  }
  
  return numbers.top();
}


/* Convert an infix string that does NOT have all "()" to prefix.
 * When infix string is not enclosed by "()", there may be multiple
 * expression trees (see construct_from_infix.cpp), so there may be
 * multiple prefix notations. For example, infix string "1+2+3" can
 * be converted to prefix "+1+23" or "++123". 
 *
 * The following solution converts an infix string into prefix whose 
 * correpsonding expression tree is rooted at the last lowest priority 
 * operator. The idea is similar to wild infix evaluation. 
 */
string convert_wild(const string& infix) {
  if (infix.size() == 0)
    return string();

  stack<char> operators;
  stack<string> numbers;
  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    if (c >= '0' && c <= '9')
      numbers.push(string(1, c));
    else if (c == '(')
      operators.push(c);
    else if (c == '+' || c == '-') {
      while (!operators.empty()) {
	if (operators.top() == '(') 
	  break;

	pop_push(numbers, operators);
      }
      operators.push(c);
    }
    else if (c == '*' || c == '/') {
      if (!operators.empty() && (operators.top() == '*' || operators.top() == '/')) {
	pop_push(numbers, operators);
      }
      operators.push(c);
    }
    else if (c == ')') {
      while (operators.top() != '(') {
	pop_push(numbers, operators);
      }
      operators.pop();
    }
  }

  while (!operators.empty()) 
    pop_push(numbers, operators);

  return numbers.top();
}

// Test harness
int main() {
  //string infix("((1-2)+(3*(4/5)))");
  //string prefix = convert_proper_from_left(infix);

  //string infix("1*(2+3)");
  string infix("1-2+3*4/5");
  string prefix = convert_wild(infix);

  cout << prefix << endl;

}
