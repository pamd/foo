/* OJ question: 
 * Given preorder and inorder traversal of a tree, construct the binary tree.
 * (Assume that duplicates do not exist in the tree).
 */

#include <vector>
#include <iostream>

using namespace std;

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void pre_order(TreeNode* root) {
  if (!root)
    return;
  cout << root->val << " ";
  pre_order(root->left);
  pre_order(root->right);
}

void in_order(TreeNode* root) {
  if (!root)
    return;
  in_order(root->left);
  cout << root->val << " ";
  in_order(root->right);
}

void post_order(TreeNode* root) {
  if (!root)
    return;
  post_order(root->left);
  post_order(root->right);
  cout << root->val << " ";
}

// 224ms for large dataset (exactly same as construct_inorder_postorder.cpp,
// is it simply a coincidence?
class Solution {
public:
  TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
    if (inorder.size() == 0)
      return NULL;

    int root_val = preorder[0];
    preorder.erase(preorder.begin());
    size_t root_idx = 0;
    for (;  root_idx < inorder.size(); root_idx++) {
      if (inorder[root_idx] == root_val)
	break;
    }
    
    TreeNode* root = new TreeNode(root_val);

    vector<int> lv(inorder.begin(), inorder.begin() + root_idx);
    vector<int> rv(inorder.begin() + root_idx + 1, inorder.end());
    root->left = buildTree(preorder, lv);
    root->right = buildTree(preorder, rv);

    return root;
  }

};

int main() {
  int pre[] = { 1, 2, 4, 3, 5, 6 };
  int in[] = { 4, 2, 1, 5, 3, 6 };
  int po[] = { 4, 2, 5, 6, 3, 1 };

  vector<int> preorder(pre, pre + 6);
  vector<int> inorder(in, in + 6);
  vector<int> postorder(po, po + 6);
  Solution foo;
  TreeNode* root = foo.buildTree(preorder, inorder);
  
  cout << "Pre order: ";
  pre_order(root);
  cout << endl;

  cout << "In order:"; 
  in_order(root);
  cout << endl;


  
}
