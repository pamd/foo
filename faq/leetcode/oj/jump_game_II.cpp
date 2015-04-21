/* Given an array of non-negative integers, you are initially positioned at the first index of the array.
 * Each element in the array represents your maximum jump length at that position.
 * Your goal is to reach the last index in the minimum number of jumps.
 * For example: Given array A = [2,3,1,1,4], the minimum number of jumps to reach the last index is 2. 
 * (Jump 1 step from index 0 to 1, then 3 steps to the last index.)
 */

#include <iostream>

using namespace std;
// dhu: 40ms for large dataset
class Solution {
public:
  int jump(int A[ ], int n) {
    if (!A || n <= 1)
      return 0;

    int ret = 1;
    int right_edge = A[0];
    if (right_edge >= n - 1)
      return ret;

    int i = 1;
    int next_edge = right_edge;
    while (i < n) {
      while (i <= right_edge) {
	if (A[i] + i >= n -1)
	  return ++ret;
	if (next_edge < A[i] + i)
	  next_edge = A[i] + i;
	i++;
      }
      if (next_edge == right_edge)
	return -1;
      right_edge = next_edge;
      ret++;
    }
       
    return -1;
  }

};

int main() {
  int A[] = { 2, 3, 1, 1, 4 };
  int n = sizeof(A) / sizeof(int);
  Solution foo;
  cout << foo.jump(A, n) << endl;

}
