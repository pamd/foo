/* Leetcode OJ: Merge two sorted linked lists and return it as a new list. 
 * The new list should be made by splicing together the nodes of the first two lists.
 */

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// 52ms for large dataset
class Solution {
public:
  ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
    if (!l1)
      return l2;

    if (!l2)
      return l1;

    ListNode* head = 0;
    ListNode* current = 0;
    while (l1 && l2) {
      ListNode* tmp;
      if (l1->val < l2->val) { 
	tmp = l1;
	l1 = l1->next;
      }
      else {
	tmp = l2;
	l2 = l2->next;
      }

      if (!current) 
        head = tmp;
      else
	current->next = tmp;
      current = tmp;
    }

    // For linked list, simply link the rest of list
    if (l1) 
      current->next = l1;
    else
      current->next = l2;

    return head;
  }
};
