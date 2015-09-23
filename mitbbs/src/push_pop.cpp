// Deque that supports push_back, push_front and pop_back, but not pop_front.
// Code is revised from:
// http://www.mitbbs.com/article_t/JobHunting/32613553.html

#include <vector>
#include <string>
#include <deque>
#include <iostream>
#include <map>

using namespace std;

// MITBBS:
// 假设你已经维护了一个堆栈到当前状态
// front - > end:  1, 下个输入 3
// 如何决定push 前还是后？
// 在原来输入顺序里，3是在1的后面的，所以要保证pop 1在3前，只能push 3在front。
// 那么现在 堆栈状态： 3，1
// 基于这个原则：
//   1) 如果当前数字的原始顺序在back的前面 =〉push_back 保证先输出;
//   2) 如果当前数字的原始顺序在front的后面 =〉push_front 保证后输出;
// 如果与两个规则抵触即， 在back和front的中间，不可能。直接返回：

// "25134" works, but "25143" is impossible.
vector<string> get_operations(const string& seq) {
   vector<string> operations;

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
      else if (positions[dq.front()] < positions[i]) {
         dq.push_front(i);
         string action("push_front\t");
         action.push_back('0' + i);
         operations.push_back(action);
      }
      else { // Impossible to get the sequence, exit the loop.
         operations.clear();
         break;
      }
      // In dq, the positions of a value at the back is always less than
      // the position of a value closer to the front. In another word,
      // the positions of these values are sorted, with the minimum at
      // the back side and the maximum at the front side.


      while (!dq.empty() && dq.back() == seq[j] - '0') {
         dq.pop_back();
         string action("pop_back\t");
         action.push_back(seq[j]);
         operations.push_back(action);
         ++j;
      }
   }

   return operations;
}

// Test harness
int main() {
   string seq("25134");
   vector<string> ret = get_operations(seq);

   if (ret.size() == 0) {
      cout << "Impossible" << endl;
   }
   else {
      for (size_t i = 0; i < ret.size(); ++i) {
         cout << ret[i] << endl;
      }
   }

   return 0;
}
