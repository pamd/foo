/* Facebook question:
 * http://www.mitbbs.com/article_t/JobHunting/32260339.html
 * String s is called unique if all the characters of s are different.
 * String s2 is producible from string s1, if we can remove some 
 * characters of s1 to obtain s2.
 * String s1 is more beautiful than string s2 if length of s1 is more 
 * than length of s2 or they have equal length and s1 is lexicographically 
 * greater than s2.
 * Given a string s, find the most beautiful unique string that is 
 * producible from s.
 * Sample Input:  babab 
 * Sample Output: ba
 * Explanation: In the above test case all unique strings that are producible 
 * from s are "ab" and "ba" and "ba" is more beautiful than "ab".
 *
 * Pseudocode by lanti:
 *
 * bool used[26]; // char that have been used
 * int pos; // s[pos..len) haven't been explored
 * while pos < len
 * 1. scan s[pos] to s[len-1], suppose s[pos..len) has k non-used chars, 
 * 2. look for newpos such that s[newpos..len) has k non-used chars and s[newpos] 
 *    is the largest possible. this might need to be done from s[len-1] back to 
 *    s[pos]
 * 3. set used[s[newpos]] = 1
 *    the s[newpos] found in this order is the solution.
 * 
 */

#include <string>
#include <iostream>
#include <unordered_map>
#include <cassert>
#include <vector>

using namespace std;

// longway2008
void convertToMostBeautiful(string& s) {
  unordered_map<char, int> count;
  unordered_map<char, bool> chosen;
  for (size_t i = 0; i < s.length(); i++) {
    count[s[i]]++;
    chosen[s[i]] = false;
  }

  int tail = -1;
  for (size_t i = 0; i < s.size(); i++) {
    if (chosen[s[i]]) 
      count[s[i]]--;
    else {
      while (tail >= 0 && s[tail] <= s[i] && count[s[tail]] > 1) {
	chosen[s[tail]] = false;
	count[s[tail--]]--;
      }

      s[++tail] = s[i];
      chosen[s[i]] = true;
    } 
  }

  s.resize(tail + 1);
}

// By orzgod: same idea as longway2008, but code is easier to understand.
// Time complexity: O(n)
string orzgod(const string& s){
  const int N = 256;
  int len = s.size();
  if (len <= 1) 
    return s;
  
  int count[N] = { 0 };
  bool used[N] = { false };
  
  for (int i = 0; i < len; i++) 
    count[s[i]]++;
  
  vector<char> res;
  for(int i = 0; i < len; i++) {
    char ch = s[i];
    count[ch]--;
    if (used[ch]) 
      continue;

    while (res.size() > 0) {
      char ch2 = res.back();
      if (ch2 < ch && count[ch2] > 0) {
	res.pop_back();
	used[ch2] = false;
      }
      else
	break;
    }
    res.push_back(ch);
    used[ch] = true;
  }
  
  return string(res.begin(), res.end());
}


// Test harness
int main() {
  string s("nlhthgrfdnnlprjtecpdrthigjoqdejsfkasoctjijaoebqlrgaiakfsbljmpibkidjsrtkgrdnqsknbarpabgokbsrfhmeklrle");
  string ret = orzgod(s);
  cout << ret << endl;
  
  //output: tsocrpkijgdqnbafhmle
  string ans("tsocrpkijgdqnbafhmle");
  assert(ret == ans);

  return 0;
}

// input: zakbkza, output: abkz.
