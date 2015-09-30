// http://www.mitbbs.com/article_t/JobHunting/32695977.html
// Given a binary tree where all the right nodes are either empty or leaf nodes, flip it upside down
// and turn it into a tree with left leaf nodes. In the original tree, if a node has a right child,
// it also must have a left child.
//
//         1             1
//   	  / \          	/ \
//       2   3         2   3
//      /
//     4
//    / \
//   5   6
//
// Will be translated into:
//
//    	      1             1
//   	     /             /
//          2---3   	  2---3
//         /
//        4
//       /
//      5---6
// 
// Finally:
//
//       5                   2
//      / \                 / \
//     6   4               3   1 
//          \ 
//           2
//          / \
//         3   1
//
// 我的解法： follow the left node all the way to the leftmost node, and transform each left node on the way.
// 
// longway2008: recursive solution
TreeNode* convert(TreeNode * root) {
    if (!root || !root->left) {
   	    return root;
    }
  	TreeNode * left = root->left;
	  TreeNode * newRoot = convert(left);
	  left->right = root;
	  left->left = root->right;
	  root->left = root->right = NULL;

  	return newRoot;
}

// awbeer: an iterative version:
TreeNode* transform(TreeNode *root){
    if(root == nullptr) {
      return nullptr;
    }

    TreeNode *parent = nullptr;
    TreeNode *cur = root;
    TreeNode *b1 = nullptr;
    TreeNode *b2 = nullptr;
    while (cur) {
        // save the left and right child info before wiping them out.
        TreeNode *a = cur->left;
         b2 = cur->right;

         cur->left = b1;
         cur->right = parent;

         // move to the next step
         b1 = b2;
         parent = cur;
         cur = a;
    }
    return parent;
}

