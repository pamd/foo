/* Leetcode OJ: Two elements of a binary search tree (BST) are swapped by mistake,
 * recover it without changing its structure.
 * Note: A solution using O(n) space is pretty straight forward. 
 * Could you devise a constant space solution?
 */

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

// anson627 solution: 360ms for large dataset
class Solution {
public:
  void recoverTree(TreeNode* root) {
    TreeNode *prev = NULL, *first = NULL, *second = NULL;
    helper(root, prev, first, second);
    swap(first->val, second->val);
  }

  void helper(TreeNode* curNode, TreeNode*& preNode, 
	      TreeNode*& first, TreeNode*& second) {
    if (curNode == NULL) 
      return;

    helper(curNode->left, preNode, first, second);

    if (preNode && preNode->val > curNode->val) {
      if (first == NULL) 
	first = preNode;
      second = curNode;
    }

    preNode = curNode;
    helper(curNode->right, preNode, first, second);
  }
        
};
