#include <iostream>
//#include <stdlib.h>

using namespace std;

struct ListNode {
  ListNode(int val, ListNode* np = NULL) { 
    dat = val; 
    next = np; 
  }

  int dat;
  ListNode* next;
};

void print(ListNode* np) {
  while (np) {
    cout << np->dat << " => ";
    np = np->next;
  }
  cout << "NULL" << endl;
}

// dhu implementation
ListNode* reverse_recursive(ListNode* head, ListNode* prev) {
  if (!head)
    return prev;

  ListNode* next = head->next;
  head->next = prev;
  prev = head;
  return reverse_recursive(next, prev);
}

// http://www.mitbbs.com/article_t/JobHunting/31971469.html
// input is the head of the list
// return the new head of reverse list
ListNode* reverse_mitbbs(ListNode* head)
{
  if(!head || !head->next)
    return head;

  ListNode* t = head->next;
  head->next = NULL;
  ListNode* nhead = reverse_mitbbs(t);
  t->next = head;
  return nhead;
}

int main() {
  //ListNode* n1 = NULL;

  ListNode* n1 = new ListNode(1);
  ListNode* n2 = new ListNode(2);
  ListNode* n3 = new ListNode(3);
  ListNode* n4 = new ListNode(4);
  n1->next = n2;
  n2->next = n3;
  n3->next = n4;
  print(n1);

  //ListNode* new_head = reverse_recursive(n1, NULL);
  ListNode* new_head = reverse_mitbbs(n1);
  print(new_head);

  return 0;
}

