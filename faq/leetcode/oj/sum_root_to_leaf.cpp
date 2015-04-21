/* Given a binary tree containing digits from 0-9 only, each root-to-leaf 
 * path could represent a number.
 * An example is the root-to-leaf path 1->2->3 which represents the number 123.
 * Find the total sum of all root-to-leaf numbers.
 *
 * For example,
 *
 *    1
 *   / \
 *  2   3
 *
 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.
 * Return the sum = 12 + 13 = 25.
 */


// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 20ms for large dataset
class Solution {
public:
  int sumNumbers(TreeNode *root) {
    if (!root)
      return 0;

    return rec_helper(0, root);
  }

  int rec_helper(int parent_val, TreeNode* root) {
    int curr = parent_val * 10 + root->val;
    int left = -1;
    int right = -1;
    if (root->left) 
      left = rec_helper(curr, root->left);
    if (root->right) 
      right = rec_helper(curr, root->right);

    if (left == -1 && right == -1)
      return curr;

    if (left == -1)
      return right;

    if (right == -1)
      return left;

    return left + right;
  }

};

// anson627
class Solution_anson {
public:
  int sumNumbers(TreeNode *root) {
    if (root == NULL) 
      return 0;

    int sum = 0, res = 0;
    sumNumbersHelper(root, sum, res);
    return res;
  }

  void sumNumbersHelper(TreeNode *node, int sum, int & res) {
    sum += node->val;
    if (node->left == NULL && node->right == NULL) {
      res += sum;
      return;
    }

    sum *= 10;
    if (node->left) 
      sumNumbersHelper(node->left, sum, res);
    
    if (node->right) 
      sumNumbersHelper(node->right, sum, res);
  }

};
