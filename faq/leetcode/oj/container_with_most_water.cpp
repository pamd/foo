/* leetcode OJ: Given n non-negative integers a1, a2, ..., an, 
 * where each represents a point at coordinate (i, ai). 
 * n vertical lines are drawn such that the two endpoints of line i is 
 * at (i, ai) and (i, 0). 
 * Find two lines, which together with x-axis forms a container, 
 * such that the container contains the most water.
 *
 * Note: You may not slant the container. 
 */

#include <iostream>
#include <vector>

using namespace std;

int maxArea(vector<int>& height) {
  if (height.size() == 0)
    return 0;

  int max_area = 0;
  int left = 0;
  int right = height.size() - 1;
  while (left < right) {
    int curr_area = 0;
    if (height[left] > height[right]) {
      curr_area = (right - left) * height[right];
      right--;
    }

    // When height[left] == height[right], we can do:
    // 
    // else if (height[left] == height[right]) {
    //   curr_area = (right - left) * height[right];
    //   left++;
    //   right--;
    // }
    //
    // This section is optional because the current if/else  
    // has already covered this case implicitly.

    else {
      curr_area = (right - left) * height[left];
      left++;
    }

    if (max_area < curr_area)
      max_area = curr_area;
  }

  return max_area;
        
}

// anson627: slight optimization
class Solution_anson {
public:
  int maxArea(vector<int> &height) {
    int i = 0;
    int j = height.size() - 1;
    int max = 0;
    while (i < j) {
      int h = (height[i] < height[j]) ? height[i] : height[j];
      int res = h * (j - i);
      if (res > max) max = res;
      if (height[i] <= height[j]) {
	i++;
	while (height[i] < h && i < j) // optimization
	  i++;
      }
      else {
	j--;
	while (height[j] < h && i < j) // optimization
	  j--;
      }
    }

    return max;
  }

};
