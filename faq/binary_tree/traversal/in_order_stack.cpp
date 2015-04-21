/* Binary tree in-order traversal using a stack. */

#include <stack>
#include <iostream>

using namespace std;

// TreeNode def
struct TreeNode {
  TreeNode(int i) : dat(i), left(0), right(0) { }

  int dat;
  TreeNode* left;
  TreeNode* right;
}

/* Leetcode and EPI book implementation, copied from:
 * http://www.mitbbs.com/article_t1/JobHunting/32097715_0_2.html
 */
void leetcode_stack(BinaryTree *root) {
  stack<TreeNode*> s;
  TreeNode* current = root;
  while (!s.empty() || current) {
    if (current) {
      s.push(current);
      current = current->left;
    } 
    else {
      current = s.top();
      s.pop();
      cout << current->data << " ";
      current = current->right;
    }
  }
}

/* Another approach copied from:
 * http://forums.devarticles.com/c-c-help-52/non-recursive-tree-traversal-74033.html
 * Less readable than the one by leetcode and EPI book.
 */
void Tree::in_order() {
  stack<TreeNode*> s;
  TreeNode* curr = root;

  while (true) {
    while (current) {
      s.push(current);
      current = current->left;
    }

    if (s.isEmpty()) 
      break;

    current = s.pop();
    cout << current->data;  // Visit the node here
    current = current->right;
  }
}

/* Binary tree iterator of in-order traversal using an explicit stack, 
 * also from:
 * http://www.mitbbs.com/article_t1/JobHunting/32097715_0_2.html
 * Modified from Java code written by hackie. */
struct BinaryTreeIterator {
  stack<TreeNode*> stk;

  // Ctor: populate stack by traversing the left subtree
  BinaryTreeIterator(TreeNode* root) {
    while (root) {
      stk.push(root);
      root = root->left;
    }
  }

  // Does the next node exist?
  boolean hasNext() {
    return !stk.empty();
  }

  // Return the next node or 0 (if the next node does not exist).
  TreeNode* next() {
    if (!hasNext())
      return 0;

    TreeNode* curr = stk.top();
    stk.pop();
    // Push nodes on right subtree into stack
    TreeNode* next = curr->right;
    while (next) {
      stk.push(next);
      next = next->left;
    }

    return curr;
  }

};

/* Use an explicit stack to find next node in in-order traversal. 
 * Written by Speedlite, refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32160107.html
 */
Node* findInOrderSuccessor(Node *root, Node *target){
  stack<Node *> s;
  Node* curr = root;
  Node* prev = 0; 
  while (true) { 
    while (curr) {
      s.push(curr);
      curr = curr->left;
    }
    
    if (s.empty())
      break;
    
    curr = s.pop();
    if (prev == target) 
      return curr; 
    
    prev = curr; 
    curr = curr->right;
  }

  return 0; 
}

// Another approach copied from:
// http://web.cs.wpi.edu/~cs2005/common/iterative.inorder
//---------------------------------------------------------
// Algorithm for an iterative inorder traversal of a
// binary tree.  Compare this to the simplicity of
// a recursive inorder traversal (page 483)
//
// Assume that the binary tree is pointed to by root_ptr
//
// dhu: Terrible code, do not even want to compile and test.

/*
void in_order_wpi(binary_tree_node<Item> *root_ptr) {
  bool done;
  binary_tree_node<Item> *root_ptr, *cursor;
  stack<binary_tree_node<Item> *> s;

  cursor = root_ptr;  // Set cursor to root of binary tree
  done = false;

  while (!done) {
    if (cursor != NULL) {
      // Place pointer to node on the stack before traversing 
      // the node's left subtree. 
      s.push(cursor);          
      cursor = cursor->left; // traverse the left subtree
    }
    // Backtrack from the empty subtree and visit the node at the top 
    // of the stack. If the stack is empty, we are done. 
    else {
      if (!s.empty()) {
	cursor = s.top();
	s.pop();
	cout << cursor->data;
	cursor = cursor->right;
      }
      else
	done = true;
    }
  }
}
*/
