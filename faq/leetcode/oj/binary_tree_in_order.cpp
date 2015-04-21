/* Leetcode OJ: in-order traversal of binary tree.
 * 16 ms for large dataset. 
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
  vector<int> inorderTraversal(TreeNode *root) {
    vector<int> ret;
    if (!root)
      return ret;

    traverse(root, ret);
    return ret;
  }

  // Helper function
  void traverse(TreeNode* root, vector<int>& v) {
    if (!root)
      return;
    traverse(root->left, v);
    v.push_back(root->val);
    traverse(root->right, v);
  }

};

int main() {
  Solution foo;
  
}
