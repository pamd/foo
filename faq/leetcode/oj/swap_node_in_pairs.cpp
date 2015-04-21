/* Leetcode OJ: Given a linked list, swap every two adjacent nodes 
 * and return its head. For example, given 1->2->3->4, you should 
 * return the list as 2->1->4->3.
 * Your algorithm should use only constant space. You may not modify 
 * the values in the list, only nodes itself can be changed.
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
  ListNode* swapPairs(ListNode *head) {
    // If the list has less than two nodes
    if (!head || !head->next)
      return head;
        
    ListNode* ret = head->next;
    ListNode* tail = 0;
    while (head && head->next) {
      ListNode* next = head->next;
      ListNode* tmp = next->next;
      next->next = head;
      if (tail)
	tail->next = next;
      tail = head;
      head = tmp;
    }

    // Tail must be a valid node, because the list has at least two nodes 
    tail->next = head;

    return ret;
  }
};

// Dropbox solution: use pointer to pointer, 
// seems fancy, but harder to follow
//--------------------------------------------------------------------
void ReverseList(ListNode ** head, ListNode* tail) {
  ListNode* p = *head;
  ListNode* q = tail;
  ListNode* n;

  // Make 'next' pointer of node point to previous node
  while( p != tail) {
    n = p->next;
    p->next = q;
	
    q = p;
    p = n;
  }

  // Make head pointer to new start
  *head = q;
}

ListNode *SwapPairs(ListNode *head) {
  ListNode ** h = &head;
  ListNode * t = head;
  ListNode * n = head;
	
  while(1) {
    int count = 2;
    while(--count > 0 && t != NULL) {
      t = t->next;
    }
    
    if (t == NULL) 
      break;
		
    /* After reverse the list, the head node would be the last node,
     * and pointer to the next segment, we need to reserve this node 
     * to find next start point. */
    n = *h;
    
    ReverseList(h, t->next);
    
    // Begin next reverse
    h = &n->next;
    t= n->next;
  }

  return head;    
}

