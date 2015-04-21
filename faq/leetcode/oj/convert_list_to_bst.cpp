/* OJ question: 
 * Given a singly linked list where elements are sorted in ascending order, 
 * convert it to a height balanced BST.*/

#include <iostream>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// Definition for binary tree
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// 160ms for large dataset
class Solution {
public:
  TreeNode *sortedListToBST(ListNode *head) {
    if (!head)
      return NULL;

    if (!head->next)
      return new TreeNode(head->val);

    ListNode* slow = head;
    ListNode* fast = head;
    ListNode* left_head = 0;
    ListNode* prev = 0;
    while (fast->next) {
      if (!prev) {
	left_head = new ListNode(slow->val);
	prev = left_head;
      }
      else {
	prev->next = new ListNode(slow->val);
	prev = prev->next;
      }

      slow = slow->next;
      fast = fast->next->next;
      if (!fast)
	break;
    }

    TreeNode* root = new TreeNode(slow->val);
    root->left = sortedListToBST(left_head);
    root->right = sortedListToBST(slow->next);
    return root;
  }

};

/* Another solution based on Leetcode blog article:
 * http://www.leetcode.com/2010/11/convert-sorted-list-to-balanced-binary.html
 * 140ms for large dataset.
 *
 * dhu: This solution is better than mine, because it does not generate a
 * intermediate linked list to record the left half of input list.
 */
class Solution2 {
public:
  TreeNode *sortedListToBST(ListNode *head) {
    // Count the number of nodes in input list
    int cnt = 0;
    ListNode* tmp = head;
    while (tmp) {
      tmp = tmp->next;
      cnt++;
    }

    // Call helper function
    return helper(head, 0, cnt - 1);
  }
  
  TreeNode* helper(ListNode *& list, int start, int end) {
    if (start > end) 
      return NULL;

    // same as (start + end) / 2, avoids overflow
    int mid = start + (end - start) / 2;
    TreeNode *leftChild = helper(list, start, mid - 1);
    TreeNode *parent = new TreeNode(list->val);
    parent->left = leftChild;

    // This is the key reason why no intermediate list is not needed!
    list = list->next;  

    parent->right = helper(list, mid + 1, end);
    return parent;
  }

};

// Another solution that is based on Solution2 but more compact
class Solution3 {
public:
  TreeNode *sortedListToBST(ListNode *head) {
    int len = 0;
    ListNode* curr = head;
    while (curr) {
      len++;
      curr = curr->next;
    }

    return helper(head, len);
  }

  TreeNode* helper(ListNode*& head, int len) {
    if (len <= 0)
      return 0;

    TreeNode* left = helper(head, len / 2);
    TreeNode* root = new TreeNode(head->val);
    head = head->next;
    TreeNode* right = helper(head, len - len / 2 - 1);
    
    root->left = left;
    root->right = right;
    return root;
  }
};
