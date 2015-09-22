// Tarjan’s Algorithm to find Strongly Connected Components (SCC)
// http://www.geeksforgeeks.org/tarjan-algorithm-find-strongly-connected-components/

#include <iostream>
#include <list>
#include <stack>
#define NIL -1

using namespace std;

// A class that represents an directed graph
class Graph
{
   int V;           // No. of vertices
   list<int> * adj; // A dynamic array of adjacency lists

   // A Recursive DFS based function used by SCC()
   void SCCUtil(int u, int discovery[], int low[], stack<int> *st, bool in_stack[]);

public:
   Graph(int V);               // Constructor
   void addEdge(int v, int w); // Add an edge to graph
   void SCC();                 // Print strongly connected components
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}

// A recursive function that finds and prints strongly connected
// components using DFS traversal
// u: The vertex to be visited next
// discovery[]: Stores discovery times of visited vertices
// low[]: Earliest visited vertex (the vertex with minimum discovery time)
//        that can be reached from subtree rooted with current vertex
// *st -- >> To store all the connected ancestors (could be part
//           of SCC)
// in_stack[] --> bit/index array for faster check whether
//                  a node is in stack
void Graph::SCCUtil(int u, int discovery[], int low[], stack<int> *stk, bool in_stack[])
{
   // A static variable is used for simplicity, we can avoid use
   // of static variable by passing a pointer.
   static int time = 0;

   // Initialize discovery time and low value
   discovery[u] = low[u] = ++time;
   stk->push(u);
   in_stack[u] = true;

   // Go through all vertices adjacent to this
   list<int>::iterator i;
   for (i = adj[u].begin(); i != adj[u].end(); ++i) {
      int v = *i;  // v is current adjacent of 'u'

      // If v is not visited yet, then recur for it
      if (discovery[v] == -1) {
         SCCUtil(v, discovery, low, st, in_stack);
         // Check whether the subtree rooted with 'v' has a connection to
         // one of the ancestors of 'u'.
         low[u]  = min(low[u], low[v]);
      }

      // Update low value of 'u' only if 'v' is still in stack
      // (i.e. it's a back edge, not cross edge).
      // Case 2 (per above discussion on Discovery and Low value)
      else if (in_stack[v] == true) {
         low[u]  = min(low[u], discovery[v]);
      }
   }

   // Head node found, pop the stack and print an SCC.
   int w = 0;  // To store stack extracted vertices
   if (low[u] == discovery[u]) {
      while (stk->top() != u) {
         w = (int) stk->top();
         cout << w << " ";
         in_stack[w] = false;
         stk->pop();
      }
      w = (int) stk->top();
      cout << w << "\n";
      in_stack[w] = false;
      stk->pop();
   }
}

// The function to do DFS traversal. It uses SCCUtil()
void Graph::SCC()
{
   int *discovery = new int[V];
   int *low = new int[V];
   bool *in_stack = new bool[V];
   stack<int> *stk = new stack<int>();

   // Initialize discovery and low, and in_stack arrays
   for (int i = 0; i < V; i++) {
      discovery[i] = NIL;
      low[i] = NIL;
      in_stack[i] = false;
   }

   // Call the recursive helper function to find strongly
   // connected components in DFS tree with vertex 'i'
   for (int i = 0; i < V; i++) {
      if (discovery[i] == NIL) {
         SCCUtil(i, discovery, low, stk, in_stack);
      }
   }
}

// Driver program to test above function
int main()
{
    cout << "\nSCCs in first graph \n";
    Graph g1(5);
    g1.addEdge(1, 0);
    g1.addEdge(0, 2);
    g1.addEdge(2, 1);
    g1.addEdge(0, 3);
    g1.addEdge(3, 4);
    g1.SCC();

    cout << "\nSCCs in second graph \n";
    Graph g2(4);
    g2.addEdge(0, 1);
    g2.addEdge(1, 2);
    g2.addEdge(2, 3);
    g2.SCC();

    cout << "\nSCCs in third graph \n";
    Graph g3(7);
    g3.addEdge(0, 1);
    g3.addEdge(1, 2);
    g3.addEdge(2, 0);
    g3.addEdge(1, 3);
    g3.addEdge(1, 4);
    g3.addEdge(1, 6);
    g3.addEdge(3, 5);
    g3.addEdge(4, 5);
    g3.SCC();

    cout << "\nSCCs in fourth graph \n";
    Graph g4(11);
    g4.addEdge(0,1);g4.addEdge(0,3);
    g4.addEdge(1,2);g4.addEdge(1,4);
    g4.addEdge(2,0);g4.addEdge(2,6);
    g4.addEdge(3,2);
    g4.addEdge(4,5);g4.addEdge(4,6);
    g4.addEdge(5,6);g4.addEdge(5,7);g4.addEdge(5,8);g4.addEdge(5,9);
    g4.addEdge(6,4);
    g4.addEdge(7,9);
    g4.addEdge(8,9);
    g4.addEdge(9,8);
    g4.SCC();

    cout << "\nSCCs in fifth graph \n";
    Graph g5(5);
    g5.addEdge(0,1);
    g5.addEdge(1,2);
    g5.addEdge(2,3);
    g5.addEdge(2,4);
    g5.addEdge(3,0);
    g5.addEdge(4,2);
    g5.SCC();

    return 0;
}

/*
Output:

SCCs in first graph
4
3
1 2 0

SCCs in second graph
3
2
1
0

SCCs in third graph
5
3
4
6
2 1 0

SCCs in fourth graph
8 9
7
5 4 6
3 2 1 0
10

SCCs in fifth graph
4 3 2 1 0
*/
