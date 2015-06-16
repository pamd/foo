/***************************************************************************************************
 *
 * Later in 1977, Jon Bentley considered this problem:
 *
 *     Given a collection of n rectangles, find the area of their union.
 *
 * He also obtained an algorithm whose time complexity is O(n * log n), now known
 * as "Bentley's algorithm", based on reducing the problem to n 1-dimensional problems.
 * This is done by sweeping a vertical line across the area. Using this method, the
 * area of the union can be computed without explicitly constructing the union itself.
 *
 * Bentley's algorithm is now also known to be optimal (in the 2-dimensional case),
 * and is used in computer graphics, among other areas.
 *
 * -------------------------------------------------------------------------------------------------
 *
 * Bentley's algorithm sweeps a vertical line from left to right across the rectangles,
 * maintaining the intersection of the rectangles and the sweep line (a collection of intervals)
 * in a segment tree. Whenever the sweep line hits a vertical edge of a rectangle, the segment
 * tree is updated, along with a running total of the swept area. Each update happens in O(log n)
 * time.

 * Perhaps the most important feature of Bentley's algorithm is: it computes the area without
 * explicitly constructing the union, which can easily have quadratic complexity.
 *
 * Bentley's sweepline strategy transforms a single d-dimensional measure problem into n
 * (d-1)-dimensional measure problems, so it immediately yields an algorithm whose running time
 * is O(n^2 * log n) when d=3. However, this algorithm does not exploit the "coherence" between
 * successive lower-dimensional problems.
 *
 * In 1985, Jan van Leeuwen and Derek Wood improved Bentley's algorithm by a logarithmic factor
 * using dynamic quadtrees, which allow a single 2-dimensional box to be inserted or deleted
 * in O(n) time.
 *
 **************************************************************************************************/
// dhu Explanation of Bentley's Algorithm
//-------------------------------------------------------------------------------------------------
// dhu: Segment node definition in Bentley's algorithm to calculate the rectangle union's area.
struct Segment
{
   int start;
   int end;
   unordered_set<size_t> interval_indexes;
   int contribution;
};

// In the comments below:
//  * "interval" is used to denote the input intervals (some of them may overlap);
//
//  * "segment" is used to denote the sections divided by the input intervals' starting and
//     ending points. Each node on the segment tree represents a certain segments.
//     NONE of the segments AT THE SAME LEVEL of the tree will overlap.
//
// start: starting position of the segment;
// end:   ending position of the segment;
//
// interval_indexes: the indexes of input rectangles whose range in Y direction completely covers
//                   the current node.
//                   Suppose the interval is [a, b], then a <= start <= end <= b, AND this node
//                   MUST be the node that is closetst to the root node.
//
//                   Here we use std::unordered_set instead of std::vector to so that this variable
//                   can be updated in O(1) time.

//
// contribution: Length that the current node contributes to the total merged length of all
//               ACTIVE rectangles on the tree.
//
//               (This value should be initialized to 0 at the beginning.)
//
//               Note that the contribution value should NOT include the intersection region more
//               than once. For example, if the segment on the current node is [0, 4], and we have
//               two active rectangles [0, 2] and [1, 3], then the contribution value of this node
//               should be 3 instead of 4, because [1, 2] shouldn't be double counted.
//               This value is not available in regular segment tree. This is why this tree is
//               called "AUGMENTED" semi-static segment tree.
//
// When (start == end), this segment actually denotes a starting or ending point.
//
// This kind of segment is actually not necessary to calculate the rectangle union's area. They are
// used in problems where the starting and ending points of input intervals should be distinguished
// from the points in the middle. For example, the input interval may be an open range (start, end),
// or half-open-half-close range (start, end] or [start, end).
//
// Suppose the total number of unique starting/ending points is x, these points divides (-inf, +inf)
// into (x+1) segments, so the total number of leaf nodes is (2 * x + 1), and the number of non-leaf
// nodes is (2 * x). So the total number of nodes in the segment tree is (4 * x + 1).
//
// If we do NOT include these x starting/ending points, then the number of leaf nodes is (x+1), the
// number of non-leaf nodes is x, so the total number of nodes in the segment tree is (2 * x + 1).
// So excluding these starting/ending points will make the algorithm faster, but will NOT affect the
// time complexity.
//
// -------------------------------------------------------------------------------------------------
//            Insert an input interval and update the augmented semi-static segment tree
//            (when we sweeps the left side of an input rectangle)
// -------------------------------------------------------------------------------------------------
// (1) Search the segment tree and find the node(s) whose segments are covered by the input interval
//     completely, then add this rectangle's index into interval_indexes of these nodes.
//
// (2) Denote one of the nodes that we find in step (1) as "curr_node", then:
//
             if (curr_node.contribution == curr_node.end - curr_node.start) {
                // The segment of on curr_node is already fully covered by other interval(s),
                // so we don't need to update curr_node.contribution; we are done with curr_node.
             }
//
//     Otherwise, curr_node.contribution must be less than (curr_node.end - curr_node.start),
//     so the contribution values of current node and its ancestors should be incremented:
//
             contribution_increment = curr_node.end - curr_node.start - curr_node.contribution;
//
//     The increment update should go up along the tree until either an ancestor node's contribution value
//     is equal to the length of segment, or we have passed the root node.
//
// -------------------------------------------------------------------------------------------------
//           Delete an input interval and update the augmented semi-static segment tree
//           (when we sweeps the right side of an input rectangle)
// -------------------------------------------------------------------------------------------------
// (1) Search the segment tree and find the nodes whose segments are covered by the input interval
//     completely, remove the rectangle's index from interval_indexes.
//
// (2) Denote one of the nodes that we find in step (1) as "curr_node", then:
//
             if (!curr_node.interval_indexes.empty()) {
                // current node's segment is still fully covered by some other interval(s),
                // so we don't need to update curr_node.contribution; we are done with curr_node.
             }
//
//     Otherwise, we need to check the contribution values of curr_node's left and right children,
//     if (left_child.contribution + right_child.contribution == curr_node.end - curr_node.start),
//     then we don't need to update curr_node.contribution either, we are done with curr_node.
//
//     if (left_child.contribution + right_child.contribution < curr_node.end - curr_node.start),
//     then the contribution values of curr_node and its ancestors should be decremented:
//
              contribution_decrement =
                (curr_node.end - curr_node.start) - (left_child.contribution + right_child.contribution);
//
//     The decrement update should go up the along the tree until an ancestor node's segment has been
//     fully covered by other interval(s), or we have passed the root node.
//
// Both insertion and deletion of a rectangle will take O(log n), so we can find the union of segments
// in Y direction in O(log n) time, and calculate the union of area when we sweep each rectangle's left
// and right edges along X direction.
