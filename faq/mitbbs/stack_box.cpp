/* Dynamic Programming:
 * A packer of boxes in a Target warehouse is packing small radios into larger 
 * boxes that measure 25 in. by 43 in. by 62 in. If the measurement of each 
 * radio is 7 in. by 6 in. by 5 in., then at most how many radios can be placed
 * in the box?
 * Reference: 
 * http://www.mitbbs.com/article_t/JobHunting/31965415.html
 * (Variable and function names are modified to more user-friendly symbols.)
 */

#include <iostream>
#include <algorithm>

using namespace std;

int stack(int, int, int);
int put_in(int, int, int);

// Dimentions of the big box
const int Width = 25;
const int Height = 43;
const int Depth = 62;

// Dimentions of radio
const int rw = 5;
const int rh = 6;
const int rd = 7;

int dp[Width + 1][Height + 1][Depth + 1];

int max(int v1, int v2) {
  if (v1 > v2)
    return v1;
  return v2;
}

int solve() {
  for (int i = 0; i <= Width; i++)
    for (int j = 0; j <= Height; j++)
      for (int k = 0; k <= Depth; k++)
	dp[i][j][k] = -1;
  dp[rw][rh][rd] = 1;
  return stack(Width, Height, Depth);
}

// stack() calls put_in() multiple times.
// s1, s2 and s3 are sizes of the box.
int stack(int s1, int s2, int s3) {
  int sorted[] = { s1, s2, s3 };
  sort(sorted, sorted + 3);
  s1 = sorted[0];
  s2 = sorted[1];
  s3 = sorted[2];
  if (dp[s1][s2][s3] >= 0) 
    return dp[s1][s2][s3];

  int ret = 0;
  ret = max(ret, put_in(s1, s2, s3));
  ret = max(ret, put_in(s1, s3, s2));
  
  ret = max(ret, put_in(s2, s1, s3));
  ret = max(ret, put_in(s2, s3, s1));

  ret = max(ret, put_in(s3, s1, s2));
  ret = max(ret, put_in(s3, s2, s1));

  dp[s1][s2][s3] = ret;

  return ret;
}

// put_in() calls stack() too
int put_in(int s1, int s2, int s3) {
  if (s1 < rw || s2 < rh || s3 < rd) 
    return 0;

  /* stack((s1 - rw, s2, s3) calculates the maximum number of radios that 
   * can be put into the space (s1-rw) x (s2) x (s3). Suppose we put the radio 
   * at the upper left corner, (s1-rw) x (s2) x (s3) will be the space on the 
   * right side of the box. 
   *
   *
   *       _________________________________________________
   *      |      |rd                                        |
   *      |______|                                          |
   *      |  rw  |       (s1-rw) x (s2) x (s3)              |
   *      |      |                                          | 
   *      |      |                                          |
   *      |______|__________________________________________|
   */
  int ret = 1 + stack(s1 - rw, s2, s3);

  /* There are two approaches to stack radios into the space on the left side:
   * (1) Stack more radios on top of the first one, then stack radios from 
   *     very bottom for space beneath the first radio.
   * (2) Stack the radio on the bottom first, then stack upwards.
   */
  ret += max(stack(rw, s2 - rh, rd) + stack(rw, s2, s3 - rd), 
	     stack(rw, rh, s3 - rd) + stack(rw, s2 - rh, s3));
  return ret;
}
// dhu: what if the optimal packing is to cover the bottom first, then 
// packs all the way up to the top? Is this arrangement already included
// in various arrangements in stack() function? 
// (Maybe I am thinking too much about this solution?)

int main() 
{
  cout << solve() << endl;

}


