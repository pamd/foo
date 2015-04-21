#include <iostream>
#include <string>

using namespace std;

struct Node {
  Node(char c) { dat = c; left = 0; right = 0; }

  char dat;
  Node* left;
  Node* right;
};

// Do the real calculation based on left operand, operator and right operand
int eval(int left, char op, int right)
{
  if (op == '+')
    return left + right;

  if (op == '-')
    return left - right;

  if (op == '*')
    return left * right;

  if (op == '/')
    return left / right;

  cout << "Invalid operator: " << op << endl;
  return -999;
}

/* Evaluate expression tree recursively. */
int eval_expr_tree(Node* root)
{
  if (!root) {
    cout << "root is 0" << endl;
    return -999;
  }

  // If root does not have any child, it must be an operand
  if (!root->left && !root->right)
    return root->dat - '0';

  // If root only has one child, throw exception
  if (!root->left || !root->right) {
    cout << "Root has only one child" << endl;
    return -999;
  }

  int left = eval_expr_tree(root->left);
  int right = eval_expr_tree(root->right);
  return eval(left, root->dat, right);
}

// Test harness
int main() 
{
  Node* root = new Node('+');

  Node* plus = new Node('+'); 
  Node* minus = new Node('-'); 
  Node* mult = new Node('*'); 

  Node* v1 = new Node('1');
  Node* v2 = new Node('2');
  Node* v3 = new Node('3');
  Node* v4 = new Node('4');
  Node* v5 = new Node('5');

  root->left = plus;
  root->right = minus;

  plus->left = v1;
  plus->right = mult;

  mult->left = v2;
  mult->right = v3;

  minus->left = v4;
  minus->right = v5;

  cout << eval_expr_tree(root) << endl;
}
