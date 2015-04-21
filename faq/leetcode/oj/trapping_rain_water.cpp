/* Given n non-negative integers representing an elevation map where the width 
 * of each bar is 1, compute how much water it is able to trap after raining.
 * For example, given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
 */

// 28ms for large dataset
class Solution {
public:
  int trap(int A[], int n) {
    if (!A || n == 0)
      return 0;

    int max_idx = 0;
    for (int i = 1; i < n; i++) {
      if (A[i] > A[max_idx])
	max_idx = i;
    }

    int result = 0;
    int left_border = 0;
    for (int i = 1; i < max_idx; i++) {
      if (A[i] < A[left_border])
	result += A[left_border] - A[i];
      else
	left_border = i;
    }

    int right_border = n - 1;
    for (int i = n - 2; i > max_idx; i--) {
      if (A[i] < A[right_border])
	result += A[right_border] - A[i];
      else
	right_border = i;
    }

    return result;
  }
};

// Dropbox solution: not easy to follow
//////////////////////////////////////////////////////////////
// Fill rain water in the valley presented with left/right.
// New left peak will be returned for next trapping.
// The new left peak is just the maximum value of left and right.
int FillValley(int eMap[], int left, int right, int& count) {
  int i = 0;
  int maxRain = 0;
  // Right peak make decision 
  if (eMap[left] > eMap[right]) {
    i = right;
    maxRain = eMap[right];
    // The equal for maxRain check could not be got rid of,
    // as some value on the left side of right peak may equal to right-peak
    while(--i >= left && maxRain >= eMap[i]) {
      count += maxRain - eMap[i];
      eMap[i] = maxRain;
    }

    return left;
  }
  else { // Left peak makes decision 
    i = left;
    maxRain = eMap[left];
    // No need of the equal for maxRain check,
    // as no value on the right side of left peak would equal to left-peak
    //for consistency I add equal
    while (++i <= right && maxRain >= eMap[i]) { 
      count += maxRain - eMap[i];
      eMap[i] = maxRain;
    }

    return right;
  }
}

// eMap: elevation map, n: size of map
int TrappingRainWater(int eMap[], int n) {
  if (n < 3) 
    return 0;
  
  int rain = 0;
  int leftPeak, rightPeak;
  
  // Find the first left peak
  for (leftPeak = 0; leftPeak < n-1; ++leftPeak)
    if (eMap[leftPeak] > eMap[leftPeak+1]) 
      break;
    
  for (rightPeak = leftPeak+1; rightPeak < n-1; ++rightPeak)
    // I include equal for loose left bound check, but strict right bound check
    if (eMap[rightPeak] > eMap[rightPeak+1] && eMap[rightPeak] >= eMap[rightPeak-1])
      // Find right peak, then fill up the valley,
      leftPeak = FillValley(eMap, leftPeak, rightPeak, rain);
  
  // R last rain traped
  FillValley(eMap, leftPeak, rightPeak, rain);

  return rain;
}
