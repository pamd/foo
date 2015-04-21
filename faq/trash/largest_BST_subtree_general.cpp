/*******************************************************************
 * Correction of the implementation above.
 * Copied from:
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

  BinaryTree(int d, BinaryTree* l = NULL, BinaryTree* r = NULL) {
    data = d;
    left = l;
    right = r;
    updateSize();
  }

  ~BinaryTree() {
    if (left != NULL) delete(left);
    if (right != NULL) delete(right);
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


int findLargestBST_1337(BinaryTree* p, int min, int max, int& maxNodes, 
			BinaryTree*& largestBST, BinaryTree*& child) 
{
  // Return 0 if the current node is null. This means that the parent 
  // of current node must be either a leaf node or has only one child.
  if (!p) 
    return 0;

  // If the value of current node is between min and max, the current node 
  // is a valid node of the current BST sub-tree.
  if (p->data > min && p->data < max) {
    int leftNodes = findLargestBST_1337(p->left, min, p->data, maxNodes, largestBST, child);
    BinaryTree* leftChild = (leftNodes == 0) ? NULL : child;

    int rightNodes = findLargestBST_1337(p->right, p->data, max, maxNodes, largestBST, child);
    BinaryTree* rightChild = (rightNodes == 0) ? NULL : child;

    // Create a copy of the current node and assign its left and right child.
    BinaryTree *parent = new BinaryTree(p->data);
    parent->left = leftChild;
    parent->right = rightChild;

    // Pass the parent as the child to the above tree.
    child = parent;

    // Calculate the number of nodes in the current BST sub-tree
    int totalNodes = leftNodes + rightNodes + 1;

    // If the number of nodes in the current BST sub-tree is more than the 
    // maximum so far, update maxNodes and largestBST records.
    if (totalNodes > maxNodes) {
      maxNodes = totalNodes;
      largestBST = parent;
    }
    // Finally, return the number of nodes in the new BST sub-tree.
    return totalNodes;
  } 

  // If including the current node breaks the BST constraint, treat this node 
  // as an entirely new tree and check if a larger BST exists in this tree.
  else {
    findLargestBST_1337(p, INT_MIN, INT_MAX, maxNodes, largestBST, child);
    // Must return 0 to exclude this node
    return 0;
  }
}
 
// Wrapper function
BinaryTree* findLargestBST_1337(BinaryTree *root) {
  BinaryTree* largestBST = NULL;
  BinaryTree* child;
  int maxNodes = INT_MIN;

  findLargestBST_1337(root, INT_MIN, INT_MAX, maxNodes, largestBST, child);

  return largestBST;
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
  BinaryTree* b = BT(11, BT(12), BT( 15, BT(10, BT(5), BT(7, BT(2, BT(0), BT(8)), BT(5, BT(3), NULL))), BT(20)));
  cout << "Original tree: " << endl;
  b->print();
  printf("\n\n");

  BinaryTree* ret = findLargestBST_1337(b);
  cout << "Largest BST from 1337: " << endl;
  ret->print();
  printf("\n\n");
  
  return 0;
}
