References:
------------

* http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lineSweep
TopCoder Linesweep Tutorial.

* line_sweep.pdf: good supplementary material with Topcoder tutorial.

* Jon L. Bentley: "Algorithms for Klee’s rectangle problems"
Unpublished notes, Computer Science Department, Carnegie Mellon University, 1977
dhu: FIRST publication that solves the problem in O(nlogn), but never found online.

* S4.pdf
(http://wwwisg.cs.uni-magdeburg.de/ag/lehre/WS1213/GDS/slides/S4.pdf)
According to slide #12, Jon L. Bentley's algorithm:
(1) use a plane-sweep algorithm;
(2) maintain the intersection intervals of rectangles and sweep line;
(3) maintain the length of the union of the intersection intervals;
(4) use an augmented semi-static segment tree for that purpose.
See slide #10 on "semi-static segment tree".

* Wikipedia "Klee's measure problem"
http://en.wikipedia.org/wiki/Klee's_measure_problem

* UIUC brief notes on Klee's measure problem
http://compgeom.cs.uiuc.edu/~jeffe/open/klee.html

* Book: "Computational Geometry: algorithms and applications" 
Springer-Verlag, 2nd Edtion, 2000
Written by: de Berg, Mark; van Kreveld, Marc; Overmars, Mark; Schwarzkopf, Otfried
dhu: Referred to by Wikipedia "Segment tree".

* Book: "Computational Geometry: An Introduction", 
Springer-Verlag, 1985
Written by: Franco P. Preparata and Michael Ian Shamos
Referred to by Wikipedia Klee's measure problem" and "Interval tree".

------------------------------------------------------------------------------------

* http://codercareer.blogspot.com/2011/12/no-27-area-of-rectangles.html
Harry He Blog, terrible implementation.

* http://stackoverflow.com/questions/244452/what-is-an-efficient-algorithm-to-find-area-of-overlapping-rectangles
Stackoverflow discussions, not worth the time.

* http://ideone.com/MpLqp
dhu: Interval Tree approach in C++, probably NOT worth the time.
