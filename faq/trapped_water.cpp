/* Given an array of positive integers, where each integer represents 
 * the height of a landscape at that position, determine how much rain 
 * water gets trapped in this landscape after a deluge.
 * Reference:
 * MIT Google Interview Lectures page 20 of 89
 * and:
 * http://www.mitbbs.com/article_t/JobHunting/31983619.html
 *
 */

#include <iostream>
#include <stack>

using namespace std;

// max() helper
int max(int v1, int v2)
{
  if (v1 > v2)
    return v1;
  return v2;
}

// min() helper
int min(int v1, int v2)
{
  if (v1 < v2)
    return v1;
  return v2;
}

/* Algorithm from MIT Google lecture. 
 * It is straight forward, but needs O(N) exrta 
 * space to hold the left bound and right bound.
 */
int mit_get_trapped_water(int arr[], int len)
{
  int leftBound[len];
  int rightBound[len];
	
  leftBound[0]=0;	
  int currentMax=0;
	
  // Build left boundary array
  for (int a = 1; a < len; a++){
    currentMax = max(currentMax, arr[a - 1]);
    leftBound[a] = currentMax;
  }

  // Build right boundary array
  rightBound[len - 1] = 0;
  currentMax=0;	
  for (int a = len - 1 ; a > -1 ; a--) {
    currentMax = max(currentMax, arr[a]);
    rightBound[a] = currentMax;	
  }
	
  // Calculate sum	
  int waterSum = 0;
  for (int a = 0; a < len; a++) {
    int amount = min(leftBound[a], rightBound[a]) - arr[a];
    if (amount > 0) 
      waterSum = waterSum + amount;
  }

  return waterSum;
}

// Algorithm from gloomyturkey@mitbbs, very straightforward
int turkey_mitbbs(int arr[], int len) {
  int idx_max = 0;
  for (int i = 1; i < len; i++) 
    if (arr[i] > arr[idx_max]) 
      idx_max = i;
        
  int waterSum = 0;
  int left_side = arr[0];
  for (int i = 1; i < idx_max; i++) {
    if (arr[i] > left_side) 
      left_side = arr[i];
    else 
      waterSum += left_side - arr[i];
  }
  
  int right_side = arr[len - 1];
  for (int i = len - 2; i > idx_max; i--) {
    if (arr[i] > right_side) 
      right_side = arr[i];
    else 
      waterSum += right_side - arr[i];
  }
  
  return waterSum;
}

// Algorithm from fantasist@mitbbs
int fantasist_mitbbs(int arr[], int len) {
  stack<pair<int, int> > myStack;
  int waterSum = 0;
  
  for(int i = 0; i < len; i++) {
    while(!myStack.empty() && myStack.top().second <= arr[i]) {
      int bottom = myStack.top().second;
      myStack.pop();
      if( myStack.empty())
        break;
      int top = myStack.top().second < arr[i]? myStack.top().second: arr[i];
      int length = i - myStack.top().first - 1;
      waterSum = waterSum + (top-bottom) * length;
    }
    myStack.push(make_pair(i, arr[i]));
  }
  
  return waterSum;
}

// Test harness
int main() 
{
  int arr[] = { 5, 2, 3, 6, 1, 4, 3 };
  int len = sizeof(arr) / sizeof(int);
  cout << "turkey: " << turkey_mitbbs(arr, len) << endl;
  cout << "fantasist: " << fantasist_mitbbs(arr, len) << endl;
}
