/* Given an array for which the ith element is the price of a given stock on day i.
 * If we are permitted to complete as many transactions as we want, (ie, buy one 
 * and sell one share of the stock), but each transaction has a fixed cost c. 
 * Design an algorithm to find the maximum profit.
 *
 * dhu idea (not tested yet): scan the input array from the very beginning
 * to get all local minimuma and maxima. For local minimum,
 *     min_max.push_back(prices[i] + cost / 2);
 * For local maxima, 
 *     min_max.push_back(prices[i] - cost / 2);
 * Note that if prices[0] < prices[1], prices[0] is a local minimum;
 * if prices[n - 1] > prices[n - 2], prices[n - 1] is a local maximum.
 * local min should be always before local maximum, and they should be always in pairs.
 * Then scan min_max to get all increasing sections.
 *
 * Not correct: consider input array { 1, 7, 6, 10, 8, 13 }, cost = 6
 * min_max will be: { 4, 4, 9, 7, 11, 10 }.
 */
int maxProfit(vector<int>& prices, int cost) {
  if (prices.size() <= 1)
    return 0;

  vector<double> min_max;
  if (prices[0] < prices[1]) 
    min_max.push_back(prices[0] + cost / 2.0);

  for (size_t i = 1; i < prices.size() - 1; i++) {
    // Current price is a local maximum.
    if (prices[i] > prices[i - 1] && prices[i] > prices[i + 1]) {
      min_max.push_back(prices[i] - cost / 2.0);
    }
    // Current price is a local minimum.
    else if (prices[i] < prices[i - 1] && prices[i] < prices[i + 1])
      min_max.push_back(prices[i] + cost / 2.0);
  }

  if (prices.back() > prices[prices.size() - 2])
    min_max.push_back(prices.back() - cost / 2.0);
  
  // Input array is decreasing all the way
  if (min_max.size() == 0)
    return 0;

  int profit = 0;
  int curr_min = min_max[0];
  for (size_t i = 1; i < min_max.size(); i++) {
    if (min_max[i] < curr_min)
      curr_min = min_max[i];
    else
      profit += min_max[i] - curr_min;
  }

  return profit;
}
