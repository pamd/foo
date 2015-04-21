/* Werid BFS and DFS implementations from the book "Programming Problems", 
 * which is written by B. Green. 
 */

#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <queue>

using namespace std;

// Vertex definition
struct Node {
  Node(char ci) : val(ci) { }

  char val;
  vector<Node*> neighbors;
};

/* BFS: page 99, Listing 8.3.
 */
void bfs(Node* origin) {
  set<Node*> visited;   // Original code called this variable queued, very confusing 

  queue<Node*> q;
  q.push(origin);
  while (!q.empty()) {
    Node* current = q.front();
    q.pop();
    cout << current-> val << endl; // visit current node
    // Instead of inserting current in the following for loop, insert it here.
    visited.insert(current);

    for (size_t i = 0; i < current->neighbors.size(); i++) {
      if (visited.find(current->neighbors[i]) == visited.end()) {
	/* If we insert current here, current may be inserted multiple times.
	 * Although it still gives correct output, I found it very misleading! */
	// visited.insert(current);
	q.push(current->neighbors[i]);
      }
    } // end of for loop
  } // end of while loop
}

/* DFS: page 104, Listing 8.8.
 * If input graph is a binary tree, the following function
 * will do a post-order traversal. 
 */
void dfs(Node* origin) {
  set<Node*> queued;
  stack<pair<Node*, vector<Node*>::iterator> > stk;

  stk.push(pair<Node*, vector<Node*>::iterator>(origin, origin->neighbors.begin()));
  queued.insert(origin);

  while (!stk.empty()) {
    Node* current = stk.top().first;
    vector<Node*>::iterator& neighbor = stk.top().second;
    if (neighbor != current->neighbors.end()) {
      Node* next = *neighbor;
      ++neighbor;
      if (queued.find(next) == queued.end()) {
	stk.push(pair<Node*, vector<Node*>::iterator>(next, next->neighbors.begin()));
	/* If we insert next into queued here, then queued keeps track of whether
	 * a node has been inserted into stack or not. It does NOT keep track of 
	 * whether a node has been visited or not.
	 */
	queued.insert(next);
      }
      continue;
    }
    
    cout << current->val << endl;  // Visit the node

    // It also works if we insert the current node here
    //queued.insert(current);  

    stk.pop();
  }

}

int main() {
  Node* A = new Node('A');
  Node* B = new Node('B');
  Node* C = new Node('C');
  Node* D = new Node('D');

  A->neighbors.push_back(B);
  A->neighbors.push_back(D);
  B->neighbors.push_back(C);
  D->neighbors.push_back(A);

  bfs(A);

  //dfs(A);
}
