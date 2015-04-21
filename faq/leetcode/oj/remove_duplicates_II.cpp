/* Leetcode: Remove Duplicates from Sorted List II
 * Given a sorted linked list, delete all duplicate numbers, leave only 
 * distinct numbers from original list. e.g., 
 * Given 1->2->3->3->4->4->5, return 1->2->5;
 * Given 1->1->1->2->3, return 2->3.
 * Refer to:
 * http://www.mitbbs.com/article_t1/JobHunting/32103027_0_1.html
 */

// Code by longway2008
Node * DeleteDuplicates(Node * head) {
  Node * tail = NULL;
  Node * cur = head;
  head = NULL;
  
  while (cur){
    if (cur->next == NULL || cur->next->val!= cur->val) {
      if (head == NULL) {
	tail = head = cur;
      } 
      else {
	tail->next = cur;
	tail = cur;
      }
      cur = cur->next;
      tail->next = NULL;
    } 
    else {
      int value = cur->val;
      while(cur && cur->val == value ) {
	Node * toBeDeleted = cur;
	cur = cur->next;
	delete toBeDeleted;
      }
    }
  }

  return head;  
}

