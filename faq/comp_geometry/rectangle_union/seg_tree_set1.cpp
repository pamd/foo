// Segment tree set 1: Sum of given range
// http://www.geeksforgeeks.org/segment-tree-set-1-sum-of-given-range/
// Code has been revised to make it more readable.

#include <stdio.h>
#include <math.h>

// Return the middle index based on starting and ending indexes.
int get_mid(int start, int end) {
   return start + (end - start) / 2;
}

// Recursive function to get the sum of values in given range of the array.
int get_sum_recur(int* seg_tree, int arr_idx_start, int arr_idx_end,
                  int query_start, int query_end, int st_idx)
{
   // If the range of query covers the range of seg_tree[st_idx],
   // return the sum of this segment.
   if (query_start <= arr_idx_start && query_end >= arr_idx_end) {
      return seg_tree[st_idx];
   }

   // If there is no any overlap between query range and the current node's range, return 0.
   if (arr_idx_end < query_start || arr_idx_start > query_end) {
      return 0;
   }

   // If the query's range partially overlaps with the node's range,
   // find the overlap recursively.
    int mid_idx = get_mid(arr_idx_start, arr_idx_end);
    return get_sum_recur(seg_tree, arr_idx_start, mid_idx,     query_start, query_end, 2 * st_idx + 1) +
           get_sum_recur(seg_tree, mid_idx + 1,   arr_idx_end, query_start, query_end, 2 * st_idx + 2);
}

// Return sum of elements in range from index qs (quey start) to
// qe (query end).  It mainly uses getSumUtil()
int get_sum(int* seg_tree, int arr_len, int query_start, int query_end) {
   // Check for erroneous input values
   if (query_start < 0 || query_end > arr_len - 1 || query_start > query_end) {
      printf("Invalid Input");
      return -1;
   }

   return get_sum_recur(seg_tree, 0, arr_len - 1, query_start, query_end, 0);
}

// Recursive function to update the nodes which have the given index in their range.
// arr_idx: index of the array element that is to be updated.
// diff:    Value to be added to all nodes which have arr_idx in range
void update_recur(int* seg_tree, int arr_idx_start, int arr_idx_end, int arr_idx, int diff, int st_idx)
{
    // Base Case: If the input index lies outside the range of this segment
   if (arr_idx < arr_idx_start || arr_idx > arr_idx_end) {
      return;
   }

   // If the input index is in range of this node, update the value
   // of the node and its children.
   seg_tree[st_idx] = seg_tree[st_idx] + diff;

   // If arr_idx_start == arr_idx_end, then seg_tree[st_idx] must be a leaf node, so we are done;
   // Otherwise, seg_tree[st_idx] must be an internal node, so we need to update its two children.
   if (arr_idx_end != arr_idx_start) {
      int mid_idx = get_mid(arr_idx_start, arr_idx_end);
      update_recur(seg_tree, arr_idx_start, mid_idx,     arr_idx, diff, 2 * st_idx + 1);
      update_recur(seg_tree, mid_idx + 1,   arr_idx_end, arr_idx, diff, 2 * st_idx + 2);
   }
}

// Update a value in input array and segment tree.
// It calls update_recur() to update the value in segment tree.
void update(int arr[], int* seg_tree, int arr_len, int arr_idx, int new_val)
{
    // Check for erroneous input index
    if (arr_idx < 0 || arr_idx > arr_len - 1) {
       printf("Invalid Input");
       return;
    }

    // Get the difference between new value and old value
    int diff = new_val - arr[arr_idx];

    // Update the value in array
    arr[arr_idx] = new_val;

    // Update the values of nodes in segment tree
    update_recur(seg_tree, 0, arr_len - 1, arr_idx, diff, 0);
}

// A recursive function that constructs Segment Tree for array[start_idx : end_idx].
// si is index of current node in segment tree st
int construct_recur(int arr[], int arr_idx_start, int arr_idx_end, int* seg_tree, int st_idx)
{
   // If there is only one element in input array's index range,
   // store it in current node of segment tree and return.
   if (arr_idx_start == arr_idx_end) {
      seg_tree[st_idx] = arr[arr_idx_start];
      return arr[arr_idx_start];
   }

   // If there are more than one element, recur for left and
   // right subtrees, then store the sum of values in this node.
   int mid_idx = get_mid(arr_idx_start, arr_idx_end);
   seg_tree[st_idx] = construct_recur(arr, arr_idx_start, mid_idx,     seg_tree, 2 * st_idx + 1) +
                      construct_recur(arr, mid_idx + 1,   arr_idx_end, seg_tree, 2 * st_idx + 2);
   return seg_tree[st_idx];
}

// Construct segment tree from the input array.
// This function allocates memory for segment tree and calls
// construct_recur() to fill the allocated memory.
int* construct(int arr[], int n)
{
    // Allocate memory for segment tree
    int x = (int) (ceil(log2(n)));          // Height of segment tree
    int max_size = 2 * (int) pow(2, x) - 1; // Maximum # of nodes in segment tree
    int* seg_tree = new int[max_size];

    // Fill the allocated memory
    construct_recur(arr, 0, n - 1, seg_tree, 0);

    // Return the constructed segment tree
    return seg_tree;
}

// Driver program to test above functions
int main()
{
    int arr[] = { 1, 3, 5, 7, 9, 11 };
    int n = sizeof(arr) / sizeof(arr[0]);

    // Build segment tree from given array
    int* seg_tree = construct(arr, n);

    // Print sum of values in array from index 1 to 3
    printf("Sum of values in given range = %d\n", get_sum(seg_tree, n, 1, 3));

    // Update: set arr[1] = 10 and update corresponding segment tree nodes.
    update(arr, seg_tree, n, 1, 10);

    // Find sum after the value is updated.
    printf("Updated sum of values in given range = %d\n", get_sum(seg_tree, n, 1, 3));

    return 0;
}


// Output:
// Sum of values in given range = 15
// Updated sum of values in given range = 22

