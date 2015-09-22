// Suppose a deque supports push_back, push_front, pop_back and pop_front. If we always
// push the values in increasing order (1, 2, ..., n-1, n), can we generate any order 
// by mixing push and pop operations?
// Code is revised from push_pop.cpp.

#include <vector>
#include <string>
#include <deque>
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

vector<string> get_operations(const string& seq) {
   vector<string> operations;
   string pop_seq;

   // positions maps the seqeunce values (1, 2, ..., n) to their positions
   // (aka. indexes) in seq[]. We can also use std::unordered_map for optimization.
   map<int, int> positions;
   for (int i = 0; i < seq.size(); ++i) {
      positions[seq[i] - '0'] = i;
   }

   deque<int> dq; // "dq" simulates the deque in this problem.

   // i is the number that will be pushed/popped, so it starts at 1, and ends at seq.size().
   // j keeps track of the index in seq[] that will be popped back next.
   for (int i = 1, j = 0; i <= seq.size(); ++i) {
      if (dq.empty() || positions[dq.back()] > positions[i]) {
         dq.push_back(i);
         string action("push_back\t");
         action.push_back('0' + i);
         operations.push_back(action);
      }
      else {
         dq.push_front(i);
         string action("push_front\t");
         action.push_back('0' + i);
         operations.push_back(action);
      }

      // Try both pop_back() and pop_front() 
      while (!dq.empty() && (dq.back() == seq[j] - '0' || dq.front() == seq[j] - '0')) {
	string action;
	if (dq.back() == seq[j] - '0') {
	  dq.pop_back();
	  action = "pop_back\t";
	}
	else {
	  dq.pop_front();
	  action = "pop_front\t";
	}
	action.push_back(seq[j]);
	operations.push_back(action);
	pop_seq.push_back(seq[j]);
	++j;
      }
   }

   if (pop_seq != seq) {
     cout << "seq: " << seq << endl;
     cout << "pop: " << pop_seq << endl;
   }

   return operations;
}

// Test harness
int main() {
   string seq("12345");

   // Test 10 random permutations and print out the results
   for (int i = 0; i < 10; ++i) {
     random_shuffle(seq.begin(), seq.end());
     cout << seq << endl;
     vector<string> ret = get_operations(seq);
     for (size_t i = 0; i < ret.size(); ++i) {
       cout << ret[i] << endl;
     }
     cout << endl;
   }

  // Test all permutations
   cout << "Test all ... ";
   while (next_permutation(seq.begin(), seq.end())) {
     vector<string> ret = get_operations(seq);
   }
   cout << "done" << endl;

   return 0;
}
