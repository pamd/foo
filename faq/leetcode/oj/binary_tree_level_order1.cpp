/* Leetcode OJ: Binary tree level order traversal #1. 
 * 28 ms for large dataset. 
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
  // Approach #1: 28ms
  vector<vector<int> > levelOrder1(TreeNode *root) {
    vector<vector<int> > ret;
    if (!root)
      return ret;

    vector<TreeNode*> nodes;
    nodes.push_back(root);
    size_t level_end = 0;
    vector<int> one_level_nodes;
    for (size_t i = 0; i < nodes.size(); i++) {
      one_level_nodes.push_back(nodes[i]->val);
      if (nodes[i]->left)
	nodes.push_back(nodes[i]->left);
      if (nodes[i]->right)
	nodes.push_back(nodes[i]->right);
      
      if (i == level_end) {
	ret.push_back(one_level_nodes);
	one_level_nodes.clear();
	level_end = nodes.size() - 1;
      }     
    }

    return ret;
  }

  // Approach #2: 28ms too
  vector<vector<int> > levelOrder(TreeNode *root) {
    vector<vector<int> > ret;
    vector<TreeNode*> curr_level;
    if (root)
      curr_level.push_back(root);

    while (curr_level.size()) {
      ret.push_back(vector<int>());
      vector<TreeNode*> next_level;
      for (size_t i = 0; i < curr_level.size(); i++) {
	ret.back().push_back(curr_level[i]->val);
	if (curr_level[i]->left)
	  next_level.push_back(curr_level[i]->left);
	if (curr_level[i]->right)
	  next_level.push_back(curr_level[i]->right);
      }
      curr_level = next_level;
    }

    return ret;
  }

};
