// OJ problem: Find the maximum depth of an input binary tree.
// The maximum depth is the number of nodes along the longest 
// path from the root node down to the farthest leaf node.
class Solution {
public:
  // 72ms for large dataset.
  int maxDepth(TreeNode *root) {
    if (!root)
      return 0;
    
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    if (left > right)
      return left + 1;
    return right + 1;
  }
        
};
