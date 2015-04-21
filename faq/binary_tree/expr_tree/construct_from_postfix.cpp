/* Construct expression tree based on an input postfix string. */

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
void postorder(Node* root) {
  if (!root)
    return;

  postorder(root->left);
  postorder(root->right);
  cout << root->c << " ";

}

/* Scan input string from left to right, same idea as eval_postfix.cpp. */
Node* construct_from_postfix(const string& postfix) {
  stack<Node*> stk;
  for (size_t i = 0; i < postfix.size(); i++) {
    char c = postfix[i];
    Node* tmp = new Node(c);
    if (c >= '0' && c <= '9') 
      stk.push(tmp);
    else {
      tmp->right = stk.top();
      stk.pop();
      tmp->left = stk.top();
      stk.pop();
      stk.push(tmp);
    }
  }

  return stk.top();
}

/* Alternatively, we can scan the input string from right to left, 
 * then use the idea in construct_from_prefix2() to build the expression tree.
 * Code not provided. */
 
/* Recursive approach, inspired by darksteel and leetcode deserializatrion.
 * http://www.leetcode.com/2010/09/serializationdeserialization-of-binary.html
 */
Node* recurse(const string& postfix, int& idx) {
  if (idx < 0)
    return NULL;

  char c = postfix[idx];
  Node* root = new Node(c);
  if (c >= '0' && c <= '9')
    return root;

  root->right = recurse(postfix, --idx);
  root->left = recurse(postfix, --idx);

  return root;
}
  
// Test harness
int main() {
  //string prefix("+*2/824");
  string postfix("282/*4+");

  //Node* root = construct_from_postfix(postfix);

  int idx = postfix.size() - 1;
  Node* root = recurse(postfix, idx);

  postorder(root);
  cout << endl;
}
