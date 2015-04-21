/* Evaluate an input postfix string. */

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

/* Method #1: from "Algorithms in C++", written by Robert Sedgewick, page 148. 
 * The idea is simple: scan the input postfix string from left to right.
 * For each number, push it into a stack; 
 * For each operator, pop two elements out of the stack, calculate the
 * new value based on the current operator, then push the new number
 * back into stack. At the very end, there will be only one number in the 
 * stack, which is the final answer.
 * Because a prefix or postfix string can determine a unique expression tree
 * without using "()", we never need to deal with "()". So this problem is
 * much easier than evaluation of infix string.
 *
 * Here we assume that each operand is asingle digit 0~9, and the only 
 * possible operators are '+', '-', '*' or '/', 
 * and the input infix string always starts with '(' and ends with ')'. */
int eval_postfix(const string& postfix) {
  stack<int> numbers;
  for (size_t i = 0; i < postfix.size(); i++) {
    char c = postfix[i];
    // Push number into a stack
    if (c >= '0' && c <= '9')
      numbers.push(c - '0');
    // For operators, pop two top elements out of stack and do calculation
    else {
      /* IMPORTANT: Due to the order of post-order traversal, the top element in stack 
       * is the right operand, and the one below the top element is the left operand. */ 
      int right = numbers.top();
      numbers.pop();
      int left = numbers.top();
      numbers.pop();
      numbers.push(calc(left, c, right));
    }
  }

  return numbers.top();
}

/* Method #2: scan input postfix string from right to left, use the idea
 * as eval_prefix2(). Code not provided. */

/* Method #3: recursive approach that scans from right to left,
 * based on prefix/postfix conversion by darksteel. */
int eval_recurse(const string& prefix, size_t& idx) {
  char c = prefix[idx];
  if (c >= '0' && c <= '9')
    return c - '0';

  int left = eval_recurse(prefix, --idx);
  int right = eval_recurse(prefix, --idx);
  return calc(left, c, right);
}


// Test harness
int main() {
  string postfix("23*4+");

  size_t idx = postfix.size() - 1;
  int result = eval_recurse(postfix, idx);
  cout << result << endl;

  return 0;
}





