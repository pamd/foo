/* Leetcode OJ: Given a binary tree and a sum, find all root-to-leaf paths 
 * where each path's sum equals the given sum. For example:
 * Given the below binary tree and sum = 22,
 *
 *              5
 *             / \
 *            4   8
 *           /   / \
 *          11  13  4
 *         /  \    / \
 *        7    2  5   1
 *
 * return [5,4,11,2] and [5,8,4,5]
 */

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 88ms for large dataset
class Solution {
public:
  vector<vector<int> > pathSum(TreeNode *root, int sum) {
    vector<vector<int> > result;
    vector<int> tmp;
    helper(root, sum, tmp, result);
    return result;
  }

  void helper(TreeNode *root, int sum, vector<int>& tmp, 
	      vector<vector<int> >& result) {
    if (!root)
      return;

    tmp.push_back(root->val);
    if (!root->left && !root->right && root->val == sum) {
      result.push_back(tmp);
      tmp.pop_back();
      return;
    }
    
    sum -= root->val;
    helper(root->left, sum, tmp, result);
    helper(root->right, sum, tmp, result);
    tmp.pop_back();        
  }
};
