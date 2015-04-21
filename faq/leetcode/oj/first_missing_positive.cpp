/* Given an unsorted integer array, find the first missing positive integer.
 *
 * For example,
 * Given [1, 2, 0], return 3;
 * and given [3, 4, -1, 1], return 2.
 *
 * Your algorithm should run in O(n) time and uses constant space.
 */

#include <iostream>

using namespace std;

// dhu OJ solution: 16ms for large dataset
class Solution {
public:
  void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
  }

  int firstMissingPositive(int A[], int n) {
    if (!A || n == 0)
      return 1;

    for (int i = 0; i < n; i++) {
      int j = A[i];
      while (j > 0 && j <= n && A[j - 1] != j) {
	swap(A[i], A[j - 1]);
	j = A[i];
      }
    }

    for (int i = 0; i < n; i++) {
      if (A[i] != i + 1)
	return i + 1;
    }
    return n + 1;
  }
};

// Dropbox solution
int FirstMissingPositive(int A[], int n) {
  int i = 0;
  while (i < n) {
    int ai = A[i];
    // Find the position for each element, kind like sort it, but much faster
    if (0 <= ai && ai < n)
      // Prevent from infinite swap 
      if (A[ai] != ai) {
	A[i] = A[ai];
	A[ai] = ai;
	continue;
      }

    ++i;
  }

  i = 1;
  while (i < n && A[i] == i) 
    i++;
	
  // Fisrt element may be n; if so, the largest missed positive number should be n+1
  if (A[0] == i) 
    ++i;

  return i;
}

// MITBBS solutions
// By dhu
int find_missing(int* arr, int len)
{
  for (int i = 0; i < len; i++) {
    while (arr[i] != i + 1) {
      if (arr[i] <= 0 || arr[i] > len || arr[arr[i] - 1] == arr[i])
	break;
      swap(arr[i], arr[arr[i] - 1]);
    }
  }

  //cout << "out" << endl;
  for (int i = 0; i < len; i++) {
    if (arr[i] != i + 1)
      return i + 1;
  }

  return len + 1;
}

// By gloomyturkey
int turkey(int a[], int len) {
  int least = len;      
  for (int i = len - 1; i >= 0; i--) {
    if (a[i] <= 0 || a[i] > i + 1) {
      least = i;
      continue;
    }

    if (a[i] != i + 1) {
      if (a[i] == a[a[i]-1]) 
	least = i;
      else {
	int t = a[i] - 1;
	a[i] = a[t];
	a[t] = t + 1;
	i++;
      } // end of else
    } // end of if
  }  // end of for
  
  return least + 1;
}

// By cx3959
int cx3959(int* a, int len) 
{
  int i = 0;
  while (i < len) {
    int m = a[i];
    if (m >= 0 && m < len && a[m] != m) {
      int tmp;
      tmp = a[m];
      a[m] = m;
      a[i] = tmp;
    }
    else
      i++;
  }

  for (i = 1; i < len; i++) {
    if (a[i] != i) {
      return i;
    }
  }

  if(a[0] == len)
    return len+1;

  return len;
}

// By leetcode, same idea as cx3959
int firstMissingPositive(int A[], int n) {
  if (n == 0) 
    return 1;

  for (int i = 0; i < n; i++) {
    while (A[i] >= 0 && A[i] < n && A[i] != A[A[i]])
      swap(A[i], A[A[i]]);
  }

  for (int i = 1; i < n; i++) {
    if (A[i] != i) 
      return i;
  }

  return (A[0] == n) ? n+1 : n;
}

// Test harness
int main() {
  int A[] = { 3, 4, -1, 1 };
  int n = sizeof(A) / sizeof(int);
  Solution foo;
  cout << foo.firstMissingPositive(A, n) << endl;
}
