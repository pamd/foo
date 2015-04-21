/* Binary tree pre-order traversal, 
 * with the help of a parent link in each node. */

#include <iostream>
#include <stack>
#include <cstdio>

using namespace std;

struct TreeNode {
  TreeNode(int i) : dat(i), left(NULL), right(NULL), parent(NULL) { }

  int dat;
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
};

/* Implementation of pre-order traversal, based on the idea 
 * of curr and prev nodes in EPI book.
 */
void pre_order_parent_epi(TreeNode* root) {
  TreeNode* curr = root;
  TreeNode* prev = 0;
  while (curr) {
    TreeNode* next = 0;
    if (!prev || prev->left == curr || prev->right == curr) {
      cout << curr->dat << endl;
      if (curr->left)
	next = curr->left;
      else if (curr->right)
	next = curr->right;
      else
	next = curr->parent;
    }
    else if (curr->left == prev) {
      if (curr->right)
	next = curr->right;
      else 
	next = curr->parent;
    }
    else
      next = curr->parent;

    prev = curr;
    curr = next;
  }
}

/* Pre-order traversal with a parent link in each node. */
void pre_order_parent1(TreeNode* root) {
  TreeNode* curr = root;
  while (curr) {
    cout << curr->dat << endl;
    if (curr->left)
      curr = curr->left;
    else if (curr->right)
      curr = curr->right;
    else {
      TreeNode* parent = curr->parent;
      while (parent && (!parent->right || parent->right == curr)) {
	curr = parent;
	parent = parent->parent;
      }
      
      if (!parent)
	break;
      
      curr = parent->right;
    }
  }
}

/* Another pre-order traversal, also based on the idea of curr and prev nodes. 
 * This one is commented out because it is harder to understand than the 
 * one based on the code in EPI book. */
/*
void pre_order_parent2(TreeNode* root) {
  TreeNode* curr = root;
  TreeNode* prev = root;
  while (curr) {
    if (curr->left != prev && curr->right != prev) {
      cout << curr->dat << endl;
      prev = curr;
      if (curr->left)
	curr = curr->left;
      else if (curr->right)
	curr = curr->right;
      else
	curr = curr->parent;
    }

    // curr->left == prev || curr->right == prev

    else if (curr->right && curr->right != prev) { // curr->left == prev && curr->right
      prev = curr;
      curr = curr->right;
    }

    else { // curr->right == prev || (curr->left == prev && !curr->right)
      prev = curr;
      curr = curr->parent;
    }
  }

}
*/

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

  p2->parent = p1;
  p3->parent = p1;
  p4->parent = p2;
  p5->parent = p4;
  p6->parent = p4;
  p7->parent = p3;

  pre_order_parent3(p1);

}
