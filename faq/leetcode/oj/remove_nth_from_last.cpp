/* Leetcode OJ: Given a linked list, remove the nth node from 
 * the end of list and return its head. For example, given linked list: 
 * 1->2->3->4->5, and n = 2,
 * after removing the 2nd node from the end, the linked list becomes 1->2->3->5.
 * Note: Given n will always be valid. Try to do this in one pass.
 */

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// 36ms for large dataset
class Solution {
public:
  ListNode *removeNthFromEnd(ListNode *head, int n) {
    if (!head)
      return 0;

    ListNode* head2 = head;
    ListNode* p1 = head;
    for (int i = 0; i < n; i++) 
      p1 = p1->next;

    if (!p1)
      return head->next;

    ListNode* p2 = head;
    while (p1->next) {
      p1 = p1->next;
      p2 = p2->next;
    }

    p2->next = p2->next->next;
    return head2;
  }
};
