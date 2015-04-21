/* http://acm.zju.edu.cn/onlinejudge/showProblem.do?problemCode=2107
 * Code by songlj, terrible coding style, and the algorithm is totally WRONG!
 * 
 * 
 */

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string>
#include <algorithm>

using namespace std;

const int maxn = 100005;
const double eps = 1e-8;

struct Point {
  double x, y, dis;

  Point() { }

  Point(double vx, double vy) {
    x = vx;
    y = vy;
    dis = sqrt(x * x + y * y);
  }
};

// Global variables
int n;
Point p[maxn];

// Comparison function, used by std::sort()
bool cmpp(const Point &p1,const Point &p2) {
  return p1.dis < p2.dis;
}

// Solve the problem
void solve() {
  sort(p, p + n, cmpp);
  double ans = 1e18;
  double now;
  int i, j;
  for (i = 0; i < n - 1; i++) {
    for ( j = i + 1; j < n; j++) {
      if (p[j].dis - p[i].dis > ans - eps) 
	break; //这里会减枝很多
      now = sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y)) / 2;
      if (now + eps < ans) 
	ans = now;
    }
  }
  printf("%.2lf\n", ans);
}


int main()
{
  /* Original code that reads n and coordinatwes from std input
  while (cin>>n&&n) {
    memset(p,0,sizeof(p));
    for (int i=0;i<n;i++) {
      scanf("%lf %lf",&p[i].x,&p[i].y);
      p[i].dis=sqrt(p[i].x*p[i].x+p[i].y*p[i].y);
    }
    solve();
  }
  */

  // Test case #1 in original URL
  /*
  n = 2;
  p[0] = Point(0, 0);
  p[1] = Point(1, 1);
  */

  n = 3;
  p[0] = Point(0, 0);
  p[1] = Point(0, 10);
  p[2] = Point(0, 100);
  solve();

  return 0;
}

