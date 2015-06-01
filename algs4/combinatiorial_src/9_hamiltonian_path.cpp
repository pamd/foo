/**********************************************************************
 * Slide #44-46: 
 * Find a simple path that visits every vertex exactly once.
 * Remark: Eulerian path is easy, but Hamiltonian path is NP-complete.
 * 
 * Backtracking solution. To find Hamilton path starting at v:
 * (1) Add v to current path.
 * (2) For each vertex w adjacent to v, find a simple path starting at w 
 *     using all remaining vertices
 * (3) Clean up: remove v from current path.
 */

// Modified from Java code on slide #47

int count = 0;       // number of Hamiltonian paths
vector<bool> marked(G.V()); // vertices on current path

// Recursive DFS, depth is length of current path (depth of recursion)
void dfs(Graph G, int v, int depth) { 
  marked[v] = true;
  
  // Found one
  if (depth == G.V()) 
    count++;
  
  for (int w : G.adj(v)) {
    if (!marked[w]) // backtrack if w is already part of path
      dfs(G, w, depth+1);
  }
  
  marked[v] = false; // clean up
}

void HamiltonianPath(Graph G) {
  // Try each vertex as the starting point
  for (int v = 0; v < G.V(); v++)
    dfs(G, v, 1);
}




