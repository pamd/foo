/* Given a singly linked list where each node is a digit between 0 and 9.
 * Determine whether it is a palindrome.
 * If extra space is allowed, we can either make a reversed copy of the input list, 
 * then compare each node; or we can read each node from the head, and put the digit 
 * into a stack, then compare the digits in the stack with the nodes in the list.
 *
 * The following recursive solution is copie from Career Cup Chapter 2.
 * It does not use explicit space.
 */

#include <iostream>

using namespace std;

struct ListNode {
  ListNode(int i) : val(i), next(0) { }

  int val;
  ListNode* next;
};

int getSize(const ListNode* head) {
  int len = 0;
  while (head) {
    len++;
    head = head->next;
  }
  
  return len;
}

int recursive_helper(const ListNode* head, int length, ListNode*& next) {
  if (length == 1) {
    next = head->next;
    return true;
  }

  if (length == 2) {
    int tmp = next->val;
    next = head->next->next;
    return head->val == tmp;
  }

  if (recursive_helper(head->next, length - 2, next) && head->val == next->val) {
    next = next->next;
    return true;
  }

  return false;
}
 
bool isPalindrome(const ListNode* head) {
  int length = getSize(head);
  if (length <= 1)
    return true;

  ListNode* next = head->next;
  return recursive_helper(head, length, next);
}

int main() {
  ListNode* n1 = new ListNode(1);
  ListNode* n2 = new ListNode(2);
  //ListNode* n3 = new ListNode(3);
  ListNode* n4 = new ListNode(2);
  ListNode* n5 = new ListNode(1);

  
  n1->next = n2;
  n2->next = n4;
  //n3->next = n4;
  //n4->next = n5;
  

  if (isPalindrome(n1)) 
    cout << "yes" << endl;
  else
    cout << "no" << endl;
}
