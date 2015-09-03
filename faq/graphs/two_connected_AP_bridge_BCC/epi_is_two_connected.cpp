// Based on https://github.com/epibook/epibook.github.io/blob/master/solutions/cpp/2-for-all.cc
//
// Assume input graph is undirected and connected, determine whether the graph is still connected
// after we move ANY edge in the graph.
//
// Note: a 2-connected graph is NOT necessarily a biconnected graph. See is_biconnected.cpp for details.

#include <vector>
#include <limits>
#include <cassert>
#include <iostream>

using namespace std;

struct GraphVertex {
  int discovery, low;  // discovery: discovery time; low: lowest discovery time of ancestors.
  vector<GraphVertex*> edges;

  GraphVertex() : discovery(0), low(numeric_limits<int>::max()) {
  }

};

bool is_two_connected(GraphVertex* cur, GraphVertex* pre, int time) {
  cur->discovery = ++time;
  for (GraphVertex*& next : cur->edges) {
    if (next != pre) {
      if (next->discovery != 0) {  // Back edge: next has been visited before.
        cur->low = min(cur->low, next->discovery);
      }
      else {  // Forward edge: next is not visited yet.
        if (!is_two_connected(next, cur, time)) {
          return false;
        }
        cur->low = min(cur->low, next->low); // Reset cur->low in post-order
      }
    } // end of "if (next != pre)"
  } // end of "for"

  return (pre == nullptr || cur->low < cur->discovery);
}

bool IsGraphFaultTolerant(vector<GraphVertex>* G) {
  if (!G->empty()) {
    return is_two_connected(&G->front(), nullptr, 0);
  }
  return true;
}

void TestTriangle() {
  vector<GraphVertex> G(3);
  G[0].edges.emplace_back(&G[1]);
  G[0].edges.emplace_back(&G[2]);
  G[1].edges.emplace_back(&G[0]);
  G[1].edges.emplace_back(&G[2]);
  G[2].edges.emplace_back(&G[0]);
  G[2].edges.emplace_back(&G[1]);

  bool result = IsGraphFaultTolerant(&G);
  assert(true == result);
  for (int i = 0; i < 3; ++i) {
    cout << i << ": discovery = " << G[i].discovery << ", ";
    cout << "low = " << G[i].low << endl;
  }
}

int main() {
  TestTriangle();

  return 0;
}
