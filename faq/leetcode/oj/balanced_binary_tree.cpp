/* Leetcode OJ: Given a binary tree, determine if it is height-balanced.
 * For this problem, a height-balanced binary tree is defined as a binary tree 
 * in which the depth of the two subtrees of every node never differ by more than 1.
 */

#include <iostream>

using namespace std;


// Definition for binary tree
struct TreeNode {
   int val;
   TreeNode *left;
   TreeNode *right;
   TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

class Solution {
public:
  // dhu solution
  bool isBalanced_dhu(TreeNode *root) {
    int maxDepth = getMaxDepth(root);
    int minDepth = getMinDepth(root);
    return maxDepth - minDepth <= 1;
  }

  // dhu helper function
  int getMaxDepth(TreeNode* root) {
    if (!root)
      return 0;

    int left = getMaxDepth(root->left);
    int right = getMaxDepth(root->right);
    if (left > right)
      return left + 1;

    return right + 1;
  }

  // dhu helper function
  int getMinDepth(TreeNode* root) {
    if (!root)
      return 0;

    int left = getMinDepth(root->left);
    int right = getMinDepth(root->right);
    if (left < right)
      return left + 1;

    return right + 1;
  }
  
  // OJ helper function: return the depth of a tree rooted at input node
  int oj_helper(TreeNode* root) {
    if (!root)
      return 0;

    int left = oj_helper(root->left);
    int right = oj_helper(root->right);
    if (left == -1 || right == -1 || left - right > 1 || right - left > 1)
      return -1;
    
    if (left > right)
      return left + 1;
    return right + 1;
  }

  // Written to pass OJ: 108 ms for large dataset
  bool isBalanced(TreeNode* root) {
    if (!root)
      return true;

    int left = oj_helper(root->left);
    int right = oj_helper(root->right);
    if (left == -1 || right == -1)
      return false;

    if (left - right > 1 || right - left > 1)
      return false;

    return true;
  }

};

int main() {
  TreeNode* n1 = new TreeNode(1);
  TreeNode* n2 = new TreeNode(2);
  TreeNode* n3 = new TreeNode(3);
  TreeNode* n4 = new TreeNode(4);
  TreeNode* n5 = new TreeNode(5);
  //TreeNode* n6 = new TreeNode(6);
  //TreeNode* n7 = new TreeNode(7);  

  /*
  n1->left = n2;
  n1->right = n3;

  n2->left = n4;
  n2->right = n5;

  n3->right = n6;

  n4->left = n7;
  */

  n1->left = n2;
  n2->left = n3;
  n3->left = n4;
  n4->left = n5;
  Solution foo;
  //cout << "max: " << foo.getMaxDepth(n1) << endl;
  //cout << "min: " << foo.getMinDepth(n1) << endl;
  cout << foo.oj_helper(n1->left) << endl;
  cout << foo.oj_helper(n1->right) << endl;

  
  if (foo.isBalanced(n1))
    cout << "yes" << endl;
  else
    cout << "no" << endl;
  
}
