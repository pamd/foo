/* Leetcode OJ: Given a binary tree and a sum, determine if the tree 
 * has a root-to-leaf path such that adding up all the values along 
 * the path equals the given sum. For example:
 * Given the below binary tree and sum = 22,
 *
 *             5
 *            /	\
 *           4   8
 *          /   / \
 *         11  13  4
 *        /  \	    \
 *       7    2      1
 *
 * return true, as there exists a root-to-leaf path 5->4->11->2 whose sum is 22.
 */

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) { }
};

// 92ms for large dataset
class Solution {
public:
  bool hasPathSum(TreeNode *root, int sum) {
    if (!root)
      return false;

    if (!root->left && !root->right && root->val == sum)
      return true;

    sum -= root->val;
    return hasPathSum(root->left, sum) || hasPathSum(root->right, sum);
  }

};
