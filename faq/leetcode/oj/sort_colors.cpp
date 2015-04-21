/* Leetcode OJ: Given an array with n objects colored red, white or blue, 
 * sort them so that objects of the same color are adjacent, with the colors
 * in the order red, white and blue.
 * Here, we will use the integers 0, 1, and 2 to represent the colors red, 
 * white, and blue respectively. 
 * Note: You are not suppose to use the library's sort function for this problem.
 * 
 * Follow up: A rather straight forward solution is a two-pass algorithm using 
 * counting sort. First, iterate the array counting number of 0's, 1's, and 2's, 
 * then overwrite array with total number of 0's, then 1's and followed by 2's.
 * Could you come up with an one-pass algorithm using only constant space?
 */

class Solution {
public:
  void sortColors(int A[], int n) {
    //counting_sort(A, n);
        
  }

  /* Counting sort requires 2 scans of input array.
   * 12ms for large dataset .*/
  void counting_sort(int A[], int n) {
    if (n <= 1)
      return;

    int n0 = 0, n1 = 0, n2 = 0;
    for (int i = 0; i < n; i++) {
      if (A[i] == 0)
	n0++;
      else if (A[i] == 1)
	n1++;
      else
	n2++;
    }

    for (int i = 0; i < n0; i++)
      A[i] = 0;
    for (int i = n0; i < n0 + n1; i++)
      A[i] = 1;
    for (int i = n0 + n1; i < n; i++)
      A[i] = 2;
  }

  /* Three-way partitioning: copied from anson627. 
   * 20ms for large dataset. */
  void sortColors(int A[], int n) {
    if (n <= 1) 
      return;

    /* "low" is the index where the next 0 will be put in; 
     * it is also the index where the left-most 1 is located. */
    int low = 0; 

    /* "mid" is the index where the next 1 will be put in;
     * it is also the index where the left-most 2 is located. */
    int mid = 0; 

    // "high" is the index where the next 2 will be put in.
    int high = n - 1; 

    while (mid <= high) {
      if (A[mid] == 0) {
	A[mid] = A[low];
	A[low] = 0;
	low++;
	mid++;
      }
      else if (A[mid] == 1) {
	mid++;
      }
      else if (A[mid] == 2) {
	A[mid] = A[high];
	A[high] = 2;
	high--;
      }
    }  // end of while loop
  }

};

// Dropbox solution: counting sort
void SortColors(int A[], int n) {
  int size[3] = {0, 0, 0};
  for (int i = 0; i < n; ++i)
    size[A[i]]++;
    
  size[1] += size[0];
  size[2] += size[1];
  int i = 0;
	
  while (i < size[0]) 
    A[i++] = 0;
  while (i < size[1]) 
    A[i++] = 1;
  while (i < size[2]) 
    A[i++] = 2;
}
