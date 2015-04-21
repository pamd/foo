/* Leetcode OJ: Given a sorted linked list, delete all duplicates 
 * such that each element appear only once.
 * For example, given 1->1->2, return 1->2.
 * Given 1->1->2->3->3, return 1->2->3.
 */

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) { }
};

class Solution {
public:
  // 68ms for large dataset. 
  ListNode *deleteDuplicates_general(ListNode *head) {
    if (!head)
      return 0;

    ListNode* ret = head;
    ListNode* curr = head;
    head = head->next;
    while (head) {
      if (head->val != curr->val) {
	curr->next = head;
	curr = head;
      }
      head = head->next;
    }

    curr->next = 0;
    return ret;
  }

  /* This solution uses an accessory std::set, 
   * so it will work for unsorted linked list too. 
   * 84ms for large dataset. */
  ListNode *deleteDuplicates_general(ListNode *head) {
    if (!head)
      return 0;

    ListNode* ret = head;
    ListNode* curr = head;
    set<int> prev;
    prev.insert(head->val);
    head = head->next;
    while (head) {
      if (prev.find(head->val) == prev.end()) {
	curr->next = head;
	curr = head;
	prev.insert(head->val);
      }
      head = head->next;
    }
    curr->next = 0;
    return ret;        
  }

};
