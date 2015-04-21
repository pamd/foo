#include <string>
#include <iostream>

using namespace std;

// Transform S into T.
// For example, S = "abba", T = "$#a#b#b#a#$".
// $ signs are appended to each end to avoid bounds checking
string preProcess(const string& s) {
  int n = s.length();
  if (n == 0) return "$$";
  string ret = "$";
  for (int i = 0; i < n; i++)
    ret += "#" + s.substr(i, 1);
 
  ret += "#$";
  return ret;
}
 
string longestPalindrome(const string& text) {
  string T = preProcess(text);
  int n = T.length();
  int *P = new int[n];
  // Set all elements in P to 0
  for (int i = 0; i < n; i++) 
    P[i] = 0;

  for (int i = 1; i < n; i++) {
    if (i < 10)
      cout << "0" << i << " ";
    else
      cout << i << " ";
  }
  cout << endl;
  
  int C = 0, R = 0;
  for (int i = 1; i < n-1; i++) {
    int i_mirror = 2*C-i; // equals to i' = C - (i-C)
 
    P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
 
    // Attempt to expand palindrome centered at i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
      P[i]++;
 
    // If palindrome centered at i expand past R,
    // adjust center based on expanded palindrome.
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }

    // Print out elements in P (for debugging only)
    for (int k = 1; k < n; k++)
      cout << P[k] << "  ";
    cout << "i: " << i << ", C: " << C << ", R: " << R << endl; 

  }
 
  // Find the maximum element in P.
  int maxLen = 0;
  int centerIndex = 0;
  for (int i = 1; i < n-1; i++) {
    if (P[i] > maxLen) {
      maxLen = P[i];
      centerIndex = i;
    }
  }
  delete[] P;
 
  return text.substr((centerIndex - 1 - maxLen) / 2, maxLen);
}

int main() 
{
  string test("babcbabcbaccba");
  cout << longestPalindrome(test) << endl;

  return 0;
}
