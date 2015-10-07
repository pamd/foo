1. read4k
<br>http://www.mitbbs.com/article_t/JobHunting/32705761.html

1. 树状数组 (Binary Indexed Trees)
<br>http://www.hawstein.com/posts/binary-indexed-trees.html

1. http://www.mitbbs.com/article_t/JobHunting/32689155.html 
<br>#1: 给定一个二维矩阵，有update(x,y) 和 sum(x1,y1, x2, y2)两个方法。怎么设计使得update() and sum()比较快?
<br>2-D binary indexed tree?
<br>#2: 给定一个数列, 返回一个最大的数，使得数列中大于它的数的数量也大于它，这个数不需要在数列里，写代码。(Answer: 先sort， 然后一个一个找).  然后问, 如果数列里有很多重复数字, 该怎么弄比较快？答bucket sort, 再讨论了下具体的bucket细节/数量。
<br>Better solution: partition in quicksort?

2. Given a complete binary search tree in form of array, write a sort function to sort the given array in O(n) time.
<br>http://www.mitbbs.com/article_t/JobHunting/32702215.html
<br> The solution is buggy. Couldn't figure out a good solution without using recursion.

1. Permuation with duplicate
<br>http://www.mitbbs.com/article_t/JobHunting/32603015.html

2. Minimize cash flow among lenders and borrowers
<br>http://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/

3. Validate BST: variant
<br>http://www.mitbbs.com/article_t/JobHunting/32605903.html

4. 一个二维数组，元素是0或1，找出最大的由1构成的"X"形状
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
<br>求(2^i) * (3^j) 数列的前k项和（从小到大排序）对q取模的值。k很大，可以到10^15，q可以到10^9.
<br>https://gist.github.com/anonymous/8763947 (code by DarkSteel, very confusing)

7. 网页去重
<br>http://blog.csdn.net/beta2/article/details/5014530

8. Conway's gameof life: 
<br>http://en.wikipedia.org/wiki/Conway's_Game_of_Life

9. Preorder by 100 nodes per batch (code by lcheng)
<br>http://www.mitbbs.com/article_t/JobHunting/32643137.html

10. Bad neighbors (variant: the first and last can not be taken together)
<br>https://gist.github.com/krisys/4089748 (code is wrong, not worth the time)
<br>http://community.topcoder.com/tc?module=Static&d1=match_editorials&d2=tccc04_online_rd_4

11. Permutation serialization:
<br>http://www.mitbbs.com/article_t/JobHunting/32600331.html

12. Interval scheduling:
<br>http://www.cs.rit.edu/~zjb/courses/800/lec8.pdf

13. Maximum of S.size() * T.size()
<br>http://www.mitbbs.com/article_t/JobHunting/32606267.html
<br>http://www.quora.com/Given-a-dictionary-of-words-how-can-we-efficiently-find-a-pair-words-s-t-they-dont-have-characters-in-common-and-sum-of-their-length-is-maximum

12. Merge two quad-tree images (G phone, Nov 2013)
<br>http://www.mitbbs.com/article_t/JobHunting/32582727.html

15. 一个two dimensional array, array的元素是0 或者1。问能不能找到一个矩形，矩形的4个角都是1?
<br>http://www.mitbbs.com/article_t/JobHunting/32673693.html 

18. Geeks4geeks: AVL tree
<br>http://www.geeksforgeeks.org/avl-tree-set-1-insertion/ (insertion)
<br>http://www.geeksforgeeks.org/avl-tree-set-2-deletion/ (deletion)

20. Count the number of possible triangles: O(n^2) time
<br>http://www.geeksforgeeks.org/find-number-of-triangles-possible/

21. Count the number of ranges in which the number of 1's >= the number of 0's.
<br>http://www.mitbbs.com/article_t/JobHunting/32709473.html


