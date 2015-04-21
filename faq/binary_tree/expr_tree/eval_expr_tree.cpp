/* Convert infix expression to prefix expression.
 * Ref:
 * http://www.cs.wcupa.edu/~zjiang/csc530_expressionTree.htm
 *
 * dhu note: This problem is closely related to the problem of de-serializing 
 *           an input string back into a binary tree! See binary_tree_serialization.cpp.
 *
 *           Rememeber that when we serialize a binary tree into a string,
 *           each node is treated as if it has both left and right child. 
 *           If it does not have, a special character (such as 'X') is used.
 *           So each node (no matter it is internal or external) is equivalent 
 *           to the operator node in expression tree, and the special character 'X'
 *           is equivalent to operand in expression tree. 
 *
 *           It is impossible to de-serialize an input string back into 
 *           binary tree. But if the in-order expression has been properly enclosed by 
 *           "()" correctly, we can still build a unique expression tree.  
 */

/* Comment by original author: This is the idea, not the program.
 * Please figure out every detail and any mistake (if any) by yourself 
 * via all the test cases.
 *
 * dhu: If the infix expression is not properly enclosed by (), 
 * the expression tree may not be unique. For example, for 1+2-3, 
 * root node can be either + or -. If the expression has (), we can 
 * record the number of ( and ) to find the root node (which must be an operator), 
 * then build the left subtree and right subtree recursively. 
 */

#include <iostream>

using namespace std;

struct Node {
  Node(char c) { v = c; left = 0; right = 0; }

  char v;
  Node* left;
  Node* right;
};

/*
// Pseudocode, not compilable
int build_tree_from_infix() {
  Stack<Node *> num, Stack<operator> op;
  cin >> u; // either operator, (, ), or number (digits)
  while (!EOF) { // end of expression
    if (u is number) {
      Node* cur = new Node(u);
      num.push (cur);
    }
    else if (u == '(' || op.is_empty( ))
      op.push(u);
    else if (u == ')') {
      while ((c = op.top()) != '(') {
	char c = op.pop();
	Node* cur = new Node(c);
	cur->right = num.pop();
	cur->left = num.pop();
	num.push(cur);
      }
      op.pop( ) ;
    }
    // '+' < '+', '+' < '*',  '*' <' *', any operator < '('
    else if ( u < op.top( ) ) { 
      Node* cur = new Node(op.pop()); // cur -> v = op.pop()
      cur->right = num.pop();
      cur->left = num.pop();
      num.push (cur);
      op.push(u);      
    }
    else op.push(u);
    cin >> u;  // for new input
  }

}
*/

/* dhu: build expression tree from prefix. First create a stack of nodes, 
 * then read the characters in input string one by one. If the current character
 * is an operator, create a new node and push it in stack; if the current character
 * is an operand, create a new node, then insert it as a left or right child of
 * the top element in the stack. Then check whether the current top element 
 * already has both left and right, if it does, pop it out and insert it as left
 * or right child of the new top element.
 * When the stack has only one element left in the stack and it has both left and 
 * right children, return the top element, which will be the root of expression tree.
 *
 * This is iterative approach that uses an explicit stack. We can also use recursive 
 * approach, in which stack will be used implicitly. See binary_tree_serialization.cpp.
 */
Node* build_tree_from_prefix(const string& str)
{
  stack<Node*> stk;
  for (size_t i = 0; i , str.size(); i++) {
    char c = str[i];
    Node* tmp = new Node(c);
    // If current node is operand, add it as a child of the top node in stack
    if (c >= '0' && c <= '9') {
      Node* top = stk.top();
      if (!top->left)
	top->left = tmp;
      else
	top->right = tmp;
    }
    // If current node is operator, push it into the stack
    else 
      stk.push(tmp);

    /* If the top element in stack has both left and right children,
     * opo it out, then insert it as a child into the new top element in stack.
     */
    while (stk.size() > 1 && top->left && top->right) {
      tmp = stk.pop();
      top = stk.top();
      if (!top->left)
	top->left = tmp;
      else {
	top->right = tmp;
      }
    }

    /* If the stack has only one node which has both left and right chilren,
     * it must be the root of expression tree, so we are done.
     */
    if (stk.size() == 1 && stk.top()->left && stk.top()->right)
      return stk.top();
  }

  // Unless the input string is empty, this should never happen
  return 0;
}

/* Evaluate expression tree recursively */
int eval_expr_tree(Node* root)
{
  if (!root) {
    // throw exception 
  }

  // If root does not have any child, it must be an operand
  if (!root->left && !root->right)
    return atoi(root->dat);

  // If root only has one child, throw exception
  if (!root->left || !root->right) {
    //  throw exception 
  }

  int left = eval_expr_tree(root->left);
  int right = eval_expr_tree(root->right);
  return eval(left, root->dat, right);
}

/* Do the real calculation based on left operand, operator 
 * and right operand, called by eval_expr_tree(). */
int eval(int left, const string& op, int right)
{
  if (op == "+")
    return left + right;

  if (op == "-")
    return left - right;

  if (op == "*")
    return left * right;

  if (op == "/")
    return left / right;

  // Any other operators are invalid, throw exception
}
