// Based on https://github.com/epibook/epibook.github.io/blob/master/solutions/cpp/2-for-all.cc
//
// Assume input graph is undirected and connected, determine whether the graph is still connected
// after we move ANY edge in the graph.
//
// Note: a 2-connected graph is NOT necessarily a biconnected graph. See is_biconnected.cpp for details.


struct GraphVertex {
  int d, l;  // d: discovery time; l: lowest discovery time of ancestors.
  vector<GraphVertex*> edges;

  GraphVertex() : d(0), l(numeric_limits<int>::max()) {
  }

};

bool IsGraphFaultTolerant(vector<GraphVertex>* G) {
  if (!G->empty()) {
    return is_two_connected(&G->front(), nullptr, 0);
  }
  return true;
}

bool is_two_connected(GraphVertex* cur, GraphVertex* pre, int time) {
  cur->d = ++time;
  for (GraphVertex*& next : cur->edges) {
    if (next != pre) {
      if (next->d != 0) {  // Back edge.
        cur->l = min(cur->l, next->d);
      }
      else {  // Forward edge.
        if (!is_two_connected(next, cur, time)) {
          return false;
        }
        cur->l = min(cur->l, next->l);
      }
    } // end of "if (next != pre)"
  } // end of "for"

  return (pre == nullptr || cur->l < cur->d);
}
