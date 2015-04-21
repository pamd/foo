/***************************************************
http://discuss.joelonsoftware.com/default.asp?interview.11.465104.8   

   Maximum Sum Submatrix Problem
------------------------------------

This runs in O(n^3) time and the algorithm is basically :

If you consider each row of the matrix, then you will see that the maximum submatrix will have 
either n rows, n-1 rows, n-2 rows, ...,  1 row.

We consider all possibilities e.g. for a 4 x 4 matrix, we consider :
1
1,2
1,2,3
1,2,3,4
2
2,3
2,3,4
3
3,4
4

There are n^2 such combinations(n + (n-1) + (n-2) + .. 1).
For each combination we are transforming it into a single 1D array by adding the values. 
So all we have to do is find the maximum sum of this 1D array now. 
If, for example, in the transformation of the 1,2,3,4 rows combined, we find that the maximum sum 
is from elements indexed 1 to 3, then that tells us that the maximum sum in the actual 2D array, 
the maximum sum includes the columns 1 through 3 and the rows 1 through 4.

***********************************************************/

maxSum = -INF;

int curSum[n];

for(i = 0; i < n; i++) {
  for(j = 0; j < n; j++)  // initialize curSum[n] to 0
    curSum[j] = 0;

  for(k = i; k < n; k++) {
    for(j = 0; j < n; j++) {
      curSum[j] += array[k][j];
    }
    newSum = MaxSumArray(curSum);  // get current maximum submatrix
    if(newSum > maxSum)
      maxSum = newSum;
  }
}

return maxSum;

/*************************************************************
I have another way of doing this:

Input: Array A[1..n, 1..n] of numbers (positive and negative).

Begin Algorithm
  1 Replace each row of A by its prefix sums.
  2 Add a column of zeroes as the zeroth column of A.
  3 For all 1 <= g <= h <= n do
      (a) Compute the sequence Cgh
              For all 1<=i<=n do
              Cgh[i] := A[i][h] - A[i][g-1]       
      (b) Compute the maximum subsequence sum of C into M .
  4 Find the maximum of all Mgh, 1<=g<=h<=n into MSA.
  5 Output MSA.
End Algorithm

this clearly runs in O(n^3)

actually this was a algorithm published in parallel computing paper....
very interesting solution 

******************************************************************/
