/****************************************************************************
 * Another solution from stackoverflow website:
 * "What is an Efficient algorithm to find Area of Overlapping Rectangles?"
 * http://tinyurl.com/2elcjsd
 *
 * Time complexity: O(n^3).
 ***************************************************************************/

#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

// Rectangle class def
class Rectangle {
public:
  // x[0]: left edge, x[1]: right edge; 
  // y[0]: bottom edge, y[1]: top edge (suppose y increases from bottom to top).
  int x[2], y[2];

  // Ctor
  Rectangle(int x1, int y1, int x2, int y2) {
    x[0] = x1;
    y[0] = y1;
    x[1] = x2;
    y[1] = y2; 
  };

  // Helper function
  void print(void) const {
    cout << "Rect: " << x[0] << " " << y[0] << " " 
	 << x[1] << " " << y[1] << " " << endl;
  }

};

// Compare two rectqangles by left edge
bool mycomp1(Rectangle* a, Rectangle* b) {
  return (a->x[0] < b->x[0]);
}

// Compare two rectangles by right edge
bool mycomp2(Rectangle* a, Rectangle* b) {
  return (a->x[1] < b->x[1]);
}

// Recursive binary search to find the first rect in rects whose
// y[0] is equl to or larger than curr_rect->y[0].
// Note that rects is a vector that is always sorted by y[0].
vector<Rectangle *>::iterator bsearch(vector<Rectangle *>& rects, int left, int right, 
				      Rectangle* curr_rect) {
  int mid = (left + right) / 2;
  if (rects[mid]->y[0] == curr_rect->y[0]) {
    if (rects[mid]->y[1] == curr_rect->y[1])
      return rects.begin() + mid;

    if (rects[mid]->y[1] < curr_rect->y[1]) {
      if (mid == right)
	return rects.begin() + mid + 1;
      return bsearch(rects, mid + 1, right, curr_rect);
    }

    if (mid == left)
      return rects.begin() + mid;
    return bsearch(rects, left, mid - 1, curr_rect);
  }

  if (rects[mid]->y[0] < curr_rect->y[0]) {
    if (mid == right) 
      return rects.begin() + mid + 1;
    return bsearch(rects, mid + 1, right, curr_rect);
  }

  if (mid == left) 
    return rects.begin() + mid;
    
  return bsearch(rects, left, mid - 1, curr_rect);
}

// Add rect to rects. 
// dhu: The binary search takes O(logn), but each insertion into the vector
// may take O(n), so the total time complexity of keeping rects sorted is 
// O(n^2). And the total time complexity of the whole algorithm is O(n^3). 
// If we define rects as a binary tree, the total complexity will be reduced
// to O(n^2 * logn).
void add_rect(Rectangle* rect, vector<Rectangle *>& rects) {
  if (rects.size() == 0) 
    rects.push_back(rect);
  else {
    vector<Rectangle *>::iterator it = bsearch(rects, 0, rects.size() - 1, rect);
    rects.insert(it, rect);
  }
}

// Remove rect from rects.
// Since rects is a vector, each deletion will take O(n) time.
void rm_rect(Rectangle *rect, vector<Rectangle *>& rects) {
  vector<Rectangle *>::iterator it = bsearch(rects, 0, rects.size() - 1, rect);
  rects.erase(it);
}

// Calculate the total length in Y direction covered by rects.
// dhu: Because rects is sorted by y[0], the time complexity of this step is O(n).
int find_y_union(vector<Rectangle *> rects) {
  int n = rects.size();
  
  int total_len = 0;
  int start, end;
  
  int i = 0;
  while (i < n) {
    start = rects[i]->y[0];
    end = rects[i]->y[1];
    while (i < n && rects[i]->y[0] <= end) {
      if (rects[i]->y[1] > end) 
	end = rects[i]->y[1];
      i++;
    }

    total_len += end - start;
  }

  return total_len;
}

// Main algorithm
int find_area(vector<Rectangle *> rects_in) {
  vector<Rectangle *> start = rects_in;
  vector<Rectangle *> end = rects_in;
  // "start" holds all rectangles that are sorted by left edges.
  sort(start.begin(), start.end(), mycomp1);

  // "end" holds all rectangles that are sorted by right edges.
  sort(end.begin(), end.end(), mycomp2);

  // "rects" is the active set of rectangles, which will be 
  // sorted by each rectangle's y[0], aka. bottom edge. 
  vector<Rectangle *> rects; 
  int n = rects_in.size();

  int total_area = 0;
  int current = start[0]->x[0];
  int next;
  int i = 0, j = 0;
  while (j < n) {
    // Add rectangles that start at current position.
    while (i < n && start[i]->x[0] == current) {
      // add start[i] to active set
      add_rect(start[i], rects); 
      i++;
    }
  
    // Remove rectangles that end at current position.
    while (j < n && end[j]->x[1] == current) {
      // Remove end[j] from active set 
      rm_rect(end[j], rects);
      j++;
    }

    // Find next event x
    if (i < n && j < n) {
      if (start[i]->x[0] <= end[j]->x[1]) 
	next = start[i]->x[0];
      else 
	next = end[j]->x[1];
    }
    else if (j < n) // i == n && j < n
      next = end[j]->x[1];

    // distance to next event
    int horiz = next - current;
    
    // Figure out vertical dist
    int y_union = find_y_union(rects);
    total_area += y_union * horiz;
    current = next;
  }

  return total_area;
}

// Test harness
int main() {
  vector<Rectangle *> rects;
  rects.push_back(new Rectangle(0, 0, 1, 1)); // Left bottom: (0, 0), right top: (1, 1) 
  rects.push_back(new Rectangle(1, 0, 2, 3));
  rects.push_back(new Rectangle(0, 0, 3, 3));
  rects.push_back(new Rectangle(1, 0, 5, 1));

  cout << find_area(rects) << endl;
}
