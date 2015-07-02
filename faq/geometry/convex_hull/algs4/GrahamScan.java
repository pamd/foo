/*************************************************************************
 *  Compilation:  javac GrahamaScan.java
 *  Execution:    java GrahamScan < input.txt
 *  Dependencies: Point2D.java
 * 
 *  Create points from standard input and compute the convex hull using
 *  Graham scan algorithm.
 *
 *  May be floating-point issues if x and y coordinates are not integers.
 *
 *************************************************************************/

// dhu: code copied from:
// http://algs4.cs.princeton.edu/99hull/GrahamScan.java.html

import java.util.Arrays;

public class GrahamScan {
    private Stack<Point2D> hull = new Stack<Point2D>();

    public GrahamScan(Point2D[] pts) {
        // defensive copy
        int N = pts.length;
        Point2D[] points = new Point2D[N];
        for (int i = 0; i < N; i++)
            points[i] = pts[i];

        // Preprocess so that points[0] has lowest y-coordinate; break ties by 
	// x-coordinate. points[0] must be an extreme point of the convex hull
        // (alternatively, could do easily in linear time).
        Arrays.sort(points);

        // Sort by polar angle with respect to base point points[0],
        // breaking ties by distance to points[0]
        Arrays.sort(points, 1, N, points[0].POLAR_ORDER);

        hull.push(points[0]);       // p[0] is the first extreme point

        // find index k1 of first point not equal to points[0]
        int k1;
        for (k1 = 1; k1 < N; k1++) {
            if (!points[0].equals(points[k1])) 
		break;
	}
        if (k1 == N) 
	    return;        // all points equal

        // Find index k2 where points[k2] is the first point 
	// that does NOT collinear with points[0] and points[k1].
        int k2;
        for (k2 = k1 + 1; k2 < N; k2++) {
            if (Point2D.ccw(points[0], points[k1], points[k2]) != 0) 
		break;
	}
        hull.push(points[k2 - 1]);    // points[k2-1] is the second extreme point

        // Graham scan; note that points[N-1] is extreme point different from points[0].
	// dhu bug report: If points[0], points[N-1] and points[N-2] are collinear,
	// the following code may put all these three points into the hull.
	// See dhu_test.txt input file.
        for (int i = k2; i < N; i++) {
            Point2D top = hull.pop();
	    // dhu: because points[] have been sorted, hull[0], top and points[i]
	    // will always form valid convex hull, so hull[0] will never be popped 
	    // out, in another word, hull[] will never be empty, so hull.peek()
	    // will always return a valid point. 
            while (Point2D.ccw(hull.peek(), top, points[i]) <= 0) {
                top = hull.pop();
            }
            hull.push(top);
            hull.push(points[i]);
        }

        assert isConvex();
    }

    // return extreme points on convex hull in counterclockwise order as an Iterable
    public Iterable<Point2D> hull() {
        Stack<Point2D> s = new Stack<Point2D>();
        for (Point2D p : hull) 
	    s.push(p);

        return s;
    }

    // check that boundary of hull is strictly convex
    private boolean isConvex() {
        int N = hull.size();
        if (N <= 2) 
	    return true;

        Point2D[] points = new Point2D[N];
        int n = 0;
        for (Point2D p : hull()) {
            points[n++] = p;
        }

        for (int i = 0; i < N; i++) {
            if (Point2D.ccw(points[i], points[(i+1) % N], points[(i+2) % N]) <= 0) {
                return false;
            }
        }
        return true;
    }

    // test client
    public static void main(String[] args) {
        int N = StdIn.readInt();
        Point2D[] points = new Point2D[N];
        for (int i = 0; i < N; i++) {
            int x = StdIn.readInt();
            int y = StdIn.readInt();
            points[i] = new Point2D(x, y);
        }
        GrahamScan graham = new GrahamScan(points);
        for (Point2D p : graham.hull())
            StdOut.println(p);
    }

}
