/* Leetcode OJ: Given a sorted linked list, delete all nodes that have 
 * duplicate numbers, leaving only distinct numbers from the original list.
 * For example, given 1->2->3->3->4->4->5, return 1->2->5.
 * Given 1->1->1->2->3, return 2->3.
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
  ListNode *deleteDuplicates(ListNode *head) {
    if (!head)
      return 0;

    ListNode* ret = 0;
    ListNode* tail = 0;
    ListNode* prev = head;
    ListNode* curr = head->next;
    int counter = 1;
    while (curr) {
      if (curr->val == prev->val) 
	counter++;
      else if (counter == 1) {
	if (!tail) 
	  ret = prev;
	else 
	  tail->next = prev;

	tail = prev;
	tail->next = 0;
      }
      else 
	counter = 1;

      prev = curr;
      curr = curr->next;
    }

    if (counter == 1) {
      if (!ret) 
	ret = prev;
      else {
	tail->next = prev;
	prev->next = 0;
      }
    }

    return ret;
  }

};

