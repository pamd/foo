/* Leetcode OJ: Given a linked list, reverse the nodes of 
 * a linked list k at a time and return its modified list.
 * If the number of nodes is not a multiple of k, then 
 * left-out nodes in the end should remain as is.
 * You may not alter the values in the nodes, only nodes 
 * itself may be changed. Only constant memory is allowed.
 * For example,given this linked list: 1->2->3->4->5
 * For k = 2, you should return: 2->1->4->3->5
 * For k = 3, you should return: 3->2->1->4->5
 */

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

// 128ms for large dataset
class Solution {
public:
  ListNode *reverseKGroup(ListNode *head, int k) {
    if (!head || k == 1)
      return head;

    int counter = 0;
    ListNode* new_head = 0;          // New head node that will be returned
    ListNode* rev_start = head;      // Starting point of each reverse section
    ListNode* prev_tail = 0;         // Tail of previous reverse section
    ListNode* tail_after_rev = head; // Tail node after each reverse section is done
    ListNode* current = head;
    while (current) {
      counter++;
      current = current->next;

      // Found a k-node-group
      if (counter % k == 0) {
	// Reverse nodes from rev_start to current	
	ListNode* prev = 0;
	tail_after_rev = rev_start;
	for (int i = 1; i <= k; i++) {
	  ListNode* next = rev_start->next;
	  rev_start->next = prev;
	  prev = rev_start;
	  rev_start = next;
	}

	if (!new_head)
	  new_head = prev;
	if (prev_tail)
	  prev_tail->next = prev;
	
	prev_tail = tail_after_rev;
      }
    }

    if (!new_head)
      return head;

    // If the last section has less than k nodes, just link it with the new tail
    if (counter % k) 
      prev_tail->next = rev_start;

    return new_head;
  }
};

/* Dropbox solution: code is more compact because it uses pointer to pointer. 
 * --------------------------------------------------------------------------*/

// Helper function: reverse nodes from head to tail (tail node excluded) 
void ReverseList(ListNode ** head, ListNode* tail) {
  ListNode* p = *head;
  ListNode* q = tail;
  ListNode* n;

  // Make next pointer of node point to previous node
  while (p != tail) {
    n = p->next;
    p->next = q;
    q = p;
    p = n;
  }

  // Make head pointer to new start
  *head = q;
}

// Main algorithm
ListNode *ReverseNodesink_Group(ListNode *head, k) {
  ListNode** h = &head;
  ListNode*  t = head;
  ListNode*  n = head;
  
  while (1) {
    int count = k;
    while (--count > 0 && t != NULL) {
      t = t->next;
    }

    if (t == NULL) 
      break;
        
    // After reverse the list, the head node would be the last node,
    // and pointer to the next segment, we need to reserve this node 
    // to find next start point.
    n = *h;
    ReverseList(h, t->next);
    
    // Begin next reverse
    h = &n->next;
    t = n->next;
  }

  return head;    
}
