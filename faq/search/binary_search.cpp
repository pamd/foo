#include <iostream>
#include <cmath> 

using namespace std;

/* Based on code on "Programming Pearls" page 93.
 * arr is input array, arr_size is the number of elements in arr, 
 * x is the value that we are looking for. 
 * Returns index of the element, or -1 if element is not found. 
 * This approach is trickier than it seems to be. 
 */
int first_occurrence(int* arr, int arr_size, int x)
{
  int l = -1;
  int u = arr_size;
  while (l + 1 < u) {
    int m = l + (u - l) / 2;
    if (arr[m] < x)
      /* l = m + 1 is not correct, because we are using u as the final result. 
       * Suppose we are looking for 4 in { 1, 4, 4 }, l = -1, u = 2, so m = 0, 
       * if we set l = m + 1, then l = 1, u = 2, the loop will be terminated, 
       * and u=2 is returned as the final answer, but 2 is not correct. The answer 
       * should be 1 instead. */  
      l = m;  
    else
      u = m;
  }

  if (u >= arr_size || arr[u] != x)
    return -1;
  
  return u;

}

/* dhu function that returns the first occurrence of x.
 * It is based on the idea on "Beauty of Programming" (Chinese version) page 259.
 * Returns index of the element, or -1 if element is not found. */ 
int dhu_first_occurrence(int* arr, int arr_size, int x)
{
  int l = 0;
  int u = arr_size - 1;
  while (l + 1 < u) {
    int m = l + (u - l) / 2;
    if (arr[m] < x)
      l = m + 1; // Both l = m and l = m + 1 will work here
    else
      u = m;
  }

  if (arr[l] == x)
    return l;
  
  if (arr[u] == x)
    return u;

  return -1;
}

/* Function that returns the last occurrence of x. 
 * Copied from "Beauty of Programming" (Chinese version) page 259.
 * Returns index of the element, or -1 if element is not found. */
int last_occurrence(int* arr, int arr_size, int x)
{
  int l = 0;
  int u = arr_size - 1;
  while (l + 1 < u) {
    int m = l + (u - l) / 2;
    if (arr[m] <= x)
      l = m; 
    else
      // Although the book claims that u = m - 1 is not correct, 
      // both "u = m;" and"u = m - 1;" will work in the next line. 
      u = m - 1;
  }

  if (arr[u] == x)
    return u;
  
  if (arr[l] == x)
    return l;

  return -1;
}

/* Search the largest element that is smaller than x. 
 * Returns index of the element, or -1 if no element is smaller than x. */
int largest_less_than(int* arr, int arr_size, int x) 
{
  int l = 0;
  int u = arr_size - 1;
  while (l + 1 < u) {
    int m = l + (u - l) / 2;
    if (arr[m] < x)
      l = m; 
    else
      u = m;  // Both "u = m" and "u = m - 1" will work here 
  }

  if (arr[u] < x)
    return u;
  
  if (arr[l] < x)
    return l;

  return -1;
}

/* Search the largest element that is smaller than x. 
 * Returns index of the element, or -1 if element is not found. */
int smallest_greater_than(int* arr, int arr_size, int x) 
{
  int l = 0;
  int u = arr_size - 1;
  while (l + 1 < u) {
    int m = l + (u - l) / 2;
    if (arr[m] > x)
      u = m;  
    else
      l = m; // Both "l = m" and "l = m + 1" will work here.
  }

  if (arr[l] > x)
    return l;
  
  if (arr[u] > x)
    return u;

  return -1;
}

/* Binary search to calculate square root of an input unisgned integer x. 
 * If sqrt(x) is integer, return that integer, otherwise return floor(sqrt(x)).
 * Copied from "Algorithms for Interviews" Solution 1.1 on page 110. */
unsigned int sqrt_search(unsigned int x)
{
  int begin = 0;
  int end = 65536;
  while (begin + 1 < end) {
    int mid = begin + (end - begin) / 2;
    unsigned int mid_sqr = mid * mid;
    if (mid_sqr == x)
      return mid;

    if (mid_sqr > x)
      end = mid;
    else
      begin = mid;
  }
      
  return begin;
}

/* Another function that calculates square root of a double value x. 
 * Precision is set by the arbitrary variable "epsilon". 
 */ 
double sqrt_search(double x) 
{
  const double epsilon = 1e-6;
  double begin = 0;
  double end = x;
  while (end - begin > epsilon) {
    double mid = begin + (end - begin) / 2;
    double mid_sqr = mid * mid;
    if (mid_sqr > x)
      end = mid;
    else
      begin = mid;
  }
      
  return begin;
}

// Test harness
int main()
{
//   // index:     0  1  2  3  4  5  6
//   int arr[] = { 1, 2, 4, 4, 4, 7, 8 };
//   int arr_size = sizeof(arr) / sizeof(int);

//   int result = largest_less_than(arr, arr_size, 10);
//   cout << "result: " << result << endl;


  for (unsigned i = 1; i < 50; i++)
    cout << i << ": " << sqrt_search((double) i) << ", " << sqrt(i) << endl;
  
  return 0;
}
