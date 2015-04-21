/* Facebook Problem: 
 * http://www.mitbbs.com/article_t/JobHunting/32396691.html
 *
 * Suppose we have one group of distinct bolts and 
 * one group of distinct nuts. Each bolt matches a unique nut
 * anf vice versa. We also have a robot that can match a certain 
 * bolt with a certain nut. If bolt is larger than nut, it returns 
 * 1; if bolt matches nut, it returns 0; if bolt is smaller than
 * nut, it returns -1. Design an algorithm to sort both groups
 * by calling the robot.
 * 
 * This is actually a variant of Quick Sort. First use a random 
 * bolt to partition the nut group, then use the nut that matches 
 * the bolt above to partition the bolt group. Then recursively 
 * sort the left half of bolt and nut groups and the right half 
 * of bolt and nut groups.  
 */

#include <iostream>
#include <vector>
#include <utility> 

using namespace std;

// Three color partition, 
// returns index of the element that is equal to pivot.
int partition(vector<int>& group, int lower, int upper, int pivot) {
  int left = lower;
  int right = upper;
  int idx = lower;
  while (idx <= right) {
    //int x = group[idx];
    if (group[idx] < pivot) {
      swap(group[left], group[idx]);
      left++;
      idx++;
    }
    else if (group[idx] == pivot) {
      idx++;
    }
    else { // group[idx] > pivot
      swap(group[idx], group[right]);
      right--;
    }
  }

  return left;
}

// Sort bolts and nuts recursively
void sort_bots_nuts(vector<int>& bolts, int b1, int b2,
		    vector<int>& nuts,  int n1, int n2) {
  if (b1 >= b2 || n1 >= n2)
    return;

  int pivot_bolt = bolts[b1];
  int p_nut = partition(nuts, n1, n2, pivot_bolt);

  int pivot_nut = nuts[p_nut];
  int p_bolt = partition(bolts, b1, b2, pivot_nut);

  sort_bots_nuts(bolts, b1, p_bolt-1, nuts, n1, p_nut-1);
  sort_bots_nuts(bolts, p_bolt+1, b2, nuts, p_nut+1, n2);
}

// Test harness
int main() {
  int a[] = { 2, 7, 8, 4, 6, 5, 1 };
  vector<int> bolts(a, a + sizeof(a) / sizeof(int));

  int b[] = { 4, 8, 6, 1, 2, 5, 7 };
  vector<int> nuts(b, b + sizeof(b) / sizeof(int));

  sort_bots_nuts(bolts, 0, bolts.size() - 1, nuts, 0, nuts.size() - 1);

  for (size_t i = 0; i < nuts.size(); ++i) {
    cout << bolts[i] << " " << nuts[i] << endl;
  }

  return 0;
}
