
/* 293. InterviewStreet: Vertical Sticks
 * http://www.mitbbs.com/article_t/JobHunting/32011987.html
 * https://gist.github.com/1565740
 * Given array of integers Y=y1,...,yn, we have n line segments such that endpoints of 
 * segment i are (i, 0) and (i, yi). Imagine that from the top of each segment a 
 * horizontal ray is shot to the left, and this ray stops when it touches another 
 * segment or it hits the y-axis. We construct an array of n integers, v1, ..., 
 * vn, where vi is equal to length of ray shot from the top of segment i. 
 * We define V(y1, ..., yn) = v1 + ... + vn.
 * For example, if we have Y=[3,2,5,3,3,4,1,2], then v1, ..., v8 = [1,1,3,1,1,3,1,2],
 * as shown in the picture below:
 * For each permutation p of [1,...,n], we can calculate V(yp1, ..., ypn). 
 * If we choose a uniformly random permutation p of [1,..., n], what is the expected 
 * value of V(yp1, ..., ypn)?
 */

// Solutions by viisa:
/* Calculate expected value for every position and sum up all.
 * Pos_1: expected value = 1.00
 * Pos_2: expected value = Sum of {if it is y_i, then (how many chance of length 1) * 1, 
 * (how many chance of length 2) * 2, how ...} / N
 * Ans = Sum {Pos_i | for all position i}. */

// D[i], input
double solve() {
  double ans = 1.0;
  for (int pos = 2; pos <= N; pos++) {
    double t1 = 0.0;
    for (int i = 0; i < N; i++) { // choose i in position pos
      int x = C[ i ][0]; // <  D[i]
      int y = C[ i ][1]; // >= D[i]
      
      double pre = 1.0;
      int k = 1;
      for (; k <= (pos - 1); k++) {
	double t2 = pre * ( (double)y / (double)(x + y) );
	t1 += (t2 * k);
	pre *= ( (double)x / (double) (x + y) );
	if (x-- == 0) 
	  break;
      }
      if (k == pos)
	t1 += (pre * pos);
    }
    ans += (t1 / N);
  }
  return ans;
}
