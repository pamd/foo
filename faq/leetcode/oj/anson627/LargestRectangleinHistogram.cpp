//============================================================================
// Given n non-negative integers representing the histogram's bar height where
// the width of each bar is 1, find the area of largest rectangle in the
// histogram.
//
// For example,
// Given height = [2,1,5,6,2,3],
// return 10.
//============================================================================

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
    	int n = height.size();
    	int y[n];
    	stack<int> stk;
    	for (int i = 0; i < n; i++) {
    		while (!stk.empty()) {
    			if (height[i] <= height[stk.top()]) stk.pop();
    			else break;
    		}
    		int j = (stk.empty()) ? -1 : stk.top();
    		// Calculating number of bars on the left
    		y[i] = i - j - 1;
    		stk.push(i);
    	}

    	while (!stk.empty()) stk.pop();

    	for (int i = n - 1; i > 0; i--) {
    		while (!stk.empty()) {
    			if (height[i] <= height[stk.top()]) stk.pop();
    			else break;
    		}
    		int j = (stk.empty()) ? n : stk.top();
    		// Calculating number of bars on the left + right
    		y[i] += (j - i - 1);
    		stk.push(i);
    	}

    	int res = 0;
    	for (int i = 0; i < n; i++) {
    		// Calculating height * width
    		y[i] = height[i] * (y[i] + 1);
    		if (y[i] > res) res = y[i];
    	}
    	return res;
    }
};

int main() {
	return 0;
}
