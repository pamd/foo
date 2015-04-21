/* Count the number of nodes in a complete binary tree. Refer to:
 *
 * http://www.mitbbs.com/article_t1/JobHunting/32250857_0_1.html
 *
 * According to Wikipedia:
 *
 * http://en.wikipedia.org/wiki/Full_binary_tree#Types_of_binary_trees
 *
 * "A complete binary tree is a binary tree in which every level, 
 * except possibly the last, is completely filled, and all nodes are as far 
 * left as possible. A tree is called an almost complete binary tree or 
 * nearly complete binary tree if the exception holds, i.e. the last level 
 * is not completely filled. This type of tree is used as a specialized data 
 * structure called a heap."
 *
 * The basic idea is to find the leaf node that do not have sibling on its right.
 * In another word, we try to find the "gap" on the last level.
 * We can use a variant of binary search: first compare the depth of rightmost 
 * node on left subtree and the depth of leftmost node on right subtree. If they 
 * are equal, then the leaf node. 
 *
 * Time complexity: O(h^2), in which h is the depth of input binary tree.
 */

#include <iostream>
#include <cassert>

using namespace std;

struct TreeNode {
  TreeNode(int i) : dat(i), left(0), right(0) { }

  int dat;
  TreeNode* left;
  TreeNode* right;
};

// Return the depth of the leftmost node
int getLeftDepth(TreeNode* root) {
  int d = 0;
  while (root) {
    root = root->left;
    d++;
  }

  return d - 1;
}

// Return the depth of the rightmost node    
int getRightDepth(TreeNode* root) {
  int d = 0;
  while (root) {
    d++;
    root = root->right;
  }

  return d - 1;
}

// Recursive solution;
// depth is the depth of the subtree that is rooted at root.
int rec_count(TreeNode* root, int depth) {
  if (!root) 
    return 0;

  int rd = getRightDepth(root->left);
  if (rd == depth - 1) // left side is full 
    return  (1 << depth) + rec_count(root->right, depth - 1);
  else // right side is full
    return (1 << (depth - 1)) + rec_count(root->left, depth - 1);
}

// Wrapper that calls recursive solution
int rec_wrapper(TreeNode* root) {
  int depth = getLeftDepth(root);
  return rec_count(root, depth);
}

// Brute force method to confirm the answer (preorder traversal)
int brute_count(TreeNode* root) {
  if (!root)
    return 0;

  return 1 + brute_count(root->left) + brute_count(root->right);
}

// Iterative solution
int iter_count(TreeNode* root) {
  if (!root)
    return 0;

  int depth = getLeftDepth(root);
  int counter = 0;
  while (root) {
    int d2 = getRightDepth(root->left);
    if (d2 == depth - 1) { // left side is full
      counter += (1 << depth);
      root = root->right;
    }
    else { // right side is full
      counter += (1 << (depth - 1));
      root = root->left;
    }
    depth--;
  }

  return counter;
}

// Test harness
int main() {
  for (int n = 1; n <= 100; n++) {
    TreeNode* a[n + 1];
    for (int i = 1; i <= n; i++) 
      a[i] = new TreeNode(i);
    
    for (int i = 1; i <= n / 2; i++) {
      a[i]->left = a[i * 2];
      if (i * 2 + 1 <= n)
	a[i]->right = a[i * 2 + 1];
    }

    int ret1 = rec_wrapper(a[1]);
    //int ret2 = iter_count(a[1]);
    //cout << n << ": " << ret1 << endl;
    assert(ret1 == n);
  }


  return 0;
}
