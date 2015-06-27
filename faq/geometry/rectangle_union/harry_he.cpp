/* Harry He's approach to get area of a set of rectangles whose edges 
 * are parallel to X-axis or Y-axis. Code copied from:
 *
 * http://codercareer.blogspot.com/2011/12/no-27-area-of-rectangles.html
 * 
 * dhu note: the solution is straightforward, 
 * but time complexity seems to be O(n^3). 
 */

#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;

/* Rect def by Harry He 
 * Assumming: left <= right; top <= bottom. */
struct Rect {
    int left;
    int right;
    int top;
    int bottom;
};

/* Range def by Harry He: range in X or Y direction. */
struct Range {
  // less should be always less than greater
  int less;
  int greater;

  // Ctor
  Range(int l, int g) {
    less = (l < g) ? l : g;
    greater = (l + g) - less;
  }

  // Does current range overlap with input Range?
  bool IsOverlapping(const Range& other) {
    return !(less > other.greater || other.less > greater);
  }

  // Merge current range with input Range
  void Merge(const Range& other) {
    if (IsOverlapping(other)) {
      less = (less < other.less) ? less : other.less;
      greater = (greater > other.greater) ? greater : other.greater;
    }
  }
};

/* Rect comparison function based on input rectangles' right sides.
 * (defined to sort Rect). */
bool operator <(const Rect& rect1, const Rect& rect2) {
  return (rect1.right < rect2.right);
}

// Harry He helper function: get x-values of all input rectangles.
void GetAllX(const vector<Rect>& rects, vector<int>& xes) {
  vector<Rect>::const_iterator iter = rects.begin();
  for (; iter != rects.end(); ++iter) {
    xes.push_back(iter->left);
    xes.push_back(iter->right);
  }
}

/* Helper function:
 * InsertRangeY() inserts a range of y-value into a list. 
 * When the range overlaps with another range in the list, 
 * remove the existing range, then insert a new merged range. 
 * O(n) time complexity. */
void InsertRangeY(list<Range>& ranges, Range& range_in) {
  list<Range>::iterator iter = ranges.begin();
  while (iter != ranges.end()) {
    // Input range overlaps with current Y range on input list
    if (range_in.IsOverlapping(*iter)) {
      range_in.Merge(*iter);
      
      list<Range>::iterator iterCopy = iter;
      ++iter;
      ranges.erase(iterCopy);
    }
    else
      ++iter;
  }

  ranges.push_back(range_in);
}

/* Helper function:
 * GetRangesOfY() gets the ranges of Y of rectangles that are covered by
 * the input X range. Note that the input X range may cover multiple 
 * non-overlapping rectangles. For example, Rect1 and Rect2 in the figure 
 * do not overlap with each other. Therefore, we cannot merge their ranges 
 * of y-values. That is why this function needs a list of ranges of y-values
 * for an input X range. 
 * O(n^2) time complexity. */
void GetRangesOfY(const vector<Rect>& rects, vector<Rect>::const_iterator iterRect, 
		  const Range& rangeX, list<Range>& ranges) {
  for (; iterRect != rects.end(); ++iterRect) {
    // If current rectangle is covered by input X range, insert it into rangesofY
    if (rangeX.less < iterRect->right && rangeX.greater > iterRect->left)
      InsertRangeY(ranges, Range(iterRect->top, iterRect->bottom));
  }
}

/* Helper function:
 * GetRectArea() gets the total area of all 
 * rectangle pieces in a range of x coordinates. */
int GetRectArea(const Range& rangeX, const list<Range>& rangesOfY) {
  int width = rangeX.greater - rangeX.less;
  
  list<Range>::const_iterator iter = rangesOfY.begin();
  int area = 0;
  for (; iter != rangesOfY.end(); ++iter) {
    int height = iter->greater - iter->less;
    area += width * height;
  }

  return area;
}

/* Harry He main algorithm function: 
 * First get x coordinates of all rectangles, then check whether each 
 * rectangle fills into each range formed by two neighboring x-values. 
 * If multiple rectangles fill into an x-value range, merge their ranges 
 * of y-value before calculating the area of a piece of merged rectangle.
 *
 * For optimization purpose, we sort all input rectangles according to their 
 * x coordinates of right edges, and sort the vector of all x coordinates. */
int GetArea(vector<Rect>& rects) {
  // Sort rectangles according to x-value of right edges
  sort(rects.begin(), rects.end()); // O(n*logn)

  vector<int> xes;
  GetAllX(rects, xes);
  sort(xes.begin(), xes.end()); // O(n*logn)

  int area = 0;
  vector<int>::iterator iterX1 = xes.begin();
  vector<Rect>::const_iterator iterRect = rects.begin();
  for (; iterX1 != xes.end() && iterX1 != xes.end() - 1; ++iterX1) {
    vector<int>::iterator iterX2 = iterX1 + 1;
    // Ignore duplicated X-values
    if (*iterX1 == *iterX2) 
      continue;

    Range rangeX(*iterX1, *iterX2);      
    while (iterRect->right < *iterX1)
      ++iterRect;
    
    // For each x and its right side neighbor, create a list 
    // of Y ranges that are covered by this X range.
    list<Range> rangesOfY; 
    GetRangesOfY(rects, iterRect, rangeX, rangesOfY);
    area += GetRectArea(rangeX, rangesOfY); 
  }

  return area;
}

// Test harness
int main() {
  vector<Rect *> rects;
  rects.push_back(new Rect(0, 0, 1, 1)); // Left bottom: (0, 0), right top: (1, 1) 
  rects.push_back(new Rect(1, 0, 2, 3));
  rects.push_back(new Rect(0, 0, 3, 3));
  rects.push_back(new Rect(1, 0, 5, 1));

  cout << find_area(rects) << endl;
}
