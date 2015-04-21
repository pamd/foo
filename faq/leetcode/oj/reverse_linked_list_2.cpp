/* Leetcode OJ: Reverse a linked list from position m to n. 
 * Do it in-place and in one-pass.
 * For example:
 * Given 1->2->3->4->5->NULL, m = 2 and n = 4,
 * return 1->4->3->2->5->NULL.
 * Note:
 * Given m, n satisfy the following condition:
 * 1 <= m <= n <= length of list.
 */


// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// 16ms for large dataset
class Solution {
public:
  ListNode *reverseBetween(ListNode *head, int m, int n) {
    if (!head)
      return 0;
    if (m == n)
      return head;

    ListNode* before_m = 0;
    if (m > 1) {
      before_m = head;
      for (int i = 0; i < m - 2; i++)
	before_m = before_m->next;
    }

    ListNode* m_th = 0;
    if (!before_m)
      m_th = head;
    else
      m_th = before_m->next;

    ListNode* reversed_tail = m_th;

    ListNode* prev = 0;
    for (int i = m; i <= n; i++) {
      ListNode* next = m_th->next;
      m_th->next = prev;
      prev = m_th;
      m_th = next;
    }

    reversed_tail->next = m_th;
    if (before_m) {
      before_m->next = prev;
      return head;
    }
    
    return prev;
  }
};

/* Dropbox solution: uses pointer to pointer to 
 * make code more compact but less readable.
 */
ListNode *ReverseBetween(ListNode *head, int m, int n) 
{
  //if (m == n) return head;

  ListNode** h = &head; // the start of list for reversing
  n = n - m + 1;        // how many nodes need to be reversed
  while (--m > 0)
    h = &((*h)->next);

  //reverse the nodes in [m,n]
  ListNode* cur = *h;
  ListNode* pre = NULL;
  ListNode* nxt;
  while (n-- > 0) {
    nxt = cur->next;
    cur->next = pre;

    pre = cur;
    cur = nxt;
  }

  // make the original fisrt node point to next node of original last
  (*h)->next = cur;
  // make head point to original last node
  *h = pre;
  
  return head;
}

