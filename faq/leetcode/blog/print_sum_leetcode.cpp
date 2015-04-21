/* Given a target number, and a series of candidate numbers, 
 * print out all combinations, so that the sum of candidate 
 * numbers equals to the target. 
 * Ref:
 * http://www.leetcode.com/2010/09/print-all-combinations-of-number-as-sum.html
 */

#include <iostream>
#include <vector>

using namespace std;

// Naive solution that prints out duplicate combinations
void dhu_get_sum0(int arr[], int len, int target, vector<int> expr) 
{
  if (target < 0)
    return;
  if (target == 0) {
    for (size_t i = 0; i < expr.size(); i++)
      cout << expr[i] << " ";
    cout << endl;
    return;
  }

  for (int i = 0; i < len; i++) {
    expr.push_back(arr[i]);
    dhu_get_sum0(arr, len, target - arr[i], expr);
    expr.pop_back();
  }
}

/* Without duplicate outputs. This approach is similar to the problem
 * of finding combinations of coins in career cup 150 book. */
void dhu_get_sum1(int arr[], int len, int target, vector<int> expr, int level) 
{
  if (target < 0)
    return;

  if (target == 0) {
    for (size_t i = 0; i < expr.size(); i++)
      cout << expr[i] << " ";
    cout << endl;
    return;
  }

  /* This condition must be tested here, in case the last element is
   * included in a valid sum. If we combine it together with target < 0
   * so that it becomes: 
   *
   * if (level == len || target < 0) 
   *   return; 
   * 
   * we may miss these cases.
   */
  if (level == len) 
    return;

  // arr[level] not included in the current sum
  dhu_get_sum1(arr, len, target, expr, level + 1);

  // Increase the number of arr[level] one by one, then test the sum
  for (int j = 1; j <= target / arr[level]; j++) {
    expr.push_back(arr[level]);
    dhu_get_sum1(arr, len, target - j * arr[level], expr, level + 1);
  }

}

// dhu solution: if each element is required to be used at most once
void dhu_get_sum2(int arr[], int len, int target, vector<int> expr, int level)
{
  if (target < 0)
    return;
  if (target == 0) {
    for (size_t i = 0; i < expr.size(); i++)
      cout << expr[i] << " ";
    cout << endl;
    return;
  }

  for (int i = level; i < len; i++) {
    expr.push_back(arr[i]);
    dhu_get_sum2(arr, len, target - arr[i], expr, i + 1);
    expr.pop_back();
  }
}
 
// leetcode
void printSum(int candidates[], int index[], int n) {
  for (int i = 1; i <= n; i++)
    cout << candidates[index[i]] << ((i == n) ? "" : "+");
  cout << endl;
}
 
// leetcode algorithm
void solve(int target, int sum, int candidates[], int sz, int index[], int n) {
  if (sum > target)
    return;
  if (sum == target)
    printSum(candidates, index, n);
 
  for (int i = index[n]; i < sz; i++) {
    index[n+1] = i;
    solve(target, sum + candidates[i], candidates, sz, index, n+1);
  }
}
 
// leetcode wrapper function
void solve(int target, int candidates[], int sz) {
  int index[10000];
  index[0] = 0;
  solve(target, 0, candidates, sz, index, 0);
}

int main() 
{
  int arr[] = { 2, 3, 4, 5, 6, 7 };
  int len = sizeof(arr) / sizeof(int);
  int target = 7;
  vector<int> expr;
  //solve(target, arr, len);
  dhu_get_sum1(arr, len, target, expr, 0);

}
