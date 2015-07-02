/* Given an input array of distinct integers, build a binary max tree whose 
 * root is the max element, left subtree is the max tree for elements before 
 * the max element in the array, and right subtree is the max tree for all 
 * elements after the max element in the array.
 * 
 * If max is changed into min, this problem will become construction of 
 * Cartesian Tree. Refer to:
 * http://en.wikipedia.org/wiki/Cartesian_tree
 */

#include <vector>
#include <iostream>
#include <stack>

using namespace std;

// Binary tree node def
struct TreeNode {
  // ctor
  TreeNode(int i) : dat(i), left(0), right(0) { }

  int dat;
  TreeNode* left;
  TreeNode* right;
};

// Pre-order traversal
void preorder(TreeNode* root) {
  if (!root)
    return;

  cout << root->dat << " ";
  preorder(root->left);
  preorder(root->right);
}

// In-order traversal
void inorder(TreeNode* root) {
  if (!root)
    return;

  inorder(root->left);
  cout << root->dat << " ";
  inorder(root->right);
}

// Check whether two input binary trees are identical
bool isIdentical(TreeNode* r1, TreeNode* r2) {
  if (!r1 && !r2)
    return true;

  if (!r1 || !r2)
    return false;

  if (r1->dat != r2->dat)
    return false;

  return isIdentical(r1->left, r2->left) && isIdentical(r1->right, r2->right);
}

/* The intuitive solution is: scan the input array to find the max element,
 * then create the root node, then recursively build left and right subtrees.
 * Suppose the time complexity is T(n), we have: 
 * T(n) = 2 * T(n/2) + O(n)
 * so it is a O(n*lgn) solution. 
 */
TreeNode* max_tree_nlgn(const vector<int>& v, int idx_s, int idx_e) {
  if (idx_s < 0 || idx_e >= (int) v.size() || idx_s > idx_e)
    return 0;
  
  int idx_max = idx_s;
  for (int i = idx_s + 1; i <= idx_e; i++) {
    if (v[i] > v[idx_max]) 
      idx_max = i;
  }

  TreeNode* root = new TreeNode(v[idx_max]);
  root->left = max_tree_nlgn(v, idx_s, idx_max - 1);
  root->right = max_tree_nlgn(v, idx_max + 1, idx_e);

  return root;
}

/* This problem can be solved in O(n) by using a stack.
 * When scanning the input array, we maintain a stack in which
 * elements are sorted. An element at the bottom will be always 
 * larger than an element on top. If the current element is larger 
 * than top element in stack, we keep popping stack until either
 * the top element in stack is larger than current element, or 
 * the stack becomes empty. When popping and pushing the stack,
 * we also keep track of the node of maximum element, which will
 * be returned at the end as the root of max tree.
 *
 * Each element in the array will be pushed in and/or popped out 
 * at most once. So this is an O(n) solution.
 */
TreeNode* max_tree_stack(const vector<int>& v) {
  TreeNode* root = 0;
  stack<TreeNode*> stk;
  for (size_t i = 0; i < v.size(); i++) {
    TreeNode* curr = new TreeNode(v[i]); // current node
    TreeNode* prev = 0;
    while (!stk.empty() && stk.top()->dat < v[i]) {
      prev = stk.top();
      stk.pop();
    }
    // Set the last popped element (or NULL) as left child of current node.
    curr->left = prev;

    // If the stack is empty, current element must be the 
    // maximum element so far, so we set it as root node.
    if (stk.empty()) 
      root = curr;
    // Otherwise, set curr as the right child of the top element in stack
    else 
      stk.top()->right = curr;

    // Push curr into the stack
    stk.push(curr);
  }      
   
  return root;
}

/* Alternatively, we can use recursion to solve this problem. 
 * Time complexity is still O(n). 
 * Note that in each call of this function, idx will either 
 * stay the same, or increment by 1. 
 * 
 * This approach seems awkward. Is there a better way of recursion?
 */
void max_tree_recur(const vector<int>& v, size_t& idx, TreeNode* prev, TreeNode*& root) {
  if (idx == v.size())
    return;

  // If current element is larger than previous element, do nothing;
  // v[idx] will be handled by another call at the end. 
  // (See the last line in this function).
  if (prev && v[idx] > prev->dat)
    return;

  TreeNode* curr = new TreeNode(v[idx]);
  // If previous element does not exist, current element will be the new root.
  if (!prev) {
    curr->left = root;
    root = curr;
  }

  // If current element is less than previous element, set 
  // current element as the right child of previous element.
  else { // if (curr->dat < prev->dat)  
    curr->left = prev->right;
    prev->right = curr;
  }

  // After processing the current element, 
  // recursively process the elements that follows.
  idx++;
  max_tree_recur(v, idx, curr, root);

  // If we get stuck on v[idx], try prev as the parent.
  // Since idx has been incremented by at least 1, 
  // this function call is different from the original call.
  max_tree_recur(v, idx, prev, root);
}

// Wrapper that calls recursive helper
TreeNode* max_tree_recur_wrapper(const vector<int>& v) {
  TreeNode* root = 0;
  size_t idx = 0;
  max_tree_recur(v, idx, 0, root); 
 
  return root;
}
  
// Test harness
int main() {
  int a[] = { 5, 6, 2, 28, 64, 0 };
  vector<int> v(a, a + sizeof(a) / sizeof(int));

  TreeNode* r1 = max_tree_nlgn(v, 0, v.size() - 1);

  //TreeNode* r2 = max_tree_stack(v);

  TreeNode* r2 = max_tree_recur_wrapper(v);

  if (isIdentical(r1, r2)) 
    cout << "Same" << endl;
  else
    cout << "Different" << endl;
  cout << "------------" << endl;
  
  cout << "Pre-order:\t";
  preorder(r2);
  cout << endl;

  cout << "In-order:\t";
  inorder(r2);
  cout << endl;
  
}
