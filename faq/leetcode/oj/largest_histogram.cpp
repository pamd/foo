/* OJ question: Given n non-negative integers representing the histogram's 
 * bar height where the width of each bar is 1, find the area of largest 
 * rectangle in the histogram.
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
  // dhu solution: 88ms for large dataset
  int largestRectangleArea(vector<int> &height) {
    if (height.size() == 0)
      return 0;

    int maxArea = 0;
    vector<size_t> stack_idx;
    vector<size_t> stack_left;
    stack_idx.push_back(0);
    stack_left.push_back(0);
    for (size_t i = 1; i < height.size(); i++) {
      size_t curr_idx = stack_idx.back();
      int curr_height = height[curr_idx];
      // tag1: "height[i] > curr_height" also works here
      if (height[i] >= curr_height) {  
	stack_idx.push_back(i);
	stack_left.push_back(0);
	continue;
      }

      size_t counter = 0;
      size_t right_idx = curr_idx;
      // If tag1 is "height[i] > curr_height", then in next line, we should use:
      // "height[stack_idx.back()] >= height[i]"
      while (stack_idx.size() && height[stack_idx.back()] > height[i]) {

	curr_idx = stack_idx.back();
	curr_height = height[curr_idx];
	size_t offset = stack_left.back();
	int tmpArea = curr_height * (offset + 1 + right_idx - curr_idx);
	if (tmpArea > maxArea)
	  maxArea = tmpArea;
	stack_idx.pop_back();
	stack_left.pop_back();
	counter += offset + 1;
      }
      stack_idx.push_back(i);
      stack_left.push_back(counter);
    }

    if (stack_idx.size() == 0)
      return maxArea;

    int right_idx = stack_idx.back();
    while (stack_idx.size()) {
      size_t curr_idx = stack_idx.back();
      int tmpArea = height[curr_idx] * (stack_left.back() + 1 + right_idx - curr_idx);
      if (tmpArea > maxArea)
	maxArea = tmpArea;
      stack_idx.pop_back();
      stack_left.pop_back();
    }
    return maxArea;
  }

};

/* Dropbox solution.
 * Check here for algorithm analysis: 
 * http://tech-queries.blogspot.com/2011/03/maximum-area-rectangle-in-histogram.html
 */
int LargestRectangleArea(vector<int> &height) {
  stack<int> sLimit;
  int size = height.size();
  int width[size];

  sLimit.push(-1); // make -1 as sentinel
  // Search left boundary for each bar
  for (int i = 0; i < size; ++i) {
    // Find the left bar that current bar could reach
    while (sLimit.top() >= 0) {
      // Find first bar on the left that is less than current one,
      // that is left boundary for this bar
      if (height[i] > height[sLimit.top()])
	break;
      // The bar is larger than current one, no need to compare in the future
      else // heigth[i] <= height[sLimit.top()]
	sLimit.pop();
    }
    
    width[i] = i - sLimit.top() - 1; // -1 indicates that the current bar is excluded
    sLimit.push(i);
  }
	
  sLimit = stack<int>(); // Clear up sLimit
  sLimit.push(size);
  // Search right boundary for each bar
  for (int i = size - 1; i >= 0; --i) {
    while (sLimit.top() < size) {
      if (height[i] > height[sLimit.top()])
	break;
      else
	sLimit.pop();
    }

    width[i] += sLimit.top() - i; // no -1 here, include current bar as well
    sLimit.push(i);
  }
	
  int maxArea = 0;
  for (int i = 0; i < size; ++i) {
    int area = width[i] * height[i];
    if (area > maxArea) 
      maxArea = area;
  }

  return maxArea;
}


// Test harness
int main(int argc, char** argv)
{
  int A[] = { 2, 1, 2};
  vector<int> Av;
  
  for (int i = 0; i < sizeof(A) / sizeof(int); ++i)
    Av.push_back(A[i]);
  
  cout << LargestRectangleArea(Av);
  
  return 0;
}

/* MITBBS solution:
 * http://www.mitbbs.com/article_t/JobHunting/31573617.html
 */

#include <stdio.h>

const int MAX_SIZE = 100;

struct HistElem {
  // Index of the element, 0, 1, 2, ...
  int index;          
  // Height of the element
  int height;         
  // How far can we extend to the left boundary,
  // originally called "far_length_left".
  int left_extension; 
}; 

// The last element of the histogram is set to the dummy value -1.
// This sentinel is be used to indicate that we have reached the right boundary.
int MaxRect(int Hist[], int n) {
  if (n < 1 || Hist[n-1] != -1) {
    printf("Incorrect input.\n");
    return -1;
  }

  int S = 0;
  HistElem Stack[MAX_SIZE];  // An array that simulates stack
  int top = -1;

  for (int i = 0; i < n; i++) {
    // Look backward for elements available for rectangle area calculation
    while (top != -1 && Hist[i] < Stack[top].height) {
      int area = Stack[top].height * (Stack[top].left_extension + (i - Stack[top].index));
      if (area > S)
	S = area;
      // We can pop up these elements now
      top--;
    }

    // Find left_extension for current element
    int tmp_left_extension = i;
    if (top != -1)
      tmp_left_extension = i - Stack[top].index - 1;

    // Push current element into the stack
    top++;
    if (top == MAX_SIZE) {
      printf("Stack overflow.\n");
      return -1;
    }
    // Update top element in the stack
    Stack[top].index = i;
    Stack[top].height = Hist[i];
    Stack[top].left_extension = tmp_left_extension;
  }

  return S;
}

// Another approach in post #10 by AprilFlower
// This approach is buggy and doesn't give the right answer! 
// Ignore it or fix it!
struct HistElem2
{
  int index; 
  int leftWidth; 
};

// Buggy solution from AprilFlower
int MaxRect2(int * H, int n) {
  struct HistElem2 Stack[MAX_SIZE];
  int top = -1;
  int area, maxArea = 0;
  for(int pos = 0; pos < n; pos++) {
    while (top != -1 && H[pos] < H[Stack[top].index]) {
      area = H[Stack[top].index] * (Stack[top].leftWidth + pos - Stack[top].index);
      if(area > maxArea) 
	maxArea = area;
      top--;
    }

    int leftWidth = 0;
    if (top != -1 && H[pos] >= H[Stack[top].index])
      leftWidth = pos - Stack[top].index - 1;                     

    top++;
    Stack[top].leftWidth = leftWidth;            
    Stack[top].index = pos;            
  }

  while (top != -1) {
    area = H[Stack[top].index] * (Stack[top].leftWidth + n - Stack[top].index);
    if (area > maxArea) 
      maxArea = area;
    top--;
  }

  return maxArea;
}

/* EPI book solution: Problem 12.8.
 * Similar idea as the one in Dropbox, but the code here is more compact. 
 */
int calculate_largest_rectangle(const vector<int> &A) {
  // Calculate Left side extension
  stack<int> s;
  vector<int> L;
  for (int i = 0; i < A.size(); ++i) {
    while (!s.empty() && A[s.top()] >= A[i]) 
      s.pop();
    
    // tag1: the next line can also be: 
    // L.push_back(s.empty() ? 0 : s.top() + 1);
    L.push_back(s.empty() ? -1 : s.top());
    s.push(i);
  }

  // Clear stack before calculating right side
  while (!s.empty()) 
    s.pop();

  // Calculate right side extension
  vector<int> R(A.size());
  for (int i = A.size() - 1; i >= 0; --i) {
    while (!s.empty() && A[s.top()] >= A[i]) 
      s.pop();
    
    R[i] = (s.empty() ? A.size() : s.top());
    s.push(i);
  }

  // For each A[i], find maximum area that includes itself
  int max_area = 0;
  for (int i = 0; i < A.size(); ++i) {
    // If tag1 is used, the next line should be:
    // int tmp_area = A[i] * (R[i] - L[i]);
    int tmp_area = A[i] * (R[i] - L[i] - 1);
    if (tmpArea > max_area) 
      max_area = tmp_area;
  }

  return max_area;
}

