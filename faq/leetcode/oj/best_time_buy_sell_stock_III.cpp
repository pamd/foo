/* Say you have an array for which the ith element is the price of a given stock on day i.
 * Design an algorithm to find the maximum profit. You may complete at most two transactions.
 * Note: You may not engage in multiple transactions at the same time 
 * (ie, you must sell the stock before you buy again).
 */

/* dhu incorrect solution for this test case:
 * [1,2,4,2,5,7,2,4,9,0]
 * The ansow should be: buy at 1, sell at 7; then buy at 2, sell at 9;
 * total profit is (7 - 1) + (9 - 2) = 13, but my code gives:
 * buy at 2, sell at 7; then buy at 2, sell at 9; total profit is 12.
 */
class Solution {
public:
  int maxProfit(vector<int> &prices) {
    vector<int> daily_change;
    bool isDown = false;
    for (size_t i = 1; i < prices.size(); i++) {
      int diff = prices[i] - prices[i - 1];
      if (diff > 0) {
	if (isDown || daily_change.size() == 0) {
	  daily_change.push_back(diff);
	  isDown = false;
	}
	else 
	  daily_change.back() += diff;
      }
      else if (diff < 0) 
	isDown = true;
    }

    size_t sz = daily_change.size();
    if (sz == 0)
      return 0;

    if (sz == 1)
      return daily_change[0];

    if (sz == 2)
      return daily_change[0] + daily_change[1];

    int max1 = daily_change[0];
    int max2 = daily_change[1];
    if (max1 < max2)
      swap(max1, max2);

    for (size_t i = 2; i < daily_change.size(); i++) {
      if (daily_change[i] > max1) {
	max2 = max1;
	max1 = daily_change[i];
      }
      else if (daily_change[i] > max2) {
	max2 = daily_change[i];
      }
    }
    
    return max1 + max2;
  }

};

// anson627 solution: 52ms for large dataset
// Can we solve this problem without using extra O(n) space?
class Solution_anson {
public:
  int maxProfit(vector<int> &prices) {
    int N = prices.size();
    if (N <= 1) 
      return 0;

    int min_val = prices[0];
    // left[i] is the maximum profit with one transaction from the first day up to i-th day
    vector<int> left(N, 0);

    for (int i = 1; i < N; ++i) {
      if (prices[i] < min_val) 
	min_val = prices[i];
      left[i] = max(left[i - 1], prices[i] - min_val);
    }

    int max_val = prices[N - 1];
    // right[i] is the maximum profit with one transaction from i-th day up to the last day
    vector<int> right(N, 0);
    for (int i = N - 2; i >= 0; --i) {
      if (prices[i] > max_val) 
	max_val = prices[i];
      right[i] = max(right[i + 1], max_val - prices[i]);
    }

    int res = 0;
    for (int i = 0; i < N; ++i)
      res = max(res, left[i] + right[i]);
    return res;
  }
};

