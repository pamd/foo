//============================================================================
// Search in Rotated Sorted Array II
//
// Follow up for "Search in Rotated Sorted Array":
// What if duplicates are allowed?
//
// Would this affect the run-time complexity? How and why?
//
// Write a function to determine if a given target is in the array.
//============================================================================

#include <iostream>
using namespace std;

/* dhu note: when duplicates are allowed in inoput array, regular binary 
 * search won't work. In the worse case, time complexity will be O(n). 
 * But we can (and probably should) still call binary search (partially) 
 * to improve the complxity. So the following brute-force solution may not 
 * be what an interviewer expects.
 */
class Solution {
public:
  bool search(int A[], int n, int target) {
    for (int i = 0; i < n; i++) {
      if (A[i] == target) 
	return true;
    }
    return false;
  }
};

int main() {
  return 0;
}
