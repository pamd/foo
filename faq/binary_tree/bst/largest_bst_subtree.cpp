/*******************************************************************
 * Greg's Correction of ihasleetcode1337's implementation.
 * Based on the code in:
 * http://pastebin.com/5QjBnjiS
 *******************************************************************/

#include <iostream>
#include <stdio.h>
#include <climits>

using namespace std;

#define BT new BinaryTree


/* Generic class of Binary Tree */
class BinaryTree {
public:
  int data;
  // Store current tree size to avoid computing it over and over again...
  int size;
  BinaryTree* left;
  BinaryTree* right;

  // Ctor
  BinaryTree(int d, BinaryTree* l = NULL, BinaryTree* r = NULL) {
    data = d;
    left = l;
    right = r;
    updateSize();
  }

  // Copy ctor does deep copy
  BinaryTree(const BinaryTree& inputTree) {
    data = inputTree.data;
    size = inputTree.size;
    if (inputTree.left)
      left = new BinaryTree(*(inputTree.left));
    else
      left = NULL;

    if (inputTree.right)
      right = new BinaryTree(*(inputTree.right));
    else
      right = NULL;
  }
	
  ~BinaryTree() {
    if (left != NULL) 
      delete(left);
    if (right != NULL) 
      delete(right);
  }

  void print() {
    if (left || right) {
      printf("(%i, ", data);
      // Print left subtree
      if (left)  
	left->print(); 
      else 
	printf("NULL");
      // "," separates left and right subtrees
      printf(", ");
      // Print right subtree
      if (right) 
	right->print(); 
      else 
	printf("NULL");
      // ")" ends the subtree that is rooted at current node
      printf(")");
    } 
    else 
      printf("(%i)", data);
  }

  void updateSize(){
    size = 1;
    if (left != NULL){
      size += left->size;
    }
    if (right != NULL){
      size += right->size;
    }
  }
};

/* Find the largest BST subtree in a binary tree.
 * Copied from:
 * http://www.ihas1337code.com/2010/11/largest-binary-search-tree-bst-in.html
 * 
 * In this problem, the node in the sub-tree must include all of its descendants.
 * It is easier than the other problem: Largest BST in a binary tree, in which the 
 * node in the target sub-tree doesn't have to include its descendants.

 * If the subtree is a BST, return total number of nodes.
 * If the subtree is not a BST, return -1.
 * 
 * dhu comments: min and max are minimum and maximum values in the sub-tree 
 * (or the original tree) whose root is "p" variable; 
 * targetSize records the number of nodes in the lagest 
 * BST sub-tree that has been found so far;
 * targetRoot records the root of the largest BST sub-tree
 * that has been found so far. 
 * Every call of this function WILL update min and max.
 * Every call of this function MAY update targetSize and targetRoot.
 *
 * In this problem, the data memeber "size" in BinaryTree class is never used. 
 * It is actually added for the next more general problem. 
 */
int findLargestBSTSubtree(const BinaryTree* p, int& min, int& max, 
			  int& targetSize, const BinaryTree*& targetBST) 
{
  // Return 0 if the current node is null. 
  // This means the parent of p is a leaf node.
  if (!p) 
    return 0;

  bool isBST = true;

  // Check whether node "p" and its left subtree make a valid BST?
  int leftNodes = findLargestBSTSubtree(p->left, min, max, targetSize, targetBST);
  // Since min may be reset by every call of findLargestBSTSubtree(), 
  // currMin must be set here!
  int currMin = (leftNodes == 0) ? p->data : min;
  if (leftNodes == -1 || (leftNodes != 0 && p->data <= max))
    isBST = false;

  // Even if node "p" and its left sub-tree don't make a valid BST, we still need
  // to check the right sub-tree of p, because the largest BST sub-tree may be on
  // the right sub-tree of p.

  // Do node "p" and its right subtree make a valid BST?
  int rightNodes = findLargestBSTSubtree(p->right, min, max, targetSize, targetBST);
  // Since max may be reset by every call of findLargestBSTSubtree(), 
  // currMax must be set here!
  int currMax = (rightNodes == 0) ? p->data : max;
  if (rightNodes == -1 || (rightNodes != 0 && p->data >= min))
    isBST = false;

  // Return -1 if the current sub-tree is not a valid BST 
  if (!isBST) 
    return -1;   

  // Reset min and max to cuuMin and currMax
  min = currMin; 
  max = currMax; 

  // If the current sub-tree rooted at node "p" makes a valid BST, 
  // check this subtree's size. When the size is larger than current maximum records, 
  // update targetSize and targetBST.
  int currSize = leftNodes + rightNodes + 1;
  if (currSize > targetSize) {
    targetSize = currSize;
    targetBST = p;
  }

  // Finally, return the number of nodes in the current sub-tree.  
  return currSize; 
}

// Wrapper function 
const BinaryTree* findLargestBSTSubtree(const BinaryTree *root) {
  const BinaryTree* targetBST = NULL;
  int min, max; 
  int targetSize = INT_MIN;
  // See dhu comments in front of the other findLargestBSTSubtree() for details.
  findLargestBSTSubtree(root, min, max, targetSize, targetBST);
  return targetBST;
}

/* Limit lower bound in O(log n), 
 * used to prune the right side of subtree rooted at t */
BinaryTree* boundMin(BinaryTree* t, int min) {
  if ((t == NULL) || (t->data < min)) 
    return NULL;

  /* Because t is already a BST, we don't have to worry 
   * about its right side when enforcing the minimum. */  
  t->left = boundMin(t->left, min);
  t->updateSize();

  return t;
}

/* Limit upper bound: O(log n), 
 * used to prune the left side of subtree rooted at t. */
BinaryTree* boundMax(BinaryTree* t, int max) {
  if ((t == NULL) || (t->data > max)) 
    return NULL;
  
  /* Because t is already a BST, we don't have to worry 
   * about its left side when enforcing the maximum. */  
  t->right = boundMax(t->right, max);
  t->updateSize();

  return t;
}

/* Find the largest BST: bottom up approach by Gregory. 
 * Start going down, and when moving up, re-create a tree from which 
 * we can cut off the branches that don't respect the BST.
 * n nodes are visisted, each step is 2 * O(log n), so the total
 * complexity is O(n log n) */
BinaryTree* findLargestBST_greg(const BinaryTree* p, int& targetSize, BinaryTree*& targetRoot) 
{
  if (!p) 
    return NULL;

  // Bottom up approach. Check out the children first.
  BinaryTree* left = findLargestBST_greg(p->left, targetSize, targetRoot);
  BinaryTree* right = findLargestBST_greg(p->right, targetSize, targetRoot);

  // Limit the max value on the left side.
  left = boundMax(left, p->data);

  // Limit the min value on the right side.
  right = boundMin(right, p->data);

  // Build a valid BST rooted at p
  BinaryTree* t = new BinaryTree(p->data, left, right);

  /* Update targetsize and targetRoot if the new tree has 
   * more nodes than the one saved so far. */
  if(t->size > targetSize) {
    targetSize = t->size;
    /********************************************************************************
     * dhu: The original code by Greg is: 
     * -----------------------------------------------------------
     *     targetRoot = p; // Store root node from ORIGINAL tree
     * -----------------------------------------------------------
     * Instead, I copied the whole tree t into targetRoot. 
     * With this copy we don't need tree2BST() later to prune invalid nodes.
     * Note that we can not write:
     *     targetRoot = t;
     * because t is returned in this function and may be modified when the parent node
     * calls boundMax() and boundMin().
     * In order to copy the whole tree instead of only the current node, we also define
     * an explicit copy constructor in BinaryTree class that does deep copy.
     ********************************************************************************/
    delete targetRoot; // avoid memory leak
    targetRoot = new BinaryTree(*t);   
  }

  return t;
}

/* Turn a tree into a BST by cutting off the nodes that don't respect the BST constraints.
 * Maximum n nodes => O(n).
 * With the modification on line 213, this function is not required any more. */
BinaryTree* tree2BST(BinaryTree* t, int min, int max) {
  // End case
  if (t == NULL) 
    return NULL;

  // No node
  if ((t->data < min) || (t->data > max)) 
    return NULL;

  t->left = tree2BST(t->left, min, t->data);
  t->right = tree2BST(t->right, t->data, max);
  return t;
}

/* Find the targetRoot's root node, then create the BST from it.
 * O(n log n) + O(n) => O(n log n) */
BinaryTree* findLargestBST_greg(BinaryTree* root) {
  BinaryTree* targetRoot = NULL;
  int targetSize = INT_MIN;

  // Find root
  findLargestBST_greg(root, targetSize, targetRoot);

  /* Create BST from the targetRoot 
   * (similar to the procedure of checking whether a binary tree is BST or not) 
   * This line is commented out now because targetRoot doesn't point to the node
   * in original input binary tree. Instead, it is brand-new node created dynamically. 
   * ----------------------------------------------------
   * targetRoot = tree2BST(targetRoot, INT_MIN, INT_MAX);
   * -----------------------------------------------------
   */
  cout << "Size of largest BST from Greg: " << targetSize << endl; 
  return targetRoot;
}

/* Original approach by ihasleetcode1337, copied from: 
 * http://www.ihas1337code.com/2010/11/largest-binary-search-tree-bst-in_22.html
 * -------------------------------------------------------------------------------
 * This implementation has a bug! From the comments in above URL:
 * Gregory said...
 * Actually there seems to be a problem if the root of the largest BST is 
 * actually contained in a BST currently being computed... 
 * The only possible roots in your code are the nodes that didn't make it 
 * in a BST (unless I missed something).
 * November 29, 2010 12:22 PM
 * -------------------------------------------------------------------------------
 * This code does not delete dynamically-allocated nodes,
 * so memory will be leaked upon exit.
 * The min and max values are passed top-down to check if
 * including a node satisfies the current BST constraint.
 * The child nodes are passed bottom-up to be assigned to its parent.
 * Returns the total number of nodes the child holds.
 */
int findLargestBST_1337(BinaryTree* p, int min, int max, int& targetSize, 
			BinaryTree*& targetRoot, BinaryTree*& child) 
{
  /* Return 0 if the current node is null. This means that the parent 
   * of current node must be either a leaf node or has only one child. */
  if (!p) 
    return 0;

  /* If the value of current node is between min and max, the current node 
   * is a valid node of the current BST sub-tree. */
  if (p->data > min && p->data < max) {
    int leftNodes = findLargestBST_1337(p->left, min, p->data, targetSize, targetRoot, child);
    BinaryTree* leftChild = (leftNodes == 0) ? NULL : child;

    int rightNodes = findLargestBST_1337(p->right, p->data, max, targetSize, targetRoot, child);
    BinaryTree* rightChild = (rightNodes == 0) ? NULL : child;

    // Create a copy of the current node and assign its left and right child.
    BinaryTree* parent = new BinaryTree(p->data);
    parent->left = leftChild;
    parent->right = rightChild;

    // Pass the parent as the child to the above tree.
    child = parent;

    // Calculate the number of nodes in the current BST sub-tree
    int currSize = leftNodes + rightNodes + 1;

    /* If the number of nodes in the current BST sub-tree is more than the 
     * maximum so far, update targetSize and targetRoot records. */
    if (currSize > targetSize) {
      targetSize = currSize;
      targetRoot = parent;
    }
    // Finally, return the number of nodes in the new BST sub-tree.
    return currSize;
  } 

  /* If including the current node breaks the BST constraint, treat this node 
   * as an entirely new tree and check if a larger BST exists in this tree. */
  else {
    findLargestBST_1337(p, INT_MIN, INT_MAX, targetSize, targetRoot, child);
    // Must return 0 to exclude this node
    return 0;
  }
}
 
// Wrapper function of ihasleetcode133t's implementation
BinaryTree* findLargestBST_1337(BinaryTree *root) {
  BinaryTree* targetRoot = NULL;
  BinaryTree* child;
  int targetSize = INT_MIN;
  findLargestBST_1337(root, INT_MIN, INT_MAX, targetSize, targetRoot, child);

  printf("Size of largest BST from 1337: %i\n", targetSize);
  return targetRoot;
}

/******************************************************************
                Test harness
 
Test case 1:

                ___________________15___________________
               /					\
   ___________10___________                             20
  /			   \
  5                  ____ _7____
                    /           \
                  __2__       __5
                 /     \     /
                 0      8   3


Test case 2:

         _________11_________
        /                    \
       12      ______________15______________
              /                              \
  ___________10___________                   20
 /                        \
 5                   _____7____
                    /          \
                  __2__       __5
                 /     \     /
                 0      8    3

**********************************************************************/

int main()
{
  //BinaryTree *testTree = BT(15, BT(10, BT(5), BT(7, BT(2, BT(0), BT(8)), BT(5, BT(3), NULL))), BT(20));
  //BinaryTree* testTree = BT(11, BT(12), BT( 15, BT(10, BT(5), BT(7, BT(2, BT(0), BT(8)), BT(5, BT(3), NULL))), BT(20)));
  BinaryTree* testTree = BT(9, BT(12), BT( 15, BT(10, BT(5), BT(7, BT(2, BT(0), BT(8)), BT(5, BT(3), NULL))), BT(20)));
  cout << "Input binary tree: " << endl;
  testTree->print();
  printf("\n\n");

  /* In test case #2, findLargestBST_greg(b2) gives the following largest BST sub-tree:
   * 
   *            15
   *            / \
   *          10  20
   *          /
   *         5
   *
   * But findLaLargestBST_1337(b2) gives:
   *
   *               7               
   *              /
   *             2
   *            /
   *           0
   *
   * because 15 is both root of the largest BST sub-tree and an internal node of 
   * the following smaller BST sub-tree. 
   *    
   *            11
   *              \
   *              15
   *                \
   *                20
   * 
   * What a bug!
   *
   */

  BinaryTree* greg = findLargestBST_greg(testTree);
  cout << "Largest BST from Greg: " << endl;
  greg->print();
  printf("\n\n");
  
  // BinaryTree* c1337 = findLargestBST_1337(testTree);
  // cout << "Largest BST from 1337: " << endl;
  // c1337->print();
  // printf("\n\n");

  return 0;
}


















