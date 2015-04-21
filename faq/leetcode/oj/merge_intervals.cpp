/* Leetcode OJ: Given a collection of intervals, merge all overlapping intervals.
 * For example, given [1,3], [2,6], [8,10], [15,18], return [1,6], [8,10], [15,18]. 
 */

// Definition for an interval.
struct Interval {
  int start;
  int end;

  Interval() : start(0), end(0) { }
  Interval(int s, int e) : start(s), end(e) {}
};
 
bool icmp(const Interval& v1, const Interval& v2) {
  return v1.start < v2.start;
}

// 52ms for large dataset
class Solution {
public:
  vector<Interval> merge(vector<Interval> &intervals) {
    vector<Interval> ret;
    if (intervals.size() == 0)
      return ret;

    sort(intervals.begin(), intervals.end(), icmp);
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
