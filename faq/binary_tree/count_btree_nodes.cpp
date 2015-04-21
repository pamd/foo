/* This file includes a function to count the number of nodes in a binary tree.
 * Code copied from:
 * http://math.hws.edu/eck/cs225/s03/binary_trees/
 */

struct TreeNode {
  int item;         // The data in this node.
  TreeNode *left;   // Pointer to the left subtree.
  TreeNode *right;  // Pointer to the right subtree.
}

// Count the nodes in the binary tree to which root points, and return the answer.
int countNodes( TreeNode *root ) {
  if ( root == NULL )
    return 0;  // The tree is empty.  It contains no nodes.
  else {
    int count = 1;   // Start by counting the root.
    count += countNodes(root->left);  // Add the number of nodes
    //     in the left subtree.
    count += countNodes(root->right); // Add the number of nodes
    //    in the right subtree.
    return count;  // Return the total.
  }
} // end countNodes()
