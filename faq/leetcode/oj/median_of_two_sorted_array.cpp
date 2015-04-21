/* Leetcode OJ: There are two sorted arrays A and B of size m and n respectively. 
 * Find the median of the two sorted arrays. 
 * The overall run time complexity should be O(log (m+n)).
 */

class Solution {
public:
  // 192ms for large dataset
  double findMedianSortedArrays(int A[], int m, int B[], int n) {
    if (m == 0 && n == 0)
      return 0;

    int k = (m + n + 1) / 2;
    int kth = findKth(A, m, B, n, k);
    if ((m + n) % 2)
      return kth;

    int next = findKth(A, m, B, n, k + 1);
    double sum = kth + next;
    return sum / 2.0;
  }

  // This function already takes care of the corner cases of m == 0 or n == 0
  int findKth(int A[], int m, int B[], int n, int k) {
    int left = max(0, k - n);
    int right = min(k, m);
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (mid < m && k - mid - 1 >= 0 && A[mid] < B[k - mid - 1])
	left = mid + 1;
      else if (mid >= 1 && k - mid < n && B[k - mid] < A[mid - 1])
	right = mid - 1;
      else {
	left = mid;
	break;
      }
    }
    if (left == 0)
      return B[k - 1];
    
    if (left == k)
      return A[k - 1];
    
    return max(A[left - 1], B[k - left - 1]);
  }

  // This naive method takes 248ms for large dataset
  double findMedianSortedArrays(int A[], int m, int B[], int n) {
    vector<int>v(A, A + m);
    for (int i = 0; i < n; i++)
      v.push_back(B[i]);
    sort(v.begin(), v.end());
    if (v.size() % 2)
      return v[v.size() / 2];
    return (v[v.size() / 2 - 1] + v[v.size() / 2]) / 2.0;    
  }

};
