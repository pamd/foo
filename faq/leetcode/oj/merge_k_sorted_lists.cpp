/* Leetcode OJ: Merge k sorted linked lists and return it as one sorted list. 
 * Analyze and describe its complexity.
 */

#include <vector>
#include <map>
#include <iostream>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(0) {}
};

// dhu solution #1: use std::multimap. 76ms for large dataset.
// Time complexity: nlgk, where n is the total number of nodes in k lists
class Solution {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    ListNode* head = 0;
    if (lists.size() == 0)
      return head;

    multimap<int, size_t> val2idx;
    for (size_t i = 0; i < lists.size(); i++) {
      if (lists[i])
	val2idx.insert(make_pair<int, size_t>(lists[i]->val, i));
    }

    ListNode* curr = 0;
    while (val2idx.size()) {
      int min = val2idx.begin()->first;
      int idx = val2idx.begin()->second;
      val2idx.erase(val2idx.begin());

      if (!curr) {
	head = lists[idx];
	curr = head;
      }
      else {
	curr->next = lists[idx];
	curr = curr->next;
      }
      
      lists[idx] = lists[idx]->next;
      if (lists[idx])
	val2idx.insert(make_pair<int, size_t>(lists[idx]->val, idx));
    }
    
    return head;
  }
};

// dhu solution #2: use std::priority_queue (anson627 used same idea).
// --------------------------------------------------------------------
// Comparison class defined for std::priority_queue
class CmpNodes {
public:
  bool operator()(const ListNode* left, const ListNode* right) {
    return left->val > right->val;
  }

};

class Solution_dhu2 {
public:
  ListNode *mergeKLists(vector<ListNode *> &lists) {
    ListNode* head = 0;
    ListNode* tail = 0;
    priority_queue<ListNode*, vector<ListNode*>, CmpNodes> Q;
    for (size_t i = 0; i < lists.size(); i++) {
      if (lists[i])
	Q.push(lists[i]);
    }

    while (!Q.empty()) {
      ListNode* curr = Q.top();
      Q.pop();
      if (curr->next) 
	Q.push(curr->next);
        
      if (!head) {
	head = curr;
	tail = curr;
      }
      else {
	tail->next = curr;
	tail = curr;
      }
    }

    return head;
  }

};
