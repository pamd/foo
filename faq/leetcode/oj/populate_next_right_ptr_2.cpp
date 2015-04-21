/* Leetcode OJ: Follow up for problem "Populating Next Right Pointers in Each Node".
 * What if the given tree could be any binary tree? Would your previous solution still work?
 * Note: You may only use constant extra space.
 */

// Definition for binary tree with next pointer.
struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) { }
};

// 216ms for large dataset, code copied from mitbbs
class Solution {
public:
  void connect(TreeLinkNode *root) {
    root->next = 0;
    TreeLinkNode* curr;
    // Accessory node that will be the head at each level
    TreeLinkNode* dummy = new TreeLinkNode(0);
    while (root) {
      curr = dummy;
      // Inner loop takes care of one level of the binary tree
      while (root) {
	if (root->left) {
	  curr->next = root->left;
	  curr = root->left;
	}
	
	if (root->right) {
	  curr->next = root->right;
	  curr = root->right;
	}
	root = root->next;
      } // end of inner while 

      curr->next = 0;
      root = dummy->next;
    } // end if outer while

    delete dummy;
  }

};
        

