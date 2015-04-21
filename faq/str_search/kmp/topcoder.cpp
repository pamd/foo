/* /********************************************************************************* 
 * Another approach in TopCoder tutorial:
 *
 * http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=stringSearching
 *
 * Note the subtle differences between this approach and the wikipedia version.
 *********************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Pay attention! 
// The prefix under index i in the table above is is the string from needle[0] 
// to needle[i - 1] inclusive, so the last character of the string under index 
// i is needle[i - 1].   
//
// dhu: Note that in this approach, DP[0] = 0, 
// but in wikipedia approach, DP[0] is set to -1.
vector<int> build_failure_function(const string& needle) {
  size_t m = needle.size(); // let m be the length of the needle 
  vector<int> table(m + 1, 0);
  for (size_t i = 2; i <= m; i++) {
    // j is the index of the largest next partial match 
    // (the longest suffix/prefix) of the string under index i - 1.
    int j = table[i - 1];
    while (true) {
      // If we can expand the previous largest match to needle[i-1],
      // then increment the match and table[i] is done.
      if (needle[j] == needle[i - 1]) { 
        table[i] = j + 1; 
	break; 
      }
      // If we cannot "expand" the empty string, set table[i] to 0.
      if (j == 0) { 
	table[i] = 0; 
	break; 
      }
      // else go to the next best "candidate" partial match
      j = table[j];

    } // end of "while" loop

  } // end of "for" loop

  return table;
}

// dhu implementation of build_failure_function(). 
// This version does not use the "while" loop inside "for" loop,
// which is easier to understand.
//
// This implementation is almost identical to getOverlap_wiki().
// except that table[0] is set to 0 here, but getOverlap_wiki() 
// sets it to -1.
vector<int> build_failure_function_dhu(const string& needle) {
  size_t m = needle.size(); // let m be the length of the needle 
  vector<int> table(m + 1, 0);
  size_t index = 2;
  int candidate = 0;
  while (index <= m) {
    if (needle[candidate] == needle[index - 1]) { 
      table[index] = candidate + 1; 
      candidate++;
      index++;
    }
    // If candidate is not 0 yet
    else if (candidate) 
      candidate = table[candidate];
    // If candidate is 0, we cannot "expand" the empty string, set table[index] to 0.
    else { 
      table[index] = 0; 
      index++;
    }
  } 

  return table;
}

// Copied from Topcoder tutorial. 
// This approach prints out starting indexes of all 
// occurrences of needle string in haystack.
void topcoder(const string& haystack, const string& needle) {
  size_t n = haystack.size();
  size_t m = needle.size();

  vector<int> table = build_failure_function(needle); 
 
  size_t i = 0; // index of char in needle
  size_t j = 0; // index of char in haystack
  
  while (j < n) {
    // If the current char of haystack "expands" the current match 
    if (haystack[j] == needle[i]) {
      i++; // change the state of the automaton
      j++; // get next char from haystack
      if (i == m) { // match found, print out index at which match starts
	cout << j - m << endl;
	i = table[i];
      }
    }

    // If the current state is not zero (aka. we have not reached the empty 
    // string yet), we try to "expand" the next best (largest) match.
    else if (i > 0) 
      i = table[i];

    // If we have reached the empty string and failed to "expand", we go to 
    // the next char in haystack, the state of automaton remains zero.
    else 
      j++;
  }
}

// TopCoder tutorial:
// -----------------------------------------------------------------------------
// Many problems in programming contests focus more on the properties of KMP's 
// "failure function," rather than on its use for string matching. 
// An example is: Given a string (a quite long one), find all its proper suffixes 
// that are also prefixes of it. All we have to do is just to calculate the 
// "failure function" of the given string and using the information stored in it 
// to print the answer.
// 
// Another typical problem seen quite often is: 
// Given a string, find its shortest substring, such that the concatenation of one 
// or more copies of it results in the original string. 
// 
// Again the problem can be reduced to the properties of the failure function. 
// Let's consider the string: 
//
//                 A B A B A B
//
// and all its proper suffix/prefixes in descending order:

// (1) A B A B
// (2) A B
// (3) /the empty string/

// Every such suffix/prefix uniquely defines a string, which after being "inserted" 
// in front of the given suffix/prefix gives the initial string. In our case:
//
// (1) A B
// (2) A B A B
// (3) A B A B A B
//
// Every such "augmenting" string is a potential "candidate" for a string, 
// the concatenation of several copies of which results in the initial string. 
// This follows from the fact that it is not only a prefix of the initial string 
// but also a prefix of the suffix/prefix it "augments". But that means that now 
// the suffix/prefix contains at least two copies of the "augmenting" string as a 
// prefix (since it's also a prefix of the initial string) and so on. Of course 
// if the suffix/prefix under question is long enough. In other words, the length 
// of a successful "candidate" must divide with no remainder the length of the 
// initial string.

// So all we have to do in order to solve the given problem is to iterate through 
// all proper suffixes/prefixes of the initial string in descending order. This is 
// just what the "failure function" is designed for. We iterate until we find an 
// "augmenting" string of the desired length (its length divides with no remainder 
// the length of the initial string) or get to the empty string, in which case the 
// "augmenting" string that meets the above requirement will be the initial string 
// itself.

// Test harness
int main(int argc, char** argv) {
  //               01234567890123456789
  string haystack("ABAAABABABABABAB");
  string needle("ABABAB");

  topcoder(haystack, needle);

  /*
  // For debugging only
  if (argc != 2) {
    cout << "Needle string not found" << endl;
    return 0;
  }
  */

  return 0;
}
