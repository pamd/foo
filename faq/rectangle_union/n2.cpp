/* dhu O(n^2) time complexity solution. 
 * This algorithm is inspired by the TopCoder line sweep tutorial:
 *
 * "With the right data structures, this can be implemented in O(N^2) time 
 * (hint: use a boolean array to store the active set rather than a balanced 
 * binary tree, and pre-sort the entire set of horizontal edges ...".
 *
 */

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Rectangle def
struct Rectangle {
  // Ctor
  Rectangle(int a = 0, int b = 0, int c = 0, int d = 0) {
    x1 = a, x2 = b;
    y1 = c, y2 = d;
  }

  // Overloaded operator<, which is defined to sort rectangles in Y direction
  bool operator<(const Rectangle& rhs) const {
    return y1 < rhs.y1;
  }

  int x1, x2; // x1: left edge; x2: right edge
  int y1, y2; // y1: top edge; y2: bottom edge

};

// Edges on X direction
struct X_Edge {
  // Ctor
  X_Edge(int v, bool flag, size_t i) : val(v), isLeft(flag), idx(i) { }

  // Overloaded operator<, defined for std::sort
  bool operator<(const X_Edge& rhs) const {
    if (val != rhs.val)
      return val < rhs.val;
    
    // If two edges have equal X coordinate, always put left edge before right edge
    if (isLeft && !rhs.isLeft) 
      return true;

    return false;
  }

  int val;
  bool isLeft;
  size_t idx;
};

// Calculate merged length in Y direction.
// This is equavalent to leetcode problem "Merge Intervals",
// except that here we only return merged length. 
int get_Y_union(const vector<Rectangle>& rects, const vector<bool>& isActive) {
  int y_union = 0;
  bool find_first = false;
  int tmp_start = 0;
  int tmp_end = 0;
  for (size_t i = 0; i < rects.size(); i++) {
    if (!isActive[i])
      continue;
    
    if (!find_first) {
      tmp_start = rects[i].y1;
      tmp_end = rects[i].y2;
      find_first = true;
      continue;
    }
    
    if (rects[i].y1 > tmp_end) {
      y_union += tmp_end - tmp_start;
      tmp_start = rects[i].y1;
      tmp_start = rects[i].y2;
    }
    else 
      tmp_end = max(tmp_end, rects[i].y2);
  }
  
  y_union += tmp_end - tmp_start;

  return y_union;
}

// Calculate rectangle union area
int getArea(vector<Rectangle>& rects) {
  if (rects.size() == 0)
    return 0;

  // Sort all rectangles by starting point of Y 
  sort(rects.begin(), rects.end());

  // Boolean array which tells whether rects[i] should be 
  // included or not when calculation Y union. 
  vector<bool> isActive(rects.size(), false);

  vector<X_Edge> vx; // Left and right edges
  for (size_t i = 0; i < rects.size(); i++) {
    vx.push_back(X_Edge(rects[i].x1, true, i));
    vx.push_back(X_Edge(rects[i].x2, false, i));
  }
  sort(vx.begin(), vx.end()); // Sort them by value

  int area = 0;
  int x0 = vx[0].val;

  // Calculate the area that is between each consecutive X edges.
  // Total time complexity is O(n^2).
  for (size_t i = 0; i < vx.size(); i++) { // O(n)
    if (vx[i].val != x0) {   
      int x1 = vx[i].val;
      int y_union = get_Y_union(rects, isActive); // O(n)
      area += (x1 - x0) * y_union;
      x0 = x1;
    }

    if (vx[i].isLeft) 
      isActive[vx[i].idx] = true;
    else
      isActive[vx[i].idx] = false;
  }

  return area;
}

// Test harness
int main() {
  vector<Rectangle> rects;

  // Test case #1: total area is 11
  /*
  rects.push_back(Rectangle(0, 1, 0, 1)); 
  rects.push_back(Rectangle(1, 2, 0, 3));
  rects.push_back(Rectangle(0, 3, 0, 3));
  rects.push_back(Rectangle(1, 5, 0, 1));    
  */

  // Test case #2: Total area is (3 * n + 1) 
  int n = 100;
  for (int i = 0; i < n; i++) {
    Rectangle tmp(i, i + 2, i, i + 2);
    rects.push_back(tmp);
  }
  
  int area = getArea(rects);
  cout << "Total area: " << area << endl;

  return 0;
}
