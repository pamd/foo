/* Dijkstra via priority_queue and std::set. Based on code Topcoder tutorial:
 * http://tinyurl.com/a3nwt4m
 *
 * Consider we have a weighted directed graph that is stored as:
 *    vector< vector< pair<int,int> > > G; 
 * G.size() is the number of vertices in our graph,
 * G[i].size() is the number of vertices directly reachable from vertex i,
 * G[i][j].first is the index of j-th vertex reachable from vertex i,
 * G[i][j].second is the length of the edge heading from vertex i to vertex G[i][j].first.
 */

#include <vector>
#include <queue>
#include <iostream>
#include <set>

using namespace std;

// Dijkstra via std::priority_queue
void dijkstra_pq(const vector< vector< pair<int,int> > >& G) {
  // D keeps track of the distance from source vertex to each vertex. 
  // The final result will be saved in it.
  vector<int> D(N, INT_MAX); 

  /* priority_queue with reverse comparison operator, so top() will return the 
   * least distance. Initialize the start vertex, suppose it is vertex zero. */
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > Q; 

  D[0] = 0;
  Q.push(pair<int, int>(0, 0));
  
  // Iterate each vertex in the queue
  while (!Q.empty()) {    
    // fetch the nearest element
    pair<int, int> top = Q.top();
    Q.pop();
    
    // v is vertex index, d is the distance
    int v = top.second;
    int d = top.first;
    
    /* This check is very important. We analyze each vertex only once. The other 
     * occurrences of it on queue (added earlier) will have greater distance. */
    if (d <= D[v]) {
      // iterate through all outcoming edges from v
      for (vector<pair<int, int> >::iterator it = G[v].begin; it != G[v].end(); ++it) {
	int v2 = it->first;
	int cost = it->second;
	if (D[v2] > D[v] + cost) {
	  D[v2] = D[v] + cost;               // update distance if possible
	  Q.push(pair<int, int>(D[v2], v2)); // add the vertex to queue
	}
      } // end of for loop

    } // end of if

  } // end of while loop

}

// Dijkstra via std::set
void dijkstra_set(const vector< vector< pair<int,int> > >& G) {
  vi D(N, INT_MAX);
  
  // start vertex
  set<pair<int, int> > Q;
  D[0] = 0;
  Q.insert(pair<int, int>(0, 0));
  
  while (!Q.empty()) {
    // Fetch the closest to start element from the queue implemented via std::set
    pair<int, int> top = *Q.begin();
    Q.erase(Q.begin());
    int v = top.second;
    int d = top.first;
    
    /* Here we do not need to check whether the distance is perfect, because 
     * new vertices will always add up in proper way in this implementation. */
    for (vector<pair<int, int> >::iterator it = G[v].begin; it != G[v].end(); ++it) {
      int v2 = it->first, cost = it->second;
      if (D[v2] > D[v] + cost) {
	/* This operation can not be done with priority_queue, 
	 * because priority_queue does not support DECREASE_KEY. */
	if (D[v2] != INT_MAX) 
	  Q.erase(Q.find(pair<int, int>(D[v2], v2)));

	D[v2] = D[v] + cost;
	Q.insert(pair<int, int>(D[v2], v2));
      } // end of if

    } // end of tr

  } // end of while loop
  
}
