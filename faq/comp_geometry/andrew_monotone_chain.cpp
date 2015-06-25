/***************************************************************************************************
 * https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
 *
 * Pseudocode:
 * ------------
 * Input: a list P of points in the plane.
 *
 *    Sort the points of P by x-coordinate (in case of a tie, sort by y-coordinate);
 *
 *    Initialize U and L as empty lists, which will hold the vertices of upper and lower hulls
 *    respectively;
 *
 *    // Find lower hull:
 *    for (i = 1, 2, ..., n)
 *    {
 *        while (L contains at least two points and the sequence of last two points of L
 *               AND the point P[i] does not make a COUNTER_CLOCKWISE turn)
 *        {
 *           remove the last point from L;
 *        }
 *        append P[i] to L;
 *    }
 *
 *    // Find upper hull:
 *    for (i = n, n-1, ..., 1)
 *    {
 *        while (U contains at least two points and the sequence of last two points of U
 *               AND the point P[i] does not make a COUNTER_CLOCKWISE turn)
 *        {
 *            remove the last point from U;
 *        }
 *        append P[i] to U;
 *    }
 *
 *    Remove the last point of each list (it's the same as the first point of the other list);
 *    Concatenate L and U to obtain the convex hull of P;
 *    Points in the result will be listed in counter-clockwise order.
 *
 ***************************************************************************************************/

// When two points have identical X coordinates, it doesn't really matter how to break the tie.
// We can rank either the point whose Y coordinate is larger before the other point, or vice versa,
// we just need to have a consistent tie breaking mechanism.
//
// To get the upper hull, we can either:
//    scan the points from left to right and use clockwise turn,
// or:
//    scan the points from right to left and use counter clockwise turn;
//
// Similarly, to get the lower hull, we can either:
//    scan the points from left to right and use counter clockwise turn;
// or:
//    scan the points from right to left and use clockwise turn;
//
// C++ Implementation of Andrew's monotone chain 2D convex hull algorithm.
// Asymptotic complexity: O(n * log n).
// Practical performance: 0.5 ~ 1.0 seconds for n = 1000000 on a 1GHz machine.

#include <vector>
#include <algorithm>

using namespace std;

// To simplify the problem, we assume each point's X and Y coordinates are integers.
struct Point {
   int x, y;

   bool operator<(const Point& p) const {
      return (x < p.x || (x == p.x && y < p.y));
   }
};

// Suppose O is the origin, we calculate 2-D cross product of OA and OB vectors,
// i.e. z-component of their 3-D cross product.
// If return value is positive, OAB must be making a counter-clockwise turn;
// If return value is negative, OAB must be making a clockwise turn;
// If return value is zero,     OAB must be collinear.
double cross(const Point& Origin, const Point& A, const Point& B)
{
   return (long)(A.x - Origin.x) * (B.y - Origin.y) - (long)(A.y - O.y) * (B.x - Origin.x);
}

// Returns a list of points on the convex hull in counter-clockwise order.
// Note: the last point in the returned list is the same as the first one.
vector<Point> convex_hull(const vector<Point>& P)
{
   int n = P.size();
   int k = 0;
   vector<Point> H(2 * n);

   // Sort points in X direction.
   sort(P.begin(), P.end());

   // Build lower hull: scan form left to right and take counter clockwise turn.
   for (int i = 0; i < n; ++i) {
      while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) {
         k--;
      }
      H[k++] = P[i];
   }

   // Build upper hull: P[n - 1] is already in H, so we start from P[n - 2],
   // then scan from right to left, and take counter clockwise turn.
   int t = k + 1;
   for (int i = n - 2; i >= 0; i--) {
      while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0) {
         k--;
      }
      H[k++] = P[i];
   }

   H.resize(k);

   return H;
}
