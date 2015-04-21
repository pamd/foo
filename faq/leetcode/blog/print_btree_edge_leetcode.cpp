/* This is my implementation of printing out edge nodes in a binary tree 
 * in counter-clockwise direction. ALso refer to:
 * http://www.leetcode.com/2010/10/print-edge-nodes-boundary-of-binary.html
 */

#include <iostream>

using namespace std;

struct Node {
  Node(int i, Node* l = 0, Node* r = 0) {
    dat = i;
    left = l;
    right = r;
  }

  int dat;
  Node* left;
  Node* right;
};

void printRight(Node*, bool);

// Print left subtree
void printLeft(Node* root, bool hasEdge) {
  if (!root)
    return;
  if (!root->left && !root->right) {
    cout << root->dat << ", ";
    return;
  }

  if (hasEdge) 
    cout << root->dat << ", ";

  printLeft(root->left, hasEdge);

  // dhu implementation calls printLeft() and printRight()
  printRight(root->right, false);

  // leetcode implementation calls printLeft twice
  //printLeft(root->right, false); 
}

// Print right subtree
void printRight(Node* root, bool hasEdge) {
  if (!root)
    return;
  if (!root->left && !root->right) {
    cout << root->dat << ", ";
    return;
  }

  // dhu implementation calls printLeft() and printRight()
  printLeft(root->left, false);

  // leetcode calls printRight() twice
  //printRight(root->left, false);

  printRight(root->right, hasEdge);

  if (hasEdge)
   cout << root->dat << ", ";
}

// Driver function
void printEdges(Node* root) {
  if (!root)
    return;

  cout << root->dat << ", ";
  printLeft(root->left, true);
  printRight(root->right, true);
  cout << endl;
}


// Test harness
int main() {
  Node* n30 = new Node(30);
  Node* n20 = new Node(20);
  Node* n40 = new Node(40);
  Node* n10 = new Node(10);
  Node* n25 = new Node(25);
  Node* n35 = new Node(35);
  Node* n50 = new Node(50);
  Node*  n5 = new Node(5);
  Node* n15 = new Node(15);
  Node* n28 = new Node(28);
  Node* n41 = new Node(41);

  n30->left = n20;
  n30->right = n40;
  n20->left = n10;
  n20->right = n25;
  n40->left = n35;
  n40->right = n50;
  n10->left = n5;
  n10->right = n15;
  n25->right = n28;
  n50->left = n41;

  Node* root = n30;
  printEdges(root);
}
