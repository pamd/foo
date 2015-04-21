/* This program calculates the number of ways to select m 
 * objects out of n choices, aka, C(n, m).
 * Instead of using the formula C(n,m) = n!/(m!*(n - m)!),
 * We use the following recursive equation:
 * C(n, m) = C(n - 1, m) + C(n - 1, m - 1)
 */

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <vector>

using namespace std;

vector<vector<double> > tab;

void initTab(size_t n, size_t m)
{
  for (size_t i = 0; i <= n; i++) {
    tab.push_back(vector<double>(m + 1));
    for (size_t j = 0; j <= m; j++)
      tab[i][j] = 0;

    tab[i][1] = i;
    if (i <= m)
      tab[i][i] = 1;
  }
}

double combnt(size_t n, size_t m) 
{
  assert(n >= m);
  if (m > n / 2)
    return combnt(n, n - m);

  if (tab[n][m])
    return tab[n][m];

  double ret = combnt(n - 1, m - 1) + combnt(n - 1, m);
  if (ret <= combnt(n - 1, m - 1) || ret <= combnt(n - 1, m)) {
    cout << combnt(n - 1, m - 1) << " " << combnt(n - 1, m) << endl;
    cout << "Overflow at n = " << n << ", m = " << m << endl;
    exit(1);
  }

  tab[n][m] = ret;

  return ret;
}

int main() 
{
  size_t n = 6000;
  size_t m = 200;

  initTab(n, m);
  cout << combnt(n, m) << endl;

}
