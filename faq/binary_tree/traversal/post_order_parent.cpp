/* Various implementations of post-order traversal. */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>

using namespace std;

// Binary tree node 
struct TreeNode {
  TreeNode(int d = 0) : dat(d), left(0), right(0), parent(0) { }

  int dat;
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
};

/* Post-order traversal based on in-order traversal on EPI book. 
 * It uses the idea of prev and curr nodes. */
void post_order_epi(TreeNode* root) {
  TreeNode* curr = root;
  TreeNode* prev = 0;
  while (curr) {
    TreeNode* next = 0;
    if (!prev || prev->left == curr || prev->right == curr) {
      if (curr->left)
	next = curr->left;
      else if (curr->right)
	next = curr->right;
      else {
	cout << curr->dat << endl;
	next = curr->parent;
      }
    }
    else if (curr->left == prev && curr->right) {
      next = curr->right;
    }
    else {
      cout << curr->dat << endl;
      next = curr->parent;
    }

    prev = curr;
    curr = next;
  } // end of "while" loop

}

/* Post-order traversal with parent link, by longway2008, refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32123359.html
 * This approach also uses prev and curr nodes, but is less readable.
 */
void post_order_longway2008(TreeNode* root) {
  // dhu: Change the following one-line for loop into a 3-line while loop
  //for (Node* p = root, prev = root; p; } {

  TreeNode* curr = root;
  TreeNode* prev = root;
  while (curr) {
    // If left subtree exists but has not been visited, go to left side.
    if (prev != curr->left && prev != curr->right && curr->left) {
      prev = curr; 
      curr = curr->left;
    }

    /* If left subtree does not exist or has been visited, while right subtree 
     * exists but has not been visited, go to right side. */
    else if (prev != curr->right && curr->right) { 
      prev = curr; 
      curr = curr->right;
    }

    /* If neither left nor right subtree exists, or both sides have been visited, 
     * then visit the current node and move up to its parent. */ 
    else {
      cout << curr->dat << endl;
      prev = curr; 
      curr = curr->parent;
    }
  }

}

/*******************************************************************************
 * Another implementation (with dhu improvement)
 *******************************************************************************/

// This function does not change input root value
TreeNode* get_next_dhu(TreeNode* curr) { 
  TreeNode* next = curr;
  while (next->left || next->right) {
    if (next->left) 
      next = next->left;
    else 
      next = next->right;
  }

  return next;
}

// Post-order traversal function that calls get_next_dhu()
void post_order3_dhu(TreeNode* root) {
  if (!root)
    return;

  TreeNode* curr = get_next_dhu(root); 
  while (curr->parent) { 
    cout << curr->dat << endl; // Visit current node

    // If current node is a left child, and its right sibling node also exists, 
    // set current node to the lowest child on right side. 
    if (curr == curr->parent->left && curr->parent->right)  
      curr = get_next_dhu(curr->parent->right);

    // If current node is a left child, and its right sibling node doesn't exist, 
    // or current node is a right child, simply move up to the parent node. 
    else 
      curr = curr->parent;
  }  // end while

  // Visit current node (which becomes root now) at the very end
  cout << curr->dat << endl; 
}

/* Original post_order3(), commented out because it is 
 * less readable than dhu revised version. */
/*
// Helper function for post-order traversal with parent link.
// Note that input node is modified in this function. 
void get_next(TreeNode*& curr) {  
  while (curr->left || curr->right) {
    if (curr->left) 
      curr = curr->left;
    else 
      curr = curr->right;
  }
}

// Driver function that calls nextPost()
void post_order3(TreeNode* root) {
  if (!root)
    return;

  TreeNode* curr = root;
  get_next(curr); 
  while (curr->parent) { 
    cout << curr->dat << endl; // visit current node

    // If current node is a left child, and its right sibling exists, 
    // set current node to the lowest descendant on right subtree. 
    if (curr == curr->parent->left && curr->parent->right) { 
      curr = curr->parent->right;
      get_next(curr);
    }

    // If current node is a left child and its right sibling does 
    // not exist, or it is a right child, move up to the parent node.
    else 
      curr = curr->parent;
  }

  // Visit root node at the end 
  cout << curr->dat << endl; 
}
*/

/******************************************************************
 * Post-order traversal in Java that uses a visited flag in node.
 ******************************************************************/
/*
public void postOrderTraversal(TreeNode root) {
  Stack s = new Stack();
  s.push(root);

  while(!s.isEmpty()) {
    TreeNode node = (TreeNode) s.peek();
    if(node.left != null && !node.left.visited)
      s.push(node.left);
    else if(node.right != null && !node.right.visited)
      s.push(node.right);
    else {
      System.out.print(node.value+" ");
      node.visited = true;
      s.pop();
    }
  }
}
*/

// Test harness
int main() { 
  /* Constructed binary tree is
   *  
   *          1
   *         / \
   *        2   3
   *       / \
   *      4   5
   */

  TreeNode* p1 = new TreeNode(1);
  TreeNode* p2 = new TreeNode(2);
  TreeNode* p3 = new TreeNode(3);
  TreeNode* p4 = new TreeNode(4);
  TreeNode* p5 = new TreeNode(5);

  p1->left = p2;
  p1->right = p3;

  p2->parent = p1;
  p3->parent = p1;

  p2->left = p4;
  p2->right = p5;

  p4->parent = p2;
  p5->parent = p2;
 
  post_order3_dhu(p1);

  return 0;
}
