
1. Dijkstra algorithm on Euclidean plane (Sedgewick Princeton 2007)
https://www.cs.princeton.edu/~rs/AlgsDS07/15ShortestPaths.pdf (slide #30)
(Saved as 15_shortest_path.pdf)

(1) At the very beginning, we can set the priority of s to either 0 or Euclidean_distance(s, t),
and insert it into the priority queue.

(2) For edge v-w, use weight d(v, w) + Euclidean_distance(w, t) – Euclidean_distance(v, t) instead of d(v, w) only.
In another word: 

    priority[w] = min(priority[w], priority[v] + d(v, w) + Euclidean_distance(w, t) – Euclidean_distance(v, t));

Here Euclidean_distance(v, t) should be substracted because the priority[v] already includes Euclidean_distance(v, t).
When the priority of s is set to Euclidean_distance(s, t), the priority of each node x in the queue is actually
the sum of the shortest actual path from s to x and Euclidean_distance(x, t). In A* algorithm's terms, the shortest 
actual path from s to x is g(x), and Euclidean_distance(x, t) is h(x), thus it is a special case of A* algorithm.
For more details, see wikipedia and Amit's A* webpage.

(3) If the priority of s is set to 0, then when t is scanned at the end of the algorithm, the shortest path 
from s to t will be actually the priority of t plus Euclidean_distance(s, t). On the other hand, if the priority
of s is set to Euclidean_distance(s, t), then the priority of t will be the shortest path from s to t. 

(4) In practice, only O(sqrt(V)) vertices examined, because A* algorithm only scans the node that are most likely to give
the optimal path. For more details, see Amit's A* webpage.

2. A* search algorithm on Wikipedia:
http://en.wikipedia.org/wiki/A*_search_algorithm

3. Amit's A* Pages (everythong you want to know about Dijkstra and A*):
http://theory.stanford.edu/~amitp/GameProgramming/index.html
http://www.redblobgames.com/pathfinding/a-star/introduction.html (with animations)

4. Efficient Point-to-Point Shortest Path Algorithms (Princeton 2006), Slides #12-13 
http://www.cs.princeton.edu/courses/archive/spr06/cos423/Handouts/EPP%20shortest%20path%20algorithms.pdf
(Saved as EPP_shortest_pat3h.pdf)

5. A_star.cpp: a simple (and buggy) A* example
Based on B. Green "Programming Problems" Volume 1.
