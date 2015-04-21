/* Leetcode OJ: Given a sorted array, remove the duplicates in place 
 * such that each element appear only once and return the new length.
 * Do not allocate extra space for another array, you must do this 
 * in place with constant memory. For example, Given input array A = [1,1,2],
 * your function should return length = 2, and A is now [1,2].
 */

// 68ms for large dataset
class Solution {
public:
  int removeDuplicates(int A[], int n) {
    if (n <= 1)
      return n;

    int left_border = 1;
    for (int i = 1; i < n; i++) {
      if (A[i] != A[i - 1]) {
	A[left_border++] = A[i];
      }
    }

    return left_border;
        
  }
};
