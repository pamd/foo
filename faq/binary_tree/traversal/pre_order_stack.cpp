/* Binary tree pre-order traversal, with the help of
 * either an explicit stack, or a parent link in each node. */

#include <iostream>
#include <stack>
#include <cstdio>

using namespace std;

struct TreeNode {
  TreeNode(int i) : dat(i), left(NULL), right(NULL), parent(NULL) { }

  int dat;
  TreeNode* left;
  TreeNode* right;
};

/* Pre-order traversal with a stack */
void pre_order_stack(TreeNode* root) {
  if (!root)
    return;

  stack<TreeNode*> stk;
  stk.push(root);
  while (!stk.empty()) {
    TreeNode* curr = stk.top();
    cout << curr->dat << endl;
    stk.pop();

    // IMPORTANT: push right child before left child
    if (curr->right)
      stk.push(curr->right);

    if (curr->left)
      stk.push(curr->left);
  }
}

// Test harness
int main() {
  /*
   *        1
   *       / \
   *      2   3
   *     /   /
   *    4   7
   *   / \
   *  5   6
   *
   */
  TreeNode* p1 = new TreeNode(1);
  TreeNode* p2 = new TreeNode(2);
  TreeNode* p3 = new TreeNode(3);
  TreeNode* p4 = new TreeNode(4);
  TreeNode* p5 = new TreeNode(5);
  TreeNode* p6 = new TreeNode(6);
  TreeNode* p7 = new TreeNode(7);

  p1->left = p2;
  p1->right = p3;

  p2->left = p4;
  p4->left = p5;
  p4->right = p6;

  p3->left = p7;

  //pre_order_stack(p1);

  p2->parent = p1;
  p3->parent = p1;
  p4->parent = p2;
  p5->parent = p4;
  p6->parent = p4;
  p7->parent = p3;

  pre_order_stack(p1);

}
