/************************************************************************************
 * Given N jobs of varying length, divide among two machines to
 * minimize the makespan (time the last job finishes).
 *
 * Slide #39:
 * Maintain difference in finish times and avoid recomputing cost
 * from scratch. This has factor of N speedup (using Gray code order).
 * dhu: To implement this idea, maintain the sum of elements selected in a[],
 * Every time a new element is added or removed from the group by
 * "a[k] = 1 - a[k];' in partition(), modify the sum by:
 *    current_sum = a[k] ? (current_sum + jobs[k]) : (current_sum - jobs[k]);
 * ---------------------------------------------------------------------------------
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 3;
vector<int> jobs(N);
vector<int> a(N, 0);
vector<int> optimum(N, 0);
int result = 0;
int sum = 0;
int process_called = 0;

// Compare load in a[] with optimum and update optimum if necessary
void process() {
   ++process_called;
   //cout << "process called #" << process_called << ": ";
   //for (int i = 0; i < N; ++i) {
   //   cout << a[i] << " ";
   //}
   //cout << endl;

   int group_sum = 0;
   for (int i = 0; i < N; i++) {
      if (a[i]) {
         group_sum += jobs[i];
      }
   }

   int group_diff = group_sum - (sum - group_sum);
   if (group_diff < 0) {
      group_diff = -group_diff;
   }

   if (group_diff <= result) {
      result = group_diff;
      optimum = a;
   }
}

// Backtrack: how to implement this function?
bool canBacktrack(int k) {
   int current_sum = 0;
   for (int i = 0; i < k; ++i) { // "NOTE: i <= k" is WRONG!
      if (a[i]) {
         current_sum += jobs[i];
      }
   }

   return current_sum > sum / 2;

   /* The following section is WRONG!
   if (a[k] == 0 && current_sum > sum / 2)
      return true;
   if (a[k] == 1 && current_sum < sum / 2)
      return true;

   return false;
   */
}

// Recursive partition
void partition(int k) {
   // Debug printout
   cout << "parition(): ";
   for (int i = 0; i < N; ++i) {
      cout << a[i] << " ";
   }
   cout << endl;
   // End of debug

   if (k == N) {
      process();
      return;
   }

   if (canBacktrack(k)) {
      // Debug
      cout << " k = " << k << ", can backtrack: ";
      for (int i = 0; i < N; ++i) {
         cout << a[i] << " ";
      }
      cout << endl;
      // End of debug

      return;
   }

   partition(k+1);
   a[k] = 1 - a[k];
   // Optimization (see comments at the beginning)
   // current_sum = a[k] ? (current_sum + jobs[k]) : (current_sum - jobs[k]);
   partition(k+1);
}

// Wrapper
void wrapper() {
   jobs[0] = 9;
   jobs[1] = 1;
   jobs[2] = 2;

   for (int i = 0; i < N; i++) {
      sum += jobs[i];
   }
   result = sum;

   ///*
   sort(jobs.begin(), jobs.end());
   do {
      cout << "input: ";
      for (int i = 0; i < N; i++) {
         cout << jobs[i] << " ";
      }
      cout << endl;

      result = sum;
      process_called = 0;
      a = vector<int>(N, 0);
      optimum = a;
      partition(0);

      cout << "process_called: " << process_called << endl;
      cout << "Output: ";
      for (int i = 0; i < N; i++) {
         if (optimum[i]) {
            cout << jobs[i] << " ";
         }
      }
      cout << endl << "Best result: " << result << endl << endl;
   } while (next_permutation(jobs.begin(), jobs.end()));
   //*/

   /*
   optimum = a;
   partition(0);
   cout << "process_called: " << process_called << endl;
   for (int i = 0; i < N; i++) {
      if (optimum[i]) {
         cout << jobs[i] << " ";
      }
   }
   cout << endl;
   cout << "Best result: " << result << endl;
   */
}

// Test harness
int main() {
   wrapper();

   return 0;
}

// backtrack when partial schedule cannot beat best known
// (check total against goal: half of total job times)

/* 5-bit gray code sequences:
 *
 1)  0 0 0 0 0
 2)  0 0 0 0 1
 3)  0 0 0 1 1
 4)  0 0 0 1 0
 5)  0 0 1 1 0
 6)  0 0 1 1 1
 7)  0 0 1 0 1
 8)  0 0 1 0 0
 9)  0 1 1 0 0
 10) 0 1 1 0 1
 11) 0 1 1 1 1
 12) 0 1 1 1 0
 13) 0 1 0 1 0
 14) 0 1 0 1 1
 15) 0 1 0 0 1
 16) 0 1 0 0 0

 17) 1 1 0 0 0
 18) 1 1 0 0 1
 19) 1 1 0 1 1
 20) 1 1 0 1 0
 21) 1 1 1 1 0
 22) 1 1 1 1 1
 23) 1 1 1 0 1
 24) 1 1 1 0 0
 25) 1 0 1 0 0
 26) 1 0 1 0 1
 27) 1 0 1 1 1
 28) 1 0 1 1 0
 29) 1 0 0 1 0
 30) 1 0 0 1 1
 31) 1 0 0 0 1
 32) 1 0 0 0 0
 *
 */
