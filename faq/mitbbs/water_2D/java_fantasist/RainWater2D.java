/* Java code that solves 2D versionm of water trap.
 * Copied from:
 * https://github.com/fantasist/InterviewProblems/blob/master/InterviewProblems/src/fantasist/InterviewProblems/other
 */

//package fantasist.InterviewProblems.other;

import java.util.PriorityQueue;

public class RainWater2D {

    private final int[][] directions = {
	{1, 0}, {0, 1}, {-1, 0}, {0, -1}
    };
	
    private int width, height;
	
    private class Point implements Comparable<Point> {
	public int x, y, h;
	public Point(int y, int x, int h) {
	    this.y = y;
	    this.x = x;
	    this.h = h;
	}

	@Override
	    public int compareTo(Point p) {
	    return h > p.h ? 1 : -1;
	}
    }
	
    private boolean isValid(int y, int x) {
	if (y < 0 || x < 0 || y >= height || x >= width)
	    return false;
	return true;
    }
	
    public int preserveWater(int[][] A) {
	if (A == null || A.length < 3 || A[0].length < 3)
	    return 0;
	height = A.length;
	width = A[0].length;
	boolean[][] visited = new boolean[height][width];
	int water = 0;
	PriorityQueue<Point> heap = new PriorityQueue<Point>();
	for (int i = 0; i < width; i++) {
	    heap.add(new Point(0, i, A[0][i]));
	    visited[0][i] = true;
	    heap.add(new Point(height - 1, i, A[height - 1][i]));
	    visited[height - 1][i] = true;
	}
	for (int i = 1; i < height - 1; i++) {
	    heap.add(new Point(i, 0, A[i][0]));
	    visited[i][0] = true;
	    heap.add(new Point(i, width - 1, A[i][width - 1]));
	    visited[i][width - 1] = true;
	}
	while (!heap.isEmpty()) {
	    Point p = heap.poll();
	    for (int i = 0; i < 4; i++) {
		int ny = p.y + directions[i][0];
		int nx = p.x + directions[i][1];
		if (isValid(ny, nx) && !visited[ny][nx]) {
		    if (A[ny][nx] < p.h) {
			water = p.h - A[ny][nx] + water;
			heap.add(new Point(ny, nx, p.h));
		    } else
			heap.add(new Point(ny, nx, A[ny][nx]));
		    visited[ny][nx] = true;
		}
	    }
	}
		
	return water;
    }
	
    public static void main(String[] args) {
	int[][] A = {
	    {5, 5, 5, 5},
	    {5, 3, 2, 5},
	    {5, 4, 4, 5},
	    {5, 1, 5, 5}
	};
	RainWater2D r = new RainWater2D();
	System.out.println(r.preserveWater(A));
    }

}
