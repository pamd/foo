/* Leetcode OJ: Binary tree level order traversal #2. 
 * Return the nodes by level, from bottom to top.
 */

#include <vector>

using namespace std;

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
  // 48ms for large dataset 
  vector<vector<int> > levelOrderBottom(TreeNode *root) {
    vector<vector<int> > ret;
    if (!root)
      return ret;
    
    vector<TreeNode*> curr_level;
    curr_level.push_back(root);
    helper(curr_level, ret);
    return ret;
  }

  // Recursive helper function
  void helper(vector<TreeNode*> curr_level, vector<vector<int> >& ret) {
    if (curr_level.size() == 0)
      return;

    vector<TreeNode*> next_level;
    vector<int> curr_vec;
    for (size_t i = 0; i < curr_level.size(); i++) {
      curr_vec.push_back(curr_level[i]->val);
      if (curr_level[i]->left)
	next_level.push_back(curr_level[i]->left);
      if (curr_level[i]->right)
	next_level.push_back(curr_level[i]->right);
    }
    
    helper(next_level, ret);
    ret.push_back(curr_vec);
  }

};
