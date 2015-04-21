/* Get binary tree’s next node of pre-order and post-order traversal WITHOUT
 * using recursion or stack. (Assume that each node also has a parent link.)
 * http://www.mitbbs.com/article_t/JobHunting/32099093.html
 * (Next node in in-order traversal is available in CareerCup 150 book.)
 */

// swanswan
Node* preOrderNext(Node* n) {
  if (n->left) 
    return n->left;
  if (n->right) 
    return n->right;
  Node* p = n->parent;
  while (p && p->right == n) {  // bug
   n = p;
   p = n->parent;
  }

  if (!p) return p;
  if (p->right) 
    return p->right;
  return p;  // bug
}

// zyy: fixed two bugs in above function.
Node* preOrderNext(Node* n)
{
  if (n->left) return n->left;
  if (n->right) return n->right;
  Node* p = n->parent;
  while (p && (p->right == NULL || p->right == n))  // fixed
  {
    n = p;
    p = n->parent;
  }
  if (!p) 
    return p;

  return p->right; // fixed
}

// swanswan: helper function for in-order and post-order
Node* left_most(Node* n) {
  assert(n);
  while (n->left) {
    n = n->left;
  }
  return n;
}

// swanswan
Node* postOrderNext(Node* n) {
  Node* p = n->parent;
  if (!p) reutrn p;
  if (n == p->right) 
    return p;

  if (p->right) 
    return left_most(p->right);
  return p;
}

// swanswan
Node* inorderNext(Node* n) {
  if (n->right) 
    return left_most(p->right);
  Node* p = n->parent;
  while (p && p->right == n) {
    n = p;
    p = n->parent;
  }
  return p;
}


/* Revisited:
 * http://www.mitbbs.com/article_t1/JobHunting/32148123_0_1.html
 */

/* lolhaha: post-order:
while(1)
{
   if(current->parent==NULL) return;
   if(current->parent->left==current&¤t->parent->right)
   {  current=current->parent->right; break; }
   current=current->parent;          
}
*/

/* peking2: pre-order (python, not tested
def preorder2(root):
    f=0
    n=root
    while n!=None:
        if f==2:
            if n.parent!=None and n==n.parent.left:
                f=1
            n=n.parent
        elif f==1:
            if n.right!=None:
                f=0
                n=n.right
            else:
                f=2
        else:
            print n.val
            if n.left!=None:
                n=n.left
            else:
                f=1
*****************************
// peking2: post-order (pythin, not tested)
def postorder(root):
    f=0
    n=root
    while n!=None:
        if f==2:
            print n.val
            if n.parent!=None and n==n.parent.left:
                f=1
            n=n.parent
        elif f==1:
            if n.right!=None:
                f=0
                n=n.right
            else:
                f=2
        else:
            if n.left!=None:
                n=n.left
            else:
                f=1

*/
