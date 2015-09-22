/* Variant 16.4.1 Part 1: Let G be a connected undirected graph. 
 * A vertex of G is an "articulation point" (AP) if its removal 
 * disconnects G. Find all APs in input graph.
 *
 * The main algorithm is based on:
 * http://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
 * 
 * Other interesting references include:
 * http://www.eecs.wsu.edu/~holder/courses/CptS223/spr08/slides/graphapps.pdf
 * (very helpful on DFS and Euler Circuit, locally saved as pdf/wsu_graphapps.pdf)
 *
 * https://courses.cs.washington.edu/courses/cse421/04su/slides/artic.pdf
 * (geeksforgeeks figure copied from it, locally saved as pdf/washington_artic.pdf)
 *
 * Also refer to CLRS 3rd edition Problem 22-2, pp621-622.
 *
 */  

#include<iostream>
#include <list>

using namespace std;

// A class that represents an undirected graph
class Graph {
  int V;          // Number. of vertices
  list<int>* adj; // Dynamic array of adjacency lists
  void AP_util(int v, bool visited[], int discovery[], int low[], 
	      int parent[], bool ap[]);
public:
  Graph(int V);               // Constructor
  void addEdge(int v, int w); // Add an edge to graph
  void AP();                  // Print out articulation points
};
 
Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w) {
  adj[v].push_back(w);
  adj[w].push_back(v);  // Note: the graph is undirected
}
 
// Recursive function that finds articulation points using DFS traversal.
// u --> The vertex to be visited next
// visited[ ] --> keeps track of visited vertices
// discovery[ ] --> stores discovery times of visited vertices
// parent[ ] --> stores parent vertices in DFS tree
// ap[ ] --> stores articulation points
// low[u] --> stores the lowest vertex ID that vertex u can possibly reach in a SIMPLE cycle
void Graph::AP_util(int u, bool visited[], int discovery[], 
		   int low[], int parent[], bool ap[]) {
  // A static variable is used for simplicity, 
  // we can avoid it by passing a pointer.
  static int time = 0;
 
  // Mark the current node as visited
  visited[u] = true;
  
  // Initially, discovery[u] and low[u] are equal,
  // then we try to decrease low[u] in recursion.
  discovery[u] = low[u] = ++time;
 
  // Go through all vertices aadjacent to this
  list<int>::iterator i;
  int children = 0;   // Count of children in DFS Tree
  for (i = adj[u].begin(); i != adj[u].end(); ++i) {
    int v = *i;  // v is the other side of an edge that connects u
    
    // If v is not visited yet, then make it a child of u
    // in DFS tree and recur for it.
    if (!visited[v]) {
      children++;
      parent[v] = u;
      AP_util(v, visited, discovery, low, parent, ap);
 
      // Check if the subtree rooted with v has a connection to
      // one of the ancestors of u
      low[u] = min(low[u], low[v]);
      
      // u will be an articulation point in following two cases:
      // (1) u is root of DFS tree and has two or more chilren.
      // If children is 1, then either u is a leaf node, or u
      // is in ONE AND ONLY ONE loop. In either case, u is not an AP.
      if (parent[u] == -1 && children > 1)
	ap[u] = true;
      
      // (2) u is not root, and low value of one of its child 
      // is equal to or larger than discovery value of u.
      if (parent[u] != -1 && discovery[u] <= low[v])
	ap[u] = true;
    }
    // If v is already visited and v is not the parent of u, 
    // update low[u] for parent function calls.
    else if (v != parent[u]) {
      low[u] = min(low[u], discovery[v]);
      // dhu: We can NOT change the above line into:
      //   low[u] = min(low[u], low[v]);
      // because low[v] could be a vertex that is reachable from v in another cycle,
      // so low[v] is not reachable from u in a SIMPLE cycle. 
      // In graph G3 in main(), if we remove the edge (1, 6), and run the algorithm using
      //   low[u] = min(low[u], low[v]), the program WON't be able to detect vertex #1 as
      // an AP, but the original implementation will find vertex #1 as AP.
    }
    // If v is already visited and v is parent of u, then
    // u->v is the same edge along which we discovered u. 
    // So this edge should be skipped.
    // else { do nothing ... }
  }
}
 
// The function to do DFS traversal. It uses recursive function AP_util()
void Graph::AP() {
  // Mark all the vertices as not visited
  bool* visited = new bool[V];
  int* discovery = new int[V];
  int* low = new int[V];
  int* parent = new int[V];
  bool* ap = new bool[V]; // To store articulation points
  
  // Initialize parent and visited, and ap(articulation point) arrays
  for (int i = 0; i < V; i++) {
    parent[i] = -1;
    visited[i] = false;
    ap[i] = false;
  }
 
  // Call the recursive helper function to find articulation points
  // in DFS tree rooted with vertex 'i'
  for (int i = 0; i < V; i++) {
    if (visited[i] == false)
      AP_util(i, visited, discovery, low, parent, ap);
  }

  // Now ap[] contains articulation points, print them
  for (int i = 0; i < V; i++) {
    if (ap[i] == true)
      cout << i << " ";
  }
}
 
// Driver program to test above function
int main() {
  // Create graphs given in above diagrams
  cout << "Articulation points in first graph:\n";
  Graph g1(5);
  g1.addEdge(1, 0);
  g1.addEdge(0, 2);
  g1.addEdge(2, 1);
  g1.addEdge(0, 3);
  g1.addEdge(3, 4);
  g1.AP();
  cout << endl << endl;

  cout << "Articulation points in second graph:\n";
  Graph g2(4);
  g2.addEdge(0, 1);
  g2.addEdge(1, 2);
  g2.addEdge(2, 3);
  g2.AP();
  cout << endl << endl;

  cout << "Articulation points in third graph:\n";
  Graph g3(7);
  g3.addEdge(0, 1);
  g3.addEdge(1, 2);
  g3.addEdge(2, 0);
  g3.addEdge(1, 3);
  g3.addEdge(1, 4);
 
  // If we remove the following edge, and set:
  //   low[u] = min(low[u], low[v]);
  // then the algorithm won't be able to detect vertex #1 as AP.
  // See comments above.

  //g3.addEdge(1, 6);

  g3.addEdge(3, 5);
  g3.addEdge(4, 5);
  g3.AP();
  cout << endl << endl;

  cout << "Articulation points in 4th graph:\n";
  Graph g4(3);
  g4.addEdge(0, 1);
  g4.addEdge(1, 2);
  g3.AP();
  cout << endl << endl;

  return 0;
}
