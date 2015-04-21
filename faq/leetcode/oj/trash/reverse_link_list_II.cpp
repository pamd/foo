/* Reverse a linked list from position m to n. Do it in-place and in one-pass.
 * For example:
 * Given 1->2->3->4->5->NULL, m = 2 and n = 4,
 * return 1->4->3->2->5->NULL.
 *
 * Note: Given m, n satisfy the following condition:
 * 1 ≤ m ≤ n ≤ length of list.
 *
 */

#include <iostream>
#include <assert.h>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// dhu helper function
void print(ListNode* head) {
  while (head) {
    cout << head->val << " ";
    head = head->next;
  }
  cout << endl;
}

// OJ solution: 12 ms for large dataset
class Solution {
public:
  ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (!head)
      return 0;

    assert(m > 0 && m <= n);

    ListNode* current = head;
    ListNode* prev = 0;
    int counter = 1;
    while (counter < m && current) {
      prev = current;
      current = current->next;
      counter++;
    }
    if (!current)
      return 0;

    ListNode* tail = 0;
    ListNode* rev_head = helper(current, m, n, tail);
    if (!rev_head)
      return 0;

    current->next = tail;
    if (prev) {
      prev->next = rev_head;
      return head;
    }
    
    return rev_head;
  }

  // dhu helper function
  ListNode* helper(ListNode* head, int m, int n, ListNode*& tail) {
    ListNode* prev = 0;
    ListNode* current = head;
    ListNode* next = 0;
    while (current && m <= n) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
      m++;
    }

    if (m <= n)
      return 0;

    tail = next;
    return prev;
  }

};

// Dropbox solution
ListNode* ReverseBetween(ListNode *head, int m, int n) {
  //if (m == n) return head;

  ListNode** h = &head; //the start of list for reversing
  n = n - m + 1; //how many nodes need to be reversed
  while (--m > 0)
    h = &((*h)->next);

  // Reverse nodes in [m,n]
  ListNode* cur = *h;
  ListNode* pre = NULL;
  ListNode* nxt;
  while (n-- > 0) {
    nxt = cur->next;
    cur->next = pre;
    pre = cur;
    cur = nxt;
  }

  // Make the original first node point to next node of original last
  (*h)->next = cur;
  // Make head point to original last node
  *h = pre;
  
  return head;
}

// wwwyhx: note that here n is the number of nodes that will be reversed
ListNode* wwwyhx(ListNode* pHead, int nStart, int n) {
  if (NULL == pHead || nStart < 1 || n < 1)
    return pHead;

  ListNode* pX = NULL;
  ListNode* pIter = pHead;
  for (int i = 1; i < nStart && pIter != NULL; i++) {
    pX = pIter;
    pIter = pIter->next;
  }
  
  if (pIter == NULL) 
    return pHead;
  
  ListNode* pEnd = pIter;
  ListNode* pPrev = NULL;
  for (int i = 0; i < n && pIter != NULL; i++) {
    ListNode* pTmp = pIter->next;
    pIter->next = pPrev;
    pPrev = pIter;
    pIter = pTmp;
  }

  pEnd->next = pIter;
  if (NULL == pX)
    return pPrev;
  
  pX->next = pPrev;
  return pHead;
}

// dhu test harness
int main() {
  ListNode* n1 = new ListNode(1);
  ListNode* n2 = new ListNode(2);
  ListNode* n3 = new ListNode(3);
  ListNode* n4 = new ListNode(4);
  ListNode* n5 = new ListNode(5);

  n1->next = n2;
  n2->next = n3;
  n3->next = n4;
  n4->next = n5;

  //print(n1);

  
  /*
  Solution foo;
  ListNode* rev = foo.reverseBetween(n1, 1, 4);
  if (!rev) {
    //print(n1);
    cout << "Fail" << endl;
    return 0;
  }
  */

  //ListNode* rev = ReverseBetween(n1, 1, 4);

  ListNode* rev = wwwyhx(n1, 1, 3);

  print(rev);

}
