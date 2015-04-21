/* Leetcode OJ: Follow up for "Remove Duplicates".
 * What if duplicates are allowed at most twice?
 * For example, given sorted array A = [1,1,1,2,2,3], 
 * your function should return length = 5, and A is now [1,1,2,2,3].
 */

#include <iostream>

// 88ms for large dataset
class Solution {
public:
  int removeDuplicates(int A[], int n) {
    if (n <= 2)
      return n;

    int left_border = 1;
    int counter = 1;
    for (int i = 1; i < n; i++) {
      if (A[i] == A[i - 1]) 
	counter++;
      else 
	counter = 1;
      if (counter < 3) 
	A[left_border++] = A[i];
    }

    return left_border;
  }

};
