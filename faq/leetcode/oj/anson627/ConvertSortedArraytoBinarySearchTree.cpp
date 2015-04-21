//============================================================================
// Convert Sorted Array to Binary Search Tree
//
// Given an array where elements are sorted in ascending order, convert it to
// a height balanced BST.
//
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

/**
 * Definition for binary tree
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode *sortedArrayToBST(vector<int> &num) {
        return sortedArrayToBSTHelper(num, 0, num.size() - 1);
    }

    // pre-order construct tree, takes O(n) time
    TreeNode* sortedArrayToBSTHelper(vector<int> &num, int start, int end) {
        if (start > end) return NULL;
        int mid = start + (end - start) / 2;
        TreeNode* node = new TreeNode(num[mid]);
        node->left = sortedArrayToBSTHelper(num, start, mid - 1);
        node->right = sortedArrayToBSTHelper(num, mid + 1, end);
        return node;
    };

};

int main() {
    return 0;
}
