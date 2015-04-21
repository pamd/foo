/* Leetcode OJ: Given a binary tree, find its minimum depth.
 * The minimum depth is the number of nodes along the shortest path 
 * from the root node down to the nearest leaf node.
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
  /* Incorrect approach! Because min depth is defined as the distance from
   * root node to a leaf node. */
  int minDepth_bad(TreeNode *root) {
    if (!root)
      return 0;
    int left = minDepth_bad(root->left);
    int right = minDepth_bad(root->right);
    if (left < right)
      return left + 1;
    return right + 1;
  }

  // 84ms for large dataset (BFS approach)
  int minDepth(TreeNode *root) {
    if (!root)
      return 0;

    vector<TreeNode*> q;
    int ret = 1;
    q.push_back(root);
    size_t start = 0;
    size_t end = 0;
    while (start <= end) {
      TreeNode* current = q[start];
      if (!current->left && !current->right)
	break;
      if (current->left)
	q.push_back(current->left);
      if (current->right)
	q.push_back(current->right);

      if (start == end) {
	ret++;
	end = q.size() - 1;
      }
      start++;
    }

    return ret;
  }

  // Recursive approach based on anson627
  int minDepth_anson627(TreeNode *root) {
    if (!root)
      return 0;

    int minDepth = INT_MAX;
    minDepthHelper(root, 0, minDepth);
    return minDepth;
  }

  // DFS 
  void minDepthHelper(TreeNode *node, int curDepth, int &minDepth) {
    if (node == NULL) 
      return;

    curDepth++;
    if (node->left == NULL && node->right == NULL) {
      // dhu: original code was: "if (curDepth > minDepth);", which is wrong  
      if (curDepth < minDepth) 
	minDepth = curDepth;
    }

    minDepthHelper(node->left, curDepth, minDepth);
    minDepthHelper(node->right, curDepth, minDepth);
  }
};
