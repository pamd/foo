/* Leetcode OJ: Decode Ways
 * A message containing letters from A-Z is being encoded to numbers using the following mapping:

 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 * Given an encoded message containing digits, determine the total number of ways to decode it.

 * For example,
 * Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).

 * The number of ways decoding "12" is 2.
 *
 * Passed in OJ, 16ms  for large dataset.
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
  int numDecodings(string s) {
    if (s.size() == 0 || s[0] == '0')
      return 0;

    vector<int> dp(s.size(), -1);
    return count(s, 0, dp);
  }
    
  int count(const string& str, size_t idx, vector<int>& dp) {
    if (idx == str.size())
      return 1;

    if (dp[idx] != -1)
      return dp[idx];
    
    if (str[idx] == '0') {
      dp[idx] = 0;
      return 0;
    }

    if (idx == str.size() - 1) {
      dp[idx] = 1;
      return 1;
    }

    int foo = (str[idx] - '0') * 10 + (str[idx + 1] - '0');
    if (foo > 26) {
      dp[idx] = count(str, idx + 1, dp);
      return dp[idx];
    }

    dp[idx] = count(str, idx + 1, dp) + count(str, idx + 2, dp); 
    return dp[idx];
  }
};

/* Dropbox solution:
**  Dynamic Programming
**  ways[i] means the ways for decoding from ith character to the end of the string
**  then we could have formula as below:
**	
**  ways[i] =
**	      0, when s[i] = '0'
**	      ways[i+1], when s[i] and s[i+1] could not combinate to a valid decoding
**	      ways[i+1] + ways[i+2] otherwise
*/

int NumDecodings(string s) 
{
  int len = s.length();
  if (len == 0) 
    return 0;
  
  int ways[len+1];
  //this value is set for easy calculation for last two numbers
  ways[len] = 1; 

  //the ways decoding for last number
  ways[len-1] = s[len-1] == '0'? 0 : 1; 
  for (int i = len-2; i >= 0; --i) {
    char c0 = s[i];
    if (c0 == '0') {
      ways[i] = 0;
      continue;
    }

    //decode current number only
    ways[i] = ways[i+1];
    
    //decode with next number to be two
    char c1 = s[i+1];
    //valid two numbers decoding
    if (c0 == '1' || (c0 == '0' && c1 != '0')  || (c0 == '2' && c1 <= '6'))
      ways[i] += ways[i+2];
    
    //We could know that when we get countinious 0s, the final result would be 0
    // if (ways[i] == 0 && ways[i+1] == 0)
    // {
    // 	ways[0] = 0;
    // 	break;
    // }
  }
  return ways[0];
}

// Test harness
int main() {
  string str("230");
  Solution foo;
  cout << foo.numDecodings(str) << endl;
}

