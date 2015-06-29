References:
------------

* http://codercareer.blogspot.com/2011/12/no-27-area-of-rectangles.html
Harry He Blog, terrible implementation.

* http://stackoverflow.com/questions/244452/what-is-an-efficient-algorithm-to-find-area-of-overlapping-rectangles
Stackoverflow discussions, not worth the time.

* http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lineSweep
TopCoder Linesweep Tutorial.

* Segment Tree (Stanford CS166)
http://web.stanford.edu/class/archive/cs/cs166/cs166.1146/lectures/00/Extra00.pdf
Very nice introduction, with helpful animations.

* Jon L. Bentley: "Algorithms for Klee’s rectangle problems"
Unpublished notes, Computer Science Department, Carnegie Mellon University, 1977
dhu: FIRST publication that solves the problem in O(nlogn), but never found online.

* http://wwwisg.cs.uni-magdeburg.de/ag/lehre/WS1213/GDS/slides/S4.pdf
The BEST tutorial I found online, covers segment tree and Jon Bentley's 
approach very well. 

According to slide #12, Jon L. Bentley's algorithm:
(1) use a plane-sweep algorithm;
(2) maintain the intersection intervals of rectangles and sweep line;
(3) maintain the length of the union of the intersection intervals;
(4) use an augmented semi-static segment tree for that purpose.

See slide #10 on "semi-static segment tree".

* http://wwwisg.cs.uni-magdeburg.de/ag/lehre/WS1112/GDS/slides/S7.pdf
dhu: Another tutorial that covers both segment tree and interval tree.

* https://www.cs.duke.edu/courses/fall05/cps234/notes/lecture07.pdf
dhu: tutorial from Duke. Nice summary of segment tree and interval tree.
Printed out.

* Wikipedia "Klee's measure problem"
http://en.wikipedia.org/wiki/Klee's_measure_problem

* Wikipedia "Segment Tree"
dhu: The figure is misleading. Copied from de Berg book, see below.
NOTE that to solve the rectangle union problem, Bentley actually uses 
a semi-static segment tree, which is different from what this webpage 
describes. 

* Wikipedia "Interval Tree"
Printed out.

* http://www.cs.nthu.edu.tw/~wkhon/ds/ds10/tutorial/tutorial6.pdf
dhu: Tutorial from National TsingHua Univ at Taiwan. Note that the 
segment tree in this tutorial does NOT treat each starting and ending 
points as a seperate interval. This is different from many approaches 
in many other tutorials (such as Mark de berg's book and s4.pdf).

* http://compgeom.cs.uiuc.edu/~jeffe/open/klee.html
UIUC brief notes.

* http://ideone.com/MpLqp
dhu: Interval Tree approach in C++, probably NOT worth the time.

* http://www.youtube.com/watch?v=JwlKLYjP1R8
* http://www.cse.iitd.ernet.in/~ssen/cs852/newscribe/soumyadip.pdf
dhu: Lecture by Sandeep Sen in IIT, details not provided.

* Book: "Computational Geometry: algorithms and applications" 
Springer-Verlag, 2nd Edtion, 2000
Written by: de Berg, Mark; van Kreveld, Marc; Overmars, Mark; Schwarzkopf, Otfried
dhu: Referred to by Wikipedia "Segment tree".

* Book: "Computational Geometry: An Introduction", 
Springer-Verlag, 1985
Written by: Franco P. Preparata and Michael Ian Shamos
Referred to by Wikipedia Klee's measure problem" and "Interval tree".

------------------------------------------------------------------------------------

* Segment Tree (Set 1: Sum of given range)
http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
https://www.youtube.com/watch?v=ZBHKZF5w4YU (Video: 27 min)

* More detailed analysis:
https://codelucid.wordpress.com/2015/05/27/segment-trees/

* Segment Tree (Set 2: Range Minimum Query)
http://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/

* ALGS4 segment tree implementation (Java)
http://algs4.cs.princeton.edu/99misc/SegmentTree.java.html
 "The SegmentTree class is an structure for efficient search of cummulative data.
  It performs  Range Minimum Query and Range Sum Query in O(log(n)) time.
  It can be easily customizable to support Range Max Query, Range Multiplication Query etc.
 
  Also it has been developed with "LazyPropagation" for range updates, which means when you
  perform update operations over a range, the update process affects the least nodes as
  possible so that the bigger the range you want to update, the less time it will consume
  to update it. Eventually those changes will be propagated to the children and the whole array
  will be up to date."

* Binary Indexed Tree (Fenwick tree)
http://www.geeksforgeeks.org/binary-indexed-tree-or-fenwick-tree-2/
https://theoryofprogramming.wordpress.com/2014/12/24/binary-indexed-tree-or-fenwick-tree/
https://www.youtube.com/watch?v=CWDQJGaN1gY&feature=youtu.be (23 min)
http://algs4.cs.princeton.edu/99misc/FenwickTree.java.html (ALGS4 implementation)

* Interval Tree
http://www.geeksforgeeks.org/interval-tree/
