/* Leetcode: The count-and-say sequence is the sequence of integers 
 * beginning as follows:
 * 1, 11, 21, 1211, 111221, ...
 * 1 is read off as "one 1" or 11.
 * 11 is read off as "two 1s" or 21.
 * 21 is read off as "one 2, then one 1" or 1211.
 * Given an integer n, generate the n-th sequence.
 * Note: The sequence of integers will be represented as a string.
 * 
 * OJ result: 4ms for large dataset.
 */

#include <iostream>
#include <string>

using namespace std;

// dhu
class Solution {
public:
  string countAndSay(int n) {
    if (n < 1)
      return string();

    string current("1");
    for (int i = 2; i <= n; i++) {
      string next;
      int counter = 1;
      for (size_t j = 1; j < current.size(); j++) {
	if (current[j] == current[j-1])
	  counter++;
	else {
	  next.push_back(counter + '0');
	  next.push_back(current[j-1]);
	  counter = 1;
	}
      }
      next.push_back(counter + '0');
      next.push_back(current[current.size() - 1]);
      current = next;
    }

    return current;
  }

};

// Online solution: almost identical to dhu solution
string CountAndSay(string s) {
  if (s.size() <= 0)return "";

  stringstream sout;
  int count = 1;
  char ch = s[0];
	
  for (size_t i = 1; i < s.size(); ++i) {
    if (s[i] == ch)
      ++count;
    else {
      sout << count << ch;
      count = 1;
      ch = s[i];
    }
  }

  sout << count << ch;
  return sout.str();
}

// Online solution: wrapper function
string CountAndSay(int n) {
  string s = "1";
  
  while(--n > 0)
    s = CountAndSay(s);
  
  return s;
}

// Test harness
int main() {
  Solution foo;
  for (int i = 1; i < 10; i++)
    cout << foo.countAndSay(i) << endl;

  return 0;
}
