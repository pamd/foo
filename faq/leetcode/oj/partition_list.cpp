/* Leetcode: Given a linked list and a value x, partition it such that 
 * all nodes less than x come before nodes greater than or equal to x.
 * You should preserve the original relative order of the nodes in each of 
 * the two partitions. For example, given 1->4->3->2->5->2 and x = 3,
 * return 1->2->2->4->3->5.
 */

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
 
// 40ms for large dataset
class Solution {
public:
  ListNode *partition(ListNode *head, int x) {
    ListNode* left_head = 0;
    ListNode* left_tail = 0;
    ListNode* right_head = 0;
    ListNode* right_tail = 0;

    while (head) {
      if (head->val < x) {
	if (!left_head) 
	  left_head = head;
	else 
	  left_tail->next = head;
	left_tail = head;
      }
      else {
	if (!right_head) 
	  right_head = head;
	else 
	  right_tail->next = head;
	right_tail = head;
      }
      head = head->next;
    }

    if (left_tail)
      left_tail->next = right_head;

    if (right_tail) 
      right_tail->next = 0;

    if (left_head)
      return left_head;
    return right_head;
  }
};

// Dropbox solution: more compact and tricky.
ListNode * PartitionList(ListNode *head, int x) {
  ListNode* less = NULL;
  ListNode* notLess = NULL;
  ListNode** lp = &less;
  ListNode** lnp = &notLess;

  while(head) {
    if (head->val < x) {
      *lp = head;
      lp = &(head->next);
    }
    else {
      *lnp = head;
      lnp = &(head->next);
    }

    head = head->next;
  }

  *lp = notLess;
  *lnp = NULL;

  return less;
}
