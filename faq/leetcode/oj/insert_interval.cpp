/* Given a set of non-overlapping intervals, insert a new interval 
 * into the intervals (merge if necessary).
 * You may assume that the intervals were initially sorted according 
 * to their start times.
 *
 * Example 1:
 * Given intervals [1,3],[6,9], insert and merge [2,5] in as [1,5],[6,9].
 * Example 2:
 * Given [1,2],[3,5],[6,7],[8,10],[12,16], insert and merge [4,9] in as:
 * [1,2],[3,10],[12,16].
 * This is because the new interval [4,9] overlaps with [3,5],[6,7],[8,10].
 */

#include <iostream>
#include <vector>

using namespace std;

/**
 * Definition for an interval.
 */
struct Interval {
  Interval() : start(0), end(0) { }
  Interval(int s, int e) : start(s), end(e) { }

  int start;
  int end;
};
 
int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

int min(int a, int b) {
  if (a < b)
    return a;
  return b;
}

// dhu solution: 68ms for large dataset
class Solution {
public:
  vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
    vector<Interval> ret;
    Interval merged = newInterval;
    bool insertionFlag = false;
    for (size_t i = 0; i < intervals.size(); i++) {
      if (intervals[i].end < newInterval.start) { 
	ret.push_back(intervals[i]);
	continue;
      }

      if (intervals[i].start > newInterval.end) {
	if (!insertionFlag) {
	  ret.push_back(merged);
	  insertionFlag = true;
	}
	ret.push_back(intervals[i]);
	continue;
      }

      merged.start = min(intervals[i].start, merged.start);
      merged.end = max(intervals[i].end, merged.end);
    }

    if (!insertionFlag)
      ret.push_back(merged);

    return ret;
  }

};

// dhu Test harness
/*
int main() {
  Solution foo;
  vector<Interval> v;
  v.push_back(Interval(1, 2));
  v.push_back(Interval(3, 5));
  v.push_back(Interval(6, 7));
  v.push_back(Interval(8, 10));
  v.push_back(Interval(12, 16));

  Interval x(4, 9);
  vector<Interval> ret = foo.insert(v, x);
  for (size_t i = 0; i < ret.size(); i++) {
    cout << "[" << ret[i].start << ", " << ret[i].end << "]" << endl;
  }
}
*/

// Dropbox solution: 60ms for large dataset
// -----------------------------------------
// Binary search to get the index of the first interval that overlaps
// with the new interval.
int BSeachLowerBoundForStart(vector<Interval> &intervals, int start) {
  if (intervals.size() <= 0 || start < intervals[0].start) 
    return -1;

  int low = 0;
  int high = intervals.size() - 1;
  int mid = (low + high + 1) / 2;
  while(low < high) {
    if(start < intervals[mid].start)
      high = mid - 1;
    else
      low = mid;
    mid = (low + high + 1) / 2;
  }

  return mid;
}

// Binary search to get the index of the last interval that overlaps
// with the new interval.
int BSeachUpperBoundForEnd(vector<Interval> &intervals, int end) {
  if(intervals.size() <= 0 || intervals[intervals.size()-1].end < end) 
    return intervals.size();

  int low = 0;
  int high = intervals.size() - 1;
  int mid = (low + high) / 2;
  while (low < high) {
    if (intervals[mid].end < end)
      low = mid + 1;
    else
      high = mid;
    mid = (low + high) / 2;
  }

  return mid;
}

// Dropbox: main function
vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {
  int low = BSeachLowerBoundForStart(intervals, newInterval.start);
  int high = BSeachUpperBoundForEnd(intervals, newInterval.end);

  // Find intervals in the container that will be joined together.
  // These intervals would be removed.
  if (low >=0 && intervals[low].end >= newInterval.start)
    newInterval.start = intervals[low].start;
  else
    low = low + 1; 
  
  if (high < intervals.size() && intervals[high].start <= newInterval.end)
    newInterval.end = intervals[high].end;
  else
    high = high - 1;
   

  vector<Interval> r;
  // Get intervals from original container
  int i = -1;
  while (++i < low)
    r.push_back(intervals[i]);
  
  // Add new interval
  r.push_back(newInterval);
  
  // Skip those removed intervals
  i = high;
  while (++i < intervals.size())
    r.push_back(intervals[i]);
  
  return r;
}

// Dropbox: helper function
void PrintIntervals(vector<Interval>& v) {
  for (int i = 0; i < v.size(); ++i)
    cout << '[' << v[i].start << ',' << v[i].end << "], ";
  
  cout << endl;
}

// Dropbox: test harness
int main(int argc, char** argv) {
  //[1,3],[6,9]; 
  vector<Interval> v1;
  v1.push_back(Interval(1,3));
  v1.push_back(Interval(6,9));
  
  vector<Interval> r1 = InsertInterval(v1, Interval(2,5));
  PrintIntervals(r1); //[1,5],[6,9]
  
  
  //[1,2],[3,5],[6,7],[8,10],[12,16]
  vector<Interval> v2;
  v2.push_back(Interval(1,2));
  v2.push_back(Interval(3,5));
  v2.push_back(Interval(6,7));
  v2.push_back(Interval(8,10));
  v2.push_back(Interval(12,16));
  
  vector<Interval> r2 = InsertInterval(v2, Interval(4,9));
  PrintIntervals(r2); //[1,2],[3,10],[12,16]
  
  return 0;
}
