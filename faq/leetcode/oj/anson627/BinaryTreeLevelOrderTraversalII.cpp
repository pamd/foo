//============================================================================
// Binary Tree Level Order Traversal II
// Given a binary tree, return the bottom-up level order traversal of its
// nodes' values. (ie, from left to right, level by level from leaf to root).
//
// For example:
// Given binary tree {3,9,20,#,#,15,7},
//    3
//   / \
//  9  20
//    /  \
//   15   7
// return its bottom-up level order traversal as:
// [
//   [15,7]
//   [9,20],
//   [3],
// ]
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
    vector<vector<int> > levelOrderBottom(TreeNode *root) {
        vector<vector<int> > res;
        vector<int> row;
        for (int level = maxHeight(root); level >= 1; level--) {
            row.clear();
            levelOrderBottomHelper(root, level, row);
            res.push_back(row);
        }
        return res;

    }

    int maxHeight(TreeNode *node) {
        if(NULL == node) return 0;
        return 1 + max(maxHeight(node->left), maxHeight(node->right));
    };

    void levelOrderBottomHelper(TreeNode *node, int level, vector<int> &row) {
        if (level == 0 || node == NULL) return;
        if (level == 1) {
            row.push_back(node->val);
            return;
        }
        levelOrderBottomHelper(node->left, level-1, row);
        levelOrderBottomHelper(node->right, level-1, row);
    }
};

int main() {
    return 0;
}
