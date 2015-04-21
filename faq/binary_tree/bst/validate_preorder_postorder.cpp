/* Given an input vector of integers, determine whether it is a valid 
 * preorder or postorder traversal of a binary search tree (BST). */

#include <vector>
#include <iostream>
#include <string>
#include <climits>
#include <stack>

using namespace std;

// Is input vector a BST preorder traversal?
bool isBST_preorder(const vector<int>& v, size_t& idx, int min, int max) {
  if (idx == v.size()) 
    return true;

  int x = v[idx];
  /* If x is less than min, there is nowhere to add this node into a BST, 
   * because in preorder traversal, left branch is always visited before 
   * right branch, and we are scanning the input vector from left to right. 
   * For example, suppose the input vector is: { 10, 7, 3, 1, 5, -1, ... }, 
   * when we scan -1, we will return false immediately. It is not necessary 
   * to check whether -1 can be right child of 10, 7, 3 or 1, because all these
   * cases are impossible. */
  if (x < min)
    return false;

  /* If x is larger than required maximum, 
   * leave this value to the the other right branches. */
  if (x > max)
    return true;

  /* x is covered by current range, add it into BST, 
   * then search the left and right branches of the new node. */
  idx++;
  return isBST_preorder(v, idx, min, x) && isBST_preorder(v, idx, x, max);
}

/* Alternatively, we can use an explicit stack to solve the problem.
 * The inut array is scanned from left to right. */
bool isBST_preorder_stack(const vector<int>& v) {
  stack<pair<int, int> > stk;
  stk.push(pair<int, int>(INT_MIN, INT_MAX));
  for (size_t i = 0; i < v.size(); i++) {
    int curr = v[i];
    while (!stk.empty()) {
      pair<int, int> top = stk.top();
      if (curr < top.first)
	return false;
      if (curr > top.second)
	stk.pop();
      else {
	stk.push(pair<int, int>(curr, top.second)); // range of right child
	stk.push(pair<int, int>(top.first, curr));  // range of left child
	break;
      }
    }    
    if (stk.empty())
      return false;
  }

  return true;
}

// Is input vector a BST postorder traversal?
bool isBST_postorder(const vector<int>& v, int& idx, int min, int max) {
  if (idx == -1)
    return true;

  int x = v[idx];
  /* If x is larger than required maximum, there is nowhere to add this value into
   * a BST, because in post-order traversal, right branch is always visited after 
   * left branch, and we are scanning the inout vector from right to left. 
   *
   * Note the difference between this algorithm and the one by longway2008.
   * In longway2008's approach, the function won't return false immediately. 
   * Instead, it will leave x for later recursions, which will fail eventually.
   * My approach should save some time. 
   * 
   * For example, suppose the inout vector is: { ..., 99, 20, 23, 19, 10 }, 
   * when we scan 99, we will return false immediately. But longway2008's approach 
   * will still check whether 99 can be the left child of 20, 19 or 10. */
  if (x > max)
    return false;

  if (x < min)
    return true;

  idx--;
  return isBST_postorder(v, idx, x, max) && isBST_postorder(v, idx, min, x);
}

/* Use an explicit stack to solve the same problem. 
 * Scan input array from right to left. */
bool isBST_postorder_stack(const vector<int>& v) {
  stack<pair<int, int> > stk;
  stk.push(pair<int, int>(INT_MIN, INT_MAX));
  for (int i = v.size() - 1; i >= 0; i--) {
    int curr = v[i];
    while (!stk.empty()) {
      pair<int, int> top = stk.top();
      if (curr > top.second)
	return false;
      if (curr < top.first)
	stk.pop();
      else {
	stk.push(pair<int, int>(top.first, curr));
	stk.push(pair<int, int>(curr, top.second));
	break;
      }
    }
    if (stk.empty())
      return false;
  }

  return true;
}

// Test harness
int main() {
  /*
  // Preorder test
  int a[] = { 10, 7, 3, 1, 5, 14, 12, 19, 13 };
  int n = sizeof(a) / sizeof(int);
  vector<int> v(a, a + n);

  //size_t idx = 0;
  //bool stat = isBST_preorder(v, idx, INT_MIN, INT_MAX);
  bool stat = isBST_preorder_stack(v);
  */

 
  // Postorder test
  //int a[] = { 1, 5, 3, 7, 8, 23, 19, 14, 10 }; // valid
  int a[] = { 1, 5, 3, 17, 8, 23, 19, 14, 10 }; // invalid
  int n = sizeof(a) / sizeof(int);
  vector<int> v(a, a + n);

  //int idx = v.size() - 1;
  //bool stat = isBST_postorder(v, idx, INT_MIN, INT_MAX);
  bool stat = isBST_postorder_stack(v);

  if (stat) 
    cout << "true" << endl;
  else
    cout << "false" << endl;

}

/////////////////////////////////////////////////////////////////////
// He Haitao O(nlogn) solution
//
// Verify whether a squence of integers are the post order traversal
// of a binary search tree (BST).
// Input: squence - the squence of integers;
// length - the length of squence;
// Return: return ture if the squence is traversal result of a BST,
// otherwise, return false.
/////////////////////////////////////////////////////////////////////

/* dhu note: This problem turns out to be quite different from the problem
 * of re-constructing a binary tree based on its in-order and post-order 
 * traversal.
 * Since we know that root element is always located at the end of post-order
 * traversal, we do not need to pass min and max range for each subtree.
 * Thus the code is simpler. Time complexity: O(nlgn).
 */ 
bool verifySquenceOfBST(int squence[], int length) {
  if (squence == NULL || length <= 0)
    return false;

  // Root of a BST is at the end of post order traversal squence.
  int root = squence[length - 1];
  // Nodes in left sub-tree are less than the root.
  int i = 0;
  for(; i < length - 1; ++i) {
    if (squence[i] > root)
      break;
  }

  // Nodes in the right sub-tree are greater than the root.
  int j = i;
  for (; j < length - 1; ++j) {
    if (squence[j] < root)
      return false;
  }

  // Verify whether the left sub-tree is a BST
  bool left = true;
  if (i > 0)
    left = verifySquenceOfBST(squence, i);

  // Verify whether the right sub-tree is a BST
  bool right = true;
  if (i < length - 1)
    right = verifySquenceOfBST(squence + i, length - i - 1);

  return left && right;
}

/* MITBBS: O(n) solution, by longway2008, refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32271851.html
 */
int scanPostOrder(int *A, int idx, int minVal, int maxVal) {
  // If scan is done, or A[idx] is out of valid range, return idx 
  if (idx < 0 || A[idx] < minVal || A[idx] > maxVal)
    return idx; 

  int val = A[idx];
  idx = scanPostOrder(A, idx - 1, val, maxVal); // right subtree
  return scanPostOrder(A, idx, minVal, val);    // left  subtree 
}

// longway2008
bool checkPostOrder(int *A, int n) {
  /* If idx < 0, then we have scanned the whole input array, 
   * so the input array must be valid. */  
  return scanPostOrder(A, n - 1, INT_MIN, INT_MAX) < 0;
}

// Test harness
/*
int main() {
  int arr[] = { 5, 7, 6, 9, 11, 10, 8 };
  //int arr[] = { 7, 4, 6, 5 };
  int len = sizeof(arr) / sizeof(int);

  vector<int> postorder(arr, arr + len);
  
  if (checkPostOrder(arr, len))
    cout << "valid" << endl;
  else
    cout << "not valid" << endl;

}
*/
