/* Leetcode OJ: Given a collection of intervals, merge all overlapping intervals.
 * For example, given [1,3], [2,6], [8,10], [15,18], return [1,6], [8,10], [15,18]. 
 */

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Definition for an interval.
struct Interval {
  int start;
  int end;

  Interval() : start(0), end(0) { }
  Interval(int s, int e) : start(s), end(e) {}
};
 
bool cmp_interval(const Interval& v1, const Interval& v2) {
  return v1.start < v2.start;
}

// Leetcode solution: 52ms for large dataset
class Solution1 {
public:
  vector<Interval> merge(vector<Interval> &intervals) {
    vector<Interval> ret;
    if (intervals.size() == 0)
      return ret;

    sort(intervals.begin(), intervals.end(), cmp_interval);
    Interval tmp(intervals[0]);
    for (size_t i = 1; i < intervals.size(); i++) {
      if (intervals[i].start <= tmp.end) {
	if (intervals[i].end > tmp.end)
	  tmp.end = intervals[i].end;
      }
      else {
	ret.push_back(tmp);
	tmp = intervals[i];
      }
    }
    ret.push_back(tmp);

    return ret;
  }
};

// EndPoint class, defined for Solution2
struct EndPoint {
  EndPoint(int v = 0, bool flag = false) : val(v), isLeft(flag) { }

  // Overloaded operator<
  bool operator<(const EndPoint& p2) const {
    if (val != p2.val)
      return val < p2.val;
    
    // If two end points are equal, always put the starting point before ending point
    if (isLeft && !p2.isLeft)
      return true;

    return false;
  }
 
  int val;
  bool isLeft;
};

// Solution #2: sort all ending points, then increment or decrement 
// a counter, which will tell whether we meet a gap in merged interval.
class Solution2 {
public:
  vector<Interval> merge(vector<Interval> &intervals) {
    vector<Interval> ret;
    if (intervals.size() == 0)
      return ret;

    vector<EndPoint> points;
    for (size_t i = 0; i < intervals.size(); i++) {
      points.push_back(EndPoint(intervals[i].start, true));      
      points.push_back(EndPoint(intervals[i].end, false));
    }

    sort(points.begin(), points.end());
    int cnt = 0;
    int curr_start = 0;
    for (size_t i = 0; i < points.size(); i++) {
      if (points[i].isLeft) {
	if (cnt == 0)
	  curr_start = points[i].val;
	++cnt;
      }
      else {
	--cnt;
	if (cnt == 0) 
	  ret.push_back(Interval(curr_start, points[i].val));
      }
    }

    return ret;
  }

};

// Solution #3: use divide and conquer (same idea as merge sort)
// 100ms for leetcode large dataset. Implementation is also tedious.
class Solution3 {
public:
  // Wrapper that calls a recursive fuinction
  vector<Interval> merge(vector<Interval> &intervals) {
    return rec_helper(intervals, 0, intervals.size() - 1);
  }

  // Recursive merge function
  vector<Interval> rec_helper(const vector<Interval>& intervals, int lower, int upper) {
    vector<Interval> result;
    // Base case #1: no interval
    if (lower > upper)
      return result;

    // Base case #2: only one interval
    if (lower == upper) {
      result.push_back(intervals[lower]);
      return result;
    }
      
    int mid = lower + (upper - lower) / 2;
    vector<Interval> left = rec_helper(intervals, lower, mid);
    vector<Interval> right = rec_helper(intervals, mid + 1, upper);
    size_t i1 = 0;
    size_t i2 = 0;
    while (i1 < left.size() && i2 < right.size()) {
      if (left[i1].start > right[i2].end)
	result.push_back(right[i2++]);
      else if (left[i1].end < right[i2].start)
	result.push_back(left[i1++]);
      else if (left[i1].start <= right[i2].start) {
	merge2(result, left, i1, right, i2);
      }
      else
	merge2(result, right, i2, left, i1);
    }

    while (i1 < left.size()) 
      result.push_back(left[i1++]);

    while (i2 < right.size()) 
      result.push_back(right[i2++]);
    
    return result;
  }

  // Merge two intervals
  void merge2(vector<Interval>& result, vector<Interval>& v1, size_t& i1,
	      vector<Interval>& v2, size_t& i2) {
    if (v1[i1].end >= v2[i2].end)
      i2++;
    else {
      v2[i2].start = v1[i1].start;  
      i1++;
    }
  }

};

// Test harness
int main() {
  vector<Interval> intervals;
  intervals.push_back(Interval(1, 3));

  Solution3 foo;
  vector<Interval> ret = foo.merge(intervals);
  for (size_t i = 0; i < ret.size(); i++)
    cout << ret[i].start << ", " << ret[i].end << endl;

  return 0;
}
