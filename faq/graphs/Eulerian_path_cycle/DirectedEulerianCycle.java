/************************************************************************************
 *
 *  ALGS4 Exercise 4.2.20 (page 598): Directed Eulerian cycle
 *  ---------------------------------------------------------------------------------
 *  An Eulerian cycle is a directed cycle that contains each edge exactly once. 
 *  Write a graph client Euler that finds an Eulerian cycle or reports that no 
 *  such tour exists. 
 *
 *  Hint: Prove that a digraph G has a directed Eulerian cycle if and only if 
 *  G is connected and each vertex has its indegree equal to its outdegree.
 *
 *  Solution copied from ALGS4 web site.
 *  This solution is actually trickier than the one given in hint.
 *  It is based on Hierholzer's algorithm in 1873, see detailed description on:
 *      http://en.wikipedia.org/wiki/Euler_path#Hierholzer.27s_algorithm
 *  It is easy to tell whether Euler cycle exists in an input graph or not,
 *  BUT IT IS NOT EASY TO FIND THE CYCLE!!!
 *
 *  Compilation:  javac DirectedEulerianCycle.java
 *  Dependencies: Digraph.java Stack.java Queue.java StdOut.java
 *
 *  Time complexity: O(E + V) 
 * 
 *  dhu intuitive solution based on hint:
 *  --------------------------------------
 *  (1) Scan each vertex, use an int array to keep track of the number of 
 *  in-degree and out-degree. When scan is done, check each vertex to make sure
 *  in-degree is equal to out-degree.
 *
 *  (2) Even if each vertex has equal in-degree and out-degree, Eulerian cycle may 
 *  still not exist when input graph is not connected. So we need to run DFS to 
 *  confirm that input graph is connected.
 *
 ************************************************************************************/

public class DirectedEulerianCycle {
    private Stack<Integer> tour = new Stack<Integer>();
    private boolean isEulerian = true;
    private Stack<Integer> stack = new Stack<Integer>();
    private Queue<Integer>[] adj;

    public DirectedEulerianCycle(Digraph G) {
        // Create local copy of adjacency lists
        adj = (Queue<Integer>[]) new Queue[G.V()];
        for (int v = 0; v < G.V(); v++) {
            adj[v] = new Queue<Integer>();
            for (int w : G.adj(v))
                adj[v].enqueue(w);
        }

        // Find Eulerian tour
        stack.push(0);
        while (!stack.isEmpty()) {
            int s = stack.pop();
            tour.push(s);
            int v = s;
	    // If the vertex that was just popped out of stack 
	    // still has outbound edges, pop it back into the stack.  
            while (!adj[v].isEmpty()) {
                stack.push(v);
                v = adj[v].dequeue();
            }

            if (v != s) 
		isEulerian = false;
        }

        // Check if all edges have been used. 
	// (If input graph is not connected, then some edges haven't 
	// been used, so the graph must have no Eulerian cycle.) 
        for (int v = 0; v < G.V(); v++) {
            if (!adj[v].isEmpty()) 
		isEulerian = false;
	}
    }

    // Return Eulerian tour, or null if no such tour
    public Iterable<Integer> tour() {
        if (!isEulerian) 
	    return null;
        return tour;
    }

    // Does the digraph have an Eulerian tour?
    public boolean isEulerian() {
        return isEulerian;
    }

    // Test harness
    public static void main(String[] args) {
        int V = Integer.parseInt(args[0]);
        int E = Integer.parseInt(args[1]);

        // Random graph of V vertices and approximately E edges
        // with indegree[v] = outdegree[v] for all vertices
        Digraph G = new Digraph(V);
        int[] indegree  = new int[V];
        int[] outdegree = new int[V];
        int deficit = 0;
        for (int i = 0; i < E - deficit/2; i++) {
            int v = StdRandom.uniform(V);
            int w = StdRandom.uniform(V);
            if (v == w) { 
		i--; 
		continue; 
	    }
            G.addEdge(v, w);
            if (outdegree[v] >= indegree[v]) 
		deficit++;
            else                             
		deficit--;

            outdegree[v]++;

            if (indegree[w] >= outdegree[w]) 
		deficit++;
            else                             
		deficit--;

            indegree[w]++;
        }

        while (deficit > 0) {
            int v = StdRandom.uniform(V);
            int w = StdRandom.uniform(V);
            if (v == w) 
		continue;
            if (outdegree[v] >= indegree[v]) 
		continue;
            if (indegree[w]  >= outdegree[w]) 
		continue;

            G.addEdge(v, w);

            if (outdegree[v] >= indegree[v]) 
		deficit++;
            else  
		deficit--;

            outdegree[v]++;

            if (indegree[w] >= outdegree[w]) 
		deficit++;
            else
		deficit--;

            indegree[w]++;
        }

        StdOut.println(G);

        DirectedEulerianCycle euler = new DirectedEulerianCycle(G);
        if (euler.isEulerian()) {
            for (int v : euler.tour()) {
                StdOut.print(v + " ");
            }
            StdOut.println();
        }
        else {
            StdOut.println("Not eulerian");
        }
    }

}

