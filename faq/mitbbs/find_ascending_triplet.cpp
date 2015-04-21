/* Google: Given an array of integers, find any three indexes i, j, k 
 * such that i < j < k and a[i] < a[j] < a[k]. O(n) time required.
 * Refer to:
 * http://www.mitbbs.com/article_t/JobHunting/32260335.html
 *
 */

#include <iostream>
#include <vector>

using namespace std;

// By bemile, time O(n), space O(1)
vector<int> FindIncreasingNum(vector<int> vec) {
  if (vec.size() < 3)
    return vector<int>();

  int first = INT_MAX;
  int second = INT_MAX;
  int min_val = vec[0];
  for (int i = 1; i < vec.size(); i++) {
    if (vec[i] > vec[i - 1]) {
      if (vec[i] > second) {
	vector<int> res;
	res.push_back(first);
	res.push_back(second);
	res.push_back(vec[i]);
	return res;
      }

      first = min_val;
      second = vec[i];
    }
    else {
      if (vec[i] > first && vec[i] < second)
	second = vec[i];
      else if (vec[i] < min_val)
	min_val = vec[i];
    }
  }

  return vector<int>();
}

// By peking2: needs O(n) space
void Find(int arr[], int n) {
  vector<int> dp(n);
  dp[n-1] = n - 1;
  // dp[i] is the index of the min element in arr[0:i]
  for (int i = 1; i < n - 1; i++)
    dp[i] = (arr[i] < arr[dp[i-1]]) ? i : dp[i-1];
        
  for (int i = n - 2; i > 0; i--) {
    // If arr[i] > min element in arr[0:(i-1)],
    // and arr[i] < max element in arr[(i+1):(n-1)], 
    // then we find the triplet!
    if (arr[i] > arr[dp[i-1]] && arr[i] < arr[dp[i+1]]) {
      cout << dp[i-1] <<  i << dp[i+1] << endl;
      return;
    }

    // Now set dp[i] as the largest element in arr[i:(n-1)]
    dp[i] = (arr[i] > arr[dp[i+1]]) ? i : dp[i+1];
  }
  
  cout << "not found" << endl;
}
