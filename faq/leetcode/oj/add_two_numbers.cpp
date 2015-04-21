/* leetcode: Add Two Numbers:
 * You are given two linked lists representing two non-negative numbers. 
 * The digits are stored in reverse order and each of their nodes contain 
 * a single digit. Add the two numbers and return it as a linked list.

 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 */

#include <iostream>
#include <stdio.h>

using namespace std;

/**
 * Definition for singly-linked list
 */
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution {
public:
  ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
    ListNode* h1 = l1;
    ListNode* h2 = l2;
    ListNode* head = 0;
    ListNode* prev = 0;
    int carry = 0;
    while (h1 && h2) {
      int val = h1->val + h2->val + carry;
      if (val >= 10) {
	val = val - 10;
	carry = 1;
      }
      else
	carry = 0;

      ListNode* current = new ListNode(val);
      if (!head) {
	head = current;
      }
      else {
	prev->next = current;
      }
      prev = current;
      h1 = h1->next;
      h2 = h2->next;	
    }

    while (h1) {
      int val = h1->val + carry;
      if (val >= 10) {
	val = val - 10;
	carry = 1;
      }
      else
	carry = 0;
      ListNode* current = new ListNode(val);
      if (!head) {
	head = current;
      }
      else {
	prev->next = current;
      }
      prev = current;
      h1 = h1->next;
    }

    while (h2) {
      int val = h2->val + carry;
      if (val >= 10) {
	val = val - 10;
	carry = 1;
      }
      else
	carry = 0;
      ListNode* current = new ListNode(val);
      if (!head) {
	head = current;
      }
      else {
	prev->next = current;
      }
      prev = current;
      h2 = h2->next;
    }

    if (carry) {
      ListNode* tail = new ListNode(carry);
      prev->next = tail;
    }
      
    return head;
  }
};

// Online solution
ListNode* AddTwoNumbers(ListNode *l1, ListNode *l2) 
{
  if (!l1) return l2;
  if (!l2) return l1;

  int val = l1->val + l2->val;
  bool carried = (val > 9);
  ListNode* head = new ListNode(val % 10);
  ListNode* p = head;
    
  l1 = l1->next;
  l2 = l2->next;
  
  // Add up number in each node
  while (l1 && l2) {
    val = l1->val + l2->val + (carried? 1 : 0);
    carried = (val > 9);
    p->next = new ListNode(val % 10);
    
    l1 = l1->next;
    l2 = l2->next;
    p = p->next;
  }

  // Add up the remain numbers with carried
  ListNode* remain = l1? l1 : l2;
  while(remain) {
    val = remain->val + (carried? 1 : 0);
    carried = (val > 9);
    p->next = new ListNode(val%10);
    
    p = p->next;
    remain=remain->nex;
  }
    
  // If there still has carried, add '1'
  if (carried)
    p->next = new ListNode(1);

  return head;
}
