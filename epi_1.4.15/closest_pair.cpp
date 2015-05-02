/* Given N points in a place with their (x,y) coordinates, find two points 
 * with least distance between them. 
 */

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <utility>
#include <assert.h>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

// Point def
struct Point {
  double x, y;

  Point(double vx, double vy) : x(vx), y(vy) { }
  
  // Comparison function defined for std:set<Point>.
  // Note that it is sorted by Y coordinates! 
  bool operator<(const Point& rhs) const {
    return y < rhs.y;
  }

};

// Return distance between two points
double distance(const Point& p1, const Point& p2) {
  int x = p1.x - p2.x;
  int y = p1.y - p2.y;
  return sqrt(x * x + y * y);
}

// Compare two Point objects by X coodinates
bool xcmp(const Point& p1, const Point& p2) {
  return p1.x < p2.x;
}

// Compare two Point objects by Y coodinates
bool ycmp(const Point& p1, const Point& p2) {
  return p1.y < p2.y;
}

// dhu: brute-force approach to confirm the answer
double brute(const vector<Point>& vec) {
  if (vec.size() < 2)
    return -1.0;

  double ret = distance(vec[0], vec[1]);
  size_t p1 = 0;
  size_t p2 = 1; 
  for (size_t i = 0; i < vec.size(); i++) {
    for (size_t j = i + 1; j < vec.size(); j++) {
      double foo = distance(vec[i], vec[j]);
      if (foo < ret) {
	p1 = i;
	p2 = j;
	ret = foo;
      }
    }
  }

  return ret;
}

// Algorithm based on CLRS textbook
double clrs_recursive(const vector<Point>& X, const vector<Point>& Y);

// CLRS algorithm
double clrs(const vector<Point>& vec) {
  vector<Point> X, Y;
  for (size_t i = 0; i < vec.size(); i++) {
    X.push_back(vec[i]);
    Y.push_back(vec[i]);
  }

  sort(X.begin(), X.end(), xcmp);
  sort(Y.begin(), Y.end(), ycmp);

  return clrs_recursive(X, Y);
}

// Helper function which checks whether input points have identical X coordinates
bool alignedOnY(const vector<Point>& X) {
  double x0 = X[0].x;
  for (size_t i = 1; i < X.size(); i++) {
    if (X[i].x != x0)
      return false;
  }

  return true;
}

/* CLRS: Recursive function. 
 * This program does not consider the edge case of all points having identical 
 * X coordinates, in which we can never divide the points into left and right 
 * halves. To solve this problem, we use a function alignOnY() to deal with it. 
 */ 
double clrs_recursive(const vector<Point>& X, const vector<Point>& Y) {
  if (X.size() < 3)
    return brute(X);

  // If all input points have identical X coordinates, do not divide.
  // Instead, calculate minimum distance by scaning points in Y. 
  if (alignedOnY(X)) {
    double ret = Y[1].y - Y[0].y;
    for (size_t i = 2; i < Y.size(); i++) {
      if (ret > Y[i].y - Y[i - 1].y)
	ret = Y[i].y - Y[i - 1].y;
    }
    return ret;
  }

  size_t idx = X.size() / 2;
  // X = x_separator is the vertical line that divides 
  // all points into left and right halves.
  double x_separator = (X[idx].x + X[idx + 1].x) / 2; 

  // Generate XL and XR, which can be seen as the reverse of merge sort.
  // When the two elements in the middle have different X coordinates,
  // We can write: 
  // vector<Point> XL(X.begin(), X.begin() + idx + 1);
  // vector<Point> XR(X.begin() + idx + 1, X.end());
  // But if the two elements are identical, different ways of dividing
  // X and Y may put same point in different left/right groups.
  // So we divide X and Y in exactly the same way. 
  vector<Point> XL, XR;
  for (size_t i = 0; i < X.size(); i++) {
    if (X[i].x < x_separator)
      XL.push_back(X[i]);
    else
      XR.push_back(X[i]);
  }

  // Same idea to generate YL and YR
  vector<Point> YL, YR;
  for (size_t i = 0; i < Y.size(); i++) {
    if (Y[i].x < x_separator)
      YL.push_back(Y[i]);
    else
      YR.push_back(Y[i]);
  }

  double left = clrs_recursive(XL, YL);
  double right = clrs_recursive(XR, YR);
  double min = left;
  if (left < 0 || (right > 0 && left > right))
    min = right;

  vector<Point> subset;
  double search_len = min;
  for (size_t i = 0; i < Y.size(); i++) {
    if (Y[i].x > x_separator + search_len || Y[i].x < x_separator - search_len)
      continue;
    subset.push_back(Y[i]);
  }

  // Only consider points in subset[]
  for (size_t i = 0; i < subset.size() - 1; i++) {
    for (size_t j = i + 1; j < subset.size(); j++) {
      if (subset[j].y - subset[i].y > search_len)
	break;
      double tmp_distance = distance(subset[i], subset[j]);
      if (tmp_distance < min)
	min = tmp_distance;
    }
  }

  return min;
}

/* dhu optimization of CLRS approach: we can sort input points by only 
 * Y coordinates, then find the median of X coordinates, based on which 
 * the points will be divided into left and right halves, then use 
 * the same divide and conquer approach. 
 */
double clrs2_recursive(const vector<Point>&);

// Wrapper 
double clrs2(const vector<Point>& vec) {
  vector<Point> Y(vec);
  sort(Y.begin(), Y.end(), ycmp);

  return clrs2_recursive(Y);
}

// Get median of X coodinates
double getMedianX(vector<Point>& vec) {
  nth_element(vec.begin(), vec.begin() + vec.size() / 2, vec.end(), xcmp); 
  double x1 = vec[vec.size() / 2].x;
  // Return x1 if the number of elements in vec is odd
  if (vec.size() % 2) {
    return x1;
  }

  // If the number of elements in vec is even, find the other middle element. 
  nth_element(vec.begin(), vec.begin() + vec.size() / 2 - 1, vec.end(), xcmp);
  double x2 = vec[vec.size() / 2 - 1].x;
  return (x1 + x2) / 2.0;
}

// dhu improved divide-conquer approach, in which we do not need 
// to worry about the corner case of identical X coordinates.
double clrs2_recursive(const vector<Point>& Y) {
  if (Y.size() < 3)
    return brute(Y);

  vector<Point> tmp(Y);
  double median = getMedianX(tmp);
  vector<Point> left, right;
  bool go_left = true;
  // Divide step: reverse process of mergesort. 
  // Both left and right are still sorted by Y coordinates.
  for (size_t i = 0; i < Y.size(); i++) {
    if (Y[i].x < median)
      left.push_back(Y[i]);
    else if (Y[i].x > median)
      right.push_back(Y[i]);
    else if (go_left) {
      left.push_back(Y[i]);
      go_left = false;
    }
    else { 
      right.push_back(Y[i]);
      go_left = true;
    }
  }

  double min_left = clrs2_recursive(left);
  double min_right = clrs2_recursive(right);

  // Conquer step:
  double min = min_left;
  if (min_left < 0 || (min_right > 0 && min_left > min_right))
    min = min_right;
  
  // Only consider points around the X separator line
  vector<Point> subset;
  double search_len = min;
  for (size_t i = 0; i < Y.size(); i++) {
    if (Y[i].x > median + min || Y[i].x < median - min)
      continue;
    subset.push_back(Y[i]);
  }
  // Check points in subset
  for (size_t i = 0; i < subset.size() - 1; i++) {
    for (size_t j = i + 1; j < subset.size(); j++) {
      if (subset[j].y - subset[i].y > search_len)
	break;
      double tmp_distance = distance(subset[i], subset[j]);
      if (tmp_distance < min)
	min = tmp_distance;
    }
  }

  return min;
}

/* Another O(n*logn) solution that uses line sweep idea.
 * The implementation relies on STL heavily.
 *
 * Refer to:
 * http://community.topcoder.com/tc?module=Static&d1=tutorials&d2=lineSweep
 * 
 * Code is based on: 
 * http://olympiad.cs.uct.ac.za/presentations/camp1.../linesweep.odp
 */

/* Original code, compact, but not so easy to understand.
#define px second
#define py first

typedef pair<long long, long long> pairll;

int n;
pairll pnts [100000];
set<pairll> box;
double best;

int compx(pairll a, pairll b) { 
  return a.px < b.px; 
}

int main () {
  scanf("%d", &n);
  for (int i=0;i<n;++i) 
    scanf("%lld %lld", &pnts[i].px, &pnts[i].py);
  sort(pnts, pnts+n, compx);
  best = 1500000000; // INF
  box.insert(pnts[0]);
  int left = 0;
  for (int i=1;i<n;++i) {
    while (left<i && pnts[i].px-pnts[left].px > best) 
      box.erase(pnts[left++]);
    for (typeof(box.begin()) it=box.lower_bound(make_pair(pnts[i].py-best, pnts[i].px-best)); 
	 it! =box.end() && pnts[i].py+best>=it->py; it++) 
      best = min(best, sqrt(pow(pnts[i].py - it->py, 2.0)+pow(pnts[i].px - it->px, 2.0)));
    box.insert(pnts[i]);
  }

  printf("%.2f\n", best);
  return 0;
}
*/

// dhu revision based on topcoder solution.
double line_sweep(vector<Point>& points) {
  if (points.size() < 2)
    return 0;

  set<Point> box; // Elements in box will be sorted by Y coordinates.
  sort(points.begin(), points.end(), xcmp); // Sort input points by X coordinates.

  double best = distance(points[0], points[1]); 
  box.insert(points[0]);
  box.insert(points[1]);

  size_t left = 0;
  // Process n points in increasing order of X coordinates.
  // It takes O(logn) time to process each point, so total 
  // time complexity is O(n*logn).
  for (size_t i = 2; i < points.size(); ++i) {
    // Remove points in box that are too far from points[i] in X direction.
    // Time complexity: O(logn). 
    // Each point will be erased from the box at most once.
    while (left < i && points[i].x - points[left].x > best) 
      box.erase(points[left++]);

    // Set "it" to the lowest point (in Y direction) that 
    // satisfies it->y >= points[i].y - best.
    Point tmp(points[i].x - best, points[i].y - best);
    set<Point>::iterator it = box.lower_bound(tmp); 
    // There will be at most 6 points in the box whose y coordinate is 
    // between [points[i].y - best, points[i].y + best], so the following
    // "while" loop only takes O(1) time.
    while (it != box.end() && it->y <= points[i].y + best) { 
      best = min(best, distance(points[i], *it));
      it++;
    }

    // Insert current point into the box. This takes O(logn) time too.
    // --------------------------------------------------------------------
    // IMPORTANT: box is a std::set instead of std::multi_set, so if
    // the Y coordinate of points[i] is equal to Y coordinate of any 
    // point in box, that point in box will be replaced by points[i]. 
    // This makes sense because we are scanning input points in X direction,
    // from left to right. For any two points whose Y coordinates are equal, 
    // the point on right side will be always closer to the points that we 
    // have not scanned. So the point on the left side can be ignored.
    // ---------------------------------------------------------------------
    box.insert(points[i]);
  }

  return best;
}

// main function
int main() {  
  vector<Point> vec;
  vec.push_back(Point(0, 1));
  vec.push_back(Point(2, 8));
  vec.push_back(Point(3, 2));
  vec.push_back(Point(4, 9));
  vec.push_back(Point(1, 7));
  
  cout << "CLRS answer: " << clrs(vec) << endl;
  cout << "dhu  answer: " << clrs2(vec) << endl;
  cout << "Brute force answer: " << brute(vec) << endl;
  cout << "Line sweep: " << line_sweep(vec) << endl;

  return 0;
}
