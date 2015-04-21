/* Binary tree in-order traversal. Assume each node has a parent link. */

/* EPI Solution 6.5. */ 
void inorder_traversal(const Node* root) {
  /* In this implementation, curr is the node that is being visisted right now.
   * prev and curr are always two nodes that are linked together. That means
   * either prev is parent of curr, or curr is parent of prev. 
   * When prev is parent of curr, we are moving down the tree;
   * When curr is parent of prev, we are moving up the tree.   */
  Node* prev = 0;
  Node* curr = root;
  while (curr) {
    Node* next = 0;
    /* When curr is root of the tree (so prev is not set yet), 
     * or when prev is parent of curr. */
    if (!prev || prev->left == curr || prev->right == curr) {
      // If curr has left child, move to the left side
      if (curr->left) 
        next = curr->left;
      /* If curr does not have left child, curr must be a node
       * that we should visit. */
      else {
        cout << curr->data << endl;
	// If right subtree exists, move to the right side; otherwise move up.
        next = (curr->right ? curr->right : curr->parent);
      }
    } 

    // If prev == curr->left, curr must be a node that we should visit.
    else if (curr->left == prev) {
      cout << curr->data << endl;
      // If right subtree exists, move to the right side; otherwise move up.
      next = (curr->right ? curr->right : curr->parent);
    } 

    // If prev == curr->right, move up to the parent of curr.
    else   
      next = curr->parent;

    // Reset both prev and curr
    prev = curr;
    curr = next;
  }
}

/* By longway2008@mitbbs, same idea as EPI book solution, 
 * but harder to understand. Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32123359.html
 */
void InOrder(Node* root) {
  for (Node *p = root, *prev = root; p;) {
    if (prev != p->left && prev != p->right && p->left) {
      prev = p;  p = p->left;
      continue;
    }
 
    if (prev != p->right) {
      Print(p->data);
      if (p->right) {
	prev = p;  p = p->right;
	continue;
      }
    }

    prev = p;  
    p = p->parent;
  } 
}

