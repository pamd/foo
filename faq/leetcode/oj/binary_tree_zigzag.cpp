/* Leetcode OJ: Given a binary tree, return the zigzag level order 
 * traversal of its node values (i.e., from left to right, then right
 * to left for the next level and alternate between).
 * 32ms for large dataset.
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
  vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
    vector<vector<int> > ret;
    if (!root)
      return ret;

    vector<TreeNode*> curr_level;
    curr_level.push_back(root);
    int count = 0;
    while (curr_level.size()) {
      //ret.push_back(vector<int>());
      vector<TreeNode*> next_level;
      vector<int> v;
      for (size_t i = 0; i < curr_level.size(); i++) {
	v.push_back(curr_level[i]->val);
	if (curr_level[i]->left)
	  next_level.push_back(curr_level[i]->left);
	if (curr_level[i]->right)
	  next_level.push_back(curr_level[i]->right);
      }
      if (count & 1) {
	for (size_t i = 0; i < v.size() / 2; i++) { 
	  int foo = v[i];
	  v[i] = v[v.size() - 1 - i];
	  v[v.size() - 1 - i] = foo;
        }
      }
      ret.push_back(v);

      curr_level = next_level;
      count++;
    }

    return ret;
  }



};
