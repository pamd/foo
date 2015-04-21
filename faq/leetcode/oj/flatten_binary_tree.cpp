/* Leetcode OJ: Given a binary tree, flatten it to a linked list in-place. */

#include <iostream>

using namespace std;

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};
 
// 48ms for large dataset
class Solution {
public:
  void flatten(TreeNode *root) {
    if (!root)
      return;

    TreeNode* left = root->left;
    root->left = 0;
    flatten(left);
    TreeNode* right = root->right;
    flatten(right);
    // If left substree does not exist, we are done!
    if (!left)
      return;

    // If left subtree exists, first link left subtree to 
    // right side, then link flattened right side.
    root->right = left;
    while (root->right)
      root = root->right;
    root->right = right;
  }
};

// Another interesting solution copied from mitbbs
class Solution2 {
public:
  void flatten(TreeNode *root) {
    TreeNode* temp = 0;
    postorder(root, temp);
  }

private:
  void postorder(TreeNode* node , TreeNode*& temp) {
    if (node) {
      postorder(node->right, temp);
      postorder(node->left, temp);
      node->right = temp;
      temp = node;
      node->left = 0;
    }
  }

}; 

// Test harness
int main() {
  TreeNode* n1 = new TreeNode(1);
  TreeNode* n2 = new TreeNode(2);
  TreeNode* n3 = new TreeNode(3);
  TreeNode* n4 = new TreeNode(4);
  TreeNode* n5 = new TreeNode(5);
  TreeNode* n6 = new TreeNode(6);

  n1->left = n2;
  n1->right = n5;
  n2->left = n3;
  n2->right = n4;
  n5->right = n6;

  Solution2 foo;
  foo.flatten(n1);
  while (n1) {
    cout << n1->val << endl;
    n1 = n1->right;
  }
}
