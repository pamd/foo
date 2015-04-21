/* Say you have an array for which the ith element is the price of a given stock on day i.
 * If you were only permitted to complete at most one transaction (ie, buy one and sell 
 * one share of the stock), design an algorithm to find the maximum profit.
 */

// 52ms for large dataset
class Solution {
public:
  int maxProfit(vector<int> &prices) {
    if (prices.size() == 0)
      return 0;

    /* If we are reuired to make one and only one transaction 
     * (even if the stock is decreasing all the way and the profit
     * will be negative), then change the next line to:
     *    int max_profit = INT_MIN; 
     */
    int max_profit = 0;
    int lowest = prices[0];
    for (size_t i = 1; i < prices.size(); i++) {
      int tmp = prices[i] - lowest;
      if (max_profit < tmp)
	max_profit = tmp;
      if (lowest > prices[i])
	lowest = prices[i];
    }

    return max_profit;
        
  }
};
