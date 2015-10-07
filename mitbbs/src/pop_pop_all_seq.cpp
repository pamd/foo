// For a deque that supports push_back, push_front, pop_back and pop_front,
// if we push { 1, 2, 3, 4, 5 }, mingled with pop operations when possible
// (aka. the deque is not empty), what are all possible pop-out sequences?
//
// First we get all possible sequences of push and pop, without distinguishing 
// the two pushes and the two pops. Each sequence will include 5 pushes and 5 pops.
// We use "+' to denote pushes and '-' for pops. So each sequence is a 10-character
// string that includes only "+" and "-".
// The number of valid sequences is catalan(5) = 42. 
//
// Next, each operation in a seqeunce can have two options:
// "+" can be push_back or push_front; "-" can be pop_back or pop_front. So each sequence
// includes 2^10 = 1024 choices, some of which will generate same pop-out sequences though.  

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>

using namespace std; 

void catalan5(int push_count, int pop_count, string& curr, vector<string>& seqs) {
  if (pop_count == 5) {
    seqs.push_back(curr);
    return;
  }

  if (push_count < 5) {
    curr[push_count + pop_count] = '+';
    catalan5(push_count + 1, pop_count, curr, seqs);
  }

  if (push_count > pop_count) {
    curr[push_count + pop_count] = '-';
    catalan5(push_count, pop_count + 1, curr, seqs);
  }
}

// Generate pop sequences
void get_pop_seq(const string& seq, int level, int value, const deque<int>& dq,
   const string& curr, vector<string>& pop_seqs)
{
  if (level == 10) {
    pop_seqs.push_back(curr);
    return;
  }

  if (seq[level] == '+') {
    deque<int>dq1(dq);
    dq1.push_back(value);
    get_pop_seq(seq, level + 1, value + 1, dq1, curr, pop_seqs);

    deque<int>dq2(dq);
    dq2.push_front(value);
    get_pop_seq(seq, level + 1, value + 1, dq2, curr, pop_seqs);
  }

  if (seq[level] == '-') {
    deque<int>dq1(dq);
    string curr1(curr);
    curr1.push_back('0' + dq1.back());
    dq1.pop_back();
    get_pop_seq(seq, level + 1, value, dq1, curr1, pop_seqs);

    deque<int>dq2(dq);
    string curr2(curr);
    curr2.push_back('0' + dq2.front());
    dq2.pop_front();
    get_pop_seq(seq, level + 1, value, dq2, curr2, pop_seqs);
  }
}

// Test
int main() {
  string curr(10, '\0');
  vector<string> seqs;
  catalan5(0, 0, curr, seqs);

  vector<string> pop_seqs;
  deque<int> dq;
  for (size_t i = 0; i < seqs.size(); ++i) {
    string curr_pop_seq;
    get_pop_seq(seqs[i], 0, 1, dq, curr_pop_seq, pop_seqs);
  }

  //cout << pop_seqs.size() << endl;
  set<string> pop_uniq(pop_seqs.begin(), pop_seqs.end());
  //for (set<string>::iterator it = pop_uniq.begin(); it != pop_uniq.end(); ++it) {
  //  cout << *it << endl;
  //}
  cout << "Total: " << pop_uniq.size() << endl;

  string tmp("12345");
  while (next_permutation(tmp.begin(), tmp.end())) {
    if (pop_uniq.find(tmp) == pop_uniq.end()) {
      cout << "not found: " << tmp << endl;
    }
  }

  return 0;
}

// Total: 116
// not found: 51324
// not found: 51342
// not found: 52314
// not found: 52341
