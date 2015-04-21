/* Construct expression tree based on an input infix string. 
 * If the input infix string does not have proper "()", 
 * there will be multiple ways to construct the corresponding
 * expression tree. As a matter of fact, if we do not consider
 * any operator priorities, given an infix string that has n 
 * operators, the number of unique expression trees is Catalan(n).
 * But if we consider operator priorities, it is not Catalan(n) 
 * any more. For example, for "1+2*3", there is only one 
 * expression tree, in which '+' is the root. 
 */

#include <string>
#include <stack>
#include <iostream>

using namespace std;

/* Data structure of expression tree node.
 * In this definition, a node can be either an operator, 
 * or an operand. This is not the best object-oriented design.
 * See OOD.cpp for detailed discussion. */
struct Node {
  Node(char ci) : c(ci), left(0), right(0) { }

  char c;
  /* An operator will always have valid left and right chilren,
   * but an operand has neigher of them. */
  Node* left;
  Node* right;
};

// Helper function: print out pre-order traversal
void inorder(Node* root) {
  if (!root)
    return;
  
  if (root->left)
    cout << "(";

  inorder(root->left);
  cout << root->c;
  inorder(root->right);

  if (root->right)
    cout << ")";
}

/* Construct expression tree based on an infix string that
 * has proper "()". The idea is similar to infix evaluation. 
 * Two stacks are used. */
Node* construct_from_proper_infix(const string& infix) {
  stack<Node*> numbers;
  stack<Node*> operators;
  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    // Skip '('
    if (c == '(')
      continue;

    // Push number into numbers stack
    if (c >= '0' && c <= '9') {
      Node* tmp = new Node(c);
      numbers.push(tmp);
    }

    /* For ')', pop top two elements in numbers stack,
     * and set them as the top operator's left and right children,
     * then move operator stack's top element into numbers stack. */
    else if (c == ')') {
      operators.top()->right = numbers.top();
      numbers.pop();
      operators.top()->left = numbers.top();
      numbers.pop();
      numbers.push(operators.top());
      operators.pop();
    }

    // Push operator char into operator stack
    else {
      Node* tmp = new Node(c);
      operators.push(tmp);
    }
  }

  return numbers.top();
}

/* Helper function for construct_wild_infix(): copied from eval_infix.cpp.
 * It compare priority of two input operators.
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

/* Helper function that is based on pop_calc() in eval_infix.cpp.
 * It pops the top two elements in numbers stack, then pops the top element 
 * in operators stack, calculates the new value, and pushes it into numbers. */
void pop2_push1(stack<Node*>& numbers, stack<Node*>& operators) {
  // Make sure number stack has at least two elements and operator stack has one
  if (numbers.size() < 2 || operators.empty())
    return;

  Node* tmp = operators.top();
  operators.pop();

  tmp->right = numbers.top();
  numbers.pop();

  tmp->left = numbers.top();
  numbers.pop();

  numbers.push(tmp);
}

/* Construct expression tree based on an infix string that does NOT
 * have proper "()". Since the expression tree may be unique, we can
 * scan the infix string from left to right, find an operator that is
 * not enclosed in any pair of "()" and whose priority is the lowest,
 * then use that operator as root node, divide the original infix string 
 * into two partitions, then create expression tree for each partition.
 * The root node of left partition will be the left child of root, and the
 * root node of right partition will be the right child of root. 
 * For example, in "1+2*3", '+' will be the root node; but in "(1+2)*3",
 * '*' will be root node.
 * This approach has T(n) = 2 * T(n / 2) + O(n), so time complexity is O(nlgn). 
 * It will allow us to find ALL expression trees that correspond to input infix.
 *
 * Alternatively, we can use the same idea in eval_wild_infix() to get one
 * valid expression tree based on infix string. Time complexity is O(n).
 * In this algorithm, the root of returned expression tree will be always 
 * the last valid root candidate. Here is the code:                     
 */ 
Node* construct_from_wild_infix(const string& infix) {
  stack<Node*> numbers;
  stack<Node*> operators;
  for (size_t i = 0; i < infix.size(); i++) {
    char c = infix[i];
    if (c >= '0' && c <= '9') 
      numbers.push(new Node(c));
    else if (c == '(')
      operators.push(new Node(c));
    else if (c == ')') {
      while (!operators.empty() && operators.top()->c != '(') 
	pop2_push1(numbers, operators);
      operators.pop();
    }

    // Current char is an operator
    else {
      if (operators.empty() || operators.top()->c == '(')
	operators.push(new Node(c));
      else {
	while (!operators.empty() && !hasHigherPriority(c, operators.top()->c)) 
	  pop2_push1(numbers, operators);
	operators.push(new Node(c));
      } // end of inner else
    } // end of outer else
  } // end of for loop

  while (!operators.empty()) 
    pop2_push1(numbers, operators);

  return numbers.top();
}

// Test harness
int main() {
  string infix("(1+2)*(8/4)");
  Node* root = construct_from_wild_infix(infix);
  
  inorder(root);
  cout << endl;

}
