# General tutorials on Segment Tree

* wikipedia: segment tree
<br>As of 07/02/2015, the first figure is misleading. See my notes on the printout.

* http://wwwisg.cs.uni-magdeburg.de/ag/lehre/WS1213/GDS/slides/S4.pdf
<br>The BEST tutorial I found online, covers segment tree and Jon Bentley's 
approach very well.
<br>(saved as s4.pdf)

* http://wwwisg.cs.uni-magdeburg.de/ag/lehre/WS1112/GDS/slides/S7.pdf
<br>Another tutorial that covers both segment tree and interval tree.
<br>(Saved as s7.pdf)

* https://www.cs.duke.edu/courses/fall05/cps234/notes/lecture07.pdf
<br>Tutorial from Duke. Nice summary of segment tree and interval tree.

* Segment Tree (Stanford CS166)
<br>http://web.stanford.edu/class/archive/cs/cs166/cs166.1146/lectures/00/Extra00.pdf
<br>Very nice introduction, with helpful animations.

* http://www.cs.nthu.edu.tw/~wkhon/ds/ds10/tutorial/tutorial6.pdf (saved as Taiwan.pdf)
<br>Tutorial from National TsingHua Univ at Taiwan. Note that the 
segment tree in this tutorial does NOT treat each starting and ending 
points as a seperate interval. This is different from many approaches 
in many other tutorials (such as Mark de berg's book and s4.pdf).

* http://www.cse.iitd.ernet.in/~ssen/cs852/newscribe/soumyadip.pdf
<br>Lecture by Sandeep Sen in IIT, saved as India.pdf, printed out.

* Youtube
<br>http://www.youtube.com/watch?v=JwlKLYjP1R8

# Segment Tree and RMQ

* Segment Tree (Set 1: Sum of given range)
<br>http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
<br>https://www.youtube.com/watch?v=ZBHKZF5w4YU (Video: 27 min)

* More detailed analysis:
<br>https://codelucid.wordpress.com/2015/05/27/segment-trees/

* Segment Tree (Set 2: Range Minimum Query)
<br>http://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/

* ALGS4 segment tree implementation (Java)
<br>http://algs4.cs.princeton.edu/99misc/SegmentTree.java.html
<br>
 "The SegmentTree class is an structure for efficient search of cummulative data.
  It performs  Range Minimum Query and Range Sum Query in O(log(n)) time.
  It can be easily customizable to support Range Max Query, Range Multiplication Query etc.
 
  Also it has been developed with "LazyPropagation" for range updates, which means when you
  perform update operations over a range, the update process affects the least nodes as
  possible so that the bigger the range you want to update, the less time it will consume
  to update it. Eventually those changes will be propagated to the children and the whole array
  will be up to date."

