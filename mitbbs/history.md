1. Permuation with duplicate
<br>http://www.mitbbs.com/article_t/JobHunting/32603015.html

2. MInimize cash flow among lenders and borrowers
<br>http://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/

3. Validate BST: variant
<br>http://www.mitbbs.com/article_t/JobHunting/32605903.html

4. 一个二维数组，元素是0或1，找出最大的由1构成的"X"形状 (done)
<br>http://www.mitbbs.com/article_t/JobHunting/32620157.html
<br>对于任何一个点 i,j,分4个方向分别表示以该点为右下,左下,右上,左上斜着的连续的1的个数(含自己). 那么该点为中心的最大X中1的个数为min(4个方向计数)*4-3.这个值存在dp关系,以右下为例:
<br>dp[i][j][0] = dp[i-1][j-1][0]+1;  if A[i][j]==1
<br>dp[i][j][0] = 0;                  if A[i][j]==0
<br>四个方向道理一样,类似求解dp[i][j][0..3], 完了就可以得出最大的那个了.

5. 两个数组，里面的数字都是0 to n-1, and no duplicate. 使用swap_with_zero把第二个变成第一个.
<br>http://www.mitbbs.com/article_t/JobHunting/32620793.html
<br>http://cs.stackexchange.com/questions/13930/rearrange-an-array-using-swap-with-0

6. Rocket Fuel: (#1: Deque without pop_front; #3: Auto Racers)
<br>http://www.mitbbs.com/article_t/JobHunting/32613553.html
<br>http://get-that-job-at-google.blogspot.com/2013/02/rocketfuel-codesprint-at-iit-bombay.html
<br>Solution to "Auto Racers":
<br>Divide n races into sqrn(n) buckets. Each bucket will have sqrt(n) racers' starting times.
Then scan the racers either by ending time in incremental order, or by starting time in decreasing orders.
If we scan ending time in incremental order, find the number of racers whose starting times are later than
the current racer. This number will be the score that we are looking for. Each scan takes O(sqrn(n)) time.
Thus the total time complexity is O(n * sqrn(n)), aka. O(n^1.5), which is better than O(n^2). 
