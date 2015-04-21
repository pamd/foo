/* OJ question: 
 * Given inorder and postorder traversal of a tree, construct the binary tree.
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

// 224ms for large dataset
class Solution {
public:
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    if (inorder.size() == 0)
      return NULL;

    int root_val = postorder.back();
    postorder.pop_back();
    size_t root_idx = 0;
    for (;  root_idx < inorder.size(); root_idx++) {
      if (inorder[root_idx] == root_val)
	break;
    }

    TreeNode* root = new TreeNode(root_val);

    vector<int> lv(inorder.begin(), inorder.begin() + root_idx);
    vector<int> rv(inorder.begin() + root_idx + 1, inorder.end());
    root->right = buildTree(rv, postorder);
    root->left = buildTree(lv, postorder);

    return root;
  }
};

/*
int main() {
  int in[] = { 4, 2, 1, 5, 3, 6 };
  int po[] = { 4, 2, 5, 6, 3, 1 };

  vector<int> inorder(in, in + 6);
  vector<int> postorder(po, po + 6);
  Solution foo;
  TreeNode* root = foo.buildTree(inorder, postorder);
  
  cout << "In order:"; 
  in_order(root);
  cout << endl;

  cout << "Post order: ";
  post_order(root);
  cout << endl;
  
}
*/

// Another solution that is more compact and does not need intermediate vector
class Solution2 {
public:
  TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
    if (inorder.size() == 0)
      return 0;
    
    int p_idx = postorder.size() - 1;
    return helper(inorder, 0, inorder.size() - 1, postorder, p_idx);
  }

  TreeNode* helper(const vector<int> &inorder, int left, int right, 
		   const vector<int> &postorder, int& p_idx) {
    if (left > right || right < 0 || p_idx < 0)
      return 0;

    int tmp = postorder[p_idx];
    TreeNode* root = new TreeNode(tmp);
    p_idx--;

    int root_idx;
    for (root_idx = left; root_idx <= right; root_idx++) {
      if (inorder[root_idx] == tmp)
	break;
    }

    root->right = helper(inorder, root_idx + 1, right, postorder, p_idx);
    root->left = helper(inorder, left, root_idx - 1, postorder, p_idx);

    return root;
  }
};

int main() {
  vector<int> inorder;
  inorder.push_back(2);
  inorder.push_back(1);

  vector<int> postorder = inorder;

  Solution2 foo;
  TreeNode* root = foo.buildTree(inorder, postorder);
  in_order(root);
  cout << endl;
  post_order(root);  
  cout << endl;
}
