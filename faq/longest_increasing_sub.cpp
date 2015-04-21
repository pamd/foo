/***********************************************************************************************************

http://en.wikipedia.org/wiki/Longest_increasing_subsequence

The algorithm outlined below solves the longest increasing subsequence problem efficiently, using only 
arrays and binary searching. For the first time this algorithm was developed by M. L. Fredman in 1975. 
It processes the sequence elements in order, maintaining the longest increasing subsequence found so far. 
Denote the sequence values as X[1], X[2], etc. Then, after processing X[i], the algorithm will have stored 
values in two arrays:

    M[j]: stores the position k of the smallest value X[k] such that k <= i (note we have k <= j <= i here) 
          and there is an increasing subsequence of length j+1 ending at X[k]

    P[k]: stores the position of the predecessor of X[k] in the longest increasing subsequence ending at X[k].

In addition the algorithm stores a variable L representing the length of the longest increasing subsequence 
found so far.

Note that, at any point in the algorithm, the sequence

    X[M[1]], X[M[2]], ..., X[M[L]]

is nondecreasing. For, if there is an increasing subsequence of length i ending at X[M[i]], 
then there is also a subsequence of length i-1 ending at a smaller value: namely the one ending at P[M[i]]. 
Thus, we may do binary searches in this sequence in logarithmic time.

The algorithm, then, proceeds as follows.

 L = 0
 for i = 1, 2, ... n:
    binary search for the largest positive j <= L such that X[M[j]] < X[i] (or set j = 0 if no such value exists)
    P[i] = M[j]
    if j == L or X[i] < X[M[j+1]]:
       M[j+1] = i
       L = max(L, j+1)

The result of this is the length of the longest sequence in L. 
The actual longest sequence can be found by backtracking through the P array: 
the last item of the longest sequence is in X[M[L]], the second-to-last item is in X[P[M[L]]], etc. 
Thus, the sequence has the form

    ..., X[P[P[M[L]]]], X[P[M[L]]], X[M[L]].

Because the algorithm performs a single binary search per sequence element, its total time is O(n log n).

************************************************************************************************************/

#include <vector>
#include <cstdio>

using namespace std;
 
/* Finds longest strictly increasing subsequence. O(n*log(k)) algorithm. */
vector<int> find_lis(vector<int>& X)
{
  vector<int> M;  // see comments at the very beginning 
  vector<int> P(X.size()); // P: backtracking vector, see comments at the very beginning
  int l, r;
 
  if (X.size() < 1) 
    return M;
 
  M.push_back(0);
 
  for (size_t i = 1; i < X.size(); i++) {
    if (X[M.back()] < X[i]) {
      P[i] = M.back();
      M.push_back(i);
      continue;
    }
 
    //for (l = 0, r = M.size() - 1; l < r;) {
    // dhu modification
    // Binary search that returns the smallest element m in M where X[m] is larger than or equal to X[i]   
    l = 0; 
    r = M.size() - 1;
    while (l < r) {
      int c = (l + r) / 2;
      if (X[M[c]] < X[i]) 
	l = c + 1; 
      else 
	r = c;
    }
 
    // If X[i] is equal to X[M[l]], skip it
    if (X[i] < X[M[l]]) {
      if (l > 0) 
	P[i] = M[l - 1];
      M[l] = i;
    }	
  }
 
  // Original code is harder to understand
  //for (l = M.size(), r = M.back(); l--; r = P[r]) 
  //  M[l] = r;

  // dhu modification
  l = M.size() - 1;
  r = M.back();
  while (l > 0) {
    M[l] = r;
    r = P[r];
    l--;
  }

  return M;
}
 
// Example of usage
int main()
{
  int X[] = { 1, 9, 3, 8, 11, 4, 5, 6, 4, 19, 7, 1, 7 };
  vector<int> seq(X, X + sizeof(X) / sizeof(X[0]));
  vector<int> lis = find_lis(seq);
 
  for (size_t i = 0; i < lis.size(); i++)
    printf("%d ", seq[lis[i]]);
  printf("\n");    
 
  return 0;
}
