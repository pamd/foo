/* Discussion #413: Given an int array whose elements may be either positive 
 * or negative, find the longest subarray whose sum is less than a given int.
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32150635.html
 *
 * dhu: As of 04/10/2013, this file is obsolete, see various implementations in:
 *    faq/epi/12_meta_algorithm/07_Longest_subarray_k.cpp
 */

#include <iostream>
#include <algorithm>

using namespace std;

// Code by iverson1407, based on idea from vimabc
int* iverson(int *array, int length, int maxsum) {
  int *sum = new int[length + 1];
  sum[0] = 0;
  for(int i = 1; i <= length; i++)
    sum[i] = sum[i - 1] + array[i - 1];

  int *max = new int[length + 1];
  int *min = new int[length + 1];

  /*
  cout << "cum arr: ";
  for(int i = 0; i <= length; i++)
    cout << sum[i] <<" ";
  cout << endl;
  */

  max[0] = 0;
  for (int i = 1; i < length + 1; i++) {
    max[i] = std::max(max[i - 1], sum[i]);
  }

  min[length] = sum[length];
  for (int i = length - 1 ; i >= 0; i--) {
    min[i] = std::min(min[i + 1], sum[i]);
  }

  int prev = 0;
  int next = 0;
  int rightmost = 0;
  int leftmost = 0;
  while (prev != length + 1 && next != length + 1) {
    if (min[next] - max[prev] <= maxsum) {
      if (next != prev) {
	if (next - prev > rightmost - leftmost){
	  rightmost = next;
	  leftmost = prev;
	}
      }
      next++;
    }
    else
      prev++;        
  }

  cout << "answer: ";
  int *res = new int[rightmost - leftmost];
  for(int i = leftmost; i < rightmost; i++){
    cout << array[i] <<" ";
    res[i - leftmost] = array[i];
  }

  cout << endl;
  
  return res;
}

// dhu test harness
int main() {
  // dhu individual test cases
  //int a[] = { 0, 0, 1, 3, 6 };
  //int k = 4;

  int a[] = { 3, -4, -6, 7, 2 }; 
  int k = 5;

  int len = sizeof(a) / sizeof(int);
  iverson(a, len, k);
  
  return 0;
}
