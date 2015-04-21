/* Morris Traversal: traverse the tree without using stack and recursion.
 * Code is based on:
 * http://www.geeksforgeeks.org/archives/6358
 *
 * Quote from above URL: 
 * In this traversal, we first create links to inorder successor and print 
 * the data using these links, and finally revert the changes to restore original tree.
 *
 * 1. Initialize current as root 
 * 2. While current is not NULL
 *      If current does not have left child
 *         a) Print current data
 *         b) Go to the right, i.e., current = current->right
 *      Else
 *         a) Make current as right child of the right-most node in current's left subtree
 *         b) Go to this left child, i.e., current = current->left;
 *
 * The runtime complexity of this algorithm is still O(n), because each edge 
 * will be traversed three times (except the edges on right most boundary): 
 *
 * (1) Build the extra right thread; 
 * (2) Visit each node along the edge; 
 * (3) Remove the extra thread.
 *
 * Visiting nodes on right most boundary do not need (1) and (3).
 * 
 * Also see:
 * http://stackoverflow.com/questions/6478063/how-is-the-complexity-of-morris-traversal-on
 * and "DSinCPP" book by Adam Drozdek.
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;
 
/* Threaded node in binary tree. 
 * It has data, and pointers to left and right children. */
struct TreeNode {
  TreeNode(int d = 0) : data(d), left(0), right(0) { }

  int data;
  TreeNode* left;
  TreeNode* right;
};
 
/* In-order traversal of binary tree without recursion or stack
 * Code is based on:
 * http://www.geeksforgeeks.org/archives/6358
 */
void MorrisInorder1(TreeNode *root) {
  TreeNode* curr; // current node
  TreeNode* prev; // previous node
 
  if (!root)
    return; 
 
  curr = root;
  while (curr) {                 
    /* If current node does not have left child, print out current node,
     * then set current node's right child as current node. Note that here 
     * the link between curr and curr->right may be the thread, but we don't care. */
    if (!curr->left) {
      cout << curr->data << " ";
      curr = curr->right;      
      continue;
    }    

    // If current node has left child, process the left subtree.

    // Find the inorder predecessor of current node.
    prev = curr->left; // prev will be always a (grand)child of curr node.
    while (prev->right && prev->right != curr)
      prev = prev->right;
    /* The above while loop terminates in two scenarios: 
     * (1) prev->right == 0: this means the extra thread has not been built yet;
     * or:
     * (2) prev->right == curr: since prev is always a (grand)child of curr,
     * this condition means that the thread must have been built.
     */
    
    /* In threaded binary tree, any node will have a valid right child. 
     * so if prev->right is NULL, then the thread on prev must have not been built 
     * yet. We build the thread by setting prev->right = curr, then start working on
     * the left subtree. */
    if (!prev->right) {
      prev->right = curr;
      curr = curr->left;
    }
    /* If the thread has been built between prev and curr, remove the thread 
     * link to restore original tree. Then print out current node data. 
     * Since the left subtree of current node and current node itself have 
     * been processed, start working on the right subtree of current node. */   
    else {
      prev->right = 0;
      cout << curr->data << " ";
      curr = curr->right;      
    } 
  } // End of while loop 
  
  cout << endl;
}
 
/*********************************************************************
 * The following three functions are based on genBST.h in 
 * "Data Structures and Algorithms in C++",
 * written by Adam Drozdek, 4th edition, 2012. 
 *********************************************************************/
// In-order traqversal, commented out because it uses same idea 
// as the one from geeksforgeeks.
/*
void MorrisInorder2(TreeNode* root) {   
  TreeNode* curr = root;
  TreeNode* prev;
  while (curr) {
    if (curr->left == 0) {
      cout << curr->data << endl; // visit current node
      curr = curr->right;
    }
    else {
      prev = curr->left;
      // Go to the rightmost node of the left subtree or to the temporary parent of p;
      // If 'true' rightmost node was reached, make it a temporary parent of the current root,
      // else a temporary parent has been found; visit current node and then cut the right 
      // pointer of the current parent, whereby it ceases to be a parent. 
      while (prev->right && prev->right != curr)  
	prev = prev->right;   

      if (prev->right == 0) {   
	prev->right = curr;     
	curr = curr->left;        
      }
      else {                   
	cout << curr->data << endl; // visit current node
	prev->right = 0;
	curr = curr->right;       
      } // end of inner else                       
    } // end of outer else
  } // end of while loop
}
*/

// Pre-order Morris traversal: by Adam Drozdek
void MorrisPreorder(TreeNode* root) {
  TreeNode* curr = root;
  TreeNode* prev;
  while (curr) {
    if (!curr->left) {
      cout << curr->data << endl; // visit current node;
      curr = curr->right;
    }
    else {
      prev = curr->left;
      while (prev->right && prev->right != curr)
	prev = prev->right; 

      if (prev->right == 0) { // Build the extra thread
	/* Visit current node. 
	 * IMPORTANT!!!
	 * In in-order traversal, it is visited in "else" section that follows. */
	cout << curr->data << endl; 
	prev->right = curr;
	curr = curr->left; 
      }
      else { // Delete the thread and recover the original tree
	prev->right = 0;
	curr = curr->right;
      }
    }
  }
}

/* Post-order Morris traversal, by Adam Drozdek, 
 * much harder to follow than in-order and pre-order. */
void MorrisPostorder(TreeNode* root) {
  TreeNode* curr = new TreeNode;
  TreeNode* prev;
  TreeNode* q;
  TreeNode* r;
  TreeNode* s;

  curr->left = root;
  while (curr) {
    if (curr->left == 0)
      curr = curr->right;
    else {
      prev = curr->left;
      while (prev->right && prev->right != curr)
	prev = prev->right;

      // If the extra thread does not exist yet, build it
      if (prev->right == 0) {
	prev->right = curr;
	curr = curr->left;
      }

      /* If thread already exists, nodes between curr->left (inclusive) and curr 
       * (exclusive) extended to the right side of modified tree are processed in 
       * reverse order; the first loop descends this chain of nodes and reverses 
       * right pointers; the second loop goes back, visits nodes, and reverses 
       * right pointers again to restore the pointers to their original setting. */
      else {
	for (q = curr->left, r = q->right, s = r->right; 
	     r != curr; 
	     q = r, r = s, s = s->right)
	  r->right = q;

	for (s = q->right; 
	     q != curr->left; 
	     q->right = r, r = q, q = s, s = s->right)
	  cout << q->data << endl; // visit q

	/* Visit node curr->left, then cut the right pointer of 
	 * the current parent, whereby it ceases to be a parent. */
	cout << curr->left->data << endl;
	prev->right = 0; // Remove the extra thread to recover the tree
	curr = curr->right;
      } // end of inner else
    } // end of outer else
  } // end of while loop
}

/* Test harness */
int main() { 
  /* Constructed binary tree is
   *  
   *          1
   *         / \
   *        2   3
   *       / \
   *      4   5
   */

  TreeNode* root = new TreeNode(1);
  root->left        = new TreeNode(2);
  root->right       = new TreeNode(3);
  root->left->left  = new TreeNode(4);
  root->left->right = new TreeNode(5); 
 
  MorrisPostorder(root);
 
  return 0;
}

