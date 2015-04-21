/* Evaluate an input prefix string. */
 
#include <string>
#include <stack>
#include <iostream>

using namespace std;

// Helper function
int calc(int left, char op_char, int right) {
  if (op_char == '+')
    return left + right;

  if (op_char == '-')
    return left - right;

  if (op_char == '*')
    return left * right;

  return left / right;
}

/* Evaluation of prefix string is similar to evaluation of postfix.
 * According to "Data Structures and Algorithms in C++" (erd edition, 
 * by Adam Drozdek), pre-order traversal is "VLR", where "V" is 
 * visiting current node, "L" is left child and "R" is right child.
 * Post-order traversal is "LRV". So the reverse of pre-order traversal
 * is "RLV", which is a variant of regular post-order traversal.
 * With this insight, we can evaluate prefix string using the same idea
 * in postfix evaluation, but we have to scan the input prefix string
 * backwards, aka. from right to left.
 */
int eval_prefix1(const string& prefix) {
  stack<int> numbers;
  for (int i = prefix.size() - 1; i >= 0; i--) {
    char c = prefix[i];
    // Push number into a stack
    if (c >= '0' && c <= '9')
      numbers.push(c - '0');
    // For operators, pop two top elements out of stack and do calculation
    else {
      /* IMPORTANT: Due to the order of pre-order traversal, the top element in stack 
       * is the left operand, and the one below the top element is the right operand. 
       * This is opposite to the code of postfix evaluation. */ 
      int left = numbers.top();
      numbers.pop();
      int right = numbers.top();
      numbers.pop();
      numbers.push(calc(left, c, right));
    }
  }

  return numbers.top();
}

/* dhu tedious approach: similar to expression tree construction based on prefix. 
 * Use one stack to store operators. Each node in stack has not only the operator 
 * char, but also two extra field:
 *
 *	struct Element {
 *         Element() : hasLeft(false) { }
 *
 *         char c;    // operator character 
 *         int left;  // Value of left child
 *         bool hasLeft; // flag that tells whether left child exists or not
 *      };
 *
 * Scan input prefix string from left to right. If current character is an operator,
 * simply push it into the stack, with its initial value of hasLeft flag always set 
 * to false. If current character is a number, first check whether the top stack 
 * element has left child or not. If it does not have left child, set the left value
 * and the flag. If it has left child, the current numbber is treated as its right
 * child, and we calculate a new value based on the top element's operator and left
 * right operand. Then we pop the top element out of stack, check the new top element
 * in stack, until either the stack is empty, or the top element does not have left 
 * child. If the stack becomes empty, the final result will be returned as the 
 * evaluation result. If the stack is not empty, repeat the scan.
 * For a valid prefix string, the evaluation result will be always returned when
 * checking the last char in the string, which will be always a number.
 */

// Data structure of stack element
struct Element {
  Element() : hasLeft(false) { }

  char c; // operator character 
  int left; // Value of left child
  bool hasLeft; // flag that tells whether left child exists or not
};

// dhu approach: scan from left to right
int eval_prefix2(const string& prefix) {
  stack<Element> stk;
  
  for (size_t i = 0; i < prefix.size(); i++) {
    char c = prefix[i];
    // If current char is an operator, push it into the stack
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      Element tmp;
      tmp.c = c;
      stk.push(tmp);
    }
    // If current char is a number, do some calculations
    else {
      if (stk.top().hasLeft == false) {
	stk.top().left = c - '0';
	stk.top().hasLeft = true;
      }
      else {
	int result = calc(stk.top().left, stk.top().c, c - '0');
	stk.pop();
	while (!stk.empty() && stk.top().hasLeft) {
	  int tmp = calc(stk.top().left, stk.top().c, result);
	  stk.pop();
	  result = tmp;
	}
	// If the stack is empty, evaluation is done.
	if (stk.empty()) 
	  return result;
	  
	stk.top().left = result;
	stk.top().hasLeft = true;
      }
    }

  }

  // The program should never reach this point.
  return 0;
}

/* Recursive approach that scans from left to right, 
 * based on prefix/postfix conversion by darksteel. */
int eval_recurse(const string& prefix, size_t& idx) {
  char c = prefix[idx];
  if (c >= '0' && c <= '9')
    return c - '0';

  int left = eval_recurse(prefix, ++idx);
  int right = eval_recurse(prefix, ++idx);
  return calc(left, c, right);
}

// Test harness
int main() {
  string prefix("+*2/824");
  //string prefix("*1+23");

  size_t idx = 0;
  int result = eval_recurse(prefix, idx);
  cout << result << endl;

  return 0;
}
