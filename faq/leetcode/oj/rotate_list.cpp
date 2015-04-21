/* leetcode: Given a list, rotate the list to the right by k places, 
 * where k is non-negative.
 * For example:
 * Given 1->2->3->4->5->NULL and k = 2,
 * return 4->5->1->2->3->NULL.
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
  ListNode *rotateRight(ListNode *head, int k) {
    if (!head)
      return 0;

    int len = 0;
    ListNode* curr = head;
    while (curr) {
      len++;
      curr = curr->next;
    }

    if (k % len == 0)
      return head;

    k %= len;
    ListNode* prev = 0;
    // First reverse the whole list
    while (head) {
      ListNode* next = head->next;
      head->next = prev;
      prev = head;
      head = next;
    }

    ListNode* border = prev;
    head = prev;
    prev = 0;
    // Now reverse the first k nodes
    for (int i = 1; i <= k; i++) {
      ListNode* next = head->next;
      head->next = prev;
      prev = head;
      head = next;
    }

    ListNode* new_head = prev;
    // Reverse the other (len - k) nodes
    prev = 0;
    while (head) {
      ListNode* next = head->next;
      head->next = prev;
      prev = head;
      head = next;
    }

    border->next = prev;
    return new_head;
  }


};

// Dropbox solution: for linked list, dhu approach seems to be an overkill.

// Move top k nodes to the tail of linked list
ListNode * RotateLeft(ListNode *head, ListNode *tail, int k) {
  if (k <=0)
    return head;

  ListNode * p = head;
  while (--k > 0)
    p = p->next;

  tail->next = head;
  head = p->next;
  p->next = NULL;

  return head;
}

ListNode * RotateRight(ListNode *head, int k) {
  if (head == NULL)
    return head;
  
  int length = 1;
  ListNode* p = head;
  while (p->next != NULL) 
    p = p->next, ++length;
  
  k = k % length;

  // Rotate to the right by k is identical to rotate to the left by (length - k);
  return RotateLeft(head, p, length - k);
}

int main(int argc, char** argv) {
  ListNode nodes[21];
  for (int i = 0; i < 20; ++i) {
    nodes[i].val = i+1;
    nodes[i].next = nodes+i+1;
  }
  nodes[20].val = 21;
	
  ListNode* head = RotateRight(nodes, 147);
  while(head) {
    printf("%d,", head->val);
    head = head->next;
  }

  return 0;
}
