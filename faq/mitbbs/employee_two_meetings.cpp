/* Facebook: Given N ranges of date offsets when N employees are present in an 
 * organization. Something like:
 * 1-4 (i.e. employee will come on 1st, 2nd, 3rd and 4th day )
 * 2-6
 * 8-9
 * ..
 * 1-14
 * You have to organize an event on minimum number of days such that each 
 * employee can attend the event at least twice. Write an algorithm (there is 
 * apparently an O(n) algorithm for this).
 * Refer to:
 * http://www.mitbbs.com/article_t1/JobHunting/32051567_0_1.html
 *
 * Greedy algorithm: rank all ranges by the ending date, then save the last two dates
 * of the first employee into the finla result. Start from the second employess, 
 * check how many days the second employee's dates will overlap with the last two days 
 * in final result. If two overlaps are found, skip the current employee; if one overlap
 * is found, add his/her last day; if no overlap is found at all, add current employee's 
 * last two days into the result. Repeat this step until all employees have been checked.
 */

// Code by yjyongz, counting sort, time is max(O(M), O(N)), 
// where M is max of dates, N is the number of employees.
// dhu: the code is buggy, not worth the time. What a shame!

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

int main() {
  srand(size_t(time(0)));

  /*
  const int n  = 5;
  int sstart[n] = {1,8,2,11,15};
  int eend[n] = {4,9,6,14,18};
  */

  // Assign random input
  /*
  for (int i = 0; i < n; i++) 
    sstart[i] = rand() % 20;
  for (int i = 0; i < n; i++) 
    eend[i] = sstart[i] + rand() % 5 + 1;

  for (int i = 0; i < n; i++) {
    cout << "(" << sstart[i] << " " << eend[i] << ")" << endl;
  }
  cout << endl;
  */

  // The code is buggy, try the following simple input data
  const int n = 2;
  int sstart[n] = { 1, 2 };
  int eend[n] = { 4, 7};

  const int MAXDATE = 100;
  int radix[MAXDATE] = { 0 };
  int final[n];
  for (int i = 0; i < n; i++) 
    radix[eend[i]]++;

  for (int i = 1; i < MAXDATE; i++) 
    radix[i] += radix[i-1];

  for(int i = n - 1; i >= 0; i--)  
    final[--radix[eend[i]]] = i;

  // after sort
  for (int i = 0; i < n; i++)
    cout << "(" << sstart[final[i]] << " " << eend[final[i]] << ")" << endl;
  
  // greedy algorithm
  int e1 = eend[final[0]]; // first emplyee's last available day
  int e2 = e1-1;           // first emplyee's second to last available day

  // Final result will be saved in this vector
  vector<int> schedule;
  for (int i = 1; i < n; i++) {
    // If current employee's available dates do not overlap with previous employee's date,
    // the last two days of previous employee should be kept in final result.
    if (sstart[final[i]] > e1) { 
      schedule.push_back(e2);
      schedule.push_back(e1);
      e1 = eend[final[i]];
      e2 = e1-1;
    }

    else if (schedule.size() > 0) {
      int last = schedule[schedule.size() - 1];
      if(last >= e2){
	schedule.push_back(e1);
      }
    }
  }

  int last = schedule[schedule.size()-1];
  if(last < e2) {
    schedule.push_back(e2);
    schedule.push_back(e1);
  } 
  else if (e2 >= last) {
    schedule.push_back(e1);
  }

  for (int i = 0; i < schedule.size(); i++) 
    cout << schedule[i] << " ";
  cout << endl;
  return 0;
}

