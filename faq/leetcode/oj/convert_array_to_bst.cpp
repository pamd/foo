/* OJ question: 
 * Given an array where elements are sorted in ascending order, 
 * convert it to a height balanced BST. */

 // Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
 
// 100ms for large dataset
class Solution {
public:
  TreeNode* sortedArrayToBST(vector<int> &num) {
    if (num.size() == 0)
      return NULL;

    size_t m = num.size() / 2;
    TreeNode* root = new TreeNode(num[m]);

    vector<int> vl(num.begin(), num.begin() + m);
    root->left = sortedArrayToBST(vl);

    vector<int> vr(num.begin() + m + 1, num.end());
    root->right = sortedArrayToBST(vr);

    return root;
  }

};
