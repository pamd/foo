
* Bellman-Ford algorithm is used to find the shortest path from a given source node.

* On ALGS4 book, it is implemented by a queue. See pages 672-675.

* Bellman-Ford algorithm can be used to detect negative cycles in a graph.

For undirected graph, we can pick up any vertex as source and vertex. 

But for directed node, if we randomly pick up one vertex as the source,
it is possible that the negative cycle is not reachable from the source.

To solve this problem, a naive approach is to pick up each vertex as source
and run the algorithm |V| times. Since the itme complexity for one run is 
O(V*E), the total time complexity will be O(V*V*E), which is not optimal.

Another approach is to create a "dummy" vertex S', then create edges from
S' to every other vertexes. Set length of these new edges to 0. Since 
these new edges are all outbound from S', it will not create any "fake"
negative cycle that does not exist in the original graph. Then run the
algorithm using S' as source. 

Refer to:
---------

http://www.cs.illinois.edu/class/fa07/cs473ug/Lectures/lecture12.pdf
(With a lot of insightful figures)
 
EPI Problem 13.12: Arbitrage
(Mentioned the dummy vertex idea without details)
