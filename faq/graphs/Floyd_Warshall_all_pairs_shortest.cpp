#include <vector>
#include <limits>
#include <iostream>

using namespace std;

/* Floyd-Warshall Algorithm to find all pairs shortest distance.
 * Time complexity: O(|V|^3); space complexity: O(|V|^2)
 * Code is based on: EPI Solution 13.11.
 * Also refer to:
 * UCB "Algorithms" PDF book, "Dynamic Programming" chapter;
 * CLRS Exercise 25.2-4 (online solution available).
 */
void floyd_warshall(vector<vector<int> >& distances) {
  // Three layers of "for" loop, that's it!
  unsigned n = distances.size();
  for (size_t k = 0; k < n; k++) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
	if (distances[i][k] == numeric_limits<int>::max() || 
	    distances[k][j] == numeric_limits<int>::max())
	  continue;
	
	distances[i][j] = min(distances[i][j], distances[i][k] + distances[k][j]);
      }
    }
  }

}

// Test case
void test() {
  unsigned n = 9;
  vector<vector<int> > distances(n, vector<int>(n, numeric_limits<int>::max()));

  // This step is actually optional.
  for (size_t i = 0; i < distances.size(); i++) 
    distances[i][i] = 0;

  distances[0][1] = 13, distances[1][0] = 13;
  distances[0][2] = 24, distances[2][0] = 24;
  distances[0][3] = 28, distances[3][0] = 28;
  distances[0][4] = 25, distances[4][0] = 25;
  distances[0][5] = 30, distances[5][0] = 30;
  distances[0][6] = 31, distances[6][0] = 31; 
  distances[0][7] = 10, distances[7][0] = 10;
  distances[0][8] = 29, distances[8][0] = 29;
  
  distances[1][8] = 7,  distances[8][1] = 7;
  distances[2][8] = 1,  distances[8][2] = 1;
  distances[7][8] = 16, distances[8][7] = 16;

  floyd_warshall(distances);

  // Print out results
  for (size_t i = 0; i < n; i++) {
    cout << i << ":\t";
    for (size_t j = 0; j < n; j++) 
      cout << distances[i][j] << "\t";
    cout << endl;
  }
}

// Test harness
int main() {
  test();

  return 0;
}
