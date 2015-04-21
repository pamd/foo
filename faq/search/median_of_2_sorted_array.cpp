/* This is Sophie's code to find the median of two sorted array in O(logM + logN).
 * It is copied from:
 * http://www.leetcode.com/2011/03/median-of-two-sorted-arrays.html
 *
 * According to the following pdf file:
 * http://www2.myoops.org/course_material/mit/NR/rdonlyres/Electrical-Engineering-and-Computer-Science/6-046JFall-2005/30C68118-E436-4FE3-8C79-6BAFBB07D935/0/ps9sol.pdf
 * this algorithm actually finds the median in O(log(M + N)) time.
 * Quotated from the pdf file Problem 9-1 (a):

 * (a) Given two sorted arrays containing a total of n elements, give an algorithm 
 * to find the median of the n elements in theta(lg n) time on one processor.
 *
 * Solution:  The basic idea is that if you are given two arrays A and B and know 
 * the length of each, you can check whether an element A[i] is the median in constant 
 * time. Suppose that the median is A[i]. Since the array is sorted, it is greater than 
 * exactly i - 1 values in array A. Then if it is the median, it is also greater than exactly 
 * j = ceiling(n/2) - (i - 1) elements in B. It requires constant time to check if 
 * B[j] <= A[i] <= B[j + 1]. If A[i] is not the median, then depending on whether A[i] 
 * is greater or less than B[j] and B[j + 1], you know that A[i] is either greater than 
 * or less than the median. Thus you can binary search for A[i] in theta(lg n) worst-case time. 
 * The pseudocode is as follows: 
 *
 *   MEDIAN-SEARCH(A[1 . . l], B[1 . . m], left,right)
 *   1  if left > right 
 *   2     then return MEDIAN-SEARCH(B, A, max(1, ?n/2? - l), min(m, ?n/2?)
 *   3  i =(left + right)/2v
 *   4  j = ceiling(n/2) - i
 *   5  if (j = 0 ? A[i] > B[j]) and (j = m ? A[i] ? B[j + 1])
 *   6     then return (A, i) ? median = A[i]
 *   7  elseif (j = 0 ? A[i] > B[j]) and j ?= m and A[i] > B[j + 1]
 *   8     then return MEDIAN-SEARCH(A, B, left, i - 1) ? median < A[i]
 *   9  else return MEDIAN-SEARCH(A, B, i + 1,right) ? median > A[i]
 * 
 * Let the default values for left and right be such that calling MEDIAN-SEARCH(A, B)
 * is equivalent to 
 * MEDIAN-SEARCH(A[1 . . l], B[1 . . m], max(1, ?n/2? - m), min(l, ?n/2?))
 * The invariant in MEDIAN-SEARCH(A, B) is that the median is always in either 
 * A[left . .right or B. This is true for the initial call because A and B are sorted, 
 * so by the definition of median it must be between max(1, ?n/2? - m) and min(l, ?n/2?), 
 * inclusive. It is also true the recursive calls on lines 8 and 9, since the algorithm 
 * only eliminates parts  of the array that cannot be the median by the de?nition of median. 
 * The recursive call on line 2 also preserves the invariant since if left > right 
 * the median must be in B between the new left and right values. 
 * When the algorithm terminates, the return value is the median by the definition of median. 
 * This algorithm is guaranteed to terminate because at each step right - left decreases 
 * and the median must be either in A or B.	
 * The asymptotic worst-case running time of MEDIAN-SEARCH  is the same as for 
 * performing two binary searches, which is ?(lg n). 
 * Alternatively, you can ?nd the median by repeatedly comparing the median of the 
 * two arrays and discarding the part that cannot contain the median. It runs for at most 
 * 2?lg n? iterations because each iteration discards half of one of the input arrays. There­
 * fore this algorithm's running time is also ?(lg n). 
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Brute force method
double brute(int A[], int asz, int B[], int bsz)
{
  vector<int> tmp;
  for (int i = 0; i < asz; i++)
    tmp.push_back(A[i]);
  for (int i = 0; i < bsz; i++)
    tmp.push_back(B[i]);
  sort(tmp.begin(), tmp.end());

  int mid = (asz+ bsz) / 2;
  if (mid * 2 == (asz+ bsz)) 
    return (tmp[mid] + tmp[mid - 1]) / 2.0;
  return tmp[mid];
}

/* left is starting index of A, right is ending index of array A, 
 * asz is number of elements in A, bsz is number of elements in array B.
 * DHU NOTE: this approach is very close to the algorithm of
 * finding the k-th smallest element in two sorted array in AFI book.
 * But there are subtle differences. Please compare them very carefully!
 */
double findMedian(int A[], int B[], int left, int right, int asz, int bsz) 
{
  cout << "A: " << A[0] << "..." << endl;
  cout << "B: " << B[0] << "..." << endl;
  cout << "left: " << left << endl;
  cout << "right: " << right << endl << endl;

  int mid = (asz + bsz) / 2;
  /* When left is larger than right, the (mid+1)th (starting from 1) 
   * smallest element is not found in A. So we will search it in B,
   * which will be guaranteed to succeed. 
   */
  if (left > right) 
    return findMedian(B, A, max(0, mid - asz), min(bsz, mid), bsz, asz);

  int i = (left + right) / 2;
  // IMPORTANT: i + j = mid - 1
  int j = mid - i - 1;

  /* Find A[i] whose value is between B[j] and B[j+1]. For example, if 
   * the total # of elements in A and B is 10, mid = 10 / 2 = 5.
   * Since i + j = 5 - 1 = 4. Once i is found, the number of elements 
   * that are smaller than A[i] is: i + j + 1 = mid. So A[i] is 
   * the (mid+1)th smallest element.
   */  
  if (j >= 0 && A[i] < B[j]) 
    return findMedian(A, B, i+1, right, asz, bsz);

  if (j < bsz - 1 && A[i] > B[j+1]) 
    return findMedian(A, B, left, i-1, asz, bsz);

  /* Now i is the index of the (mid + 1)th (mid starts from 1!)
   * smallest element. For example, if total # of elements in A and B is 10,
   * then A[i] will be the 6th smallest element. If total # of elements in 
   * A and B is 11, then A[i] will be still the 6th smallest element, which is 
   * actually the median value that we are looking for.
   */

  // Total number of elements in A[] and B[] is odd   
  if ((asz + bsz) % 2 == 1) 
    return A[i];

  // Total number of elements in A[] and B[] is even
  if (i > 0) 
    return (A[i] + max(B[j], A[i-1])) / 2.0;
  
  return (A[i] + B[j]) / 2.0;
  
}

/* Constraint: the number of elements in A is less 
 * than or equal to the number of elements in B.
 */
double findMedianSortedArrays(int A[], int asz, int B[], int bsz) 
{
  // Approach suggested in the pdf file
  int mid = (asz + bsz) / 2;
  int start_idx = max(0, mid - bsz);
  int end_idx = min(asz, mid);
  return findMedian(A, B, start_idx, end_idx, asz, bsz);

  // Sophie's approach, which also works.
  //if (asz <= bsz) 
  // return findMedian(A, B, 0, asz-1, asz, bsz);

  //return findMedian(B, A, 0, bsz-1, bsz, asz);
}

// dhu: test harness
int main()
{
  int A[] = { 3, 6, 8};
  int B[] = { 1, 5 };

  int asz = sizeof(A) / sizeof(int);
  int bsz = sizeof(B) / sizeof(int);
  cout << "Brute force: " << brute(A, asz, B, bsz) << endl << endl;
  cout << "Sophine: " << findMedianSortedArrays(A, asz, B, bsz) << endl;

}





