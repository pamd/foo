/* Jump game and Junp game 2 in Leetcode Online Judge.
 * Also refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32076261.html
 */

#include <iostream>

using namespace std;

// Jump game, written by thrust
bool jump(int A[], int n) {
  int i = 0;
  int m = 0;
  while (i <= m) {
    m = max(m, i + A[i]);
    if (m >= n - 1)
       break;
    i++;
  }
  return m >= n-1;
}


// dhu version, tested in OJ
bool jump_dhu(int A[], int n) {
  int end = A[0];
  for (int i = 0; i <= end; i++) {
    if (i + A[i] >= n - 1)
      return true;
    if (i + A[i] > end)
      end = i + A[i];
  }
  return false;
}

// Jump game 2, written by dhu
int jump2(int A[], int n) {
  if (!A) 
    return 0;
  if (n == 1)
    return 0;

  if (A[0] >= n - 1)
    return 1;
            
  /* Original approach, tested in OJ
  int start = 0;
  int end = A[0]; 
  int ret = 0;
  while (start < n) {
    int tmp = end;
    ret++;
    for (; start <= end; start++) {
      if (A[start] + start >= n - 1)
	return ret + 1;
      if (A[start] + start > tmp)
	tmp = A[start] + start;
                
               
    }
    if (tmp == end)
      return 0;
    end = tmp;
  }
  */

  // Newer (and cleaner) version, tested in OJ too
  int end = A[0]; 
  int prev_end = end;
  int ret = 1;
  for (int start = 1; start <= prev_end; start++) {
    if (start + A[start] >= n - 1)
      return ret + 1;
    if (start + A[start] > end) 
      end = start + A[start];

    if (start == prev_end) {
      ret++;
      if (end == prev_end)
	return 0;
      prev_end = end;
    }

  }    

  return ret;
       
}

int main()
{
  int arr[] = { 1, 2, 1, 1, 0 };
  int n = sizeof(arr) / sizeof(int);
  cout << jump2(arr, n) << endl;
}
