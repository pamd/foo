/* Given a binary search tree, find the node whose value is closest to a target value.
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32118959.html
 * 
 * We can traverse the tree twice, the first traversal searches for the largest element 
 * that is less then target value; the second traversal searches for the smallest element
 * that is larger than target value. (See "Algorithms for Interview" book.) 
 * Each traverse takes O(lgn), so the total is O(lgn).
 *
 * The following solution traverses the tree only once, but keeps track of whether the 
 * current node is larger than or less than target value, and the difference between 
 * target and current value. If current node is larger than target, goes to left subtree; 
 * If current node is equal, return this node;
 * If current node is less than target, goes to right subtree.
 */

struct Node {
  int val;
  Node* left;
  Node* right;
};

Node* findClosest(Node* root, int target) {
  Node* ret = 0;
  int diff = 0;
  while (root) {
    if (root->val == target)
      return root;

    if (root->val > target) {
      if (!ret || root - target < diff) {
	ret = root;
	diff = root->val - target;
      }
      root = root->left;
    }
    else {
      if (!ret || target - root->val < diff) {
	ret = root;
	diff = target - root->val;
      }
      root = root->right;
    }
  }

  return ret;
}



	
