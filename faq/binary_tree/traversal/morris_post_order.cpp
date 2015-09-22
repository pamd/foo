// Based on soul machine leetcode solution.
// Morris post-order, time O(n), space O(1)
//

vector<int> postorderTraversal(TreeNode *root) {
   vector<int> result;
   TreeNode dummy(-1);
   TreeNode* current;
   TreeNode* prev = NULL;

   std::function < void(const TreeNode*)> visit = [&result](const TreeNode *node) {
      result.push_back(node->val);
   }; // visit function

   dummy.left = root;
   current = &dummy;
   while (current) {
      if (!current->left) {
         prev = current; // required
         current = current->right;
      }
      else {
         TreeNode* tmp = current->left;
         while (tmp->right && tmp->right != current) {
            tmp = tmp->right;
         }
         if (tmp->right == NULL) { // Thread is not built yet, so we build it now.
            tmp->right = current;
            prev = current; // required
            current = current->left;
         }
         else { // Thread is found, so we visit the nodes, then delete the thread.
            visit_reverse(current->left, prev, visit);
            // Because we always visit nodes from current->left to prev, "dummy" will never be visited.
            
            prev->right = 0;
            prev = current; // required
            current = current->right;
         }
      }
   }

   return result;
}

// Visit all nodes on reversed path
void visit_reverse(TreeNode* from, TreeNode* to, std::function< void(const TreeNode*) >& visit) {
   TreeNode* p = to;
   reverse(from, to); // Reverse
   while (true) {
      visit(p);
      if (p == from) {
         break;
      }
      p = p->right;
   }

   reverse(to, from); // Reverse back
}

// Reverse path. "to" is the rightmost node on the subtree rooted at "from".
// This function reverses the parent and right child relationship from "from" to "to".
// Here is an example: (Nodes x and y are not affected.)
//
//       x
//      /
//     A                       C
//    / \                       \
//   y   B         ===>          B   x
//        \                       \ /
//         C                       A
//                                /
//                               y
//
// The reverse algorithm is similar to the idea of reversing a singly linked list.
void reverse(TreeNode* from, TreeNode* to) {
   TreeNode* x = from;
   TreeNode* y = from->right;
   TreeNode* z;

   while (x != to) {
      z = y->right;
      y->right = x;
      x = y;
      y = z;
   }
}
