/* Find number of subtrees in a tree where all nodes have the same value.
 * http://www.mitbbs.com/article_t/JobHunting/32061321.html
 * dhu: Different subtrees can have different values. So each leaf node 
 * will be counted as a valid subtree that satisfies this condition.
 */

#include <iostream>

using namespace std;

struct Node {
  Node(int v) { 
    dat = v; 
  }

  int dat;
  Node* left;
  Node* right;
};

int FindIdenticalSubtree(Node* root, bool& rootIncluded) 
{
  if (!root) {
    rootIncluded = true;
    return 0;
  }

  if (!root->left && !root->right) {
    rootIncluded = true;
    return 1;
  }

  bool includeLeft = false;
  bool includeRight = false;
  int left = FindIdenticalSubtree(root->left, includeLeft);
  int right = FindIdenticalSubtree(root->right, includeRight);

  if (!includeLeft || !includeRight) {
    rootIncluded = false;
    return left + right;
  }
    
  if (root->left && root->left->dat != root->dat) {
    rootIncluded = false;
    return left + right;
  }
  if (root->right && root->right->dat != root->dat) {
    rootIncluded = false;
    return left + right;
  }

  rootIncluded = true;
  return left + right + 1;
}

int main() 
{
  Node* n1 = new Node(1);
  Node* n2 = new Node(3);
  Node* n3 = new Node(3);
  Node* n4 = new Node(3);
  Node* n5 = new Node(3);
  Node* n6 = new Node(3);

  n1->left = n2;
  n1->right = n3;
  n3->left = n4;
  n3->right = n5;
  n4->right = n6;

  bool includeRoot = false;
  cout << FindIdenticalSubtree(n1,includeRoot) << endl;
}
