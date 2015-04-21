/* Leetcode OJ: Given a binary tree:
 *
 *   struct TreeLinkNode {
 *     TreeLinkNode *left;
 *     TreeLinkNode *right;
 *     TreeLinkNode *next;
 *   }
 *
 * Populate each next pointer to point to its next right node. 
 * If there is no next right node, the next pointer should be set to NULL.
 * Initially, all next pointers are set to NULL.
 * Note:
 * You may only use constant extra space.
 * You may assume that it is a perfect binary tree (ie, all leaves are at 
 * the same level, and every parent has two children).
 */

// Definition for binary tree with next pointer.
struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) { }
};

// 156 ms for large dataset
class Solution {
public:
  void connect(TreeLinkNode *root) {
    if (!root)
      return;

    TreeLinkNode* prev_head = root;
    TreeLinkNode* curr_head = root->left;
    TreeLinkNode* curr = 0;
    while (prev_head) {
      if (!curr_head)
	break;

      if (!curr) {
	curr = prev_head->left;
	curr->next = prev_head->right;
	curr = curr->next;
      }
      else {
	curr->next = prev_head->left;
	curr->next->next = prev_head->right;
	curr = curr->next->next;
      }

      prev_head = prev_head->next;
      if (!prev_head) {
	prev_head = curr_head;
	curr_head = curr_head->left;
	curr = 0;
      }
    }
  }

};

// Anson627 solution: 156ms for large dataset.
// dhu note: the following BFS and DFS functions are recursive, 
// so they implicitly use non-constant extra space. 
class Solution_anson {
public:
  void connect(TreeLinkNode *root) {
    //connect1(root);
    connect2(root);
  }

  void connect1(TreeLinkNode *node) {
    if (node) 
      node->next = NULL;
    connectHelper1(node);
  }

  // BFS
  void connectHelper1(TreeLinkNode* node) {
    if (!node || !(node->left) || !(node->right)) 
      return;

    TreeLinkNode* curr = node;
    while (curr) {
      if (curr->left) 
	curr->left->next = curr->right;

      if (curr->right) 
	curr->right->next = (curr->next) ? curr->next->left : NULL;

      curr = curr->next;
    }   
    connectHelper1(node->left);
  }   
  
  void connect2(TreeLinkNode *node) {
    if (node) 
      node->next = NULL;
    connectHelper2(node);
  }
    
  // DFS
  void connectHelper2(TreeLinkNode* node) {
    if (!node || !(node->left) || !(node->right)) 
      return;

    node->left->next = node->right;
    node->right->next = (node->next) ? node->next->left: NULL;
    connectHelper2(node->left);
    connectHelper2(node->right);
  }
};

// Recursive solution from MITBBS (URL is dead)
void mitbbs_connect(TreeLinkNode *root){
  if (!root) 
    return;

  TreeLinkNode* next = root->next;
  while (next) {
    if (next->left) {
      next = next->left;
      break;
    }
    if (next->right) {
      next = next->right;
      break;
    }

    next = next->next;
  }

  // Connect right first, then do left
  if (root->right) 
    root->right->next = next;
  if (root->left) 
    root->left->next = root->right? root->right:next;

  // When recursing, do right first, then do left
  mitbbs_connect(root->right);
  mitbbs_connect(root->left);
}

