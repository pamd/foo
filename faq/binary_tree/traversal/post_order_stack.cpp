/* Various implementations of post-order traversal. */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>

using namespace std;

// Binary tree node 
struct TreeNode {
  TreeNode(int d = 0) : dat(d), left(0), right(0) { }

  int dat;
  TreeNode* left;
  TreeNode* right;
};

/* Post-order traversal using two explicit stacks. Refer to:
 * http://forums.devarticles.com/c-c-help-52/non-recursive-tree-traversal-74033.html
 *
 * According to "Data Structures and Algorithms in C++", post-order is 
 * "Left/Right/Current", which is exactly the reverse of the pre-order 
 * of "Current/Right/Left". So if we consider s1.pop() as a visit operation 
 * in "Current/Right/Left" pre-order, then the elements in s2 from bottom to 
 * top are in exact reverse order of post-order. This is why the solution is correct.  
 */
void post_order_stack1(TreeNode* root) {
  stack<TreeNode*> s1, s2;
  s1.push(root);
  TreeNode* tmp = 0;
  while (!s1.empty()) {
    tmp = s1.top();
    s1.pop();
    s2.push(tmp);
    if (tmp->left)
      s1.push(tmp->left);
    if (tmp->right)
      s1.push(tmp->right);
  }

  // Visit elements in s2
  while (!s2.empty()) {
    cout << s2.top()->dat << endl;
    s2.pop();
  }
}

/********************************************************** 
 * Post-order traversal that uses only one explicit stack. 
 **********************************************************/

// Help function for post_order_stack2(), which is defined after this function
void findNext(TreeNode *node, stack<TreeNode*>& stk) {
  while (node) {
    stk.push(node);
    node = (node->left) ? node->left : node->right;
  }
}

// Post-order traversal that uses one explicit stack and calls findNext().
void post_order_stack2(TreeNode *root) {
  stack<TreeNode*> stk;
  findNext(root, stk);

  TreeNode* prev = 0; // previously visited node
  while (!stk.empty()) {
    // curr is the node that is being processed
    TreeNode* curr = stk.top();

    /* In post-order traversal, if a node has right child, 
     * this node will always be visited right after its right child. 
     * So if curr does not have right child, or its right child has been
     * visited, curr will be the next node that we should visit. */
    if (!curr->right || curr->right == prev) {
      cout << curr->dat << endl; 
      stk.pop();
      prev = curr;
    }

    /* If right subtree exists, and right child has not 
     * been visited yet, go to the right side. */
    else 
      findNext(curr->right, stk);
  }

}

/* Post-order traversal with one explicit stack.
 * Based on genBST.h in "Data Structures and Algorithms in C++", 
 * written by Adam Drozdek, 4th Edition, 2012. 
 *
 * This implementation is less readable than the previous one. */
void post_order_stack3(TreeNode* root) {    
  stack<TreeNode*> stk;
  TreeNode* curr = root; 
  TreeNode* prev = root; // Previously visited node 

  while (curr) {
    /* If the tree has a left edge, push all nodes 
     * (except the left-most one) on this edge into stack. */
    while (curr->left) {
      stk.push(curr);
      curr = curr->left;
    }

    /* If current node does not have right child, or its right child
     * has been visited, visit the current node. */    
    while (!curr->right || curr->right == prev) {
      cout << curr->dat << endl; // visit current node
      prev = curr;

      if (stk.empty())
	return;

      curr = stk.top();
      stk.pop();
    }
    
    /* After the above while loop, curr is a node that has right child and 
     * its right child has not been visited yet, so push curr back into stack. */
    stk.push(curr);
    curr = curr->right;
  }
}

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

  TreeNode* root    = new TreeNode(1);
  root->left        = new TreeNode(2);
  root->right       = new TreeNode(3);
  root->left->left  = new TreeNode(4);
  root->left->right = new TreeNode(5); 
 
  post_order_stack2(root);

  return 0;
}
