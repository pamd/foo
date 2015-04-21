/* Generate permutation of an input string (assume that all characters in 
 * input string are unique. 
 * Based on algorithm on "Programming Interview Exposed" book. */

#include <iostream>
#include <vector>

using namespace std;

void permute(string inputStr, string& outStr, 
	     vector<bool>& used, int level)
{
  if (level == inputStr.length()) { 
    cout << outStr << endl;
    return;
  }

  for (int i = 0; i < inputStr.size(); i++) {
    if (used[i])
      continue;
    outStr[level] = inputStr[i];
    used[i] = true;
    permute(inputStr, outStr, used, level + 1);
    used[i] = false;
  }

}


int main()
{
  string str = "abc";
  string outStr = "   ";
  vector<bool> used;	
  for (int i = 0; i < str.length(); i++) 
    used.push_back(false);

  permute(str, outStr, used, 0);

  return 0;
}


