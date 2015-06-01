/**********************************************************************************
 * Gray code is actually a special case of Hamiltonian cycle.
 * In this program, we use Hamiltonian path detection code
 * (see 9_hamiltonian_path.cpp) to attack gray code problem.
 *
 * When N = 3, 12 Hamiltonian cycles are found:
 *
 *   Cycle #1:	000 100 110 010 011 111 101 001 
 *   Cycle #2:	000 100 110 111 101 001 011 010 
 *   Cycle #3:	000 100 101 001 011 111 110 010 
 *   Cycle #4:	000 100 101 111 110 010 011 001 
 *   Cycle #5:	000 010 110 100 101 111 011 001 
 *   Cycle #6:	000 010 110 111 011 001 101 100 
 *   Cycle #7:	000 010 011 111 110 100 101 001 
 *   Cycle #8:	000 010 011 001 101 111 110 100 
 *   Cycle #9:	000 001 101 111 011 010 110 100 
 *   Cycle #10:	000 001 101 100 110 111 011 010 
 *   Cycle #11:	000 001 011 111 101 100 110 010 
 *   Cycle #12:	000 001 011 010 110 111 101 100 
 *
 * Gray code is cycle #12, #4 is actually the same cycle in reverse direction.
 *
 */

#include <iostream>
#include <vector>

using namespace std;

// Vertex data structure
struct Vertex {
  Vertex() { }

  Vertex(int i, int N) {
    id = i;
    for (int x = N - 1 ; x >= 0; x--) {
      if (i & (1 << x)) 
	code.push_back('1');
      else 
	code.push_back('0');

      edges.push_back(i ^ (1 << x));	
    }
  }

  int id;
  string code;
  vector<int> edges;
}; 

// Undirected graph data structure
struct Graph {
  // N is the number of bits, so the number of vertices is 1<<N
  Graph(int N) { 
    for (int i = 0; i < (1 << N); i++) {
      vertices.push_back(Vertex(i, N));
    }
  }

  vector<Vertex> vertices;
};

// Does current Hamiltonian form a cycle?
// Return true if yes; false otehrwise.
bool validTour(const Graph& G, int end) {
  vector<int> edges = G.vertices[end].edges;
  for (size_t i = 0; i < edges.size(); i++) {
    if (edges[i] == 0)
      return true;
  }

  return false;
}

vector<bool> marked; // vertices on current path
int count = 0;

// Recursive DFS
void dfs(const Graph& G, int v, vector<int>& tour) { 
  marked[v] = true;
  tour.push_back(v);

  // Found one
  if (tour.size() == G.vertices.size()) {
    if (validTour(G, tour.back())) {
      count++;
      cout << "Cycle #" << count << ":\t";
      for (size_t i = 0; i < tour.size(); i++) {
	int x = tour[i];
	cout << G.vertices[x].code << " ";
      }
      cout << endl;
    }
  }
        
  //  for (int w : G.adj(v)) {
  for (size_t i = 0; i < G.vertices[v].edges.size(); i++) {
    int w = G.vertices[v].edges[i];
     if (!marked[w]) // backtrack if w is already part of path
      dfs(G, w, tour);
  }
  
  marked[v] = false; // clean up
  tour.pop_back();
}

// Wrapper that calls dfs()
void HamiltonianPath(const Graph& G) {
  vector<int> tour;
  dfs(G, 0, tour);
}

// Test harness
int main() {
  int N = 3;
  Graph G(N);
  marked.resize(1<<N);

  HamiltonianPath(G);
  
  return 0;
}
  
