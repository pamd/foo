/* RJMetrics coding question:
 * Suppose we have an array of intervals. Each interval has a boolean flag
 * which should tell whether this interval overlaps with any other intervals.
 * Write code to set the overlap flag in each interval.
 *
 * Extended problem: Merge overlapped intervals.
 * 
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Interval definition
struct Interval {
  Interval(int s, int e, bool flag = false) {
    start = s;
    end = e;
    overlap = flag;
  }

  void print() const {
    cout << "[" << start << ", " << end << "]";
    if (overlap)
      cout << ", overlap" << endl;
    else     
      cout << endl;
  }

  int start;
  int end;
  bool overlap;
};

// Overloaded operator< which is required by std::sort()
bool operator<(const Interval& x, const Interval& y)
{
  return x.start < y.start;
}

// Set overlap flags for each interval in input vector
void setOverlap(vector<Interval>& vec)
{
  // If input vector is empty or has only one interval, do nothing
  if (vec.size() <= 1)
    return;

  sort(vec.begin(), vec.end());
  int max_end = vec[0].end;
  size_t max_end_idx = 0;
  for (size_t i = 1; i < vec.size(); i++) {
    if (vec[i].start <= max_end) {
      vec[i].overlap = true;
      vec[max_end_idx].overlap = true;
    }
    if (vec[i].end > max_end) {
      max_end = vec[i].end;
      max_end_idx = i;
    }
  }      

}

/* Extended problem: merge overlapping intervals
 * In this problem, Interval::overlap is not used at all. */
void merge(vector<Interval>& vec)
{
  // If input vector is empty or has only one interval, do nothing
  if (vec.size() <= 1)
    return;

  sort(vec.begin(), vec.end());
  size_t curr_idx = 0;
  vector<bool> flags(vec.size(), false);
  for (size_t i = 1; i < vec.size(); i++) {
    // Current interval overlaps with previous ones
    if (vec[i].start <= vec[curr_idx].end) {
      if (vec[i].end > vec[curr_idx].end)
	vec[curr_idx].end = vec[i].end; 
    }
    // Current interval does not overlap with previous ones
    else {
      flags[curr_idx] = true;
      curr_idx = i;
    }
  }
  // Do not forget the last interval!
  flags[curr_idx] = true;
  
  // Remove overlapped intervals
  size_t p1 = 0;
  for (size_t i = 0; i < vec.size(); i++) {
    if (flags[i])
      vec[p1++] = vec[i];
  }
  vec.erase(vec.begin() + p1, vec.end());

}

// Test harness
int main()
{
  vector<Interval> v;
  v.push_back(Interval(1, 3));
  v.push_back(Interval(1, 4));
  //v.push_back(Interval(1, 7));
  //v.push_back(Interval(2, 4));
  v.push_back(Interval(5, 8));
  v.push_back(Interval(9, 10));
  v.push_back(Interval(8, 9));

  //setOverlap(v);

  merge(v);

  // Print out intervals for debugging
  for (size_t i = 0; i < v.size(); i++)
    v[i].print();

  return 0;
}
