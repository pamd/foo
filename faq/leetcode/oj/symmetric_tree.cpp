/* Leetcode OJ: Given a binary tree, check whether it is a mirror of itself 
 * (ie, symmetric around its center).
 */


// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
  bool isSymmetric(TreeNode *root) {
    if (!root)
      return true;

    return isMirror(root->left, root->right);          
  }

  // Recursive helper function: 44ms for large dataset
  bool isMirror(TreeNode* left, TreeNode* right) {
    if (!left && !right)
      return true;

    if (!left || !right)
      return false;

    if (left->val != right->val)
      return false;

    return isMirror(left->left, right->right) && isMirror(left->right, right->left);
  }

  // dhu iterative solution: 48ms for large dataset
  bool isMirror_iter(TreeNode* left, TreeNode* right) {
    if (!left && !right)
      return true;

    if (!left || !right)
      return false;

    vector<TreeNode*> left_stk;
    left_stk.push_back(left);
    vector<TreeNode*> right_stk;
    right_stk.push_back(right);
    while (left_stk.size() && right_stk.size()) {
      TreeNode* curr_left = left_stk.back();
      TreeNode* curr_right = right_stk.back(); 
      if (curr_left->val != curr_right->val)
	return false;

      left_stk.pop_back();
      right_stk.pop_back();
      if (curr_left->left) 
	left_stk.push_back(curr_left->left);
      if (curr_right->right)
	right_stk.push_back(curr_right->right);

      if (left_stk.size() != right_stk.size())
	return false;

      if (curr_left->right) 
	left_stk.push_back(curr_left->right);
      if (curr_right->left)
	right_stk.push_back(curr_right->left);

      if (left_stk.size() != right_stk.size())
	return false;
    }

    return true;
  }

};
