/* Given a wooden stick of length L with m markings on it at arbitrary 
 * places (integral), and the markings suggest where the cuts are to 
 * be made accordingly. For chopping a L-length stick into two pieces, 
 * the carpenter charges L dollars (does not matter whether the two pieces 
 * are of equal length or not, i.e, the chopping cost is independent of 
 * where the chopping point is). Design a dynamic programming algorithm 
 * that calculates the minimum overall cost.
 *
 * This problem is DIFFERENT from the cut-rod problem at the beginning 
 * of CLRS "Dynamic Programming" Chapter.
 * It is actually Problem 15-9 "Breaking a string" on CLRS 3rd edition page 410.
 * 
 * Ref:
 * http://www.mitbbs.com/article_t/JobHunting/32540099.html
 * http://stackoverflow.com/questions/8114897/variant-of-rod-cutting
 * http://stackoverflow.com/questions/10068568/dynamic-programming-exercise-for-string-cutting
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdlib.h> 
#include <time.h>  
#include <cassert>
using namespace std;

// Print out optimal cut points in DP
void print(const vector<vector<int> >& first_cut, int start, int end) {
  if (start + 1 < end) {
    cout << "Cut at " << first_cut[start][end] << endl; 
    print(first_cut, start, first_cut[start][end]);
    print(first_cut, first_cut[start][end], end);
  }
}

// DP idea: With m marks, we have m+2 interesting points, 0 is left end-point, 
// marks 1, ..., m, (m+1)th point is the right end point.
// Store the distance from interesting point 0 to interesting point i in an array 
// to calculate costs.
// For each 0 <= l < r <= m+1, let cost[l][r] be the lowest cost for completely 
// chopping the piece between points l and r. The solution is cost[0][m+1].
// Time complexity: O(m^3) 
// Code is based on stackflow: variant-of-rod-cutting.
int calc_dp(const vector<int>& marks, int L) {
  int m = marks.size();

  // Set (m+2) mark positions
  int pos[m+2];
  pos[0] = 0; 
  pos[m+1] = L;
  for (int i = 1; i <= m; ++i) {
    pos[i] = marks[i-1];
  }

  // Initialize DP table
  vector<vector<int> > cost(m+2, vector<int>(m+2, 0));
  vector<vector<int> > first_cut(m+2, vector<int>(m+2, 0));
  for (int x = 0; x < m; ++x) {
    // for pieces with only one mark, there's no choice, cost is length
    cost[x][x+2] = pos[x+2] - pos[x];
    first_cut[x][x+2] = x + 1;
  }

  // Update DP table
  // d+1 is the number of marks between left and right ends
  for (int d = 3; d <= m+1; ++d){      
    for (int x = 0; x <= m+1-d; ++x) { // x is the left most mark
      // What would it cost if we first chop at the left most mark?
      int best_found = cost[x+1][x+d];
      first_cut[x][x+d] = x + 1;
      for (int i = x+2; i < x+d; ++i) { // i is the position of first chop
	if (cost[x][i] + cost[i][x+d] < best_found) {
	  best_found = cost[x][i] + cost[i][x+d];
	  first_cut[x][x+d] = i;
	}
      }
      // Add cost of first chop
      cost[x][x+d] = (pos[x+d] - pos[x]) + best_found;
    }
  }

  print(first_cut, 0, m+1);
  return cost[0][m+1];
}

// MITBBS greedy appraoch: always cut at the mark 
// that is closest to the middle point.
// dhu note: This approach may not give optimal solution.
// See the test case in main().
int calc_greedy(const vector<int>& marks, int left, int right) {
  //cout << "left: " << left << "; right: " << right << endl;
  if (right - left <= 1)
    return 0;

  int L = marks[right] - marks[left];
  int mid = marks[left] + L / 2;
  if (right - left == 2)
    return L;

  int sum = L;
  int base = marks[left];
  vector<int>::const_iterator it = upper_bound(marks.begin() + left, 
  					       marks.begin() + right + 1, mid); 
  if (*it - base + *(it - 1) - base > L) {
    --it;
  }

  if (it == marks.begin() + right)
    --it;
  if (it == marks.begin() + left)
    ++it;

  //cout << "Greedy Cut at " << *it << endl;
  sum += calc_greedy(marks, left, it - marks.begin());
  sum += calc_greedy(marks, it - marks.begin(), right);
  

  return sum;
}

// Wrapper that calls calc_greedy()
int test_greedy(const vector<int>& marks_in, int L) {
  vector<int> marks(marks_in);
  marks.push_back(0);
  marks.push_back(L);
  sort(marks.begin(), marks.end());
  return calc_greedy(marks, 0, marks.size() - 1);
}

// Test harness
int main() {
  // DP gives optimal solution for the following input array,
  // but the solution from greedy approach is NOT optimal. 
  int L = 20;
  int a[] = { 8, 9, 15, 17, 19 };
  vector<int> marks(a, a + sizeof(a) / sizeof(int));

  cout << "DP: " << calc_dp(marks, L) << endl;
  // DP cut sequences: 
  // Cut #1:  8, cost is 20;
  // Cut #2: 15, cost is 12;
  // Cut #3:  9, cost is  7;
  // Cut #4: 17, cost is  5;
  // Cut #5: 19, cost is  3;
  // Total cost: 47.

  cout << "Greedy: " << test_greedy(marks, L) << endl;
  // Greedy cut sequences:
  // Cut #1:  9, cost is 20;
  // Cut #2:  8, cost is  9;
  // Cut #3: 15, cost is 11;
  // Cut #4: 17, cost is  5;
  // Cut #5: 19, cost is  3;
  // Total cost: 48.

  /*  
  // Random test
  int L = 20;
  int m = 5;
  srand (time(NULL));
  vector<int> v(L - 1);
  for (size_t i = 0; i < v.size(); ++i) {
    v[i] = i + 1;
  }

  int trial = 200;
  for (int t = 0; t < trial; ++t) {
    cout << "Trail #" << t + 1 << endl;
    random_shuffle(v.begin(), v.end());
    vector<int> marks(v.begin(), v.begin() + m);
    sort(marks.begin(), marks.end());
    for (size_t i = 0; i < marks.size(); i++) {
      cout << marks[i] << " ";
    }
    cout << endl;

    int dp = calc_dp(marks, L);
    int greedy = test_greedy(marks, L);
    if (dp != greedy) {
      cout << "DP: " << dp << endl;
      cout << "Greedy: " << greedy << endl;
      cout << endl;
      exit(0);
    }

  }
  */

  return 0;
}

