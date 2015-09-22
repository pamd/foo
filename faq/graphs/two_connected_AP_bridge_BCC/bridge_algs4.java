/* See ALGS4 excersize 4.1.36 (page 562): Edge connectivity. 
 * Source code Bridge.java" can be found at ALGS4 website:
 *    http://algs4.cs.princeton.edu/41undirected/Bridge.java.html
 *
 * Note that Input graph is UNDIRECTED, not DIRECTED.
 */

/*************************************************************************
 *  Compilation:  javac Bridge.java
 *  Execution:    java  Bridge V E
 *  Dependencies: Graph.java GraphGenerator.java
 *
 *  Identifies bridge edges and prints them out. This decomposes
 *  a graph into two-edge connected components.
 *  Runs in O(V + E) time.
 *
 *  Key quantity:  low[v] = minimum DFS preorder number of v
 *  and the set of vertices w for which there is a back edge (x, w),
 *  with x a descendant of v, and w an ancestor of v.
 *
 *  Note: Code assumes no parallel edges, e.g., two parallel edges
 *  would be incorrectly identified as bridges.
 *
 *************************************************************************/

public class Bridge {
    private int bridges;      // number of bridges
    private int cnt;          // counter
    private int[] pre;        // pre[v] = order in which dfs examines v
    private int[] low;        // low[v] = lowest preorder of any vertex connected to v

    public Bridge(Graph G) {
        low = new int[G.V()];
        pre = new int[G.V()];
        for (int v = 0; v < G.V(); v++) {
           low[v] = -1;
        }

        for (int v = 0; v < G.V(); v++) {
           pre[v] = -1;
        }

        for (int v = 0; v < G.V(); v++) {
            if (pre[v] == -1) {
               dfs(G, v, v); // NOTE that the last two parameters are identical!
	    }
	}
    }

    public int components() {
       return bridges + 1;
    }

    private void dfs(Graph G, int u, int v) {
        pre[v] = cnt++;
        low[v] = pre[v];
        for (int w : G.adj(v)) {
           if (pre[w] == -1) { // w is not visited yet
              dfs(G, v, w);
              low[v] = Math.min(low[v], low[w]); // post-order update
              // dhu: this criterion is DIFFERENT from the one in bridge_geeks.cpp
              if (low[w] == pre[w]) {
                 StdOut.println(v + "-" + w + " is a bridge");
                 bridges++;
              }
           }
           // If w has been visited, and w is NOT u (aka. the edge from v
           // to w is not the back edge of u to v), update low[v].
            else if (w != u) {
               low[v] = Math.min(low[v], pre[w]);
	    }
	}
    }

    // test client
    public static void main(String[] args) {
        int V = Integer.parseInt(args[0]);
        int E = Integer.parseInt(args[1]);
        Graph G = GraphGenerator.simple(V, E);
        StdOut.println(G);

        Bridge bridge = new Bridge(G);
        StdOut.println("Edge connected components = " + bridge.components());
    }


}
