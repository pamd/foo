/* Leetcode OJ: Given n, generate all structurally unique BST's 
 * (binary search trees) that store values 1...n.
 */

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 124ms for large dataset
class Solution {
public:
  vector<TreeNode *> generateTrees(int n) {
    return helper(1, n);
  }

  // Recursive helper function
  vector<TreeNode*> helper(int start, int end) {
    vector<TreeNode*> result;
    if (start > end) {
      result.push_back(NULL);
      return result;
    }

    for (int i = start; i <= end; i++) {
      vector<TreeNode*> left_sub = helper(start, i - 1);
      vector<TreeNode*> right_sub = helper(i + 1, end);
      for (size_t j = 0; j < left_sub.size(); j++) {
	for (size_t k = 0; k < right_sub.size(); k++) {
	  TreeNode* root = new TreeNode(i);
	  root->left = left_sub[j];
	  root->right = right_sub[k];
	  result.push_back(root);
	}
      }
    }
    return result;
  }

};

