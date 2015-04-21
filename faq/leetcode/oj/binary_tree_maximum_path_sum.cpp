/* Given a binary tree, find the maximum path sum.
 * The path may start and end at any node in the tree.
 * For example, given the below binary tree,
 *
 *       1
 *      / \
 *     2   3
 *
 *    Return 6.
 */

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// anson627: 244ms for large dataset
class Solution_anson {
public:
  int maxPathSum(TreeNode *root) {
    if (!root) 
      return 0;

    int maxSoFar = root->val;
    maxPathSumHelper(root, maxSoFar);
    return maxSoFar;
  }

  /* Returns the largest sum starting from the input node,
   * also update maxSoFar when traversing the subtrees. */ 
  int maxPathSumHelper(TreeNode *node, int &maxSoFar) {
    if (!node) 
      return 0;

    int leftMax = maxPathSumHelper(node->left, maxSoFar);
    int rightMax = maxPathSumHelper(node->right, maxSoFar);

    // maxPath is the maximum sum of the path that includes current node
    int maxPath = node->val;
    if (leftMax > 0)  
      maxPath += leftMax;
    if (rightMax > 0) 
      maxPath += rightMax;

    if (maxPath > maxSoFar) 
      maxSoFar = maxPath; 

    int res = node->val;
    return max(res, res + max(leftMax, rightMax));
  }
};

