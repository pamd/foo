/* Variant 16.4.1 Part 3: Let G be a connected graph. A biconnected component (BCC) 
 * of G is a maximal set of edges having the property that any two edges in the set 
 * lie on common simple cycle. Design algorithms for computing BCCs.
 *
 * According to this page:
 *    http://en.wikipedia.org/wiki/Biconnected_graph
 * A BCC should not have any articulation point, so an articulation point 
 * in input graph will be on multiple BCCs. See the figure in:
 *    http://en.wikipedia.org/wiki/Biconnected_component
 * An articulation point (AP) will belong to multiple BCCs.
 *
 * The following lecture talks about finding BCCs:
 *    https://www.cs.purdue.edu/homes/ayg/CS251/slides/chap9d.pdf
 * (Locally saved as pdf/purdure_chap9d.pdf)  
 * 
 * Detailed pseudo code based on:
 * -------------------------------------------------------------
 *  http://www.cs.umd.edu/class/fall2005/cmsc451/biconcomps.pdf
 * (Locally saved as: umd_biconcomps.pdf  
 *
 */
 
 

#include<iostream>
#include <list>
#include <stack>

using namespace std;

stack<pair<int, int> > stk;

void print_stk(int u, int v) {
   while (!stk.empty()) {
      int first = stk.top().first;
      int second = stk.top().second;
      stk.pop();
      cout << first << "---" << second << endl;

      if (first == u && second == v) {
         break;
      }
   }
   cout << endl;
}

// A class that represents an undirected graph
class Graph {
public:
  Graph(int V);               // Constructor
  void addEdge(int v, int w); // Add an edge to graph
  void find_bcc();            // Find BCC

private:
  void bcc_dfs(int v, bool visited[], int discovery[], int low[], int parent[]);

  int V;          // Number. of vertices
  list<int>* adj; // Dynamic array of adjacency lists
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
// u:           the vertex to be visited next
// visited[]:   keeps tract of visited vertices
// discovery[]: stores discovery times of visited vertices
// parent[]:    stores parent vertices in DFS tree
void Graph::bcc_dfs(int u, bool visited[], int discovery[], int low[], int parent[]) {
  // A static variable is used for simplicity, we can avoid it by passing a pointer.
  static int time = 0;

  // Mark the current node as visited
  visited[u] = true;

  // Initially, discovery[u] and low[u] are equal,
  // then we try to decrease low[u] in recursion.
  discovery[u] = low[u] = ++time;

  // Go through all vertices adjacent to current one.
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i) {
    int v = *i;  // v is the other side of an edge that connects u

    // If v is not visited yet, then make it a child of u in DFS tree and recur.
    if (!visited[v]) {
      stk.push(make_pair<int, int>(u, v)); // Push new edge into stack
      parent[v] = u;
      bcc_dfs(v, visited, discovery, low, parent);

      // Post-order:
      if (discovery[u] <= low[v]) {  // Print out current BCC
         print_stk(u, v);
      }
      // Check whether the subtree rooted at v has a connection to
      // one of the u's ancestors. If it does, reset low[u] to low[v],
      // which is <= low[u].
      low[u] = min(low[u], low[v]);
    }

    // If v is already visited, AND v is not parent of u, AND u is visited
    // later than v, then push the edge "u--v" into the stack, and update low[u].
    // This update will also trigger the update of low[] on u's ancestors.
    else if (v != parent[u] && discovery[u] > discovery[v]) {
       stk.push(make_pair<int, int>(u, v)); // Push back edge into stack
       low[u] = min(low[u], discovery[v]);
    }

  }
}

// The function to do DFS traversal. It calls recursive function bcc_dfs()
void Graph::find_bcc() {
  bool* visited = new bool[V];
  int* discovery = new int[V];
  int* low = new int[V];
  int* parent = new int[V];

  // Initialize parent and visited, and ap(articulation point) arrays
  for (int i = 0; i < V; i++) {
    parent[i] = -1;
    visited[i] = false;
  }

  // Call the recursive function to find articulation point(s)
  // in DFS tree rooted with vertex 'i'
  for (int i = 0; i < V; i++) {
     if (visited[i] == false) {
        bcc_dfs(i, visited, discovery, low, parent);
     }
  }
}

// Driver program to test above function
int main() {
  // Create graphs given in above diagrams
  Graph g1(5);
  g1.addEdge(1, 0);
  g1.addEdge(0, 2);
  g1.addEdge(2, 1);
  g1.addEdge(0, 3);
  g1.addEdge(3, 4);
  cout << "BCC in first graph:\n";
  g1.find_bcc();
  cout << endl;
  // Three BCCs in first graph:
  // #1:
  //  2---0
  //  1---2
  //  0---1
  //
  // #2:
  //  3---4
  //
  // #3:
  //  0---3


  Graph g2(4);
  g2.addEdge(0, 1);
  g2.addEdge(1, 2);
  g2.addEdge(2, 3);
  cout << "BCC in second graph:\n";
  g2.find_bcc();
  cout << endl;
  // Three BCCs in second graph:
  // #1:
  //  2---3
  //
  // #2:
  //  1---2
  //
  // #3:
  //  0---1



  Graph g3(7);
  g3.addEdge(0, 1);
  g3.addEdge(1, 2);
  g3.addEdge(2, 0);
  g3.addEdge(1, 3);
  g3.addEdge(1, 4);
  //g3.addEdge(1, 6);
  g3.addEdge(3, 5);
  g3.addEdge(4, 5);

  cout << "BCC in third graph:\n";
  g3.find_bcc();
  // Two BCCs if edge (1, 6) is removed:
  // #1:
  //  4---1
  //  5---4
  //  3---5
  //  1---3
  //
  // #2:
  //  2---0
  //  1---2
  //  0---1

  return 0;
}
