/* Leetcode OJ: Given a sorted array of integers, find the starting and ending 
 * position of a given target value.
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * If the target is not found in the array, return [-1, -1].
 * For example, given [5, 7, 7, 8, 8, 10] and target value 8, return [3, 4].
 */

// 56ms for large dataset
class Solution {
public:
  vector<int> searchRange(int A[], int n, int target) {
    vector<int> range(2, -1);
    if (n <= 0)
      return range;

    int first = findFirst(A, n, target);
    if (first == -1)
      return range;

    int last = findLast(A, n, target);
    range[0] = first;
    range[1] = last;
    return range;
  }

  // Find left side of range
  int findFirst(int A[], int n, int target) {
    int left = 0;
    int right = n - 1;
    int first = -1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (A[mid] > target)
	right = mid - 1;
      else if (A[mid] == target) {
	first = mid;
	right = mid - 1;
      }
      else 
	left = mid + 1;
    }

    return first;
  }

  // Find right side of range  
  int findLast(int A[], int n, int target) {
    int left = 0;
    int right = n - 1;
    int last = -1;
    while (left <= right) {
      int mid = left + (right - left) / 2;
      if (A[mid] > target)
	right = mid - 1;
      else if (A[mid] == target) {
	last = mid;
	left = mid + 1;
      }
      else 
	left = mid + 1;
    }

    return last;
  }

};

/**************************************************************************
 * Dropbox solution: not so good because it includes a lot of corner cases.
 **************************************************************************/

// Find the last element that is LESS than target in a sorted array 
int BSearchLowerBound(int array[], int low, int high, int target) {
  if (high < low  || target <= array[low]) 
    return -1;
	
  int mid = (low + high + 1) / 2; // make mid lean to right side
  while (low < high) {
    if (array[mid] < target)
      low = mid;
    else
      high = mid - 1;
    
    mid = (low + high + 1) / 2;
  }

  return mid;
}

// Find the fisrt element that is LARGER than target in a sorted array 
int BSearchUpperBound(int array[], int low, int high, int target) {
  if (low > high || target >= array[high]) 
    return -1;
    
  int mid = (low + high) / 2;
  while (high > low) {
    if (array[mid] > target)
      high = mid;
    else
      low = mid + 1;
    
    mid = (low + high) / 2;
  }

  return mid;
}

// Main function
vector<int> SearchRange(int A[], int n, int target) {
  vector<int> r(2, -1);
  if (n <= 0) 
    return r;
    
  int lower = BSearchLowerBound(A, 0, n-1, target);
  lower = lower + 1; // move to next element
  
  if (A[lower] == target)
    r[0] = lower;
  else // target is not in the array
    return r;
  
  int upper = BSearchUpperBound(A, 0, n-1, target);
  upper = upper < 0? (n-1):(upper - 1); //move to previous element

  // Since in previous search we had check whether the target is
  // in the array or not, we do not need to check it here again.
  r[1] = upper;
	
  return r;
}

/*
int main(int argc, char** argv) {
  int A[] = {1,2,3,3,3,3,4,5,6,7};
  
  vector<int> v;
  int size = sizeof(A)/sizeof(int);
  
  int target = 0;
  v = SearchRange(A, size, target);
  cout << target << ": " << v[0] << ',' << v[1] << '\n';
  
  target = 1;
  v = SearchRange(A, size, target);
  cout << target << ": " << v[0] << ',' << v[1] << '\n';
  
  target = 3;
  v = SearchRange(A, size, target);
  cout << target << ": " << v[0] << ',' << v[1] << '\n';
  
  target = 7;
  v = SearchRange(A, size, target);
  cout << target << ": " << v[0] << ',' << v[1] << '\n';
  
  target = 8;
  v = SearchRange(A, size, target);
  cout << target << ": " << v[0] << ',' << v[1] << '\n';
  
  return 0;
}
*/
