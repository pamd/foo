/* Infix evaluation: 
 * eval_infix_proper() evaluates an input infix string that has proper "()";
 * eval_infix_wild() evaluates an input infix string that does not "()"
 * that does not affect the final result.
 */

#include <string>
#include <stack>
#include <iostream>

using namespace std;

// Calculate one pair of numbers connected by operator char
int calc(int left, char op_char, int right) {
  if (op_char == '+')
    return left + right;

  if (op_char == '-')
    return left - right;

  if (op_char == '*')
    return left * right;

  return left / right;
}

/* Pop the top two elements in numbers, then pop the top element 
 * in operators, calculate the new value, and push it into numbers. */
void pop_calc(stack<int>& numbers, stack<char>& operators) {
  // Make sure number stack has at least two elements and operator stack has one
  if (numbers.size() < 2 || operators.empty())
    return;

  int right = numbers.top();
  numbers.pop();
  int left = numbers.top();
  numbers.pop();

  char op_char = operators.top();
  operators.pop();
      
  int result = calc(left, op_char, right);
  numbers.push(result);
}

/* Infix evaluation of infix string that have proper "()": use two stacks. 
 * Refer to "Algorithms" (4th Edition), written by Robert Sedgewick, page 128.
 *
 * Here we assume that each operand is asingle digit 0~9, and the only 
 * possible operators are '+', '-', '*' or '/', 
 * and the input infix string always starts with '(' and ends with ')'. */
int eval_proper_infix(const string& infix) {
  stack<char> operators;
  stack<int> numbers;

  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    // We found an operator
    if (c == '+' || c == '-' || c == '*' || c == '/') 
      operators.push(c);

    // We found an operand
    else if (c >= '0' && c <= '9')
      numbers.push(c - '0');

    // ')' means an calculation is needed
    else if (c == ')') {
      pop_calc(numbers, operators);
    }
    // Since input string has proper "()", we ignore '('
  }

  return numbers.top();
}

/* Helper function for eval_wild_infix(): compare priority of two operators.
 * Returns true if first operator has higher priority than the second one has,
 * returns false otherwise. 
 * This function returns true only when the first operator is '*' or '/' 
 * and the second is '+' or '-'.
 */
bool hasHigherPriority(char op1, char op2) {
  if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
    return true;

  if (op2 == '(')
    return true;

  return false;
}

/* Infix evaluation of an input infix string that does not have "()"
 * that does not affect the final result. It uses two stacks too, 
 * but we have to consider priorities of different operators.
 * Refer to:
 * http://baike.baidu.com/view/552648.htm
 *
 * Again we assume that each operand is asingle digit 0~9, and
 * the only possible operators are '+', '-', '*' or '/'. 
 */
int eval_wild_infix(const string& infix) {
  stack<char> operators;
  stack<int> numbers;

  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    /* If current char is an operator and operators is not empty,
     * compare current operator's priority and the top operator's 
     * priority. If current operator's priority is <= top operator's
     * priority, call pop_calc() on numbers and operators. Keep
     * doing this until either operator stack is empty, or its top
     * operator has lower priority. Then push current operator into 
     * operator stack. So the operators in stack are always sorted by
     * by their priorities, with lowest one on bottom and highest one
     * on top. */
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      /* If operator stack is empty, or the top operator is '(',
       * push current operator into stack. */
      if (operators.empty() || operators.top() == '(')
	operators.push(c);
      /* Otherwise, pop the operator stack's top element(s) whose
       * priorities are equal to or higher than current operator's. */  
      else {
	while (!operators.empty() && !hasHigherPriority(c, operators.top())) 
	  pop_calc(numbers, operators);
	operators.push(c);
      }
    }

    // If current char is a number, simply push it into number stack.
    else if (c >= '0' && c <= '9')
      numbers.push(c - '0');

    /* If we see a '(', we have to push it into operator stack,
     * because we need to use a mark to match the next ')'. */
    else if (c == '(') 
      operators.push(c);

    /* If current char if ')', it is time to do calculation. We keep
     * calling pop_calc() until the top element in operator stack is '('.
     * Then we pop '(' too. */ 
    else if (c == ')') {
      while (operators.top() != '(')
	pop_calc(numbers, operators);
      operators.pop();
    }

    // Ignore any other characters
  }

  while (operators.size())
    pop_calc(numbers, operators);

  return numbers.top();
}

/* Evaluate infix expression with recursion, assuming there is no "()". 
 * Scan input string from left to right, if operator is '*" or '/", 
 * do the calculation. When we find the first "+" or "-", divide it
 * into two partitions. Recursively parse the second partition. 
 * (The first partition has been parsed when we scanned it.) 
 * 
 * If the expression has "()", we can scan it until we find a complete
 * section of "()" pair, then parse the "()" section, and substring that follows.
 */

// Test harness
int main() {
  string infix("((1+2)*3+4)*5-6");

  int result = eval_infix_wild(infix);
  cout << result << endl;

}
