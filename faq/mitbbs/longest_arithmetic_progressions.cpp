/* Given an array, find the longest arithmetic progresstions. Code is based on:
 * http://compgeom.cs.uiuc.edu/~jeffe/pubs/pdf/arith.pdf
 *
 * Note that this algorithm assumes that the input array is already sorted in ascending order, 
 * and there is no duplicate elements in input array.
 *
 * If the input array is not sorted, and we want to find the longest arithmetic progression that 
 * is in the same order as in the input array, we can do it in brute-force method. For any combinations
 * (A[i], A[j]), in which i < j, scan all elements after A[j], keep track of the longest progressions 
 * found so far. Time complexity is O(n^3). Note that once the first two elements in a progression is 
 * set, the other elements in a progression is also set. So this is different form the problem of 
 * "Longest Increasing Sequence" (LIS). Dynamic Programming can help, but in the worst case 
 * (the longest progression is 2), for each combination of (A[i], A[j], we still need to scan all 
 * elements after A[j], so the time complexity is O(n^3). 
 */

#include <iostream>

using namespace std;

int getLongestProgressions(int arr[ ], int n) {
  int dp[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++)
      dp[i][j] = 2;
  }

  int longest = 2;
  for (int j = n - 1; j >= 1; j--) {
    int i = j - 1;
    int k = j + 1;
    while (i >= 0 && k < n) {
      if (arr[i] + arr[k] > 2 * arr[j])
	i--;
      else if (arr[i] + arr[k] < 2 * arr[j])
	k++;
      else {
	if (longest < 1 + dp[j][k])
	  longest = 1 + dp[j][k];
	dp[i][j] = 1 + dp[j][k];
	i--;
	k++;
      }
    }
  }

  return longest;
}

int main() {
  int arr[] = { 1, 2, 4, 5, 9};
  int n = sizeof(arr) / sizeof(int);
  cout << getLongestProgressions(arr, n) << endl;

}

