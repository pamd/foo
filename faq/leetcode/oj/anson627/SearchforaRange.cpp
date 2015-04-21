//============================================================================
// Search for a Range
// Given a sorted array of integers, find the starting and ending position of
// a given target value.
//
// Your algorithm's runtime complexity must be in the order of O(log n).
//
// If the target is not found in the array, return [-1, -1].
//
// For example,
// Given [5, 7, 7, 8, 8, 10] and target value 8,
// return [3, 4].
//============================================================================

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        int l = lower_bound(A, A + n, target) - A;
        int u = upper_bound(A, A + n, target) - A - 1;
        vector<int> res(2, -1);
        if (l > u) return res;
        res[0] = l;
        res[1] = u;
        return res;
    }
};

int main() {
	return 0;
}
