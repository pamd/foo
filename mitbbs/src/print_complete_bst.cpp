// Given a complete binary search tree in form of array, write a
// functionto sort the given array in O(n) time.
// http://www.mitbbs.com/article_t/JobHunting/32702215.html
// (dhu: The original solution has bug! Don't even waste time on it!)

#include <iostream>

using namespace std;

int get_next(int A[], int N, int idx, int next_leaf_idx) {
   if (idx >= N / 2) { // A[idx] is a leaf node on complete binary tree
      if (idx % 2) { // A[idx] is a left leaf node.
         return idx / 2;
      }
      // Otherwise, A[idx] must be a right leaf node.
      int leaf_counter = idx - N / 2 + 1;
      int rightmost_set_bit_mask = leaf_counter & (~(leaf_counter - 1));
      return (idx + 1) / (rightmost_set_bit_mask * 2)  - 1;
   }
   // Otherwise, A[idx] must be a non-leaf node.
   return next_leaf_idx;
}

// Print out elements in in-order traversal
void in_order_print(int A[], int N) {
   int current = N / 2;
   int next_leaf_index = current + 1;
   cout << A[current] << " ";
   for (int i = 1; i < N; ++i) {
      int next = get_next(A, N, current, next_leaf_index);
      cout << A[next] << " ";
      if (next >= N / 2) {
         ++next_leaf_index;
      }
      current = next;
   }
   cout << endl;
}

// Recursive solution is much easier:
void in_order_recur(int A[], int N, int idx) {
   if (idx >= N / 2) {
      cout << A[idx] << " ";
      return;
   }

   in_order_recur(A, N, 2 * idx + 1);
   cout << A[idx] << " ";
   in_order_recur(A, N, 2 * idx + 2);
}

// Test harness
int main() {
   int A[] = { 100,
               50, 150,
               25, 75, 125, 200,
               12, 37, 62, 83, 112, 137, 187, 212,
               10, 14, 35, 39,  60,  64,  81,  85, 110, 114, 135, 139, 185, 189, 210, 214
   };

   int N = sizeof(A) / sizeof(int);
   in_order_print(A, N);

   return 0;
}
