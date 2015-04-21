/* Heap-sort related functions, based on the code in 
 * "Algorithms in C++" by Robert Sedgewick. 
 */

#include <iostream>

using namespace std;

// Helper function to swap the value of two input integers
void swap(int& v1, int& v2) 
{
  int tmp = v1;
  v1 = v2;
  v2 = tmp;
}
  
/* Move up kth element in input array so that array becomes a heap again.
 * Note that this function does NOT need the size of array, because we know
 * when k reaches the very beginning of the array. 
 */
void swimUp(int arr[], int k) 
{
  while (k > 1 && arr[k] > arr[k / 2]) {
    swap(arr[k], arr[k/2]);
    k /= 2;
  }
}

/* Move down kth element in input array so that array becomes a heap again.
 * Note that this function needs the size of array in parameter list, otherwise
 * we have no idea when k has reached the end of input array. 
 */
void sinkDown(int arr[], int N, int k) 
{
  while (2 * k <= N) {
    int j = 2 * k;
    if (j < N && arr[j] < arr[j + 1])
      j++;

    if (arr[k] >= arr[j])
      break;

    swap(arr[k], arr[j]);
    k = j;
  }

}

// Heap sort
void heapsort(int arr[], int N)
{
  // int helper[N+1];
  // for (int i = 1; i <= N; i++)
  //   helper[i] = arr[i - 1];

  /* Instead of defining an accessory array whose valid elements 
   * starts from index 1, "Algorithms in C++" book uses a hack, 
   * in which helper points to the fictional element on the left on arr[0].
   * This trick works with gcc on Linux, but it may not be portable.
   */
  int* helper = arr - 1;
  /* Make helper a heap starting from helper[1], which is arr[0].
   * Note that time complexity of this step is O(n), not O(nlgn) */
  for (int k = N / 2; k >= 1; k--) 
    sinkDown(helper, N, k);

  int end_idx = N;
  for (int k = 1; k < N; k++) {
    swap(helper[1], helper[end_idx]);
    end_idx--;
    sinkDown(helper, end_idx, 1);
  }

  //for (int i = 1; i <= N; i++)
  //  arr[i - 1] = helper[i];
}

// Test harness
int main()
{
  int arr[] = { 3, -2, 4, -6, 4, 1, 7 };
  int sz = sizeof(arr) / sizeof(int);
  heapsort(arr, sz);

  for (int i = 0; i < sz; i++)
    cout << arr[i] << endl;

}
