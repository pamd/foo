/* Find the largest identical substree in a binary tree.
 * Here "identical" means that the structures of two substrees are
 * identical, but the data in correpsonding nodes can be different.
 * Ref:
 * http://www.mitbbs.com/article_t/JobHunting/31844127.html
 */

#include <iostream>
#include <map>

using namespace std;

// Binary tree node def
struct TreeNode {
  TreeNode(int d) { dat = d; mark = 0; left = 0; right = 0; }
  
  int dat;
  int mark;
  TreeNode* left;
  TreeNode* right;
};

/* If we are not allowed to modify the data structure of binary tree,
 * we can use another hash table (or map) to record each node's mark
 * value and look it up efficiently, something like:
 *    map<TreeNode*, mark> mark_map;
 */

// Helper function that counts the number of nodes in the input subtree.
int countTreeNode(TreeNode* root) {
  if (!root)
    return 0;

  return 1 + countTreeNode(root->left) + countTreeNode(root->right);
}

// Post-order traversal to search the largest identical subtree
void search_recur(TreeNode* root, int& max_sz, TreeNode*& sub1, TreeNode*& sub2,
		  int& mark_counter, map<pair<int, int>, pair<int, TreeNode*> >& node_map) 
{
  if (!root)
    return;
  
  search_recur(root->left, max_sz, sub1, sub2, mark_counter, node_map);  // left subtree
  search_recur(root->right, max_sz, sub1, sub2, mark_counter, node_map); // right subtree

  int left = 0;
  int right = 0;
  if (root->left)
    left = root->left->mark;

  if (root->right)
    right = root->right->mark;

  pair<int, int> tmp = make_pair(left, right);
  // If the structure of current subtree never showed up before, put it into node_map.
  if (node_map.find(tmp) == node_map.end()) {
    node_map[tmp] = make_pair(mark_counter, root);
    root->mark = mark_counter;
    mark_counter++;
    return;
  }

  /* If this structure shows up before, find the number of nodes in the subtree.
   * If it is larger than maximum size so far, update max_sz, sub1 and sub2. */
  root->mark = node_map[tmp].first;
  int curr_sz = countTreeNode(root);
  if (max_sz < curr_sz) {
    max_sz = curr_sz;
    sub1 = root;
    sub2 = node_map[tmp].second;
  }
  
}

// Wrapper that calls recursive helper function
void get_max_common_subtree(TreeNode* root) {
  /* node_map allows us to quickly find out whether a certain subtree
   * structure showed up before. 
   * In pair<int, int>, the first int is the marked value of left child, 
   * the second int is the marked value of right child. 
   * in pair<int, TreeNode*>, int is the marked value of the root node whose
   * left and right children have marked values of pair<int, int>,
   * TreeNode* points to the first node whose left and right children have 
   * marked values of pair<int, int>. 
   * We are using std::map here to simplify the coding. So searching takes O(logn).
   * To get O(1) time complexity, use std::unordered_map instead. */
  map<pair<int, int>, pair<int, TreeNode*> > node_map;

  // mark_counter is an arbitrary value that labels the subtree rooted at each node.
  int mark_counter = 1;  

  /* The following three variables keep track of the size of largest 
   * identical subtree, and the two root nodes of matching subtrees. */  
  int max_sz = 0;
  TreeNode* sub1 = 0;
  TreeNode* sub2 = 0;

  search_recur(root, max_sz, sub1, sub2, mark_counter, node_map);

  cout << "size: " << max_sz << endl;
  cout << "sub1: " << sub1->dat << endl;
  cout << "sub2: " << sub2->dat << endl;
}
  
// Test harness
int main() {
  /*
   *                         1
   *                        / \
   *                       2   3
   *                      /     \
   *                     4       5
   *                    /       / \
   *                   6       7   8
   *                          /     \
   *                         9      10
   *                        / \     / \
   *                       11  13  14  12
   *
   *
   */
  TreeNode* n1 = new TreeNode(1);
  TreeNode* n2 = new TreeNode(2);
  TreeNode* n3 = new TreeNode(3);
  TreeNode* n4 = new TreeNode(4);
  TreeNode* n5 = new TreeNode(5);
  TreeNode* n6 = new TreeNode(6);
  TreeNode* n7 = new TreeNode(7);
  TreeNode* n8 = new TreeNode(8);
  TreeNode* n9 = new TreeNode(9);
  TreeNode* n10 = new TreeNode(10);
  TreeNode* n11 = new TreeNode(11);
  TreeNode* n12 = new TreeNode(12);
  TreeNode* n13 = new TreeNode(13);
  TreeNode* n14 = new TreeNode(14);

  n1->left = n2;
  n1->right = n3;

  n2->left = n4;
  n4->left = n6;
  n3->right = n5;

  n5->left = n7;
  n5->right = n8;

  n7->left = n9;

  n9->left = n11;
  n9->right = n13;

  n8->right = n10;

  n10->right = n12;
  n10->left = n14;

  get_max_common_subtree(n1);

  return 0;
}


