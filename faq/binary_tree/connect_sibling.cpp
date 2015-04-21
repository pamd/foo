/* Suupose each node in binary tree has an extra pointer that points to
 * the sibling node. Set this sibling pointer with constant space.
 */

#include <iostream>

struct Node {
  int value;
  Node *left;
  Node *right;
  Node *sibling;
};

void connect_sibling (Node* root) {
  root->sibling = 0;
  Node *cur, *dummy;
  dummy = new Node;
  while (root) {
    cur = dummy;
    // Inner loop takes care of one level of the binary tree
    while (root) {
      if (root->left) {
	cur->sibling = root->left;
	cur = root->left;
      }
      
      if (root->right) {
	cur->sibling = root->right;
	cur = root->right;
      }
      root = root->sibling;
    } // end of inner while 

    cur->sibling = 0;
    root = dummy->sibling;
  } // end if outer while
  delete dummy;
}

