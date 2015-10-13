// Merge two 2-D images.
// http://www.mitbbs.com/article_t/JobHunting/32582727.html

#include <iostream>

using namespace std;

// Tree node data structure.
struct TreeNode {
    TreeNode* upperLeft;
    TreeNode* downLeft;
    TreeNode* upperRight;
    TreeNode* downRight;
    int size;
    bool pixel;

    TreeNode(bool p, int s) : pixel(p), size(s),
                              upperLeft(NULL), downLeft(NULL), upperRight(NULL), downRight(NULL) {
    }
};

// Copy
TreeNode* copy(TreeNode* root) {
   if (!root) {
      return NULL;
   }

   TreeNode* r   = new TreeNode(root->pixel, root->size);
   r->upperLeft  = copy(root->upperLeft);
   r->upperRight = copy(root->upperRight);
   r->downLeft   = copy(root->downLeft);
   r->downRight  = copy(root->downRight);
   return r;
}

// Count all the black pixels of this image
int getBlackPixels(TreeNode* root) {
   if (!root) {
      return 0;
   }

   if (!root->upperLeft) { // leaf node
      if (root->pixel) {   // Color is black.
         return root->size * root->size;
      }
      return 0;
   }

   int sum = 0;
   sum += getBlackPixels(root->upperLeft);
   sum += getBlackPixels(root->downLeft);
   sum += getBlackPixels(root->upperRight);
   sum += getBlackPixels(root->downRight);
   return sum;
}

// Merge two images OF SAME SIZE.
// Since all pixels are boolean, we do "AND" operation on these two images.
TreeNode* merge( const TreeNode* image1, const TreeNode* image2) {
   if (!image1->upperLeft && !image2->upperLeft) { // Both are leaf nodes
      return new TreeNode(image1->pixel && image2->pixel, image1->size);
   }

   if (!image1->upperLeft) { // image1 is leaf node, call helper.
      return mergeHelper(image1, image2);
   }

   if (!image2->upperLeft) { // image2 is leaf node, call helper.
      return mergeHelper(image2, image1);
   }

   // Neither image1 nor image2 is leaf node, recursive call.
   TreeNode* root = new TreeNode(image1->pixel, image1->size);
   root->upperLeft  = merge(image1->upperLeft, image2->upperLeft);
   root->upperRight = merge(image1->upperRight, image2->upperRight);
   root->downLeft   = merge(image1->downLeft, image2->downLeft);
   root->downRight  = merge(image1->downRight, image2->downRight);
   return root;
}

// Helper: image1 is leaf (only one color), but image2 is not a leaf.
TreeNode* mergeHelper( TreeNode* image1, TreeNode* image2) {
   if (!image1->pixel) { // image1 is all white, so the result is all white too.
      return new TreeNode(image1->pixel, image1->size);
   }

   // image1 is all black, so the merged image is identical to image2.
   return copy(image2);
}
