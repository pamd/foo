/* A sorted array has been rotated at a certain position. Find that position.
 * Code is copied from MIYTBBS. Original thread has been deleted. 
 * See reserved discussions #114. */

// Recursive solution: average: O(log N), worst case: O(N)
// st: start index, en: end index
int search(int *arr, int st, int en) {
  if (arr[st] < arr[en] || st == en)	
    return 0;
  if (en - st == 1 ) {
    if (arr[st] == arr[en])	
      return 0;
    return en;	
  }
  return search(arr, st, (st+en)/2) + search(arr, (st+en)/2, en);
}
