/* ----------------------------------------------------------
 * http://www.mitbbs.com/article_t/JobHunting/32401359.html
 * http://get-that-job-at-google.blogspot.com/2013/02/rocketfuel-codesprint-at-iit-bombay.html
 * ----------------------------------------------------------
 *
 * Rocket Fuel Problem: Given a deque that supports only push_front, 
 * push_back and pop_back, we want to push the values from 1 to N
 * into the deque in sorted order, and pop them out too. We can do
 * pop_back at any time. If we are given a permutation of 1~N, how 
 * can we push and pop elements so that the elements that are popped 
 * out will be in the order of the given permutation?
 *
 * For example, suppose N = 5, and pop-out order is { 2, 3, 1, 4, 5 },
 * the operations required should be: 
 *
 *   push back 1 
 *   push back 2 
 *   pop back 2
 *   push back 3
 *   pop back 3
 *   pop back 1
 *   push back 4
 *   pop back 4
 *   push back 5
 *   pop back 5
 *
 * To solve this problem, we maintain a deque of ranges, and initialize 
 * the expected value to 1. Then we scan the  input pop order array from 
 * left to right. 
 * Suppose the current element is x and x > expected_value,
 * we push range 1~1 to the deque, and push 2~(x-1) to both front and back
 * sides of the deque. The corresponding sequences will be to push 2~(x-1),
 * but we do not know whether it is push_back or push_front yet.
 *
 * If x == expected_value, we simply push_back and pop_back x;
 *
 * If x < expected_value, we keep popping back the ranges in the deque,
 * until either the deque is empty, or the last range in the deque covers
 * x. Then we pop_back x, and change the last range's upper limit. If last
 * range is descending from left to right, then x was push_back-ed into the
 * deque; otherwise x was push_front-ed into the deque.
 *
 * If we popped out all ranges but couldn't find any range that covers x, 
 * then the input pop list is not valid.
 *
 * Note that the operations may not be unique. For example, if pop order is
 * { 1, 2 }, we have the following two approaches:
 *
 * #1: Always pop back the element when it is ready.
 *      push back 1
 *           pop back 1
 *      push back 2
 *           pop back 2
 *
 * #2: When an element is ready for opo back, hold it and keep pushing 
 & elements to the front.
 *      push back  1
 *      push front 2
 *           pop back 1
 *           pop back 2
 *
 * But in the algorithm above, if input pop list has a valid solution
 * in #2, then it must have a valid solution in approach #1, because
 * in #2, the new elements are only added to the front side, but in #1,
 * we consider adding new elements on both front and back sides.
 *
 */

#include <iostream>
#include <deque>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

struct Operation {
  Operation(int v = 0, int d = 0) : value(v), direction(d) { }

  void print() const {
    if (direction == 1) {
      cout << "push front: " << value;
    }
    else if (direction == 2) {
      cout << " push back: " << value;
    }
    else if (direction == -1) {
      cout << "\t" << "pop back: " << value;
    }
    else {
      cout << "OPERATION UNKNOWN: " << value;
    }

    cout << endl;
  }

  int value; // Element value: 1~N

  // Operation flag: -1 is pop_back, 1 is push_front, 2 is push_back,
  // 0 is unknown push
  int direction; 
};

// Range structure
struct Range {
  Range(int l = 0, int u = 0, int i = 0) : lower(l), upper(u), increment(i) { }

  bool covers(int x) {
    return x >= lower && x <= upper;
  }

  int lower, upper;
  int increment; // increment from back side to front side
};

// Return true is input pop_order is valid; false otherwise.
bool get_seq(const vector<int>& pop_order, vector<Operation>& seq) {
  if (pop_order.size() == 0)
    return true;

  // Map pushed value to the index in seq so that 
  // we can modify that operation's direction later.
  unordered_map<int, int> push_val2seq_idx;
  push_val2seq_idx[1] = 0; // "1" is always pushed in as the first operation

  // Keep track of elements that have been popped out
  unordered_set<int> popped_val; 

  // Keep track of possibkle ranges in the front and back of the deque
  deque<Range> ranges;

  int expect = 1;
  for (size_t i = 0; i < pop_order.size(); i++) {
    int current = pop_order[i];
    if (current > expect) {
      // If ranges is empty, only push_back one range;
      // If ranges is not empty, add two ranges, 
      // one on back side, the other on front side
      if (ranges.empty()) {
	ranges.push_back(Range(expect, current - 1, -1));
      } 
      else {
	ranges.push_back(Range(expect, current - 1, -1));
	ranges.push_front(Range(expect, current - 1, 1));
      }

      // Add push operations into seq, 
      // (but we do not know they are push_back or push_front yet.
      while (current != expect) {
	seq.push_back(Operation(expect, 0));
	push_val2seq_idx[expect] = seq.size() - 1;
	++expect;
      }

      // Push_back current, then pop_back current
      seq.push_back(Operation(current, 2));
      seq.push_back(Operation(current, -1));
      popped_val.insert(current);
      expect++;
    }

    else if (current < expect) {
      while (ranges.size() && !ranges.back().covers(current))
	ranges.pop_back();

      if (ranges.empty())
	return false;
      
      if (ranges.back().increment == -1) {
	if (ranges.back().lower == current)
	  ranges.pop_back();
	else
	  ranges.back().upper = current - 1;
	
	int idx = push_val2seq_idx[current];
	seq[idx].direction = 2;
	seq.push_back(Operation(current, -1));
	popped_val.insert(current);
      }
      else {  // If ranges.back().increment == 1
	int start = ranges.back().lower;
	while (popped_val.find(start) != popped_val.end()) {
	  ++start;
	}
	if (start != current)
	  return false;

	if (ranges.back().upper == current) 
	  ranges.pop_back();
	else
	  ranges.back().lower = current + 1;

	int idx = push_val2seq_idx[current];
	seq[idx].direction = 1;
	seq.push_back(Operation(current, -1));
	popped_val.insert(current);
      }
    }

    else { // current == expect
      // Push_back current, then pop_back current
      seq.push_back(Operation(current, 2));
      seq.push_back(Operation(current, -1));
      popped_val.insert(current);
      ++expect;
    }

  }

  return true;
}

// Test harness
int main() {
  vector<Operation> seq;
  int a[] = { 2, 3, 1, 4, 5 };
  //int a[] = { 4, 1, 3, 2, 5 }; // Invalid input
  //int a[] = { 2, 3, 5, 1, 4 };

  vector<int> pop_order(a, a + sizeof(a) / sizeof(int));

  bool stat = get_seq(pop_order, seq);
  if (!stat) {
    cout << "Invalid input" << endl;
  }
  else {
    for (size_t i = 0; i < seq.size(); i++) {
      seq[i].print();
    }
  }

  return 0;
}
