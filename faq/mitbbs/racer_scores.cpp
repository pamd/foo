/* Rocket Fuel online coding problem: 
 * Given a group of racers, each of them have starting and ending times. 
 * All starting and ending times are unique. Suppose each racer's score 
 * is defined as the number of racers who that start later and end earlier 
 * than current racer. Calculate the score for each racer.
 * Time complexity must be better than O(n^2).
 *
 * Hint from:
 * http://get-that-job-at-google.blogspot.com/2013/02/rocketfuel-codesprint-at-iit-bombay.html
 * The naive brute force solution is too slow to run within the time limit. You will need to 
 * think of a faster solution. Specifically, we are looking for a solution that is guaranteed 
 * to be less than O(N^2) on all inputs. One possible way to accomplish this (there are several 
 * other acceptable methods) is to use a data structure with K buckets (e.g., K = 300), each of 
 * which is initially empty and is defined by two times. Each bucket  will eventually contain 
 * racers whose start time falls between the two times. The bucket boundaries should be chosen 
 * such that they ultimately will contain the same number of racers. Then iterate through the 
 * racers in end time order and, as you iterate over each racer, build up this bucketed data 
 * structure in such a way that you can use it to quickly count the number of racers that finished 
 * before him but started after him.
 */

#include <vector>
#include <iostream>
#include <map>

using namespace std;

// dhu O(n^2) solution.
// intervals: each racer's starting and ending times,
// returns a vector of scores for all racers.
vector<size_t> dhu_n2(const vector<pair<int, int> >& intervals) {
  size_t len = intervals.size();
  vector<size_t> scores(len, 0);

  // Sort starting and ending times by putting them into two maps.
  // Time complexity: (n*logn)
  map<int, size_t> starts; // key: starting time, value: original index
  map<int, size_t> ends;   // key: ending time, value: original index
  for (size_t i = 0; i < len; i++) {
    starts[intervals[i].first] = i;
    ends[intervals[i].second] = i;
  }

  // Start from the racer who starts the first, 
  // find how many racers finish earlier than he does. 
  // Since distance() takes O(n), this is a O(n^2) solution. 
  while (starts.size()) {
    size_t idx = starts.begin()->second;
    int curr_end = intervals[idx].second;
    map<int, size_t>::iterator it = ends.find(curr_end); 
    // O(n) in std::set. To improve it to O(logn), we have to use an 
    // order-statistics tree, which is not available in standard C++. 
    scores[idx] = distance(ends.begin(), it); 

    // The current racer will never be counted in any other racer's 
    // scores, so we delete his records from both starts and ends.
    starts.erase(starts.begin()); 
    ends.erase(curr_end);         
  }

  return scores;
}

// Idea from blaze:
// 1) Sort intervals (s_i, e_i) such that s_0 < s_1 < ... < s_n.  
// This is O(n*log(n)).
//
// 2) Compute c_i, where c_i = number j's where e_j < e_i.  
// This can be O(n*log(n)) by sorting e_i.
//
// 3) Now traverse (s_i, e_i) from 0 to n:
//       vector<int> sorted;
//       for (i = 0; i < n; i++) {
//         insert_position = binary_insert e_i into sorted; 
//         a_i = c_i - insert_position;
//       }
//
// This step takes O(n*log(n)) as well. The result is saved in a_i.
// dhu: unfortunately binary_insert step takes O(n) too, so this 
// solution is not good either.
vector<int> blaze(const vector<int>& intervals) {
  // ... 
}

// Test harness
int main() {
  vector<pair<int, int> > intervals;
  intervals.push_back(pair<int, int>(3, 6));
  intervals.push_back(pair<int, int>(2, 4));
  intervals.push_back(pair<int, int>(0, 8));

  vector<size_t> scores = get_scores(intervals);
  for (size_t i = 0; i < scores.size(); i++) {
    cout << i << ": " << scores[i] << endl;
  }

  return 0;
}
