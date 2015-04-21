/**************************************************************************
 * Knuth-Morris-Pratt string searching algorithm that uses an explicit DFA, 
 * based on the Java code on: 
 * Sedgewick "Algorithms" 4th edition, page 768.
 * This approach builds a 2-D DFA table that has R rows and M 
 * columns, in which R is the number of chars in alphabet, 
 * M is the length of needle string. So space complexity is
 * O(R * M). The code seems to be more compact. 
 **************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Build 2-D table of DFA
void build_dfa(const string& needle, vector<vector<int> >& dfa) {
  int M = needle.length();

  int R = dfa.size(); // Number of chars in alphabet
  dfa[needle[0]][0] = 1; // Initialization
 
  int X = 0;
  for (int j = 1; j < M; j++) { 
    for (int c = 0; c < R; c++)
      dfa[c][j] = dfa[c][X];
    
    dfa[needle[j]][j] = j + 1;
    X = dfa[needle[j]][X];
  }

}

// Search needle in haystack
// Memory limit exceeded in Leetcode OJ large dataset.
int sedgewick(const string& haystack, const string& needle) {
  int N = haystack.length();
  int M = needle.length();

  int R = 256; // Number of chars in alphabet
  vector<vector<int> > dfa(R, vector<int>(M, 0));
  build_dfa(needle, dfa);

  int i = 0; // Index of haystack string that is being matched now
  int j = 0; // Index of needle string that is being matched now
  for (; i < N && j < M; i++)
    j = dfa[haystack[i]][j];
  
  if (j == M) 
    return i - M; // found needle string
  
  return -1;  // NOT found
}

// Test harness
int main(int argc, char** argv) {
  //               01234567890123456789
  string haystack("ABAAABABABABABAB");
  string needle("ABABAB");

  cout << sedgewick(haystack, needle) << endl;

  return 0;
}

