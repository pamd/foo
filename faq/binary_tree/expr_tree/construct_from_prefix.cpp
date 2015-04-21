/* Construct expression tree based on prefix string. 
 * This is similar to evaluation of prefix string. 
 * There are two methods: either scan from left to right, 
 * or from right to left.
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
void preorder(Node* root) {
  if (!root)
    return;

  cout << root->c << " ";
  preorder(root->left);
  preorder(root->right);
}

// Scan input string from right to left, same idea as eval_prefix1()
Node* construct_from_prefix1(const string& prefix) {
  stack<Node*> stk;
  for (int i = prefix.size() - 1; i >= 0; i--) {
    char c = prefix[i];
    Node* tmp = new Node(c);      
    if (c >= '0' && c <= '9') 
      stk.push(tmp);
    else {
      tmp->left = stk.top();
      stk.pop();
      tmp->right = stk.top();
      stk.pop();
      stk.push(tmp);
    }
  }

  return stk.top();
}

// Scan input string from left to right, same idea as eval_prefix2()
Node* construct_from_prefix2(const string& prefix) {
  stack<Node*> stk;
  for (size_t i = 0; i < prefix.size(); i++) {
    char c = prefix[i];
    Node* tmp = new Node(c);
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      stk.push(tmp);
    }
    else {
      while (!stk.empty() && stk.top()->left) {
	stk.top()->right = tmp;
	tmp = stk.top();
	stk.pop();
      }
      if (stk.empty())
	return tmp;

      stk.top()->left = tmp;
    }
  }

  // For a valid prefix string, the program should never reach here.
  return NULL;
}

/* Recursive approach, inspired by darksteel and leetcode deserializatrion.
 * http://www.leetcode.com/2010/09/serializationdeserialization-of-binary.html
 */
Node* recurse(const string& prefix, size_t& idx) {
  if (idx == prefix.size())
    return NULL;

  char c = prefix[idx];
  Node* root = new Node(c);
  if (c >= '0' && c <= '9')
    return root;

  root->left = recurse(prefix, ++idx);
  root->right = recurse(prefix, ++idx);

  return root;
}
  
// Test harness
int main() {
  //string prefix("+*2/824");
  string prefix("*1+23");

  //Node* root = construct_from_prefix2(prefix);

  size_t idx = 0;
  Node* root = recurse(prefix, idx);

  preorder(root);
  cout << endl;
}
